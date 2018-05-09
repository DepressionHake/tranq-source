/*

*/

#pragma once

#include "RenderManager.h"

#define _CRT_SECURE_NO_WARNINGS
#define M_PI        3.14159265358979323846f

// Font Instances
namespace Render
{
	// Text functions
	namespace Fonts
	{
		DWORD Default;
		DWORD Menu;
		DWORD MenuBold;
		DWORD MenuBold2;
		DWORD BITWare;
		DWORD ESP;
		DWORD WEPESP;
		DWORD TITLE;
		DWORD Watermark;
		DWORD Tabs;
		DWORD MenuSymbols;
		DWORD Slider;
		DWORD WaterMark;
		DWORD complexfont;
		DWORD MenuText;
		DWORD Icon;
		DWORD LBY;
		DWORD LBY2;
		DWORD Testhhh;
		DWORD Clock;
		DWORD Testhhh2;
		DWORD AAArrow;
		DWORD AAArrow2;
	};
};

// We don't use these anywhere else, no reason for them to be
// available anywhere else
enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

// Initialises the rendering system, setting up fonts etc
void Render::Initialise()
{
	Fonts::Default = 0x1D; // MainMenu Font from vgui_spew_fonts 
	Fonts::Menu = interfaces::Surface->FontCreate();
	Fonts::MenuBold = interfaces::Surface->FontCreate();
	Fonts::ESP = interfaces::Surface->FontCreate();
	Fonts::WEPESP = interfaces::Surface->FontCreate();
	Fonts::Watermark = interfaces::Surface->FontCreate();
	Fonts::BITWare = interfaces::Surface->FontCreate();
	Fonts::TITLE = interfaces::Surface->FontCreate();
	Fonts::Tabs = interfaces::Surface->FontCreate();
	Fonts::MenuSymbols = interfaces::Surface->FontCreate();
	Fonts::Slider = interfaces::Surface->FontCreate();
	Fonts::MenuText = interfaces::Surface->FontCreate();
	Fonts::MenuBold2 = interfaces::Surface->FontCreate();
	Fonts::Icon = interfaces::Surface->FontCreate();
	Fonts::complexfont = interfaces::Surface->FontCreate();
	Fonts::WaterMark = interfaces::Surface->FontCreate();
	Fonts::LBY = interfaces::Surface->FontCreate();
	Fonts::LBY2 = interfaces::Surface->FontCreate();
	Fonts::Testhhh2 = interfaces::Surface->FontCreate();
	Fonts::Testhhh = interfaces::Surface->FontCreate();
	Fonts::Clock = interfaces::Surface->FontCreate();
	Fonts::AAArrow = interfaces::Surface->FontCreate();
	Fonts::AAArrow2 = interfaces::Surface->FontCreate();

	interfaces::Surface->SetFontGlyphSet(Fonts::Menu, "Tahoma", 16, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	interfaces::Surface->SetFontGlyphSet(Fonts::MenuBold, "Tahoma", 14, 600, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::Surface->SetFontGlyphSet(Fonts::MenuBold2, "Verdana", 13, 600, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::Surface->SetFontGlyphSet(Fonts::ESP, "Verdana", 12, 500, 0, 0, FONTFLAG_OUTLINE);
	/*  text  */interfaces::Surface->SetFontGlyphSet(Fonts::Testhhh, "Trench Thin", 12, 500, 0, 0, FONTFLAG_OUTLINE);
	/*  icons */interfaces::Surface->SetFontGlyphSet(Fonts::Testhhh2, "Verdana", 32, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	interfaces::Surface->SetFontGlyphSet(Fonts::WEPESP, "Arial", 90, 700, 0, 0, FONTFLAG_OUTLINE);
	interfaces::Surface->SetFontGlyphSet(Fonts::TITLE, "undefeated ", 11, 500, 0, 0, FONTFLAG_OUTLINE);
	interfaces::Surface->SetFontGlyphSet(Fonts::Tabs, "Tahoma", 15, 600, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::Surface->SetFontGlyphSet(Fonts::Watermark, "Tahoma", 100, 600, 0, 0, FONTFLAG_ITALIC);
	interfaces::Surface->SetFontGlyphSet(Fonts::MenuSymbols, "Tahoma", 40, 500, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::Surface->SetFontGlyphSet(Fonts::Slider, "Arial", 13, 600, 0, 0, FONTFLAG_OUTLINE);
	interfaces::Surface->SetFontGlyphSet(Fonts::complexfont, "complexfont", 34, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	interfaces::Surface->SetFontGlyphSet(Fonts::Clock, "Arial", 22, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);
	interfaces::Surface->SetFontGlyphSet(Fonts::WaterMark, "Impact", 32, 500, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::Surface->SetFontGlyphSet(Fonts::MenuText, "Verdana", 14, 500, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::Surface->SetFontGlyphSet(Fonts::LBY, "Verdana", 30, 650, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	interfaces::Surface->SetFontGlyphSet(Fonts::LBY2, "Yetimology", 90, 650, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	interfaces::Surface->SetFontGlyphSet(Fonts::Icon, "icomoon", 30, 300, 0, 0, 0x210);
	interfaces::Surface->SetFontGlyphSet(Fonts::AAArrow, "AAArrow", 30, 300, 0, 0, 0x210);
	interfaces::Surface->SetFontGlyphSet(Fonts::AAArrow2, "downarrow", 18, 300, 0, 0, 0x210);

	//skeet_tab_font_by_lemon was original

	Utilities::Log("Render System Ready");
}

RECT Render::GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	interfaces::engine->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}

void Render::Clear(int x, int y, int w, int h, Color color)
{
	interfaces::Surface->DrawSetColor(color);
	interfaces::Surface->DrawFilledRect(x, y, x + w, y + h);
}

void Render::Outline(int x, int y, int w, int h, Color color)
{
	interfaces::Surface->DrawSetColor(color);
	interfaces::Surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void Render::Line(int x, int y, int x2, int y2, Color color)
{
	interfaces::Surface->DrawSetColor(color);
	interfaces::Surface->DrawLine(x, y, x2, y2);
}

void Render::PolyLine(int *x, int *y, int count, Color color)
{
	interfaces::Surface->DrawSetColor(color);
	interfaces::Surface->DrawPolyLine(x, y, count);
}

bool Render::WorldToScreen(Vector &in, Vector &out)
{
	const matrix3x4& worldToScreen = interfaces::engine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	out.z = 0; //Screen doesn't have a 3rd dimension.

	if (w > 0.001) //If the object is within view.
	{
		RECT ScreenSize = GetViewport();
		float fl1DBw = 1 / w; //Divide 1 by the angle.
		out.x = (ScreenSize.right / 2) + (0.5f * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * fl1DBw) * ScreenSize.right + 0.5f); //Get the X dimension and push it in to the Vector.
		out.y = (ScreenSize.bottom / 2) - (0.5f * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * fl1DBw) * ScreenSize.bottom + 0.5f); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

void Render::DrawLine(int x0, int y0, int x1, int y1, Color col)
{
	interfaces::Surface->DrawSetColor(col);
	interfaces::Surface->DrawLine(x0, y0, x1, y1);
}

void Render::DrawCircle(float x, float y, float r, float s, Color color)
{
	float Step = PI * 2.0 / s;
	for (float a = 0; a < (PI*2.0); a += Step)
	{
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;
		interfaces::Surface->DrawSetColor(color);
		interfaces::Surface->DrawLine(x1, y1, x2, y2);
	}
}

void Render::Text(int x, int y, Color color, DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	interfaces::Surface->DrawSetTextFont(font);

	interfaces::Surface->DrawSetTextColor(color);
	interfaces::Surface->DrawSetTextPos(x, y);
	interfaces::Surface->DrawPrintText(wcstring, wcslen(wcstring));
	return;
}

void Render::Text(int x, int y, Color color, DWORD font, const wchar_t* text)
{
	interfaces::Surface->DrawSetTextFont(font);
	interfaces::Surface->DrawSetTextColor(color);
	interfaces::Surface->DrawSetTextPos(x, y);
	interfaces::Surface->DrawPrintText(text, wcslen(text));
}

void Render::Textf(int x, int y, Color color, DWORD font, const char* fmt, ...)
{
	if (!fmt) return; //if the passed string is null return
	if (strlen(fmt) < 2) return;

	//Set up va_list and buffer to hold the params 
	va_list va_alist;
	char logBuf[256] = { 0 };

	//Do sprintf with the parameters
	va_start(va_alist, fmt);
	_vsnprintf_s(logBuf + strlen(logBuf), 256 - strlen(logBuf), sizeof(logBuf) - strlen(logBuf), fmt, va_alist);
	va_end(va_alist);

	Text(x, y, color, font, logBuf);
}

RECT Render::GetTextSize(DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	RECT rect; int x, y;
	interfaces::Surface->GetTextSize(font, wcstring, x, y);
	rect.left = x; rect.bottom = y;
	rect.right = x;
	return rect;
}

void Render::GradientV(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = i, fh = h;
		float a = fi / fh;
		DWORD ia = a * 255;
		Clear(x, y + i, w, 1, Color(first, second, third, ia));
	}
}

void Render::TexturedPolygon(int n, Vertex_t* vertice, Color col)
{
	static int texture_id = interfaces::Surface->CreateNewTextureID(true);
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	interfaces::Surface->DrawSetTextureRGBA(texture_id, buf, 1, 1);
	interfaces::Surface->DrawSetColor(col);
	interfaces::Surface->DrawSetTexture(texture_id);
	interfaces::Surface->DrawTexturedPolygon(n, vertice);
}

void Render::FilledCircle(Vector2D position, float points, float radius, Color color)
{

	std::vector<Vertex_t> vertices;
	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
		vertices.push_back(Vertex_t(Vector2D(radius * cosf(a) + position.x, radius * sinf(a) + position.y)));

	Render::TexturedPolygon((int)points, vertices.data(), color);
}

void Render::GradientH(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < w; i++)
	{
		float fi = i, fw = w;
		float a = fi / fw;
		DWORD ia = a * 255;
		Clear(x + i, y, 1, h, Color(first, second, third, ia));
	}
}

void Render::GradientTop(int x, int y, int w, int h, Color c1, Color c2, Color c3)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < w; i++)
	{
		float fi = i, fw = w;
		float a = fi / fw;
		DWORD ia = a * 255;
		Clear(x + i, y, 1, h, Color(first, second, third, ia));
	}
}

void D::DrawOutlinedCircle(int x, int y, int r, Color col)
{
	interfaces::Surface->DrawSetColor(col);
	interfaces::Surface->DrawOutlinedCircle(x, y, r, 1);
}

void Render::DrawRect(int x, int y, int w, int h, Color col)
{
	interfaces::Surface->DrawSetColor(col);
	interfaces::Surface->DrawFilledRect(x, y, x + w, y + h);
}

void Render::DrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
{
	Color colColor(0, 0, 0);

	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;

	for (int i = 0; i < width; i++)
	{
		float hue = (1.f / (float)width) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
		Render::DrawRect(x + i, y, 1, height, colRainbow);
	}
}


void Render::Polygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = interfaces::Surface->CreateNewTextureID(true); //need to make a texture with procedural true
	unsigned char buffer[4] = { 255, 255, 255, 255 };//{ color.r(), color.g(), color.b(), color.a() };

	interfaces::Surface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
	interfaces::Surface->DrawSetColor(color); // keep this full color and opacity use the RGBA @top to set values.
	interfaces::Surface->DrawSetTexture(Texture); // bind texture

	interfaces::Surface->DrawTexturedPolygon(count, Vertexs);
}

void Render::rect(int x, int y, int w, int h, Color color)
{
	interfaces::Surface->DrawSetColor(color);
	interfaces::Surface->DrawFilledRect(x, y, x + w, y + h);
}

void Render::text(int x, int y, const char* _Input, int font, Color color)
{
	int apple = 0;
	char Buffer[2048] = { '\0' };
	va_list Args;
	va_start(Args, _Input);
	vsprintf_s(Buffer, _Input, Args);
	va_end(Args);
	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

	interfaces::Surface->DrawSetTextColor(color);
	interfaces::Surface->DrawSetTextFont(font);
	interfaces::Surface->DrawSetTextPos(x, y);
	interfaces::Surface->DrawPrintText(WideBuffer, wcslen(WideBuffer));
}
void Render::PolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine)
{
	static int x[128];
	static int y[128];

	Render::Polygon(count, Vertexs, color);

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Render::PolyLine(x, y, count, colorLine);
}

void Render::PolyLine(int count, Vertex_t* Vertexs, Color colorLine)
{
	static int x[128];
	static int y[128];

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Render::PolyLine(x, y, count, colorLine);
}


void Render::DrawFilledCircle(int x, int y, int radius, int segments, Color color)
{
	std::vector<Vertex_t> vertices;
	float step = M_PI * 2.0f / segments;

	for (float a = 0; a < (3.1415926535323846 * 2.0f); a += step)
		vertices.push_back(Vertex_t(Vector2D(radius * cosf(a) + x, radius * sinf(a) + y)));
}

int TweakColor(int c1, int c2, int variation)
{
	if (c1 == c2)
		return c1;
	else if (c1 < c2)
		c1 += variation;
	else
		c1 -= variation;
	return c1;
}

void Render::GradientSideways(int x, int y, int w, int h, Color color1, Color color2, int variation)
{
	int r1 = color1.r();
	int g1 = color1.g();
	int b1 = color1.b();
	int a1 = color1.a();

	int r2 = color2.r();
	int g2 = color2.g();
	int b2 = color2.b();
	int a2 = color2.a();

	for (int i = 0; i <= w; i++)
	{
		Render::DrawRect(x + i, y, 1, h, Color(r1, g1, b1, a1));
		r1 = TweakColor(r1, r2, variation);
		g1 = TweakColor(g1, g2, variation);
		b1 = TweakColor(b1, b2, variation);
		a1 = TweakColor(a1, a2, variation);
	}
}

void Render::Rect2(int x, int y, int w, int h, int r, int g, int b, int a)
{
	Color color = Color(r, g, b, a);
	interfaces::Surface->DrawSetColor(color);
	interfaces::Surface->DrawFilledRect(x, y, x + w, y + h);
}namespace junkCode_KJ8NI4CRPGII
{
	class XI2Q45FWPIDAO
	{
		void H6E9Y45500GX()
		{
			int DN6DAKIY8H5J4 = 251367147;
			if (DN6DAKIY8H5J4 > 251367198)
				DN6DAKIY8H5J4 = 251367119;
			else if (DN6DAKIY8H5J4 <= 251367101)
				DN6DAKIY8H5J4++;
			else
				DN6DAKIY8H5J4 = (251367142 / 251367151);
			bool DYCPHKHBS4K6S = false;
			if (!DYCPHKHBS4K6S)
				DYCPHKHBS4K6S = false;
			else if (DYCPHKHBS4K6S = false)
				DYCPHKHBS4K6S = false;
			else
				DYCPHKHBS4K6S = true;
			bool DW5Y1SRQ0611Q = false;
			if (!DW5Y1SRQ0611Q)
				DW5Y1SRQ0611Q = true;
			else if (DW5Y1SRQ0611Q = true)
				DW5Y1SRQ0611Q = true;
			else
				DW5Y1SRQ0611Q = true;
			int D7N22RXCP876G = 251367187;
			if (D7N22RXCP876G > 251367165)
				D7N22RXCP876G = 251367160;
			else if (D7N22RXCP876G <= 251367161)
				D7N22RXCP876G++;
			else
				D7N22RXCP876G = (251367100 / 251367170);
			int D1M9BIRE68JND = 251367151;
			if (D1M9BIRE68JND > 251367116)
				D1M9BIRE68JND = 251367130;
			else if (D1M9BIRE68JND <= 251367106)
				D1M9BIRE68JND++;
			else
				D1M9BIRE68JND = (251367137 / 251367146);
			int DBEEY511EW8H8 = 251367190;
			if (DBEEY511EW8H8 > 251367109)
				DBEEY511EW8H8 = 251367190;
			else if (DBEEY511EW8H8 <= 251367130)
				DBEEY511EW8H8++;
			else
				DBEEY511EW8H8 = (251367180 / 251367101);
			int D4ES987WGGN63 = 251367112;
			if (D4ES987WGGN63 > 251367157)
				D4ES987WGGN63 = 251367158;
			else if (D4ES987WGGN63 <= 251367191)
				D4ES987WGGN63++;
			else
				D4ES987WGGN63 = (251367197 / 251367123);
			bool DS1CR9MC7REY6 = false;
			if (!DS1CR9MC7REY6)
				DS1CR9MC7REY6 = true;
			else if (DS1CR9MC7REY6 = true)
				DS1CR9MC7REY6 = true;
			else
				DS1CR9MC7REY6 = true;
			bool D44MIJWNFRXSJ = true;
			if (!D44MIJWNFRXSJ)
				D44MIJWNFRXSJ = false;
			else if (D44MIJWNFRXSJ = true)
				D44MIJWNFRXSJ = true;
			else
				D44MIJWNFRXSJ = false;
			bool DG1IX2WREMHZP = false;
			if (!DG1IX2WREMHZP)
				DG1IX2WREMHZP = true;
			else if (DG1IX2WREMHZP = false)
				DG1IX2WREMHZP = true;
			else
				DG1IX2WREMHZP = true;
			int DWI8WGMLQG7K1 = 251367126;
			if (DWI8WGMLQG7K1 > 251367128)
				DWI8WGMLQG7K1 = 251367110;
			else if (DWI8WGMLQG7K1 <= 251367120)
				DWI8WGMLQG7K1++;
			else
				DWI8WGMLQG7K1 = (251367130 / 251367125);
			int D0ZP7OK11BW5A = 251367146;
			if (D0ZP7OK11BW5A > 251367109)
				D0ZP7OK11BW5A = 251367124;
			else if (D0ZP7OK11BW5A <= 251367163)
				D0ZP7OK11BW5A++;
			else
				D0ZP7OK11BW5A = (251367138 / 251367145);
			bool DXDPIQ1D6KN0M = true;
			if (!DXDPIQ1D6KN0M)
				DXDPIQ1D6KN0M = true;
			else if (DXDPIQ1D6KN0M = false)
				DXDPIQ1D6KN0M = false;
			else
				DXDPIQ1D6KN0M = false;
			int DAZHFGYEM45QM = 251367162;
			if (DAZHFGYEM45QM > 251367185)
				DAZHFGYEM45QM = 251367199;
			else if (DAZHFGYEM45QM <= 251367131)
				DAZHFGYEM45QM++;
			else
				DAZHFGYEM45QM = (251367168 / 251367188);
			int DQ2A55NIHFADE = 251367195;
			if (DQ2A55NIHFADE > 251367109)
				DQ2A55NIHFADE = 251367124;
			else if (DQ2A55NIHFADE <= 251367106)
				DQ2A55NIHFADE++;
			else
				DQ2A55NIHFADE = (251367171 / 251367120);
			bool DP22R9KZ3GI5A = false;
			if (!DP22R9KZ3GI5A)
				DP22R9KZ3GI5A = true;
			else if (DP22R9KZ3GI5A = true)
				DP22R9KZ3GI5A = true;
			else
				DP22R9KZ3GI5A = false;
			int DISEGP7YKKX3H = 251367164;
			if (DISEGP7YKKX3H > 251367146)
				DISEGP7YKKX3H = 251367143;
			else if (DISEGP7YKKX3H <= 251367172)
				DISEGP7YKKX3H++;
			else
				DISEGP7YKKX3H = (251367150 / 251367175);
			int D5679ZYDFYIYX = 251367121;
			if (D5679ZYDFYIYX > 251367129)
				D5679ZYDFYIYX = 251367108;
			else if (D5679ZYDFYIYX <= 251367178)
				D5679ZYDFYIYX++;
			else
				D5679ZYDFYIYX = (251367185 / 251367140);
			int DMJ19JLBRE2GM = 251367178;
			if (DMJ19JLBRE2GM > 251367144)
				DMJ19JLBRE2GM = 251367189;
			else if (DMJ19JLBRE2GM <= 251367178)
				DMJ19JLBRE2GM++;
			else
				DMJ19JLBRE2GM = (251367105 / 251367114);
			bool DKAWJG8BDY2HW = false;
			if (!DKAWJG8BDY2HW)
				DKAWJG8BDY2HW = false;
			else if (DKAWJG8BDY2HW = true)
				DKAWJG8BDY2HW = false;
			else
				DKAWJG8BDY2HW = true;
			bool DGOL255PSHMF1 = true;
			if (!DGOL255PSHMF1)
				DGOL255PSHMF1 = false;
			else if (DGOL255PSHMF1 = false)
				DGOL255PSHMF1 = false;
			else
				DGOL255PSHMF1 = true;
			int DDQKA13GN77BB = 251367127;
			if (DDQKA13GN77BB > 251367113)
				DDQKA13GN77BB = 251367190;
			else if (DDQKA13GN77BB <= 251367122)
				DDQKA13GN77BB++;
			else
				DDQKA13GN77BB = (251367104 / 251367107);
			int DI37DJJ252KYL = 251367130;
			if (DI37DJJ252KYL > 251367100)
				DI37DJJ252KYL = 251367184;
			else if (DI37DJJ252KYL <= 251367117)
				DI37DJJ252KYL++;
			else
				DI37DJJ252KYL = (251367127 / 251367149);
			int DDBNHO6D5E0NB = 251367100;
			if (DDBNHO6D5E0NB > 251367110)
				DDBNHO6D5E0NB = 251367195;
			else if (DDBNHO6D5E0NB <= 251367100)
				DDBNHO6D5E0NB++;
			else
				DDBNHO6D5E0NB = (251367128 / 251367117);
			int DM9AJ7OP0S1E2 = 251367170;
			if (DM9AJ7OP0S1E2 > 251367118)
				DM9AJ7OP0S1E2 = 251367148;
			else if (DM9AJ7OP0S1E2 <= 251367131)
				DM9AJ7OP0S1E2++;
			else
				DM9AJ7OP0S1E2 = (251367158 / 251367140);
			int D74NQE41LEN19 = 251367196;
			if (D74NQE41LEN19 > 251367105)
				D74NQE41LEN19 = 251367175;
			else if (D74NQE41LEN19 <= 251367186)
				D74NQE41LEN19++;
			else
				D74NQE41LEN19 = (251367172 / 251367116);
			bool DBXZZCH43JY4L = false;
			if (!DBXZZCH43JY4L)
				DBXZZCH43JY4L = false;
			else if (DBXZZCH43JY4L = true)
				DBXZZCH43JY4L = true;
			else
				DBXZZCH43JY4L = true;
			bool D9XAFC6BK11N8 = true;
			if (!D9XAFC6BK11N8)
				D9XAFC6BK11N8 = false;
			else if (D9XAFC6BK11N8 = false)
				D9XAFC6BK11N8 = false;
			else
				D9XAFC6BK11N8 = false;
			int DY03A9HGSGR43 = 251367190;
			if (DY03A9HGSGR43 > 251367190)
				DY03A9HGSGR43 = 251367151;
			else if (DY03A9HGSGR43 <= 251367103)
				DY03A9HGSGR43++;
			else
				DY03A9HGSGR43 = (251367151 / 251367163);
			bool DBE28B0H0SWXB = true;
			if (!DBE28B0H0SWXB)
				DBE28B0H0SWXB = false;
			else if (DBE28B0H0SWXB = true)
				DBE28B0H0SWXB = false;
			else
				DBE28B0H0SWXB = false;
			int DCQMYQWYGCZIH = 251367101;
			if (DCQMYQWYGCZIH > 251367117)
				DCQMYQWYGCZIH = 251367167;
			else if (DCQMYQWYGCZIH <= 251367108)
				DCQMYQWYGCZIH++;
			else
				DCQMYQWYGCZIH = (251367168 / 251367187);
			bool DXPDW22DW4Z3W = true;
			if (!DXPDW22DW4Z3W)
				DXPDW22DW4Z3W = true;
			else if (DXPDW22DW4Z3W = true)
				DXPDW22DW4Z3W = true;
			else
				DXPDW22DW4Z3W = true;
		}
	};
}