#include "Player.h"
#include <gl/gl.h>

Player::Player(float* pos, float* size, const std::string additional_info) :
	Mob(MobType::UNSTATIC, pos, size, additional_info)
{
	this->camera_angle_x = 0;
	this->camera_angle_y = 0;
	this->camera_angle_z = 0;
	this->camera_offset_x = 0;
	this->camera_offset_y = 0;
	this->camera_offset_z = 0;
}


void Player::PlayerControl()
{
//	 Setting offset for camera when F5 clicked once; Setting offset back (X:0, Y:0, Z:0) when clicked again
	if (GetKeyState(VK_F5) == 0) SetCameraOffset(1, 1, -3);
	else SetCameraOffset(0, 0, 0);

//	 Adjusting player's Z position (elevation) whether user pressed SPACE or SHIFT
	if (GetKeyState(VK_SPACE) < 0) Move(new float[3] {0,0, -0.05f}); // Moving UP
	if (GetKeyState(VK_LSHIFT) < 0) Move(new float[3] {0, 0, 0.05f}); // Moving UP

//	 Rotating player's camera
	if (GetKeyState(VK_UP) < 0) this->camera_angle_x += 1.0f;
	if (GetKeyState(VK_DOWN) < 0) this->camera_angle_x += -1.0f;
	if (GetKeyState(VK_LEFT) < 0) this->camera_angle_z += 1.0f;
	if (GetKeyState(VK_RIGHT) < 0) this->camera_angle_z += -1.0f;

}

void Player::CameraMovement()
{
	PlayerControl();

	float angle = -camera_angle_z / 180 * M_PI;
	float speed = 0;
	if (GetKeyState('W') < 0) speed = -0.1;
	if (GetKeyState('S') < 0) speed = 0.1;
	if (GetKeyState('A') < 0) { speed += -0.1; angle -= M_PI * 0.5; }
	if (GetKeyState('D') < 0) { speed += 0.1; angle -= M_PI * 0.5; }

	if (speed != 0)
	{
		this->pos[0] += sin(angle) * speed;
		this->pos[1] += cos(angle) * speed;
	}

	glRotatef(-camera_angle_x, 1, 0, 0);
	glRotatef(-camera_angle_z, 0, 0, 1);
	glTranslatef(this->pos[0] + this->camera_offset_x, this->pos[1] + this->camera_offset_y, this->pos[2] + this->camera_offset_z);
}

void Player::SetCameraOffset(float _offset_x, float _offset_y, float _offset_z)
{
	this->camera_offset_x = _offset_x;
	this->camera_offset_y = _offset_y;
	this->camera_offset_z = _offset_z;
}
