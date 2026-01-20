#include "Entity.h"

float* Entity::GetPosf()
{
    return this->pos;
}

void Entity::SetColor(float* color)
{
    for (int i = 0; i < 4; i++)
        this->color[i] = color[i];
    delete[] color;
}

void Entity::SetColor(float r, float g, float b, float a)
{
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
    this->color[3] = a;
}

float dot_product(float* pos1, float* pos2)
{
    return pos1[0] * pos2[0] + pos1[1] * pos2[1] + pos1[2] * pos2[2];
}

float Length(float* vec)
{
    return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}
float* Normalize(float* vec)
{
    float* normalized_vec = new float[3];
    float length = Length(vec);
    normalized_vec[0] = vec[0] / length;
    normalized_vec[1] = vec[1] / length;
    normalized_vec[2] = vec[2] / length;
    return normalized_vec;
}

void Entity::Display(float x, float y, float z)
{
    Plane *ptr_plane = new Plane(pos[0], pos[1], pos[2], 0.2f,0.2f, this->color);

    float* target_pos = new float[3]{ x - pos[0], y - pos[1], z - pos[2] };

    float* direction = Normalize(target_pos);

    float yaw = atan2f(direction[0], direction[1]);
    float pitch = asinf(-direction[2]);

    glPushMatrix();

    ptr_plane->Rotate(-90-(pitch * (180 / 3.14)),0,-(yaw * (180 / 3.14)));


    ptr_plane->Display();
    glPopMatrix();

    delete direction;
    delete ptr_plane;
    delete[] target_pos;
}