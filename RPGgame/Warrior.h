#pragma once

#include "Hero.h"

class Warrior : public Hero
{
public:
	Warrior(string name) :
		Hero(name, CharacterType::Warrior, 1,
			200, 45, // health
			80, 25, // attack
			80, 20, // protection
			Resistances(0.6f, 0.9f, 1.1f, 1.1f, 1.1f, 0.2f), // resistances
			20, 10, // magic power
			50, 10, // mana
			{ &FistPunch }, // active skills
			{ &PhysicalCrit }, // passive skills
			{ &BattleCry }, // skills list
			Inventory(WeaponSlot(&IronSword))
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Warrior", allocator);
		Hero::ExportInitialData(j, allocator);
	}
};

