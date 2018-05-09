#include "GUI.h"
#include "RenderManager.h"
#include "MetaInfo.h"
#include <algorithm>
#include "tinyxml2.h"
#include "Controls.h"
#include "Controls.h"
#include "Menu.h"

float MenuAlpha = 0.f;

CGUI GUI;
CRadar *Radar = new CRadar;

CGUI::CGUI()
{
}

void CGUI::Draw()
{
	bool ShouldDrawCursor = false;

	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			ShouldDrawCursor = true;
			DrawWindow(window);
		}

	}

	if (ShouldDrawCursor)
	{
		for (int i = 0; i < 4; i++)
			Render::Rect2(Mouse.x + 2 + i, Mouse.y + 2 + i, 1, 14 - (i * 2), 255, 255, 255, 255);
			Render::Rect2(Mouse.x + 6, Mouse.y + 6, 1, 8, 255, 255, 255, 255);
			Render::Rect2(Mouse.x + 7, Mouse.y + 7, 1, 9, 255, 255, 255, 255);
		for (int i = 0; i < 4; i++)
			Render::Rect2(Mouse.x + 8 + i, Mouse.y + 8 + i, 1, 4 - i, 255, 255, 222, 255);
			Render::Rect2(Mouse.x + 8, Mouse.y + 14, 1, 4, 255, 255, 255, 255);
			Render::Rect2(Mouse.x + 9, Mouse.y + 16, 1, 2, 255, 255, 255, 255);
	}
}

// Handle all input etc
void CGUI::Update()
{
	bool IsDraggingWindow;
	//Key Array
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++)
	{
		//oldKeys[x] = oldKeys[x] & keys[x];
		keys[x] = (GetAsyncKeyState(x));
	}

	// Mouse Location
	POINT mp; GetCursorPos(&mp);
	Mouse.x = mp.x; Mouse.y = mp.y;

	RECT Screen = Render::GetViewport();

	// Window Binds
	for (auto& bind : WindowBinds)
	{
		if (GetKeyPress(bind.first))
		{
			bind.second->Toggle();
		}
	}

	// Stop dragging
	if (IsDraggingWindow && !GetKeyState(VK_LBUTTON))
	{
		IsDraggingWindow = false;
		DraggingWindow = nullptr;
	}

	// If we are in the proccess of dragging a window
	if (IsDraggingWindow && GetKeyState(VK_LBUTTON) && !GetKeyPress(VK_LBUTTON))
	{
		if (DraggingWindow)
		{
			DraggingWindow->m_x = Mouse.x - DragOffsetX;
			DraggingWindow->m_y = Mouse.y - DragOffsetY;
		}
	}

	// Process some windows
	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			// Used to tell the widget processing that there could be a click
			bool bCheckWidgetClicks = false;

			// If the user clicks inside the window
			if (GetKeyPress(VK_LBUTTON))
			{
				if (IsMouseInRegion(window->m_x, window->m_y, window->m_x + window->m_iWidth, window->m_y + window->m_iHeight))
				{
					// Is it inside the client area?
					if (IsMouseInRegion(window->GetClientArea()))
					{
						// User is selecting a new tab
						if (IsMouseInRegion(window->GetTabArea()))
						{
							// Loose focus on the control
							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;

							int iTab = 0;
							int TabCount = window->Tabs.size();
							if (TabCount) // If there are some tabs
							{
								int TabSize = (window->m_iWidth - 4 - 12) / TabCount;
								int Dist = Mouse.x - (window->m_x + 8);
								while (Dist > TabSize)
								{
									if (Dist > TabSize)
									{
										iTab++;
										Dist -= TabSize;
									}
								}
								window->SelectedTab = window->Tabs[iTab];
							}

						}
						else
							bCheckWidgetClicks = true;
					}
					else
					{
						// Must be in the around the title or side of the window
						// So we assume the user is trying to drag the window
						IsDraggingWindow = true;
						DraggingWindow = window;
						DragOffsetX = Mouse.x - window->m_x;
						DragOffsetY = Mouse.y - window->m_y;

						// Loose focus on the control
						window->IsFocusingControl = false;
						window->FocusedControl = nullptr;
					}
				}
				else
				{
					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}


			// Controls 
			if (window->SelectedTab != nullptr)
			{
				// Focused widget
				bool SkipWidget = false;
				CControl* SkipMe = nullptr;

				// this window is focusing on a widget??
				if (window->IsFocusingControl)
				{
					if (window->FocusedControl != nullptr)
					{
						// We've processed it once, skip it later
						SkipWidget = true;
						SkipMe = window->FocusedControl;

						POINT cAbs = window->FocusedControl->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, window->FocusedControl->m_iWidth, window->FocusedControl->m_iHeight };
						window->FocusedControl->OnUpdate();

						if (window->FocusedControl->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							window->FocusedControl->OnClick();

							// If it gets clicked we loose focus
							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;
							bCheckWidgetClicks = false;
						}
					}
				}

				// Itterate over the rest of the control
				for (auto control : window->SelectedTab->Controls)
				{
					if (control != nullptr)
					{
						if (SkipWidget && SkipMe == control)
							continue;

						POINT cAbs = control->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
						control->OnUpdate();

						if (control->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							control->OnClick();
							bCheckWidgetClicks = false;

							// Change of focus
							if (control->Flag(UIFlags::UI_Focusable))
							{
								window->IsFocusingControl = true;
								window->FocusedControl = control;
							}
							else
							{
								window->IsFocusingControl = false;
								window->FocusedControl = nullptr;
							}

						}
					}
				}

				// We must have clicked whitespace
				if (bCheckWidgetClicks)
				{
					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}
		}
	}
}

