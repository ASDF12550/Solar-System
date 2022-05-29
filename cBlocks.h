#pragma once    
#include "framework.h"

class cBlock
{
public:
	unsigned int Texture[6];
	Vec3 poses[8], CorePos;
    bool Visible[6] = {1, 1, 1, 1, 1, 1};
	float R = 0, Size = 0, Dist = 0;
    int HP = 10;
    unsigned int Code = 0;
   
    cBlock(Vec3 poses[], float Size, unsigned int Texture[], unsigned int Code) : Size(Size), Code(Code)
        { std::memcpy(this->Texture, Texture, sizeof(this->Texture)); std::memcpy(this->poses, poses, sizeof(this->poses)); R = .9; } // Init


    bool VisibleCollision(Vec3 poses[], Vec3 poses2[], int C) { // Mesh
        bool Visible[6] = { 1,1,1,1,1,1 };
        int Collision_Q[2][6][4] = {
            {{2, 1, 5, 6}, {3, 0, 4, 7}, {2, 3, 7, 6}, {1, 0, 4, 5}, {4, 5, 6, 7}, {0, 1, 2, 3} },
            {{3, 0, 4, 7}, {2, 1, 5, 6}, {1, 0, 4, 5}, {2, 3, 7, 6}, {0, 1, 2, 3}, {4, 5, 6, 7} }
        };
        // 겹치는지 여부
        int k = C;
        bool Pass[4] = { 1,1,1,1 };
        for (int i = 0; i < 4; i++) if (
            (
                poses2[Collision_Q[1][k][i]].x == poses[Collision_Q[0][k][i]].x &&
                poses2[Collision_Q[1][k][i]].y == poses[Collision_Q[0][k][i]].y &&
                poses2[Collision_Q[1][k][i]].z == poses[Collision_Q[0][k][i]].z)
            ) Pass[i] = 0;

        if (!(Pass[0] && Pass[1] && Pass[2] && Pass[3])) { Visible[k] = 0; }

        return Visible[C];
    };


	void Draw() { // Draw
        CorePos.x = 0; for (int i = 0; i < 8; i++) CorePos.x += poses[i].x; CorePos.x /= 8;
        CorePos.y = 0; for (int i = 0; i < 8; i++) CorePos.y += poses[i].y; CorePos.y /= 8;
        CorePos.z = 0; for (int i = 0; i < 8; i++) CorePos.z += poses[i].z; CorePos.z /= 8;
		glPushMatrix();
        glColor4f(R, R, R, 1);
        if (Visible[0]) {
            glBindTexture(GL_TEXTURE_2D, Texture[1]);
            glBegin(GL_QUADS);
            //front
            glTexCoord2f(0, 0);   glVertex3f(poses[2].x, poses[2].y, poses[2].z);
            glTexCoord2f(1, 0);   glVertex3f(poses[1].x, poses[1].y, poses[1].z);
            glTexCoord2f(1, 1);   glVertex3f(poses[5].x, poses[5].y, poses[5].z);
            glTexCoord2f(0, 1);   glVertex3f(poses[6].x, poses[6].y, poses[6].z);
            glEnd();
        }

        if (Visible[1]) {
            glBindTexture(GL_TEXTURE_2D, Texture[2]);
            glBegin(GL_QUADS);
            //back
            glTexCoord2f(0, 0); glVertex3f(poses[3].x, poses[3].y, poses[3].z);
            glTexCoord2f(1, 0); glVertex3f(poses[0].x, poses[0].y, poses[0].z);
            glTexCoord2f(1, 1); glVertex3f(poses[4].x, poses[4].y, poses[4].z);
            glTexCoord2f(0, 1); glVertex3f(poses[7].x, poses[7].y, poses[7].z);
            glEnd();
        }

        if (Visible[2]) {
            glBindTexture(GL_TEXTURE_2D, Texture[3]);
            glBegin(GL_QUADS);
            //left
            glTexCoord2f(0, 0); glVertex3f(poses[2].x, poses[2].y, poses[2].z);
            glTexCoord2f(1, 0); glVertex3f(poses[3].x, poses[3].y, poses[3].z);
            glTexCoord2f(1, 1); glVertex3f(poses[7].x, poses[7].y, poses[7].z);
            glTexCoord2f(0, 1); glVertex3f(poses[6].x, poses[6].y, poses[6].z);
            glEnd();
        }

        if (Visible[3]) {
            glBindTexture(GL_TEXTURE_2D, Texture[4]);
            glBegin(GL_QUADS);
            //right
            glTexCoord2f(0, 0); glVertex3f(poses[1].x, poses[1].y, poses[1].z);
            glTexCoord2f(1, 0); glVertex3f(poses[0].x, poses[0].y, poses[0].z);
            glTexCoord2f(1, 1); glVertex3f(poses[4].x, poses[4].y, poses[4].z);
            glTexCoord2f(0, 1); glVertex3f(poses[5].x, poses[5].y, poses[5].z);
            glEnd();
        }

        if (Visible[4]) {
            glBindTexture(GL_TEXTURE_2D, Texture[5]);
            glBegin(GL_QUADS);
            //bottom
            glTexCoord2f(0, 0); glVertex3f(poses[4].x, poses[4].y, poses[4].z);
            glTexCoord2f(1, 0); glVertex3f(poses[5].x, poses[5].y, poses[5].z);
            glTexCoord2f(1, 1); glVertex3f(poses[6].x, poses[6].y, poses[6].z);
            glTexCoord2f(0, 1); glVertex3f(poses[7].x, poses[7].y, poses[7].z);
            glEnd(); 
        }

        if (Visible[5]) {
            glBindTexture(GL_TEXTURE_2D, Texture[0]);
            glBegin(GL_QUADS);
            //top  		
            glTexCoord2f(0, 0); glVertex3f(poses[0].x, poses[0].y, poses[0].z);
            glTexCoord2f(1, 0); glVertex3f(poses[1].x, poses[1].y, poses[1].z);
            glTexCoord2f(1, 1); glVertex3f(poses[2].x, poses[2].y, poses[2].z);
            glTexCoord2f(0, 1); glVertex3f(poses[3].x, poses[3].y, poses[3].z);
            glEnd();

        }

		glColor4f(1, 1, 1, 1);
		glPopMatrix();
	}
};


