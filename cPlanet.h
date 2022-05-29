#pragma once
#include "framework.h"

class cPlanet
{
	CModel model; // Model

	float Gravity = 0;
    unsigned int Moon_Crust[6], Moon_Mantle[6], Moon_Core[6], Grass_Block[6], Dirt[6], Stone[6], Lava[6], Brick[6], Sun_Crust[6], Sun_Core[6],
                 Mercurius_Crust[6], Mercurius_Mantle[6], Mercurius_Core[6], Venus_Crust[6], Venus_Mantle[6], Venus_Core[6], Mars_Crust[6], Mars_Mantle[6], Mars_Core[6],
                 Jupiter_Crust[6], Saturnus_Crust[6], Uranus_Crust[6], Neptunus_Crust[6];
    unsigned int BlockCode = 0;
    int Orbit = 0; // 공전
    float OrbitX = 0, OrbitY = 0, OrbitZ = 0, OrbitSize = 0;
    std::string Type = "";

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

    struct Sort {
        inline bool operator()(const cBlock* b, const cBlock* b2) {
            return b->Dist < b2->Dist;
        }
    };
    bool BlockLoop = 0;
    std::vector <cBlock*> blocks;

    void CreateBlock(Vec3 poses[], float Size, unsigned int Texture[]) { // Create Block
        cBlock* block = new cBlock(poses, Size, Texture, BlockCode);
        blocks.push_back(block);
        BlockCode++;
    }

