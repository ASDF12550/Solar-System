#pragma once
#include "framework.h"

class cPlayer
{
public:
	float Speed = 1, AngleX = 0, AngleY = 0; // View
	float Planet_AngleX = 0, Planet_AngleY = 0, Planet_AngleZ = 0; // Planet Angle
	float x, y, z, Px = 0, Py = 0, Pz = 0; // Pos
	bool isMouseLeft = 0; // Mouse
	int Mode = 0, Delay = 0;
	unsigned int Texture;
	cPlayer(float x, float y, float z) : x(x), y(y), z(z) { // init
	}

	void UpDate(std::vector <cBullet>* bullets) { // UpDate
		// Move //
		switch (Mode) {
		case 0: {
			if (GetAsyncKeyState('W') & 0x8000) {
				x -= std::sin(AngleX / 180 * 3.141592) * Speed;
				z -= std::cos(AngleX / 180 * 3.141592) * Speed;
			} if (GetAsyncKeyState('S') & 0x8000) {
				x += std::sin(AngleX / 180 * 3.141592) * Speed;
				z += std::cos(AngleX / 180 * 3.141592) * Speed;
			} if (GetAsyncKeyState('A') & 0x8000) {
				x += std::sin((AngleX - 90) / 180 * 3.141592) * Speed;
				z += std::cos((AngleX - 90) / 180 * 3.141592) * Speed;
			} if (GetAsyncKeyState('D') & 0x8000) {
				x += std::sin((AngleX + 90) / 180 * 3.141592) * Speed;
				z += std::cos((AngleX + 90) / 180 * 3.141592) * Speed;
			} if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				y += Speed;
			} if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
				y -= Speed;
			}

			// Movement Speed //
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				if (Speed < 600) Speed++; else Speed = 600;
			} if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				if (Speed > 0.05) Speed -= .05; else Speed = 0.05;
			} if (GetAsyncKeyState(VK_F1) & 0x8000) {
				Speed = 1;
			}
		}
			break;
		case 1: break;
		}

		if (Delay > 0) Delay--;
		if (((GetKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState('E') & 0x8000)) && Delay == 0 && bullets->size() < 10){ // Fire Bullet 
			cBullet bullet(&Texture, AngleX, AngleY, 1, x, y, z);
			bullets->push_back(bullet);
			Delay = 35;
		}
		if (((GetKeyState(VK_MBUTTON) & 0x8000) || (GetAsyncKeyState('T') & 0x8000)) && Delay == 0 && bullets->size() < 10) { // Fire Bullet 
			cBullet bullet(&Texture, AngleX, AngleY, 1, x, y, z);
			bullet.Size = 10;
			bullets->push_back(bullet);
			Delay = 35;
		}
		if (((GetKeyState(VK_RBUTTON) & 0x8000) || (GetAsyncKeyState('Q') & 0x8000)) && Delay == 0 && bullets->size() < 10) { // Fire Bullet 
			cBullet bullet(&Texture, AngleX, AngleY, 1, x, y, z);
			bullet.Size = 2;
			bullets->push_back(bullet);
			Delay = 35;
		}
		if (GetAsyncKeyState('P') & 0x8000) bullets->clear();

		for (auto& b : *bullets) if (Dis(b.x, b.y, b.z, x, y, z) > 300) b.Dead = 1;
	}
};

