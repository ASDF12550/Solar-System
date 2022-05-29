#pragma once
#include "framework.h"

class cUI_Manager
{
public:

	cUI_Manager() { }; // Init

	class Button { // Button UI
	public:
		cImage image; // Image
		cText text;   // Text
		int Portal = 0; // Portal
		std::string Type = ""; // Type

		Button(SDL_Renderer* renderer, std::string ImagePath, std::string Text, int Portal, float r, float g, float b) : Portal(Portal) { // Init
			image.Init(ImagePath, renderer);
			text.Init(Text, renderer, [=]()->SDL_Color { SDL_Color color = { r, g, b }; return color; }());
		}

		void Draw(SDL_Renderer* renderer) { // Draw
			image.Draw(renderer);
			text.Draw(renderer);
		}
	};

	class Label { // Label UI
	public:
		cImage image; // Image
		cText text;   // Text
		int Effect = 0;
		std::string Type = ""; // Type

		Label(SDL_Renderer* renderer, std::string ImagePath, std::string Text, int Effect, float r, float g, float b) : Effect(Effect) { // Init
			image.Init(ImagePath, renderer);
			text.Init(Text, renderer, [=]()->SDL_Color { SDL_Color color = { r, g, b }; return color; }());
		}

		void Draw(SDL_Renderer* renderer) { // Draw
			image.Draw(renderer);
			text.Draw(renderer);
		}
	};

	class Text { // Text UI
	public:
		cText text;   // Text
		std::string Type = ""; // Type

		Text(SDL_Renderer* renderer, std::string TextPath, float r, float g, float b) { // Init
			text.Init(TextPath, renderer, [=]()->SDL_Color { SDL_Color color = { r, g, b }; return color; }());
		}

		void Draw(SDL_Renderer* renderer) { // Draw
			text.Draw(renderer);
		}
	};

	void CreateButton(SDL_Renderer* renderer, std::string ImagePath, std::string TextPath, int Portal, float r, float g, float b) { // Create Button
		Button* button = new Button(renderer, ImagePath, TextPath, Portal, r, g, b);
		buttons.push_back(button);
	}

	void CreateLabel(SDL_Renderer* renderer, std::string ImagePath, std::string TextPath, int Portal, float r, float g, float b) { // Create Label
		Label* label = new Label(renderer, ImagePath, TextPath, Portal, r, g, b);
		labels.push_back(label);
	}

	void CreateText(SDL_Renderer* renderer, std::string TextPath, int Portal, float r, float g, float b) { // Create Text
		Text* text = new Text(renderer, TextPath, r, g, b);
		texts.push_back(text);
	}


	std::vector <Button*> buttons; // Button List
	std::vector <Label*> labels;   // Label List
	std::vector <Text*> texts;     // Text List

	~cUI_Manager() {
		buttons.clear();
		labels.clear();
		texts.clear();
	}
};