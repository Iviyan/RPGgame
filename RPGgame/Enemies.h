#pragma once

#include "Character.h"
#include "GameArtifacts.h"

class Zombie : public Character
{
public:
	Zombie(string name, int level) :
		Character(name, level,
			100, 20, // health
			70, 15, // attack
			50, 20, // protection
			Resistances(0.9f, 0.8f, 1.1f, 1.2f, 1.0f, 2.0f),
			0, 0, // magic power
			0, 0, // mana
			34 + 5 * level, // gold
			vector<ActiveSkill*>({ &Bite })
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Zombie", allocator);
		Character::ExportInitialData(j, allocator);
	}
};


class Skeleton : public Character
{
public:
	Skeleton(string name, int level) :
		Character(name, level,
			80, 20, // health
			60, 15, // attack
			55, 20, // protection
			Resistances(1.2f, 0.5f, 0.5f, 0.5f, 1.0f, 2.0f),
			0, 0, // magic power
			0, 0, // mana
			34 + 5 * level, // gold
			{},
			{},
			Inventory(WeaponSlot(&IronSword))
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Skeleton", allocator);
		Character::ExportInitialData(j, allocator);
	}
};

class Goblin : public Character
{
public:
	Goblin(string name, int level) :
		Character(name, level,
			90, 20, // health
			70, 15, // attack
			45, 20, // protection
			Resistances(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.4f),
			0, 0, // magic power
			0, 0, // mana
			34 + 5 * level, // gold
			{},
			{},
			Inventory(WeaponSlot(&IronDagger))
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Goblin", allocator);
		Character::ExportInitialData(j, allocator);
	}
};

class StoneGolem : public Character
{
public:
	StoneGolem(string name, int level) :
		Character(name, level,
			300, 60, // health
			90, 30, // attack
			80, 30, // protection
			Resistances(0.7f, 1.0f, 1.4f, 0.3f, 1.0f, 1.5f),
			60, 25, // magic power
			120, 45, // mana
			100 + 20 * level, // gold
			{ &FistPunch, &StoneSpears},
			{}
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "StoneGolem", allocator);
		Character::ExportInitialData(j, allocator);
	}
};

class Apostle : public Character
{
public:
	Apostle(string name, int level) :
		Character(name, level,
			250, 50, // health
			110, 35, // attack
			50, 20, // protection
			Resistances(1.2f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
		    80, 30, // magic power
			200, 50, // mana
			200 + 100 * level, // gold
			{  },
			{ &LightBarrierBuff },
			Inventory(WeaponSlot(&LightingSpear))
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Apostle", allocator);
		Character::ExportInitialData(j, allocator);
	}
};