#pragma once

#include "Group.h"
#include "Hero.h"
#include "Dungeon.h"

class Game
{
public:
	Hero* hero = nullptr;
	Group* group = nullptr;
	vector<Dungeon*> dungeons;

	int TripsToTheForestCount = 0;
	int CompletedDungeons = 0;
};