    void Reset() { // Reset
        float ox, oy, oz, onx, ony, onz, otx, oty, otz;
        int v_id, vt_id, vn_id;
        blocks.clear();
        for (int o = 0; o < model.objs.size(); o++) {
            int nFaces = model.objs[o].f.size();

            for (int q = Size; q > 0; q--) { // 블록 생성
                for (int k = 0; k < nFaces; k++) {
                    int nPoints = model.objs[o].f[k].v_pairs.size();
                    Vec3 poses[8];
                    for (auto& p : poses) { p.x = CoreX; p.y = CoreY; p.z = CoreZ; }
                    for (int i = 0; i < nPoints; i++) {
                        v_id = model.objs[o].f[k].v_pairs[i].d[0]; vt_id = model.objs[o].f[k].v_pairs[i].d[1]; vn_id = model.objs[o].f[k].v_pairs[i].d[2];
                        ox = model.objs[o].v[v_id - 1].d[0]; oy = model.objs[o].v[v_id - 1].d[1]; oz = model.objs[o].v[v_id - 1].d[2];
                        onx = model.objs[o].vn[vn_id - 1].d[0]; ony = model.objs[o].vn[vn_id - 1].d[1]; onz = model.objs[o].vn[vn_id - 1].d[2];
                        otx = model.objs[o].vt[vt_id - 1].d[0]; oty = model.objs[o].vt[vt_id - 1].d[1];

                        poses[i].x += ox * q; poses[i].y += oy * q; poses[i].z += oz * q;
                        poses[i + 4].x += ox * (q - 1); poses[i + 4].y += oy * (q - 1); poses[i + 4].z += oz * (q - 1);
                    }
                    if (Type == "Earth") { // Type = Earth
                        if (q == Size) CreateBlock(poses, q, Grass_Block);
                        else if (q < Size && q >= Size - 1) CreateBlock(poses, q, Dirt);
                        else if (q < Size - 1 && q >= Size - 4) CreateBlock(poses, q, Stone);
                        else if (q < Size - 4) CreateBlock(poses, q, Lava);
                    }
                    else if (Type == "Moon") { // Type = Moon
                        if (q == Size) CreateBlock(poses, q, Moon_Crust);
                        else if (q < Size && q >= Size - 2) CreateBlock(poses, q, Moon_Mantle);
                        else if (q < Size - 2) CreateBlock(poses, q, Moon_Core);
                    }
                    else if (Type == "Mercurius") { // Type = Mercurius
                        if (q == Size) CreateBlock(poses, q, Mercurius_Crust);
                        else if (q < Size && q >= Size - 3) CreateBlock(poses, q, Mercurius_Mantle);
                        else if (q < Size - 3) CreateBlock(poses, q, Mercurius_Core);
                    }
                    else if (Type == "Venus") { // Type = Venus
                        if (q == Size) CreateBlock(poses, q, Venus_Crust);
                        else if (q < Size && q >= Size - 3) CreateBlock(poses, q, Venus_Mantle);
                        else if (q < Size - 3) CreateBlock(poses, q, Venus_Core);
                    }
                    else if (Type == "Mars") { // Type = Mars
                        if (q == Size) CreateBlock(poses, q, Mars_Crust);
                        else if (q < Size && q >= Size - 3) CreateBlock(poses, q, Mars_Mantle);
                        else if (q < Size - 3) CreateBlock(poses, q, Mars_Core);
                    }
                    if (q == Size + 1) {
                        for (int Y = 0; Y < 3; Y++) {
                            for (auto& p : poses) { p.x = CoreX; p.y = CoreY; p.z = CoreZ; }
                            for (int i = 0; i < nPoints; i++) {
                                v_id = model.objs[o].f[k].v_pairs[i].d[0]; vt_id = model.objs[o].f[k].v_pairs[i].d[1]; vn_id = model.objs[o].f[k].v_pairs[i].d[2];
                                ox = model.objs[o].v[v_id - 1].d[0]; oy = model.objs[o].v[v_id - 1].d[1]; oz = model.objs[o].v[v_id - 1].d[2];
                                onx = model.objs[o].vn[vn_id - 1].d[0]; ony = model.objs[o].vn[vn_id - 1].d[1]; onz = model.objs[o].vn[vn_id - 1].d[2];
                                otx = model.objs[o].vt[vt_id - 1].d[0]; oty = model.objs[o].vt[vt_id - 1].d[1];

                                poses[i].x += ox * (q + Y + 1); poses[i].y += oy * (q + Y + 1); poses[i].z += oz * (q + Y + 1);
                                poses[i + 4].x += ox * (q + Y); poses[i + 4].y += oy * (q + Y); poses[i + 4].z += oz * (q + Y);
                            }
                            CreateBlock(poses, q + Y, Brick);
                       }
                    }
                }
            }
        }
    }

public:// ----------------------------------------------------------------------------------------------  public
    float CoreX, CoreY, CoreZ, OldCoreX, OldCoreY, OldCoreZ; // Core
    float Size = 0;
    cPlanet() {};
	cPlanet(float Size, float CoreX, float CoreY, float CoreZ, std::string Type) : Type(Type), Size(Size), CoreX(CoreX), CoreY(CoreY), CoreZ(CoreZ) { // Init
		std::ifstream file;
        if (Size == 4) file.open("Objects/x3.obj");
        if (Size == 6) file.open("Objects/x5.obj");
        if (Size == 7) file.open("Objects/x6.obj");
        else if (Size == 8) file.open("Objects/x7.obj");
        else if (Size == 9) file.open("Objects/x8.obj");
        else if (Size == 11) file.open("Objects/x10.obj");
        else if (Size >= 41 && this->Type != "Sun" && this->Type != "Jupiter" && this->Type != "Saturnus" && this->Type != "Uranus" && this->Type != "Neptunus") 
            file.open("Objects/x40.obj");
        if (this->Type == "Sun" || this->Type == "Jupiter" || this->Type == "Uranus" || this->Type == "Neptunus") file.open("Objects/x8.obj");
        if (this->Type == "Saturnus")file.open("Objects/x6s.obj");
		model.loadObj(file);
		file.close();

        // Textures //

        // Moon
        for (int i = 0; i < 6; i++) Moon_Crust[i] = FromFile("Images/Textures/3.png");
        for (int i = 0; i < 6; i++) Moon_Mantle[i] = FromFile("Images/Textures/7.png");
        for (int i = 0; i < 6; i++) Moon_Core[i] = FromFile("Images/Textures/4.png");

        // Mercurius
        for (int i = 0; i < 6; i++) Mercurius_Crust[i] = FromFile("Images/Textures/7.png");
        for (int i = 0; i < 6; i++) Mercurius_Mantle[i] = FromFile("Images/Textures/8.png");
        for (int i = 0; i < 6; i++) Mercurius_Core[i] = FromFile("Images/Textures/4.png");

        // Venus
        for (int i = 0; i < 6; i++) Venus_Crust[i] = FromFile("Images/Textures/10.png");
        for (int i = 0; i < 6; i++) Venus_Mantle[i] = FromFile("Images/Textures/3.png");
        for (int i = 0; i < 6; i++) Venus_Core[i] = FromFile("Images/Textures/4.png");

        // Mars
        for (int i = 0; i < 6; i++) Mars_Crust[i] = FromFile("Images/Textures/11.png");
        for (int i = 0; i < 6; i++) Mars_Mantle[i] = FromFile("Images/Textures/8.png");
        for (int i = 0; i < 6; i++) Mars_Core[i] = FromFile("Images/Textures/4.png");

        for (int i = 0; i < 6; i++) Sun_Crust[i] = FromFile("Images/Textures/9.png");
        for (int i = 0; i < 6; i++) Jupiter_Crust[i] = FromFile("Images/Textures/12.png");
        for (int i = 0; i < 6; i++) Saturnus_Crust[i] = FromFile("Images/Textures/13.png");
        for (int i = 0; i < 6; i++) Uranus_Crust[i] = FromFile("Images/Textures/14.png");
        for (int i = 0; i < 6; i++) Neptunus_Crust[i] = FromFile("Images/Textures/15.png");

        for (int i = 0; i < 6; i++) if (i == 0) Grass_Block[i] = FromFile("Images/Textures/0.png");
        else if(i == 5) Grass_Block[i] = FromFile("Images/Textures/2.png"); else Grass_Block[i] = FromFile("Images/Textures/1.png");
        for (int i = 0; i < 6; i++) Dirt[i] = FromFile("Images/Textures/2.png");
        for (int i = 0; i < 6; i++) Stone[i] = FromFile("Images/Textures/3.png");
        for (int i = 0; i < 6; i++) Lava[i] = FromFile("Images/Textures/4.png");
        for (int i = 0; i < 6; i++) Brick[i] = FromFile("Images/Textures/6.png");
        // Create Blocks //
        Reset();
        OldCoreX = CoreX; OldCoreY = CoreY; OldCoreZ = CoreZ;
	}