// Returns 
bool CGUI::GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

bool CGUI::GetKeyState(unsigned int key)
{
	return keys[key];
}

bool CGUI::IsMouseInRegion(int x, int y, int x2, int y2)
{
	if (Mouse.x > x && Mouse.y > y && Mouse.x < x2 && Mouse.y < y2)
		return true;
	else
		return false;
}

bool CGUI::IsMouseInRegion(RECT region)
{
	return IsMouseInRegion(region.left, region.top, region.left + region.right, region.top + region.bottom);
}

POINT CGUI::GetMouse()
{
	return Mouse;
}

/*Render::Clear(window->m_x - 8, window->m_y - 8, window->m_iWidth + 16, window->m_iHeight + 16, Color(72, 72, 72, 255));
Render::Clear(window->m_x, window->m_y, window->m_iWidth, window->m_iHeight, Color(19, 19, 21, 255));
Render::Clear(window->m_x, window->m_y + UI_WIN_TOPHEIGHT, window->m_iWidth, UI_WIN_TITLEHEIGHT, UI_COL_MAIN);
Render::GradientV(window->m_x, window->m_y + UI_WIN_TOPHEIGHT, window->m_iWidth, UI_WIN_TITLEHEIGHT, UI_COL_MAIN, UI_COL_MAIN);
//Render::Outline(window->m_x, window->m_y + UI_WIN_TOPHEIGHT, window->m_iWidth, UI_WIN_TITLEHEIGHT, UI_COL_SHADOW);
Render::Outline(window->m_x - 8, window->m_y - 8, window->m_iWidth + 16, window->m_iHeight + 16, Color(255, 255, 255, 115));

Render::Clear(window->m_x + 12, window->m_y + 12, window->m_iWidth - 24, window->m_iHeight - 590, Color(30, 30, 30, 255));
Render::Outline(window->m_x + 12, window->m_y + 12, window->m_iWidth - 24, window->m_iHeight - 590, Color(255, 255, 255, 175));

Render::Clear(window->m_x + 12, window->m_y + 85, window->m_iWidth - 24, window->m_iHeight - 97, Color(30, 30, 30, 255));
Render::Outline(window->m_x + 12, window->m_y + 85, window->m_iWidth - 24, window->m_iHeight - 97, Color(255, 255, 255, 175));*/


