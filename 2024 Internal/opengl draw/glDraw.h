#pragma once

#ifndef GLDRAW_H
#define GLDRAW_H

#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <gl\GL.h>
#include "..\memory\gamestructures.h"
#include "..\memory\mem.h"



namespace rgb
{
	const GLubyte red[3] = { 255, 0 , 0 };
	const GLubyte green[3] = { 0, 255 , 0 };
	const GLubyte gray[3] = { 55, 55 , 55 };
	const GLubyte lightgray[3] = { 192, 192 , 192 };
	const GLubyte black[3] = { 0, 0 , 0 };
}


namespace GL
{
	void SetUpOrtho();
	void RestoreGL();

	void DrawFillRect(float x, float y, float width, float height, const GLubyte color[3]);
	void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);


	class Font
	{
	public:
		bool bBuilt{ false };
		unsigned int base;
		HDC hdc = nullptr;
		int height;
		int width;

		void Build(int height);
		void Print(float x, float y, const unsigned char color[3], const char* format, ...);

		Vector3 centerText(float x, float y, float width, float height, float textWidth, float textHeight);
		float centerText(float x, float width, float textWidth);
	};

}

#endif 