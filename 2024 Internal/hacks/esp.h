#pragma once
#include "../memory/gamestructures.h"
#include "../interface/engine.h"

bool worldToScreen(Vector3 pos, Vector3& screen, float* matrix, int windowWidth, int windowHeight);

const int VIRTUAL_SCREEN_WIDTH = 600;
const int GAME_UNIT_MAGIC = 400;

const float PLAYER_HEIGHT = 5.25f;
const float PLAYER_WIDTH = 2.0f;
const float EYE_HEIGHT = 4.5f;

const float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;

const int ESP_FONT_HEIGHT = 15;
const int ESP_FONT_WIDTH = 9;

namespace esp
{
	inline int viewport[4];
	inline bool bIsActive;

	inline bool bESP = false;

	void Draw(GL::Font& font);
	void DrawESPBox(Entity* e, Vector3& screen, GL::Font& font, const GLubyte* color);

	void BeginESPDraw();
}