#pragma once
#include "Entity.h"
#include "HitBox.h"
#include "string.h"
#include <vector>

class Mob : public Entity
{
private:
	std::string id;
	static unsigned int index;
	HitBox hitbox;
	// Model model
protected:
	static unsigned int GetIndex();
	void SetID(std::vector<std::string> build);
public:
	static enum MobType {
		STANDART,
		STATIC,
		UNSTATIC
	};
	Mob(MobType mob_type, float x = 0.0f, float y = 0.0f, float z = 0.0f, const std::string additional_info_to_id = "");
	Mob(MobType mob_type, float* pos, float* size, const std::string additional_info_to_id = "");
	//~Mob() { index--; }

	static std::string GetSTRMobType(MobType mob_type);

	void BuildMob(std::vector<std::string> build);

	HitBox& GetHitBox();
	Mob& GetMob();

	// move by vector
	void Move(float* vec);
	// move by normalized vector and speed
	void Move(float* norm_vec, float speed);
	// move by coords
	void Move(float dx, float dy, float dz);
	// move by normalized coords and speed
	void Move(float ndx, float ndy, float ndz, float speed);

	void DisplayMob(float x, float y, float z, bool display_hitbox);

	void SetPos(float* pos);
	void SetPos(float x, float y, float z);

	std::string GetID();
};