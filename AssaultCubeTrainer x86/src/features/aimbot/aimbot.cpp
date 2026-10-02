#include "aimbot.h"

#include "../../game/game.h"

/* Gets the viewangles of src to look at dst */
ViewAngles aimbot::get_angles(Vector3& src, Vector3& dst)
{
	ViewAngles angles;
	Vector3 delta = dst - src; /* makes the world relative to the src */
	float hypLen = sqrt((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));

	angles = ViewAngles();
	angles.pitch = asin(delta.z / hypLen) * 180 / PI;
	angles.yaw = (-atan2(delta.x, delta.y) * 180 / PI) + 180; /* +180 becase yaw in AC is 1-360 */

	return angles;
}



/* Gets the best target based on ditance */
Entity* aimbot::get_best_target()
{
	using namespace assault_game;

	EntityList* entityList = global::g_entity_list;
	Entity* localPlayer = global::g_local_player;
	Entity* closestEnt = nullptr;

	float tempDistanceFromPlayer = -1.0f;
	int maxPlayers = get_max_players();

	/* -1 because server counts lp as a player and lp isnt in the ent list */
	for (int index = 0; index < maxPlayers - 1; index++)
	{
		Entity* currentEnt = entityList->Entities[index];
		float distanceFromPlayer;

		if (!currentEnt || currentEnt->bIsDead)
			continue;

		distanceFromPlayer = localPlayer->vPosition.get3DDistance(currentEnt->vPosition);

		if (distanceFromPlayer < tempDistanceFromPlayer || !closestEnt) {
			tempDistanceFromPlayer = distanceFromPlayer;
			closestEnt = currentEnt;
		}
	}

	return closestEnt;
}



/* This gets executed in a loop to trigger aimbot logic */
void aimbot::execute()
{
	/* Checking to see if player is in a valid game */
	if (assault_game::get_entity_list() == nullptr)
		return;

	Entity* localPlayer = assault_game::global::g_local_player;
	Entity* target = get_best_target();

	if (target == nullptr || localPlayer == nullptr)
		return;

	ViewAngles enemy_angle = get_angles(localPlayer->vHeadPos, target->vHeadPos);

	if (menu::features::aimbot::b_smoothing)
	{
		ViewAngles delta = enemy_angle - localPlayer->vViewAngles; 

		while (delta.yaw > 180.f) delta.yaw -= 360.f;
		while (delta.yaw < -180.f) delta.yaw += 360.f;

		localPlayer->vViewAngles = localPlayer->vViewAngles + delta / menu::features::aimbot::f_smoothing;
	}
	else
	{
		localPlayer->vViewAngles = enemy_angle;
	}

}