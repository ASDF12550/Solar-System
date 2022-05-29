#pragma once
#include "framework.h"

class cGameUI_Manager {
	cUI_Manager ui_manager; // UI Manager
	enum ButtonPortal { // Portals 
		NewProject = 0,
		OpenProject = 1,
		Setting = 2,
		Close = 3,
	};
	enum LabelEffect { // Effects
		Title = 0,
	};
	int WinX = 1200, WinY = 800;
public:
	cGameUI_Manager() {} // INit

	void Init(SDL_Renderer* renderer) { // Init Func

	}

	void SetWindowSize(int WinX, int WinY) { // Set Window Size
		this->WinX = WinX;
		this->WinY = WinY;
	}

	int UpDate(SDL_Renderer* renderer) { // UpDate
		int mx = 0, my = 0; Uint32 buttons; SDL_PumpEvents(); buttons = SDL_GetMouseState(&mx, &my); // Get Cursor Pos

		for (auto& l : ui_manager.labels) { // Labels
			switch (l->Effect) { // Label Effect
				// Setting //
			case LabelEffect::Title: l->text.SetPosition(WinX - 355, WinY - 50); l->text.SetScale(40);	 break;
			}
			l->Draw(renderer);
		}

		for (auto& b : ui_manager.buttons) { // Buttons 
			switch (b->Portal) { // Button Portal
				// Setting //
			case ButtonPortal::NewProject: b->text.SetPosition(30, 30); b->text.SetScale(30);		   break; // 0 Type
			case ButtonPortal::OpenProject: b->text.SetPosition(30, 30 + 35 * 1); b->text.SetScale(30); break; // 1 Type
			case ButtonPortal::Setting: b->text.SetPosition(30, 30 + 35 * 2); b->text.SetScale(30);	   break; // 2 Type
			case ButtonPortal::Close: b->text.SetPosition(30, 30 + 35 * 3); b->text.SetScale(30);	   break; // 3 Type 
			}

			if (mx > b->text.GetPositionX() && mx < b->text.GetPositionX() + b->text.GetString().length() * 30 / 1.5 && my > b->text.GetPositionY() && my < b->text.GetPositionY() + 30)
			{ // Collision Mouse
				if (GetKeyState(VK_LBUTTON) & 0x8000) { // Press Left Button
					return b->Portal;
				}
				b->text.SetColor(255, 255, 255);
			}
			else b->text.SetColor(125, 125, 125);

			b->Draw(renderer);
		}

		return -1;
	}
};