#include "HitBox.h"

bool HitBox::GetCurrentCollision(HitBox box2)
{
    return GetCollision({x,y,z,w,d,h},box2);
}

bool HitBox::GetCollision(const HitBox box1, const HitBox box2)
{
    float b1_mn[3] = { box1.x - 1 * box1.w,                 box1.y - 1 * box1.d,                box1.z - 1 * box1.h };
    float b1_mx[3] = { box1.x - 1 * box1.w + box1.w * 2,    box1.y - 1 * box1.d + box1.d * 2,   box1.z - 1 * box1.h + box1.h * 2 };
    float b2_mn[3] = { box2.x - 1 * box2.w,                 box2.y - 1 * box2.d,                box2.z - 1 * box2.h };
    float b2_mx[3] = { box2.x - 1 * box2.w + box2.w * 2,    box2.y - 1 * box2.d + box2.d * 2,   box2.z - 1 * box2.h + box2.h * 2 };

    return (
        b1_mn[0] <= b2_mx[0] && b1_mx[0] >= b2_mn[0] &&
        b1_mn[1] <= b2_mx[1] && b1_mx[1] >= b2_mn[1] &&
        b1_mn[2] <= b2_mx[2] && b1_mx[2] >= b2_mn[2]
        );
}

void HitBox::SetColor(float* color)
{
    for (int i = 0; i < 4; i++)
    {
        this->color[i] = color[i];
    }
    delete[] color;
}

void HitBox::Display()
{
    glPushMatrix();
        glColor4f(this->color[0],this->color[1],this->color[2],this->color[3]);
        glTranslatef(x, y, z);
        glBegin(GL_LINE_LOOP);
            glVertex3f( 1 * w, -1 * d, -1 * h);
            glVertex3f(-1 * w, -1 * d, -1 * h);
            glVertex3f(-1 * w,  1 * d, -1 * h);
            glVertex3f( 1 * w,  1 * d, -1 * h);
        glEnd();
        
        glBegin(GL_LINES);
            glVertex3f( 1 * w, -1 * d, -1 * h);
            glVertex3f( 1 * w, -1 * d,  1 * h);

            glVertex3f(-1 * w, -1 * d, -1 * h);
            glVertex3f(-1 * w, -1 * d,  1 * h);

            glVertex3f(-1 * w,  1 * d, -1 * h);
            glVertex3f(-1 * w,  1 * d,  1 * h);

            glVertex3f( 1 * w,  1 * d, -1 * h);
            glVertex3f( 1 * w,  1 * d,  1 * h);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex3f( 1 * w, -1 * d,  1 * h);
            glVertex3f(-1 * w, -1 * d,  1 * h);
            glVertex3f(-1 * w,  1 * d,  1 * h);
            glVertex3f( 1 * w,  1 * d,  1 * h);
        glEnd();

    glPopMatrix();
}

void HitBox::Update(float* pos, float* size)
{
    // update position
    if (pos != NULL)
    {
        this->x = -pos[0];
        this->y = -pos[1];
        this->z = -pos[2];
    }
    // update size
    if (size != NULL)
    {
        this->w = size[0];
        this->d = size[1];
        this->h = size[2];
    }
    delete[] pos;
    delete[] size;
}

float* HitBox::GetPos()
{
    return new float[3] {this->x, this->y, this->z};
}

float* HitBox::GetSize()
{
    return new float[3] {this->w, this->d, this->h};
}
