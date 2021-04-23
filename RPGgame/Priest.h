#pragma once

#include "Ally.h"

class Priest : public Ally
{
public:
	Priest(string name, int level = 1) :
		Ally(name, level,
			100, 30, // health
			40, 15, // attack
			50, 15, // protection
			Resistances(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0), // resistances
			60, 20, // magic power
			120, 40, // mana
			{ &Healing }, // active skills
			{ }, // passive skills
			{ &BlessingOfTheGodOfWar }, // skills list
			Inventory()
		) {}

	void ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
	{
		j.AddMember("Type", "Priest", allocator);
		Ally::ExportInitialData(j, allocator);
	}
};