#pragma once
#include "framework.h"

class cBullet
{
    CModel model;
	unsigned int Texture;
	float AngleX = 0, AngleY = 0, Speed = 0, LookAngleX = 0, LookAngleY = 0;
public: 
    float Size = .4;
    float x, y, z;
    bool Dead = 0;
	cBullet(unsigned int* Texture, float AngleX, float AngleY, float Speed, float x, float y, float z) 
        : Texture(*Texture), AngleX(AngleX), AngleY(AngleY), Speed(Speed), x(x), y(y), z(z) { // Init
		std::ifstream file;
		file.open("Objects/cube.obj");
		model.loadObj(file);
		file.close();

        LookAngleX = rand() % 360; LookAngleY = rand() % 360;
	}

    void UpDate() { // UpDate
        x -= std::sin(AngleX / 180 * PI) * Speed;
        y += std::tan(AngleY / 180 * PI) * Speed;
        z -= std::cos(AngleX / 180 * PI) * Speed;
        if (LookAngleX < 360) LookAngleX += 2; else LookAngleX = 0;
        if (LookAngleY < 360) LookAngleY += 2; else LookAngleY = 0;

        float ox, oy, oz, onx, ony, onz, otx, oty, otz;
        int v_id, vt_id, vn_id;

        for (int o = 0; o < model.objs.size(); o++) { // Draw
            glPushMatrix();
            int nFaces = model.objs[o].f.size();
            glTranslatef(x, y, z);
            glRotatef(LookAngleX, 0, 1, 0);
            glRotatef(LookAngleY, 0, 0, 1);
            glScalef(Size/2, Size/2, Size/2);
            for (int k = 0; k < nFaces; k++) {
                glBindTexture(GL_TEXTURE_2D, Texture);
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

