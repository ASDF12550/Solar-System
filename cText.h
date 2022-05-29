#pragma once
#include "framework.h"

class cText
{
	SDL_Surface* surface = 0;
	SDL_Texture* texture = 0;
	TTF_Font* font = TTF_OpenFont("Font/NanumGothicExtraBold.ttf", 64);
	float x = 0, y = 0; // Position
	float Scale = 0; // Scale
	float Angle = 0; // Angle
	std::string Text = ""; // Text
	SDL_Color* color, new_Color, old_Color, Next_Color; // Color

	void TextSetting(SDL_Renderer* renderer, int x, int y, int w, int h) { // Texture Setting
		SDL_Rect rect = { x, y, w * Text.length() / 1.5, h };
		if (color->r != Next_Color.r && color->g != Next_Color.g && color->b != Next_Color.b) {
			surface = TTF_RenderText_Solid(font, Text.c_str(), *this->color);	// Text Load
			texture = SDL_CreateTextureFromSurface(renderer, surface); // Create Texture From Surface
			Next_Color = *color;
		}
		SDL_RenderCopy(renderer, texture, NULL, &rect);

	}
public:

	cText() {}; // Init

	void Init(std::string Text, SDL_Renderer* renderer, SDL_Color color) { // Start Setting
		new_Color = old_Color = color;
		this->color = &new_Color;
		this->Text = Text;
		surface = TTF_RenderText_Solid(font, Text.c_str(), *this->color);	// Text Load
		texture = SDL_CreateTextureFromSurface(renderer, surface); // Create Texture From Surface
	}

	// Get //
	float GetPositionX() { return x; };			// Get PosX
	float GetPositionY() { return y; };			// Get PosY
	float GetScale() { return Scale; };	// Get Scale
	float GetAngle() { return Angle; };		// Get Angle
	std::string GetString() { return Text; };// Get Text
	SDL_Color GetColor() { return *color; }; // Get Color
	SDL_Color GetOldColor() { return old_Color; }; // Get Old Color

	// Set //
	void SetPosition(float x, float y) { // Set Pos
		this->x = x;
		this->y = y;
	}

	void SetScale(float s) { // Set Scale
		this->Scale = s;
	}

	void SetAngle(float Angle) { // Set Angle
		this->Angle = Angle;
	}

	void SetString(std::string text) { // Set Text
		this->Text = text;
	}

	void SetColor(float r, float g, float b) { // Set Color
		*color = [=]()->SDL_Color { SDL_Color color = { r, g, b }; return color; }();
	}

	void Draw(SDL_Renderer* renderer) { // Draw
		TextSetting(renderer, x, y, Scale, Scale);
	}

	~cText() { // Close
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
	}
};

