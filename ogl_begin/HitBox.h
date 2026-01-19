#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <string>
#pragma comment(lib, "opengl32.lib")
class HitBox
{
private:
	float x;
	float y;
	float z;
	float w; // width
	float d; // depth
	float h; // height
	float color[4];
public:
	HitBox(float x, float y, float z, float w, float d, float h) : x(x), y(y), z(z), w(w), d(d), h(h) 
	{
		for (int i = 0; i < 4; i++)
			color[i] = 1.0f;
	}

	bool GetCurrentCollision(HitBox box2);
	static bool GetCollision(HitBox box1, HitBox box2);

	void SetColor(float* color);

	void Display();
	void Update(float* pos, float* size = NULL);

	float* GetPos();
	float* GetSize();
};

