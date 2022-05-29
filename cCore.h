#pragma once
#include "framework.h"

class cCore
{
	// Window //
	SDL_Window* window; // Window
	SDL_Renderer* renderer;     // Renderer
	SDL_Surface* surface = 0;   // Surface
	bool Running = 1; // Running
	enum WinScr { InGame = 0, Pause = 1, Setting = 2 }; // Screen
	int Screen = 0;
	// Lists //
	std::vector <cBullet> bullets;
	std::vector <cEffect> effects;
	cPlayer player{0, 0, 0}; // Player
	cPlanet earth{9, 5, -10, 5, "Earth"};
	cPlanet sun{ 1080, 38500, -10, 5, "Sun"};
	cPlanet moon{ 4, 250, -10, 5, "Moon"}; 
	cPlanet mercurius{ 6, 23500, -10, 5, "Mercurius" };
	cPlanet venus{ 6, 10500, -10, 705, "Venus" };
	cPlanet mars{ 7, -10500, -10, -705, "Mars" };
	cPlanet jupiter{ 100, -20500, -10, -1705, "Jupiter" };
	cPlanet saturnus{ 90, -30100, -10, 205, "Saturnus" };
	cPlanet uranus{ 50, -48000, -10, -5, "Uranus" };
	cPlanet neptunus{ 48, -52400, -10, 105, "Neptunus" };
	// Manager //
	cGameUI_Manager gameui_manager; // GameUI

	// Texture //
	unsigned int Stone, Player_Tex[6];

	unsigned int FromFile(std::string filepath) { // Load File
		unsigned int ID = 0;
		SDL_Surface* texture = IMG_Load(filepath.c_str());
		int Mode = (texture->format->BitsPerPixel >= 4) ? GL_RGBA : GL_RGB;
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, texture->w, texture->h, 0, Mode, GL_UNSIGNED_BYTE, texture->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		SDL_FreeSurface(texture);

		return ID;
	}
	unsigned int BG;
	void cSkyBox(unsigned int BG, float x, float y, float z) { // Sky Box
		glPushMatrix();
		glTranslatef(x, y, z);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, BG);
		glBegin(GL_QUADS);
		//front
		glTexCoord2f(0, 0);   glVertex3f(-200.f, -200.f, -200.f); glTexCoord2f(1, 0);   glVertex3f(200.f, -200.f, -200.f); glTexCoord2f(1, 1);   glVertex3f(200.f, 200.f, -200.f);
		glTexCoord2f(0, 1);   glVertex3f(-200.f, 200.f, -200.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, BG);
		glBegin(GL_QUADS);
		//back
		glTexCoord2f(0, 0); glVertex3f(200.f, -200.f, 200.f); glTexCoord2f(1, 0); glVertex3f(-200.f, -200.f, 200.f); glTexCoord2f(1, 1); glVertex3f(-200.f, 250.f, 200.f);
		glTexCoord2f(0, 1); glVertex3f(200.f, 200.f, 200.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, BG);
		glBegin(GL_QUADS);
		//left
		glTexCoord2f(0, 0); glVertex3f(-250.f, -250.f, 250.f); glTexCoord2f(1, 0); glVertex3f(-250.f, -250.f, -250.f); glTexCoord2f(1, 1); glVertex3f(-250.f, 250.f, -250.f);
		glTexCoord2f(0, 1); glVertex3f(-250.f, 250.f, 250.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, BG);
		glBegin(GL_QUADS);
		//right
		glTexCoord2f(0, 0); glVertex3f(250.f, -250.f, -250.f); glTexCoord2f(1, 0); glVertex3f(250.f, -250.f, 250.f); glTexCoord2f(1, 1); glVertex3f(250.f, 250.f, 250.f);
		glTexCoord2f(0, 1); glVertex3f(250.f, 250.f, -250.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, BG);
		glBegin(GL_QUADS);
		//bottom
		glTexCoord2f(0, 0); glVertex3f(-250.f, -250.f, 250.f); glTexCoord2f(1, 0); glVertex3f(250.f, -250.f, 250.f); glTexCoord2f(1, 1); glVertex3f(250.f, -250.f, -250.f);
		glTexCoord2f(0, 1); glVertex3f(-250.f, -250.f, -250.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, BG);
		glBegin(GL_QUADS);
		//top  		
		glTexCoord2f(0, 0); glVertex3f(-250.f, 250.f, -250.f); glTexCoord2f(1, 0); glVertex3f(250.f, 250.f, -250.f); glTexCoord2f(1, 1); glVertex3f(250.f, 250.f, 250.f);
		glTexCoord2f(0, 1); glVertex3f(-250.f, 250.f, 250.f);
		glEnd();
		glColor3f(1, 1, 1);
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
public:
	cCore(SDL_Window* window) : window(window) { // Init
		std::srand(time(NULL));
		SDL_ShowCursor(false);

		glEnable(GL_DEPTH_TEST); glDepthMask(GL_TRUE); glClearDepth(1.f);
		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW); glEnable(GL_DEPTH); glCullFace(GL_BACK);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.f, 1.3, .1f, 70000.f);
		glEnable(GL_TEXTURE_2D);


		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		SetCursorPos(1500 / 2, 1000 / 2);


		// Renderer //
		renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

		gameui_manager.Init(renderer);

		// °øÀü //
		//moon.Setting(1, 5, -10, 5, 8);
		//mercurius.Setting(1, 38500, -10, 5, 960);
		//venus.Setting(-1, 38500, -10, 5, 960);
		//mars.Setting(1, 38500, -10, 5, 960);
		//earth.Setting(-1, 38500, -10, 5, 960);
		//jupiter.Setting(1, 38500, -10, 5, 960);
		//saturnus.Setting(-1, 38500, -10, 5, 960);
		player.Texture = Stone = FromFile("Images/Textures/5.png");

		BG = FromFile("Images/BG/1.png");

		Looping();
	}

	void InGame_Screen(); // InGame 

	void Looping() { // Loop
		while (Running) {
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) Running = 0; // Close Button
			}

			switch (Screen) { // Screen
				case WinScr::InGame: InGame_Screen(); break;
			}
			//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			//SDL_RenderClear(renderer);
			//
			//SDL_RenderPresent(renderer);
			SDL_GL_SwapWindow(window);
		}
	}

	~cCore(){ // Close
		SDL_DestroyWindow(window);
	}
};

