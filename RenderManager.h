/*
bonus's tranquility framework 2018
*/

#pragma once

#include "Interfaces.h"

#include "Vector2D.h"

void Quad();


namespace Render
{
	void Initialise();

	// Normal Drawing functions
	void Clear(int x, int y, int w, int h, Color color);
	void Outline(int x, int y, int w, int h, Color color);
	void Line(int x, int y, int x2, int y2, Color color);
	void PolyLine(int *x, int *y, int count, Color color);
	void GradientSideways(int x, int y, int w, int h, Color color1, Color color2, int variation);
	void DrawRect(int x, int y, int w, int h, Color col);
	void DrawRectRainbow(int x, int y, int w, int h, float flSpeed, float &flRainbow);
	void rect(int x, int y, int w, int h, Color color);
	void text(int x, int y, const char* _Input, int font, Color color);
	void Polygon(int count, Vertex_t* Vertexs, Color color);
	void TexturedPolygon(int n, Vertex_t* vertice, Color col);
	extern bool ScreenTransform(const Vector &point, Vector &screen);
	void DrawFilledCircle(int x, int y, int radius, int segments, Color color);
	void PolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine);
	void FilledCircle(Vector2D position, float points, float radius, Color color);
	void PolyLine(int count, Vertex_t* Vertexs, Color colorLine);
	void DrawLine(int x0, int y0, int x1, int y1, Color col);

	void Rect2(int x, int y, int w, int h, int r, int g, int b, int a);

	// Gradient Functions
	void GradientV(int x, int y, int w, int h, Color c1, Color c2);
	void Gradientp(Color c1, Color c2);
	void GradientH(int x, int y, int w, int h, Color c1, Color c2);
	void GradientTop(int x, int y, int w, int h, Color c1, Color c2, Color c3);


	// Text functions
	namespace Fonts
	{
		extern DWORD Default;
		extern DWORD Menu;
		extern DWORD MenuBold;
		extern DWORD MenuBold2;
		extern DWORD BITWare;
		extern DWORD ESP;
		extern DWORD WEPESP;
		extern DWORD TITLE;
		extern DWORD Watermark;
		extern DWORD Tabs;
		extern DWORD MenuSymbols;
		extern DWORD Icon;
		extern DWORD Slider;
		extern DWORD complexfont;
		extern DWORD MenuText;
		extern DWORD Testhhh;
		extern DWORD Clock;
		extern DWORD Testhhh2;
		extern DWORD AAArrow;
		extern DWORD AAArrow2;
		extern DWORD LBY;
		extern DWORD LBY2;
		extern DWORD WaterMark;
	};

	void Text(int x, int y, Color color, DWORD font, const char* text);
	void Textf(int x, int y, Color color, DWORD font, const char* fmt, ...);
	void Text(int x, int y, Color color, DWORD font, const wchar_t* text);
	RECT GetTextSize(DWORD font, const char* text);

	// Other rendering functions
	bool WorldToScreen(Vector &in, Vector &out);
	void DrawCircle(float x, float y, float r, float s, Color color);
	RECT GetViewport();
};

namespace D
{
	extern void DrawOutlinedCircle(int x, int y, int r, Color col);
};