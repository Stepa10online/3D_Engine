#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <iostream>
#include <string>
#include <array>

#pragma region Includes

#include "Plane.h"

#pragma endregion

#pragma comment(lib, "opengl32.lib")

class Entity
{
protected:
	float pos[3];
	// (for debug) color that diplays position of an entity
	float color[4];
public:
	Entity(float x, float y, float z) 
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		for (int i = 0; i < 4; i++) color[i] = 1.0f;
	}
	Entity(std::array<float, 3> pos)
	{
		this->pos[0] = pos[0];
		this->pos[1] = pos[1];
		this->pos[2] = pos[2];
		for (int i = 0; i < 4; i++) color[i] = 1.0f;
	}

	float* GetPosf();

	// (for debug) color that diplays position of an entity
	void SetColor(float* color);
	void SetColor(float r, float g,float b, float a);


	void Display(float x, float y, float z);
};

