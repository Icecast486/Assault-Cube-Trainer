
#ifndef ESP_H
#define ESP_H

#include "../../math/math.hpp"
#include "../../game/structures.h"
#include "../../draw/gldraw.h"


const int VIRTUAL_SCREEN_WIDTH = 600;
const int GAME_UNIT_MAGIC = 320;

const float PLAYER_HEIGHT = 5.25f;
const float PLAYER_WIDTH = 2.0f;
const float EYE_HEIGHT = 4.5f;

const float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;

const int ESP_FONT_HEIGHT = 15;
const int ESP_FONT_WIDTH = 9;

namespace esp
{

	inline int viewport[4];
	inline bool is_active;

	inline bool bESP = false;
	
	//void DrawESPBox(Entity* e, Vector3& screen, GL::Font& font, const GLubyte* color);

	void BeginESPDraw(HDC hDc);

	/* Captures information of an entity at a given frame for drawing esp */
	class ENTITY_ESP_INFO {
	public:
		Entity* ent_src, *ent_trg; /* ent_src is who the math is based off of */
		float dist;
		float scale;
		float x;
		float y;

		/* set up size of box and font */
		float width;
		float height;

		ENTITY_ESP_INFO(Entity* src, Entity* trg, Vector3& screen) {
			ent_src = src;
			ent_trg = trg;
			dist = src->vPosition.get3DDistance(trg->vPosition);
			scale = (GAME_UNIT_MAGIC / dist) * (viewport[2] / VIRTUAL_SCREEN_WIDTH);
			x = screen.x - scale;
			y = screen.y = screen.y - scale * PLAYER_ASPECT_RATIO;
			width = scale * 2;
			height = scale * PLAYER_ASPECT_RATIO * 2;
		}
	};


	void draw_ents(GL::Font& font);
	void draw_esp_box(ENTITY_ESP_INFO& ent_info, Vector3& screen);
	void draw_esp_name(ENTITY_ESP_INFO& ent_info, Vector3& screen, GL::Font& font);
	void draw_esp_health(ENTITY_ESP_INFO& ent_info, Vector3& screen);

}





#endif