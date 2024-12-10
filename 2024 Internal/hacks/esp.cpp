#include <Windows.h>
#include "esp.h"

bool worldToScreen(Vector3 pos, Vector3& screen, float* matrix, int windowWidth, int windowHeight)
{
	Vector4 clipCoords;

	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;	

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

	return true;
}



void ESP::DrawESPBox(Entity* e, Vector3& screen, GL::Font& font, const GLubyte* color)
{
	//const GLubyte* color = nullptr;

	/* check for team game (not implemented) */
	Entity* localPlayer = Engine::getLocalPlayer();

	//color = rgb::red;

	float dist = localPlayer->mPos.get3DDistance(e->mPos);

	float scale = (GAME_UNIT_MAGIC / dist) * (viewport[2] / VIRTUAL_SCREEN_WIDTH);
	float x = screen.x - scale;
	float y = screen.y - scale * PLAYER_ASPECT_RATIO;

	
	float width = scale * 2;
	float height = scale * PLAYER_ASPECT_RATIO * 2;

	GL::DrawOutline(x, y, width, height, 0.2f, color);

	float textX = font.centerText(x, width, strlen(e->mEntityName) * ESP_FONT_WIDTH);
	float textY = y - ESP_FONT_HEIGHT / 2;

	font.Print(textX, textY, color, "%s", e->mEntityName);

}



void ESP::Draw(GL::Font& font)
{
	glGetIntegerv(GL_VIEWPORT, viewport);
	

	for (int i = 0; i < Engine::getMaxPlayers() - 1; i++)
	{
		const GLubyte* color = rgb::red;
		Entity* e = Engine::getEntityList()->Entities[i];
		Vector3 center = e->mHeadPos;
		center.z = center.z - EYE_HEIGHT + PLAYER_HEIGHT / 2;

		if (e->mHealth < 1)
			color = rgb::gray;

		Vector3 screenCoords;

		if (worldToScreen(center, screenCoords, Engine::getViewMatrix(), viewport[2], viewport[3]))
		{
			DrawESPBox(e, screenCoords, font, color);
		}
	}

}