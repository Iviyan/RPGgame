#pragma once

#include "Ally.h"

class Paladin : public Ally
{
public:
	Paladin(string name, int level = 1) :
		Ally(name, level,
			150, 40, // health
			70, 25, // attack
			80, 20, // protection
			Resistances(1.0f, 1.0f, 1.1f, 1.1f, 1.0f, 0), // resistances
			60, 20, // magic power
			120, 35, // mana
			{  }, // active skills
			{  }, // passive skills
			{}, // skills list
			Inventory(WeaponSlot(&SwordOfLight, &ShieldOfLight))
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Paladin", allocator);
		Ally::ExportInitialData(j, allocator);
	}
};