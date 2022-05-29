#include "pch.h"
#include "cCore.h"

void cCore::InGame_Screen() { //InGame 일 때
	
	POINT mousexy;
	GetCursorPos(&mousexy);
	double xt = std::round(1500 / 2), yt = std::round(1000 / 2);

	player.AngleX += (xt - mousexy.x) / 4; player.AngleY += (yt - mousexy.y) / 4; // 방향 전환
	SetCursorPos(xt, yt);
	if (player.AngleY < -89.0 + player.Planet_AngleY) player.AngleY = -89 + player.Planet_AngleY;
	if (player.AngleY > 89.0 + player.Planet_AngleY)  player.AngleY = 89 + player.Planet_AngleY;
	

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.02f, 0.01f, 0.00f, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(player.x, player.y, player.z,
		player.x - std::sin((player.AngleX ) / 180 * PI),
		player.y + std::tan((player.AngleY) / 180 * PI),
		player.z - std::cos((player.AngleX) / 180 * PI), 0, 1, 0); // View


	cSkyBox(BG, player.x, player.y, player.z);

	for (auto& b : bullets) b.UpDate();
	for (auto& e : effects) e.UpDate();

	// Planet Setting //

	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000) {
		player.x = sun.CoreX - sun.Size - 500;
		player.y = sun.CoreY;
		player.z = sun.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) {
		player.x = mercurius.CoreX - mercurius.Size - 2;
		player.y = mercurius.CoreY;
		player.z = mercurius.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) {
		player.x = venus.CoreX - venus.Size - 2;
		player.y = venus.CoreY;
		player.z = venus.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000) {
		player.x = earth.CoreX - earth.Size - 2;
		player.y = earth.CoreY;
		player.z = earth.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000) {
		player.x = mars.CoreX - mars.Size - 2;
		player.y = mars.CoreY;
		player.z = mars.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000) {
		player.x = jupiter.CoreX - jupiter.Size - 50;
		player.y = jupiter.CoreY;
		player.z = jupiter.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000) {
		player.x = saturnus.CoreX - saturnus.Size - 50;
		player.y = saturnus.CoreY;
		player.z = saturnus.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000) {
		player.x = uranus.CoreX - uranus.Size - 50;
		player.y = uranus.CoreY;
		player.z = uranus.CoreZ;
	}
	if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000) {
		player.x = neptunus.CoreX - neptunus.Size - 50;
		player.y = neptunus.CoreY;
		player.z = neptunus.CoreZ;
	}
	moon.Setting(1, earth.CoreX, earth.CoreY, earth.CoreZ, 8);

	sun.UpDate(&player, &bullets);
	mercurius.UpDate(&player, &bullets);
	venus.UpDate(&player, &bullets);
	mars.UpDate(&player, &bullets);
	jupiter.UpDate(&player, &bullets);
	saturnus.UpDate(&player, &bullets);
	uranus.UpDate(&player, &bullets);
	neptunus.UpDate(&player, &bullets);
	earth.UpDate(&player, &bullets);
	moon.UpDate(&player, &bullets);
	player.UpDate(&bullets); // Player UpDate

	gameui_manager.UpDate(renderer);// Game UI

	for (int b = 0; b < bullets.size(); b++) if (b < bullets.size()) if (bullets[b].Dead) {
		for (int i = 0; i < 35 + rand() % 2; i++) {
			cEffect effect(&Stone, rand() % 360, rand() % 360, bullets[b].Size/4, bullets[b].x, bullets[b].y, bullets[b].z);
			effect.Size = bullets[b].Size / 4;
			effects.push_back(effect);
		}
		bullets.erase(bullets.begin() + b);
	}

	for (int e = 0; e < effects.size(); e++) if (e < effects.size()) if (bullets[e].Dead) effects.erase(effects.begin() + e);
}
