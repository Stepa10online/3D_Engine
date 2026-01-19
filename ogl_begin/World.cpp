#include "World.h"

void World::AddPlane(float x, float y, float z, float w, float h, const float color[4])
{
	planes.push_back({ x,y,z,w,h,color });
}

void World::AddPlane(Plane plane)
{
	planes.push_back(plane);
}

void World::DeletePlane(float x, float y)
{
	for (auto it_planes = planes.begin(); it_planes != planes.end(); it_planes++)
	{
		if (it_planes->GetCoords() == new float[2] {x, y})
		{
			planes.erase(it_planes);
		}
	}
}

void World::KillMob(std::string id)
{
	for (auto it_mobs = mobs.begin();
		it_mobs != mobs.end();
		it_mobs++)
	{
		if (it_mobs->GetID() == id)
		{
			mobs.erase(it_mobs);
			return;
		}
	}
}

void World::AddEntity(float x, float y, float z)
{
	Entity *ptr_entity = new Entity(x,y,z);
	ptr_entity->SetColor(new float[4] {1, 0, 1, 1});
	entities.push_back(*ptr_entity);
	delete ptr_entity;
}

void World::AddEntity(Entity entity)
{
	entity.SetColor(new float[4] {1, 0, 1, 1});
	entities.push_back(entity);
}

void World::AddMob(float x, float y, float z, Mob::MobType mob_type)
{
	Mob *ptr_mob = new Mob(mob_type, x,y,z);

	ptr_mob->SetColor(new float[4] {1, 0, 0, 1});
	mobs.push_back(*ptr_mob);
	delete ptr_mob;
}

void World::AddMob(Mob mob, const std::string mob_id)
{
	std::string str_mob_type = mob_id;

	mob.SetColor(new float[4] { 1, 0, 0, 1 });
	mobs.push_back(mob);
}

void World::AddMob(Mob mob, Mob::MobType mob_type)
{
	std::string str_mob_type = Mob::GetSTRMobType(mob_type);

	mob.BuildMob({ str_mob_type });
	mob.SetColor(new float[4]{ 1,0,0,1 });
	mobs.push_back(mob);
}

Mob& World::EditMob(int _i)
{
	return this->mobs[_i];
}

Mob& World::EditMob(std::string _id)
{
	for (int i = 0; i < mobs.size(); i++)
	{
		if (this->mobs[i].GetID() == _id)
			return this->mobs[i];
	}
}

#pragma region Mob

	unsigned int World::GetMobAmount()
	{
		return this->mobs.size();
	}

	Mob* World::GetMob(const std::string _id)
	{
		for (int i = 0; i < this->mobs.size(); i++)
		{
			if (this->mobs[i].GetID() == _id)
			{
				return &mobs[i];
			}
		}
		return NULL;
	}

	Mob* World::GetMob(const unsigned int _index)
	{
		if (_index >= this->mobs.size())
		{
			std::wstring s = L"Выход за пределы массива\nкласс: World\nфункция: World::GetMob(const unsigned int _index)\nиз-за: _index = " + std::to_wstring(_index) + L"\nстрока: 112";
			MessageBoxW(NULL, s.c_str(), L"Critical Error> Out Of Range", 1);
			//throw OSS_OUT_OF_RANGE;
			return NULL;
		}
		else
			return &mobs[_index];
	}

#pragma endregion

void World::DisplayAxes(bool over)
{
	if (over)
		glDisable(GL_DEPTH_TEST);

	glPushMatrix();
		glBegin(GL_LINES);
			glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // X
			glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // Y
			glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // Z
		glEnd();
	glPopMatrix();

	if (over)
		glEnable(GL_DEPTH_TEST);
}

void World::DisplayPlanes()
{
	for (int i = 0; i < planes.size(); i++)
	{
		planes[i].Display();
	}
}

void World::DisplayEntities(float x, float y, float z)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i].Display(x,y,z);
	}
}

void World::DisplayMobs(float x, float y, float z, bool show_hitbox)
{
	for (int i = 0; i < mobs.size(); i++)
	{
		mobs[i].DisplayMob(x,y,z, show_hitbox);
	}
}

void World::UpdateHitboxes()
{
	for (int i = 0; i < mobs.size(); i++)
	{
		mobs[i].GetHitBox().Update(mobs[i].GetPosf());
	}
}