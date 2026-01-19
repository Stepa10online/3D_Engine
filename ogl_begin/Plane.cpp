#include "Plane.h"

void Plane::Create(float x, float y, float z, float w, float h, float r, float g, float b, float a)
{
	this->x = x; this->y = y; this->z = z;
	this->w = w; this->h = h;
	if(r == -1.0f)
	{
		this->color[0] = 1.0f;
		this->color[1] = 1.0f;
		this->color[2] = 1.0f;
		this->color[3] = 1.0f;
	}
	else
	{
		this->color[0] = r;
		this->color[1] = g;
		this->color[2] = b;
		this->color[3] = a;
	}
}

void Plane::Rotate(float rX, float rY, float rZ)
{
	this->rx = rX;
	this->ry = rY;
	this->rz = rZ;
}


void Plane::Display()
{
	glColor4f(color[0], color[1], color[2], color[3]);
	glPushMatrix();
		glTranslatef(-this->x, -this->y, -this->z);
		glRotatef(this->rz, 0, 0, 1);
		glRotatef(this->ry, 0, 1, 0);
		glRotatef(this->rx, 1, 0, 0);

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(-1.0f * w, 1.0f * h);
		glVertex2f(1.0f * w, 1.0f * h);
		glVertex2f(1.0f * w, -1.0 * h);
		glVertex2f(-1.0f * w, -1.0 * h);
		glEnd();
	glPopMatrix();
}

float* Plane::GetCoords()
{
	return new float[3] {this->x, this->y, this->z};
}
