#include "glDraw.h"

void GL::SetUpOrtho()
{
	/* set up an orthographic matrix todo 2D drawing */
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}



void GL::RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}



void GL::DrawFillRect(float x, float y, float width, float height, const GLubyte color[3])
{
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}



void GL::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3], bool outline)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glColor3ub(color[0], color[1], color[2]); /* error getting color */
	glVertex2f(x - .5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y - 0.5f);
	
	glEnd();

	if (outline)
	{
		const GLubyte* col = rgb::black;
		float offset = 1.6f;

		/* draw black outline */
		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		glColor3ub(col[0], col[1], col[2]);
		glVertex2f(x - offset, y - offset);
		glVertex2f(x + width + offset, y - offset);
		glVertex2f(x + width + offset, y + height + offset);
		glVertex2f(x - offset, y + height + offset);
		glVertex2f(x - offset, y - offset);


		glEnd();
	}
}


void GL::Font::Build(int height)
{
	hdc = wglGetCurrentDC();
	base = glGenLists(96);

	HFONT hFont = CreateFontA
				( 
					-height, 0, 0, 0, FW_MEDIUM, FALSE, 
					FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, 
					CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | 
					DEFAULT_PITCH, "Consolas "
				); /* mono spaced font */

	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	wglUseFontBitmaps(hdc, 32, 96, base);
	SelectObject(hdc, hOldFont);			/* select the old font and set it back do the device context */
	DeleteObject(hFont);					/* delete our old font */

	bBuilt = true;
}
void GL::Font::Print(float x, float y, const unsigned char color[3], const char* format, ...)
{
	glColor3ub(color[0], color[1], color[2]);
	glRasterPos2f(x, y);

	char text[100];
	va_list args;

	va_start(args, format);
	vsprintf_s(text, 100, format, args);
	va_end(args);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

Vector3 GL::Font::centerText(float x, float y, float width, float height, float textWidth, float textHeight)
{
	Vector3 text;
	text.x = x + (width - textWidth) / 2;
	text.y = y + textHeight;
	return text;
}


float GL::Font::centerText(float x, float width, float textWidth)
{
	if (width > textWidth)
	{
		float difference = width - textWidth;
		return (x + (difference / 2));
	}
	else
	{
		float difference = textWidth - width;
		return (x - (difference / 2));
	}
}