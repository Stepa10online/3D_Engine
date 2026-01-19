#pragma once
#include "Mob.h"

#pragma region Includes

#include "Math.h"

#pragma endregion

class Player : public Mob
{
private:
	float camera_angle_x;
	float camera_angle_y;
	float camera_angle_z;

	float camera_offset_x;
	float camera_offset_y;
	float camera_offset_z;

public:
	Player(float* pos, float* size, const std::string additional_info_to_id = "");

	void PlayerControl();
	void CameraMovement();

	void SetCameraOffset(float _offset_x, float _offset_y, float _offset_z);
	void SetCameraPos(float _position_x, float _position_y, float _position_z);
};