    void Setting(int Orbit, float OrBitX, float OrBitY, float OrBitZ, float OrbitSize) { // 공전 설정
        this->Orbit = Orbit;
        this->OrbitX = OrbitX;
        this->OrbitY = OrbitY;
        this->OrbitZ = OrbitZ;
        this->OrbitSize = OrbitSize;
    }

    // ---------------------------------------------------------------------------------------------- 
    void UpDate(cPlayer* player, std::vector <cBullet>*bullets) { // UpDate
        bool isTouch = 0;
        bool isDif = 0;// (blocks_Cpy != blocks);

        if ((GetAsyncKeyState('R') & 0x8000)) { // Reset
            for (int b = 0; b < blocks.size(); b++) if (b < blocks.size()) { delete blocks[b]; blocks.erase(blocks.begin() + b); }
            Reset();
        }
        if (Orbit == 1) { // 공전
            float AngleX = std::atan2f(OrbitX - CoreX + OrbitSize, OrbitZ - CoreZ + OrbitSize) * 180 / PI - 90;
            CoreX += std::sin(AngleX / 180 * PI) * .5;
            CoreZ += std::cos(AngleX / 180 * PI) * .5;
        } else if (Orbit == -1) { // 공전
            float AngleX = std::atan2f(OrbitX - CoreX + OrbitSize, OrbitZ - CoreZ + OrbitSize) * 180 / PI - 90;
            CoreX += std::sin(AngleX / 180 * PI) * -.5;
            CoreZ += std::cos(AngleX / 180 * PI) * -.5;
        }
        if (Dis(player->x, player->y, player->z, CoreX, CoreY, CoreZ) < 5000)
        for (register int i = 0; i < blocks.size(); i++) {
            cBlock* b = blocks[i];
            b->Dist = Dis(player->x, player->y, player->z, b->poses[0].x, b->poses[0].y, b->poses[0].z);
            if (Dis(player->x, player->y, player->z, CoreX, CoreY, CoreZ) < 500) {
                float BAngleX = std::atan2f(-(float)b->poses[0].x + CoreX, -(float)b->poses[0].z + CoreZ) * 180 / PI - 180, BAngleY = -b->poses[0].y + CoreY;
                for (auto& b2 : *bullets) 
                    if (Dis(b->poses[0].x, b->poses[0].y, b->poses[0].z, b2.x, b2.y, b2.z) < b->Size / 4 +(b2.Size == 2 || b2.Size == 10 ? b2.Size : 0)) {  // Collision Bullet
                    if (Dis(b->poses[0].x, b->poses[0].y, b->poses[0].z, b2.x, b2.y, b2.z) < b->Size / 4) b2.Dead = 1;
                    b->HP = 0;
                }
                b->Draw();  // 블록
            }
            else {
                if (Dis(player->x, player->y, player->z, CoreX, CoreY, CoreZ) > b->Dist && Dis(b->poses[0].x, b->poses[0].y, b->poses[0].z, CoreX, CoreY, CoreZ) > Size - 1) {
                    b->Draw();  // 블록
                }
            }
            for (auto& p : b->poses) { p.x -= OldCoreX; p.y -= OldCoreY; p.z -= OldCoreZ; p.x += CoreX; p.y += CoreY; p.z += CoreZ; }
        }
        if (Type == "Sun" || Type == "Jupiter" || Type == "Saturnus" || Type == "Uranus" || Type == "Neptunus") DrawAir();
        OldCoreX = CoreX; OldCoreY = CoreY; OldCoreZ = CoreZ;
        for (register int b = 0; b < blocks.size(); b++) if (b < blocks.size()) if (blocks[b]->HP <= 0) { delete blocks[b]; blocks.erase(blocks.begin() + b); }
    }

