#include "Mob.h"

unsigned int Mob::index = 0;

Mob::Mob(MobType mob_type, float x, float y, float z, const std::string additional_info_to_id) :
	Entity(x, y, z), 
	hitbox(x, y, z, 1, 1, 1)
{
	BuildMob({ additional_info_to_id, GetSTRMobType(mob_type), std::to_string(index).c_str()});
	//MessageBoxA(NULL, this->id.c_str(), "Mob ID", 1);
	index++;
}

Mob::Mob(MobType mob_type, float* pos, float* size, const std::string additional_info_to_id) :
	Entity(pos[0], pos[1], pos[2]),
	hitbox(pos[0], pos[1], pos[2], size[0], size[1], size[2])
{
	BuildMob({ additional_info_to_id, GetSTRMobType(mob_type), std::to_string(index) });
	index++;
}


unsigned int Mob::GetIndex()
{
	return index;
}

void Mob::SetID(std::vector<std::string> build)
{
	for (int i = 0; i < build.size(); i++)
	{
		this->id += build[i];
		if(i+1 != build.size())
			 this->id += '.';
	}
}

std::string Mob::GetSTRMobType(MobType mob_type)
{
	switch (mob_type)
	{
	case Mob::MobType::STANDART:
		return "standart";
		break;
	case Mob::MobType::STATIC:
		return "static";
		break;
	case Mob::MobType::UNSTATIC:
		return "unstatic";
		break;
	default:
		return "UNDECLARED";
		break;
	};
	return ("");
}

void Mob::BuildMob(std::vector<std::string> build)
{
	SetID(build);

	//MessageBoxA(NULL, this->id.c_str(), "Mob Id Display", 1);
}

HitBox& Mob::GetHitBox()
{
	return this->hitbox;
}

Mob& Mob::GetMob()
{
	return *this;
}

void Mob::Move(float* vec)
{
	for (int i = 0; i < 3; i++)
	{
		this->pos[i] += vec[i];
	}
	delete[] vec;
}

void Mob::Move(float* _norm_vec, float _speed)
{
	for (int i = 0; i < 3; i++)
	{
		this->pos[i] += _norm_vec[i] * _speed;
	}
	delete[] _norm_vec;
}

void Mob::Move(float dx, float dy, float dz)
{
	this->pos[0] += dx;
	this->pos[1] += dy;
	this->pos[2] += dz;
}

void Mob::Move(float ndx, float ndy, float ndz, float speed)
{
	this->pos[0] += ndx * speed;
	this->pos[1] += ndy * speed;
	this->pos[2] += ndz * speed;
}

void Mob::DisplayMob(float x, float y, float z, bool display_hitbox)
{
	Display(x, y, z);
	if (display_hitbox)
		hitbox.Display();
}

void Mob::SetPos(float* _pos)
{
	for (int i = 0; i < 3; i++)
	{
		this->pos[i] = _pos[i];
	}
}

void Mob::SetPos(float x, float y, float z)
{
	this->pos[0] += x;
	this->pos[1] += y;
	this->pos[2] += z;
}

std::string Mob::GetID()
{
	return this->id;
}
