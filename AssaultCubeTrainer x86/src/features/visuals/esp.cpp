#include <Windows.h>

#include "esp.h"

#include "../../draw/gldraw.h"
#include "../../game/game.h"
#include "../../menu/menu.h"



/* Dis old code :) */

void esp::BeginESPDraw(HDC hDc)
{
	GL::Font glFont;
	const auto FONT_HEIGHT = 15;
	const auto FONT_WIDTH = 9;

	/* if the font isn't built, build it */
	if (!glFont.bBuilt || hDc != glFont.hdc)
		glFont.Build(FONT_HEIGHT);

	GL::SetUpOrtho();
	esp::draw_ents(glFont);
	GL::RestoreGL();
}



void esp::draw_ents(GL::Font& font)
{
	EntityList* entity_list = assault_game::get_entity_list();
	Entity* lp_entity = assault_game::get_local_player();

	if (!entity_list || !lp_entity)
		return;

	glGetIntegerv(GL_VIEWPORT, viewport);

	for (int i = 0; i < assault_game::get_max_players() - 1; i++) {
		Entity* e = entity_list->Entities[i];

		if (!e || e->bIsDead)
			continue;

		Vector3 screen_coords;
		Vector3 center = e->vHeadPos;
		center.z = center.z - EYE_HEIGHT + PLAYER_HEIGHT / 2;


		if (world_to_screen(center, screen_coords, assault_game::get_view_matrix(), viewport[2], viewport[3])) {

			ENTITY_ESP_INFO ent_info{ lp_entity, e, screen_coords };
			
			if (menu::features::visuals::b_box)
				draw_esp_box(ent_info, screen_coords);

			if (menu::features::visuals::b_name)
				draw_esp_name(ent_info, screen_coords, font);

			if (menu::features::visuals::b_health)
				draw_esp_health(ent_info, screen_coords);
		}
	}
}

void esp::draw_esp_box(ENTITY_ESP_INFO& ent_info, Vector3 & screen) {

	/* Handles team colors obv */
	if (assault_game::is_team_game()) {

		if (ent_info.ent_trg->TeamNumber == ent_info.ent_src->TeamNumber) {

			GL::DrawBox(
				ent_info.x, 
				ent_info.y, 
				ent_info.width, 
				ent_info.height, 
				1.0f,
				menu::features::visuals::team_box_color, true);

			return;
		}

	}

	GL::DrawBox(
		ent_info.x,
		ent_info.y,
		ent_info.width,
		ent_info.height,
		1.0f, 
		menu::features::visuals::box_color, true);
}


void esp::draw_esp_name(ENTITY_ESP_INFO& ent_info, Vector3& screen, GL::Font& font) {
	const float textX = font.centerText(ent_info.x, ent_info.width, strlen(ent_info.ent_trg->pEntityName) * ESP_FONT_WIDTH);
	const float textY = ent_info.y - ESP_FONT_HEIGHT / 2;

	font.Print(
		textX, 
		textY, 
		menu::features::visuals::name_color, 
		"%s", ent_info.ent_trg->pEntityName);
}


void esp::draw_esp_health(ENTITY_ESP_INFO& ent_info, Vector3 & screen) {
	const float healthBarLoc = (screen.x - 7) - ent_info.scale; /* location of the health bar relative to the box */
	const float healthFrac = ent_info.ent_trg->Health * 0.01f; \

	GLubyte healthColor[3] = {
		255 * (1 - healthFrac),
		(255 * healthFrac),
		0
	};

	/* Health bar outline */
	GL::DrawBox(
		healthBarLoc, 
		ent_info.y,
		2.0f, 
		ent_info.height,
		0.3f / ent_info.scale,
		rgb::black, false);

	/* Health bar */
	GL::DrawFillRect(
		healthBarLoc,
		ent_info.y + ent_info.height - (ent_info.height * ent_info.ent_trg->Health / 100),
		2.0f,
		ent_info.height * ent_info.ent_trg->Health / 100,
		healthColor);
}