    void DrawAir() { // 기체로 이루어졌거나 항성일 때
        float ox, oy, oz, onx, ony, onz, otx, oty, otz;
        int v_id, vt_id, vn_id;
        int o = 0;
        for (o = 0; o < model.objs.size(); o++) {
            glPushMatrix();
            glColor4f(1, 1, 1, 1);
            int nFaces = model.objs[o].f.size();
            glTranslatef(CoreX, CoreY, CoreZ);
            glScalef(Size, Size, Size);
            for (int k = 0; k < nFaces; k++) {
                if (Type == "Sun") glBindTexture(GL_TEXTURE_2D, Sun_Crust[0]);
                else if (Type == "Jupiter") glBindTexture(GL_TEXTURE_2D, Jupiter_Crust[0]);
                else if (Type == "Saturnus") glBindTexture(GL_TEXTURE_2D, (o == 0 ? Saturnus_Crust[0] : Jupiter_Crust[0]));
                else if (Type == "Uranus") glBindTexture(GL_TEXTURE_2D, Uranus_Crust[0]);
                else if (Type == "Neptunus") glBindTexture(GL_TEXTURE_2D, Neptunus_Crust[0]);
                glBegin(GL_POLYGON);
                int nPoints = model.objs[o].f[k].v_pairs.size();
                for (int i = 0; i < nPoints; i++) {
                    v_id = model.objs[o].f[k].v_pairs[i].d[0]; vt_id = model.objs[o].f[k].v_pairs[i].d[1]; vn_id = model.objs[o].f[k].v_pairs[i].d[2];
                    ox = model.objs[o].v[v_id - 1].d[0]; oy = model.objs[o].v[v_id - 1].d[1]; oz = model.objs[o].v[v_id - 1].d[2];
                    onx = model.objs[o].vn[vn_id - 1].d[0]; ony = model.objs[o].vn[vn_id - 1].d[1]; onz = model.objs[o].vn[vn_id - 1].d[2];
                    otx = model.objs[o].vt[vt_id - 1].d[0]; oty = model.objs[o].vt[vt_id - 1].d[1];

                    glNormal3f(onx, ony, onz); glTexCoord2f(otx, oty); glVertex3f(ox, oy, oz);
                }
                glEnd();
            }
            glPopMatrix();
        }
    }
};

/*
        concurrency::array_view<cBlock*, 1> block_amp(blocks.size(), blocks);
        concurrency::array_view<cBlock*, 1> block2_amp(blocks.size(), blocks);
        block_amp.discard_data();block2_amp.discard_data();
        concurrency::parallel_for_each(block_amp.extent, [&](concurrency::index<1> idx) restrict(amp)
            {
                //static_cast<cBlock>(*block_amp[idx]).Draw();
            }
        );
*/
