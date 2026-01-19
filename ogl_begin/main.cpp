#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <random>

#pragma comment(lib, "opengl32.lib")

#pragma region Includes

#include "Math.h"
#include "World.h"
#include "Player.h"

#pragma endregion

// git test 

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	srand(time(NULL));

	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;

	// Rotation "constants'
	float alpha = 0.0f;
	float theta = 0.0f;
	float sigma = 0.0f;

	// Setting Player: POS and SIZE for Mob
	const float POS[3] = { 0,0,0 };
	const float SIZE[3] = { 1,1,1 };
	Player player(new float[3] {POS[0], POS[1], POS[2]}, new float[3] {SIZE[0], SIZE[1], SIZE[2]}, "player");

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* create main window */
	hwnd = CreateWindowEx(0,
		"GLSample",
		"OpenGL Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		1024,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, nCmdShow);

	/* enable OpenGL for the window */
	EnableOpenGL(hwnd, &hDC, &hRC);
	glEnable(GL_DEPTH_TEST);
	glFrustum(-1,1, -1,1, 1,128);

	World world;
	for (int i = -11; i < 10; i++)
	{
		for (int j = -11; j < 10; j++)
		{
			Plane* ptr_plane = new Plane;
			if (i == 0 && j == 0)
				ptr_plane->Create(i, j, 0, 0.5, 0.5, 1, 0, 1, 1);
			else
				ptr_plane->Create(i, j, 0, 0.5, 0.5, i % 2, (j + i) % 2, (j * i) % 2, 1);

			world.AddPlane(*ptr_plane);

			delete ptr_plane;
		}
	}
	
	// Adding player_mob to world
	world.AddMob(player.GetMob(), player.GetID());
	//MessageBox(NULL, world.GetMob(player.GetID())->GetID().c_str(), "Info", 1);
	//MessageBox(NULL, player.GetID().c_str(), "Info", 1);
	//world.GetMob(player.GetID())->SetPos(0,5,0);

	// Adding 1 Mob and Editing it to stay at current place
	world.AddMob(0, -0.33, -1, Mob::MobType::UNSTATIC);
	world.EditMob(1).GetHitBox().Update(NULL, new float[3] {0.25, 0.25, 0.25});

	// Adding more mobs to the world
	for (int i = -6; i < 6; i++)
		for (int j = -6; j < 6; j++)
		{
			world.AddMob(i * 2, j * 2, -5, Mob::MobType::STATIC);
		}


	/* program main loop */
	while (!bQuit)
	{
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/* OpenGL animation code goes here */

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glPushMatrix();

			player.CameraMovement();
			
			world.GetMob(player.GetID())->SetPos(player.GetPosf());
			
			for (int i = 1; i < world.GetMobAmount(); i++)
			{
				if (HitBox::GetCollision(world.EditMob(0).GetHitBox(), world.EditMob(i).GetHitBox()))
				{
					world.EditMob(0).GetHitBox().SetColor(new float[4] {0, 1, 0, 1});
					world.EditMob(i).GetHitBox().SetColor(new float[4] {0, 1, 0, 1});
					world.EditMob(0).SetColor(new float[4] {0, 1, 0, 1});
					world.EditMob(i).SetColor(new float[4] {0, 1, 0, 1});
					if (GetKeyState(VK_DELETE) < 0)
					{
						std::string mob_id = world.EditMob(i).GetID();
						//MessageBoxA(NULL, mob_id.c_str(), "Mob ID", 1);
						world.KillMob(mob_id);
						break;
					}
				}
				else
				{
					world.EditMob(0).GetHitBox().SetColor(new float[4] {1, 1, 1, 1});
					world.EditMob(i).GetHitBox().SetColor(new float[4] {1, 1, 1, 1});
					world.EditMob(0).SetColor(new float[4] {1, 1, 1, 1});
					world.EditMob(i).SetColor(new float[4] {1, 1, 1, 1});	
				}
			}

			
			
			// Displaying map
			world.DisplayPlanes();

			// Displaying entites
			world.DisplayEntities(player.GetPosf()[0], player.GetPosf()[1], player.GetPosf()[2]);

			// Displaying mobs
			static const bool SHOW_HITBOX = true;
			world.DisplayMobs(player.GetPosf()[0], player.GetPosf()[1], player.GetPosf()[2], SHOW_HITBOX);

			// Displaying axes (3)
			world.DisplayAxes(1);
			

			world.UpdateHitboxes();

			glPopMatrix();

			SwapBuffers(hDC);


			theta += 1.0f;
			Sleep(1);
		}
	}

	/* shutdown OpenGL */
	DisableOpenGL(hwnd, hDC, hRC);

	/* destroy the window explicitly */
	DestroyWindow(hwnd);

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}

