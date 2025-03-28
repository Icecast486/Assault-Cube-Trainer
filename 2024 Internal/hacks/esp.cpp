#include <Windows.h>
#include "esp.h"
#include "../menu/menu.h"

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


void esp::BeginESPDraw()
{
	GL::Font glFont;
	const int FONT_HEIGHT = 15;
	const int FONT_WIDTH = 9;

	HDC currentHDC = wglGetCurrentDC();

	/* if the font isn't built, build it */
	if (!glFont.bBuilt || currentHDC != glFont.hdc) 
		glFont.Build(FONT_HEIGHT);
	
	GL::SetUpOrtho();

	esp::Draw(glFont);

	GL::RestoreGL();
}


void esp::Draw(GL::Font& font)
{
	glGetIntegerv(GL_VIEWPORT, viewport);

	for (int i = 0; i < Engine::getMaxPlayers() - 1; i++)
	{
		int iLPTeamNum = Engine::getLocalPlayer()->iTeamNum;
		const GLubyte* color = nullptr;

		Entity* e = Engine::getEntityList()->Entities[i];

		if (e == nullptr || Engine::getEntityList() == nullptr) {
			std::cout << "[!] Either the entitylist or player is a nullptr!" << std::endl;
			continue;
		}

		Vector3 center = e->vHeadPos;
		center.z = center.z - EYE_HEIGHT + PLAYER_HEIGHT / 2;
		color = rgb::lightgray;

		if (e->bIsDead)
			color = rgb::red;

		Vector3 screenCoords;

		if (worldToScreen(center, screenCoords, Engine::getViewMatrix(), viewport[2], viewport[3]))
			DrawESPBox(e, screenCoords, font, color);
	}
}

void esp::DrawESPBox(Entity* e, Vector3& screen, GL::Font& font, const GLubyte* color)
{
	Entity* localPlayer = Engine::getLocalPlayer();

	float dist = localPlayer->vPosition.get3DDistance(e->vPosition);

	float scale = (GAME_UNIT_MAGIC / dist) * (viewport[2] / VIRTUAL_SCREEN_WIDTH);
	float x = screen.x - scale;
	float y = screen.y - scale * PLAYER_ASPECT_RATIO;

	float x2 = (screen.x + 7) + scale; /* location of the health bar relative to the box */

	float width = scale * 2;
	float height = scale * PLAYER_ASPECT_RATIO * 2;

	float textX = font.centerText(x, width, strlen(e->pEntityName) * ESP_FONT_WIDTH);
	float textY = y - ESP_FONT_HEIGHT / 2;


	/* HEALTH BAR COLOR */
	const float healthFrac = e->iHealth * 0.01f;

	GLubyte healthColor[3] = {
		255 * (1 - healthFrac),
		(255 * healthFrac),
		0
	};

	if (menu::bNameEsp)
	{
		font.Print(textX, textY, color, "%s", e->pEntityName);
	}

	/* Drawing health bar */
	if (menu::bHealthEsp)
	{
		GL::DrawOutline(x2, y, 2.0f, height, 0.5f / scale, color, true);
		GL::DrawFillRect(x2, y + height - (height * e->iHealth / 100), 2.0f, height * e->iHealth / 100, healthColor);
	}

	/* Drawing the box */
	if (menu::bBoxEsp) 
	{
		GL::DrawOutline(x, y, width, height, 0.2f, color, true);
	}
}
