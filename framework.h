#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL/freeglut.h>
#include <amp.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <filesystem>
#include <experimental/filesystem>
#include <windows.h>
#define Dis(x, y, z, dx, dy, dz) sqrt(pow(x - dx, 2) + pow(y - dy, 2) + pow(z - dz, 2))
#define PI 3.141592
struct Vec3 { float x, y, z; Vec3() {}; Vec3(float x, float y, float z) : x(x), y(y), z(z) {}; }; // Vector 3

#include "cBlender.h"
#include "cEffect.h"
#include "cBullet.h"
#include "cPlayer.h"
#include "cBlocks.h"
#include "cPlanet.h"


#include "cText.h"
#include "cImage.h"
#include "UI_Manager.h"

#include "GameUI_Manager.h"

#include "cCore.h"

#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
