#pragma once

#include "Hero.h"

class Mage : public Hero
{
public:
	Mage(string name) :
		Hero(name, CharacterType::Mage, 1,
			100, 20, // health
			50, 10, // attack
			80, 20, // protection
			Resistances(1.2f, 1.2f, 0.8f, 0.8f, 0.8f, 0.1f), // resistances
			80, 25, // magic power
			150, 40, // mana
			{ &Fireball }, // active skills
			{ &HealthPower }, // passive skills
			{ &WindBarrier }, // skills list
			Inventory(WeaponSlot(&OakStaff))
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Mage", allocator);
		Hero::ExportInitialData(j, allocator);
	}
};

