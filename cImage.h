#pragma once
#include "framework.h"

class cImage
{
	SDL_Surface* image = 0;
	SDL_Texture* texture = 0;
	float x = 0, y = 0; // Position
	float ScaleX = 0, ScaleY = 0; // Scale
	float Angle = 0; // Angle
	int Frame = 0; // Frame
	int FrameSize = 1; // Frame Size


	void TextureSetting(SDL_Renderer* renderer, int x, int y, int w, int h, float angle) { // Texture Setting
		SDL_Rect src, dst;
		SDL_Point center;

		src.x = src.y = 0;
		SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h); // Get W H
		src.x = Frame * src.w / FrameSize;
		src.w /= FrameSize;
		dst.x = x; dst.y = y;
		dst.w = w; dst.h = h;

		center.x = w / 2;
		center.y = h / 2;

		SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &center, SDL_FLIP_NONE); // Draw
	}
public:

	cImage() {} // Init

	void Init(std::string Path, SDL_Renderer* renderer) { // Start Setting
		image = IMG_Load(Path.c_str());								// Image Load
		texture = SDL_CreateTextureFromSurface(renderer, image);    // Create Texture From Surface
		SDL_Point size; // Get Size
		SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
		ScaleX = size.x;
		ScaleY = size.y;
	}

	// Get //
	float GetPositionX() { return x; };			// Get PosX
	float GetPositionY() { return y; };			// Get PosY
	float GetWidth() { return ScaleX; };	// Get ScaleX
	float GetHeight() { return ScaleY; };	// Get ScaleY
	float GetAngle() { return Angle; };		// Get Angle
	int   GetFrame() { return Frame; }      // Get Frame

	// Set //
	void SetPosition(float x, float y) { // Set Pos
		this->x = x;
		this->y = y;
	}

	void SetScale(float w, float h) { // Set Scale
		this->ScaleX = w;
		this->ScaleY = h;
	}

	void SetAngle(float Angle) { // Set Angle
		this->Angle = Angle;
	}

	void SetFrame(int Frame, int FrameSize) { // Set Frame
		this->Frame = Frame;
		this->FrameSize = FrameSize;
	}

	void Draw(SDL_Renderer* renderer) { // Draw
		TextureSetting(renderer, x, y, ScaleX, ScaleY, Angle);
	}

	~cImage() { // Close
		SDL_FreeSurface(image);
		SDL_DestroyTexture(texture);
	}
};

