#pragma once
#include <vector>

#pragma region Includes
#include "Plane.h"
#include "Entity.h"
#include "Mob.h"
#include "Player.h"
#pragma endregion


class World
{
private:
	std::vector<Plane> planes;
	std::vector<Entity> entities;
	std::vector<Mob> mobs;

	std::vector<Player> players;
public:
	/*
	enum WorldOptions
	{
		DO_NOT_ADD_ANOTHER_ID
	};
	*/

	World() {}

#pragma region VecsIncrease

	void AddPlane(float x, float y, float z, float w = 1.0f, float h = 1.0f, const float color[4] = NULL);
	void AddPlane(Plane plane);
	void AddEntity(float x, float y, float z);
	void AddEntity(Entity entity);
	void AddMob(float x, float y, float z, Mob::MobType mob_type);
	void AddMob(Mob mob, const std::string mob_id);
	void AddMob(Mob mob, Mob::MobType mob_type);

#pragma endregion

#pragma region VecsDecrease

	void DeletePlane(float x, float y);
	void KillMob(std::string id);

#pragma endregion

#pragma region Edit

	Mob& EditMob(int i);
	Mob& EditMob(std::string id);

#pragma endregion

#pragma region Mob

	unsigned int GetMobAmount();
	Mob* GetMob(const std::string _id);
	Mob* GetMob(const unsigned int _index);

#pragma endregion


#pragma region Display

	void DisplayAxes(bool over = false);
	void DisplayPlanes();
	void DisplayEntities(float x, float y, float z);
	void DisplayMobs(float x, float y, float z, bool show_bitbox = false);

#pragma endregion

#pragma region Updates

	void UpdateHitboxes();

#pragma endregion


};