bool CGUI::DrawWindow(CWindow* window)
{
	// Main window and title
	//Render::Clear(window->m_x, window->m_y, window->m_iWidth, window->m_iHeight, Color(255,255,0,255));
	//Render::Clear(window->m_x, window->m_y + UI_WIN_TOPHEIGHT, window->m_iWidth, UI_WIN_TITLEHEIGHT, UI_COL_MAIN);
	// Main window and title 

	Render::Outline(window->m_x, window->m_y, window->m_iWidth, window->m_iHeight, Color(21, 21, 21, 80));
	Render::GradientV(window->m_x + 2, window->m_y + 2, window->m_iWidth - 4, 2, Color(0, 0, 0, 255), Color(0, 0, 0, 255));
	Render::Clear(window->m_x + 1, window->m_y + 1, window->m_iWidth - 2, window->m_iHeight - 2, Color(0, 0, 0, 255));
	Render::Outline(window->m_x + 1, window->m_y + 1, window->m_iWidth - 2, window->m_iHeight - 2, Color(0, 0, 0, 255));
	Render::Text(window->m_x + 370, window->m_y + 5, Color(255, 0, 0, 255), Render::Fonts::Clock, "tranquility");
	//Render::Text(window->m_x + 8, window->m_y + 8, Color(0, 0, 0, 255), Render::Fonts::MenuBold, window->Title.c_str());
	Render::Clear(window->m_x + 8, window->m_y + 1 + 27, window->m_iWidth - 4 - 12, window->m_iHeight - 2 - 8 - 26, Color(30, 30, 30, 255));
	Render::GradientV(window->m_x + 8, window->m_y + 28, window->m_iWidth - 4 - 12, 70, Color(49, 42, 42, 255), Color(49, 42, 42, 255));
	int TabCount = window->Tabs.size();
	if (TabCount) // If there are some tabs
	{
		int TabSize = (window->m_iWidth - 16) / TabCount;
		for (int i = 0; i < TabCount; i++)
		{
			RECT TabArea = { window->m_x + 8 + (i*TabSize), window->m_y + 40, TabSize, 40 };
			CTab *tab = window->Tabs[i];
			//top left to corner
			Render::Line(window->m_x, window->m_y + 3, 0, 0, Color(0, 0, 0));
			//top right to corner
			Render::Line(window->m_x + 850, window->m_y + 2, 2000, 0, Color(0, 0, 0));
			//bottom left to corner
			Render::Line(window->m_x, window->m_y + 600, 0, 1075, Color(0, 0, 0));
			//bottom right to corner
			Render::Line(window->m_x + 849, window->m_y + 600, 2000, 1080, Color(0, 0, 0));

			if (window->SelectedTab == tab)
			{
				Render::GradientV(window->m_x + 8 + (i*TabSize), window->m_y + 28, TabSize, 70, Color(255, 80, 80, 255), Color(255, 0, 0, 255));
			}
			else if (IsMouseInRegion(TabArea))
			{
				Render::GradientV(window->m_x + 8 + (i*TabSize), window->m_y + 28, TabSize, 70, Color(255, 80, 80, 255), Color(255, 0, 0, 255));
			}
			RECT TextSize = Render::GetTextSize(Render::Fonts::MenuBold, tab->Title.c_str());
			Render::Text(TabArea.left + (TabSize / 2) - (TextSize.right / 2), TabArea.top + 13, Color(0, 0, 0, 255), Render::Fonts::MenuBold, tab->Title.c_str());
			//Render::Clear(window->m_x + 8, window->m_y + 28, window->m_iWidth - 30, 2, Color(62, 55, 55, 255));
		}
	}

	//Render::Outline(window->m_x)
	// Controls 
	if (window->SelectedTab != nullptr)
	{
		// Focused widget
		bool SkipWidget = false;
		CControl* SkipMe = nullptr;

		// this window is focusing on a widget??
		if (window->IsFocusingControl)
		{
			if (window->FocusedControl != nullptr)
			{
				// We need to draw it last, so skip it in the regular loop
				SkipWidget = true;
				SkipMe = window->FocusedControl;
			}
		}


		// Itterate over all the other controls
		for (auto control : window->SelectedTab->Controls)
		{
			if (SkipWidget && SkipMe == control)
				continue;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

		// Draw the skipped widget last
		if (SkipWidget)
		{
			auto control = window->FocusedControl;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		} 
		return true;
	}
}

bool CGUI::DrawRadar()
{

	//radar!!!!!!!!!!!!!!!!
	//Render::Outline(Radar->m_x, Radar->m_y, Radar->m_iWidth, Radar->m_iHeight, Color(0, 255, 0));
	Render::GradientV(Radar->m_x + 2, Radar->m_y + 21, Radar->m_iWidth - 4, 7, Color(19, 19, 19), Color(140, 255, 25, 255));   //цвет шапки радара
	Render::Clear(Radar->m_x + 2, Radar->m_y + 2 + 26, Radar->m_iWidth - 4, Radar->m_iHeight - 4 - 26, Color(140, 255, 25, 255)); //тоже самое как на шапку ставить																											   //Render::Outline(Radar->m_x + 1, Radar->m_y + 1, Radar->m_iWidth - 2, Radar->m_iHeight - 2, Color(255, 255, 255)); //обводка
																								   //Render::Text(Radar->m_x + 64, Radar->m_y + 8, Color(0, 150, 0, 255), Render::Fonts::MenuBold, Radar->Title.c_str()); //цвет текста


																														   //Render::Outline(Radar->m_x + 7, Radar->m_y + 1 + 26, Radar->m_iWidth - 4 - 10, Radar->m_iHeight - 2 - 6 - 26, Color(1, 1, 1, 255));
	Render::Clear(Radar->m_x + 8, Radar->m_y + 1 + 27, Radar->m_iWidth - 4 - 12, Radar->m_iHeight - 2 - 8 - 26, Color(59, 61, 60, 255));

	if (!interfaces::engine->IsInGame()) 
	{
		//Draw info
		Render::Text(Radar->m_x + 68, Radar->m_y + 97, Color(0, 150, 0, 255), Render::Fonts::MenuBold, " ");
		return false;
	}

	IClientEntity* LocalPlayer = interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (LocalPlayer) {
		auto flAngle(LocalPlayer->GetAbsAngles2().y);

		for (size_t EntityID = 1; EntityID < 64; EntityID++) {
			IClientEntity* Entity = interfaces::g_entitylist->GetClientEntity(EntityID);
			if (!Entity || Entity == LocalPlayer || !Entity->IsAlive() || Entity->IsDormant())
				continue;

			if (g_menu.esp.OtherRadarEnemyOnly.getstate()) 
			{
				if (LocalPlayer->GetTeamNum() == Entity->GetTeamNum())
					continue;
			}

			bool Visible = true;

			if (g_menu.esp.OtherRadarVisibleOnly.getstate()) 
			{
				Visible = false;

				if (GameUtils::IsVisible(LocalPlayer, Entity, (int)CSPlayerBones::head_0) ||
					GameUtils::IsVisible(LocalPlayer, Entity, (int)CSPlayerBones::arm_upper_L) ||
					GameUtils::IsVisible(LocalPlayer, Entity, (int)CSPlayerBones::arm_upper_R) ||
					GameUtils::IsVisible(LocalPlayer, Entity, (int)CSPlayerBones::hand_L) ||
					GameUtils::IsVisible(LocalPlayer, Entity, (int)CSPlayerBones::hand_R)) {
					Visible = true;
				}
			}

			int CenterX = Radar->m_x + Radar->m_iWidth / 2;
			int CenterY = Radar->m_y + Radar->m_iHeight / 2;

			float DeltaX = Entity->GetOrigin2().x - LocalPlayer->GetOrigin2().x;
			float DeltaY = Entity->GetOrigin2().y - LocalPlayer->GetOrigin2().y;

			float Yaw = (flAngle) * (PI / 180.0);
			float MainViewAngles_CosYaw = cos(Yaw);
			float MainViewAngles_SinYaw = sin(Yaw);

			float x = DeltaY * (-MainViewAngles_CosYaw) + DeltaX * MainViewAngles_SinYaw;
			float y = DeltaX * (-MainViewAngles_CosYaw) - DeltaY * MainViewAngles_SinYaw;

			float Scale = g_menu.esp.OtherRadarScale.getvalue();

			if (fabs(x) > Scale || fabs(y) > Scale) {
				if (y > x) {
					if (y > -x) {
						x = Scale * x / y;
						y = Scale;
					}
					else {
						y = -Scale * y / x;
						x = -Scale;
					}
				}
				else {
					if (y > -x) {
						y = Scale *y / x;
						x = Scale;
					}
					else {
						x = -Scale * x / y;
						y = -Scale;
					}
				}
			}

			int	ScreenX = CenterX + int(x / Scale * 98);
			int ScreenY = CenterY + int(y / Scale * 98);

			Color _Color;

			switch (Entity->GetTeamNum()) {
			case TEAM_CS_T:
				if (Visible) {
					_Color.SetColor(g_menu.ColorTab.TColorVisR.getvalue(), g_menu.ColorTab.TColorVisG.getvalue(), g_menu.ColorTab.TColorVisB.getvalue(), 255);
					Render::Clear(ScreenX - 2, ScreenY - 2, 5, 5, _Color);
				}
				else {
					_Color.SetColor(g_menu.ColorTab.TColorNoVisB.getvalue(), g_menu.ColorTab.TColorNoVisG.getvalue(), g_menu.ColorTab.TColorNoVisB.getvalue(), 255);
					Render::Clear(ScreenX - 2, ScreenY - 2, 5, 5, _Color);
				}
				break;

			case TEAM_CS_CT:
				if (Visible) {
					_Color.SetColor(g_menu.ColorTab.CTColorVisR.getvalue(), g_menu.ColorTab.CTColorVisG.getvalue(), g_menu.ColorTab.CTColorVisB.getvalue(), 255);
					Render::Clear(ScreenX - 2, ScreenY - 2, 5, 5, _Color);
				}
				else {
					_Color.SetColor(g_menu.ColorTab.CTColorNoVisR.getvalue(), g_menu.ColorTab.CTColorNoVisG.getvalue(), g_menu.ColorTab.CTColorNoVisB.getvalue(), 255);
					Render::Clear(ScreenX - 2, ScreenY - 2, 5, 5, _Color);
				}
				break;
			}
		}
	}

	//Render::Line(Radar->m_x + 18, Radar->m_y + 28, Radar->m_x + 100, Radar->m_y + 28 + 82, Color(255, 255, 255, 255));
	//Render::Line(Radar->m_x + 100, Radar->m_y + 28 + 82, Radar->m_x + Radar->m_iWidth - 17, Radar->m_y + 27, Color(255, 255, 255, 255));
	Render::Line(Radar->m_x + 8, Radar->m_y + 28 + 82, Radar->m_x + Radar->m_iWidth - 8, Radar->m_y + 28 + 82, Color(140, 255, 25, 255));
	Render::Line(Radar->m_x + 100, Radar->m_y - 55 + 82, Radar->m_x + 100, Radar->m_y + Radar->m_iHeight - 4, Color(140, 255, 25, 255));


	return true;
}

namespace junkCode_KJ8NI4CRPGII
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

void CGUI::RegisterWindow(CWindow* window)
{
	Windows.push_back(window);

	for (auto tab : window->Tabs)
	{
		for (auto control : tab->Controls)
		{
			if (control->Flag(UIFlags::UI_RenderFirst))
			{
				CControl * c = control;
				tab->Controls.erase(std::remove(tab->Controls.begin(), tab->Controls.end(), control), tab->Controls.end());
				tab->Controls.insert(tab->Controls.begin(), control);
			}
		}
	}
}

void CGUI::BindWindow(unsigned char Key, CWindow* window)
{
	if (window)
		WindowBinds[Key] = window;
	else
		WindowBinds.erase(Key);
}

void CGUI::SaveWindowState(CWindow* window, std::string Filename)
{
	tinyxml2::XMLDocument Doc;
	tinyxml2::XMLElement *Root = Doc.NewElement("tranq");
	Doc.LinkEndChild(Root);

	if (Root && window->Tabs.size() > 0)
	{
		for (auto Tab : window->Tabs)
		{
			tinyxml2::XMLElement *TabElement = Doc.NewElement(Tab->Title.c_str());
			Root->LinkEndChild(TabElement);

			if (TabElement && Tab->Controls.size() > 0)
			{
				for (auto Control : Tab->Controls)
				{
					if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
					{
						tinyxml2::XMLElement *ControlElement = Doc.NewElement(Control->FileIdentifier.c_str());
						TabElement->LinkEndChild(ControlElement);

						if (!ControlElement)
						{
							return;
						}

						CCheckBox* cbx = nullptr;
						CComboBox* cbo = nullptr;
						CKeyBind* key = nullptr;
						CSlider* sld = nullptr;
						CSliderR* sld2 = nullptr;
						CSliderG* sld3 = nullptr;
						CSliderB* sld4 = nullptr;


						switch (Control->FileControlType)
						{
						case UIControlTypes::UIC_CheckBox:
							cbx = (CCheckBox*)Control;
							ControlElement->SetText(cbx->getstate());
							break;
						case UIControlTypes::UIC_ComboBox:
							cbo = (CComboBox*)Control;
							ControlElement->SetText(cbo->getindex());
							break;
						case UIControlTypes::UIC_KeyBind:
							key = (CKeyBind*)Control;
							ControlElement->SetText(key->GetKey());
							break;
						case UIControlTypes::UIC_Slider:
							sld = (CSlider*)Control;
							ControlElement->SetText(sld->getvalue());
							break;
						case UIControlTypes::UIC_SliderR:
							sld2 = (CSliderR*)Control;
							ControlElement->SetText(sld2->getvalue());
							break;
						case UIControlTypes::UIC_SliderG:
							sld3 = (CSliderG*)Control;
							ControlElement->SetText(sld3->getvalue());
							break;
						case UIControlTypes::UIC_SliderB:
							sld4 = (CSliderB*)Control;
							ControlElement->SetText(sld4->getvalue());
							break;
						}
					}
				}
			}
		}
	}

	//Save the file
	if (Doc.SaveFile(Filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		MessageBox(NULL, "Failed To Save Config File!", "Thunder", MB_OK);
	}

}

void CGUI::LoadWindowState(CWindow* window, std::string Filename)
{
	tinyxml2::XMLDocument Doc;
	if (Doc.LoadFile(Filename.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement *Root = Doc.RootElement();

		if (Root)
		{
			if (Root && window->Tabs.size() > 0)
			{
				for (auto Tab : window->Tabs)
				{
					tinyxml2::XMLElement *TabElement = Root->FirstChildElement(Tab->Title.c_str());
					if (TabElement)
					{
						if (TabElement && Tab->Controls.size() > 0)
						{
							for (auto Control : Tab->Controls)
							{
								if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
								{
									tinyxml2::XMLElement *ControlElement = TabElement->FirstChildElement(Control->FileIdentifier.c_str());

									if (ControlElement)
									{
										CCheckBox* cbx = nullptr;
										CComboBox* cbo = nullptr;
										CKeyBind* key = nullptr;
										CSlider* sld = nullptr;
										CSliderR* sld2 = nullptr;
										CSliderG* sld3 = nullptr;
										CSliderB* sld4 = nullptr;
										CSliderValue* sld5 = nullptr;

										switch (Control->FileControlType)
										{
										case UIControlTypes::UIC_CheckBox:
											cbx = (CCheckBox*)Control;
											cbx->SetState(ControlElement->GetText()[0] == '1' ? true : false);
											break;
										case UIControlTypes::UIC_ComboBox:
											cbo = (CComboBox*)Control;
											cbo->SelectIndex(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_KeyBind:
											key = (CKeyBind*)Control;
											key->SetKey(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_Slider:
											sld = (CSlider*)Control;
											sld->SetValue(atof(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_SliderR:
											sld2 = (CSliderR*)Control;
											sld2->SetValue(atof(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_SliderG:
											sld3 = (CSliderG*)Control;
											sld3->SetValue(atof(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_SliderB:
											sld4 = (CSliderB*)Control;
											sld4->SetValue(atof(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_CSliderValue:
											sld5 = (CSliderValue*)Control;
											sld4->SetValue(atof(ControlElement->GetText()));
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}