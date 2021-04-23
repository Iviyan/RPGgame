#pragma once

#include "Hero.h"

class Archer : public Hero
{
public:
	Archer(string name) : 
		Hero(name, CharacterType::Archer, 1,
			150, 25, // health
			95, 25, // attack
			60, 20, // protection
			Resistances(1.1f, 1.0f, 0.9f, 0.9f, 1.1f, 0.2f), // resistances
			40, 15, // magic power
			65, 20, // mana
			{ &FistPunch }, // active skills
			{ &Evasion }, // passive skills
			{ &RainOfArrows }, // skills list
			Inventory(WeaponSlot(&WoodenBow))
			) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Archer", allocator);
		Hero::ExportInitialData(j, allocator);
	}
};