#pragma once
#include <windows.h>
#include <gl/gl.h>

#pragma comment(lib, "opengl32.lib")
class Plane
{
private:
	float x; float y; float z;
	float w; float h;
	float rx; float ry; float rz;
	float color[4]; //rgba
public:

#pragma region Constructor

	Plane(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f, float h = 1.0f, const float color[4] = NULL) 
		: x(x), y(y), z(z), w(w), h(h), rx(0), ry(0), rz(0)
	{
		if (color == NULL)
			for (int i = 0; i < 4; i++)
				this->color[i] = 1.0f;
		else
			for (int i = 0; i < 4; i++)
				this->color[i] = color[i];
	}

#pragma endregion

#pragma region Public

	void Create(float x, float y, float z, float w = 1., float h = 1., float r = -1.0, float g = -1.0, float b = -1.0, float a = -1.0);
	void Rotate(float rX, float rY, float rZ);
	void Display();

	float* GetCoords();

#pragma endregion

};

