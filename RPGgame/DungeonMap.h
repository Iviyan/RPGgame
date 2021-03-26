#pragma once

#include "Dungeon.h"

class DungeonMap {
public:
	string Name;
	int Cost;
	Dungeon* GetDungeon();

	DungeonMap(string name, int cost, std::function<Dungeon* ()> getDungeon) : Name(name), Cost(cost), getDungeon(getDungeon) {}
private:
	std::function<Dungeon* ()> getDungeon;
	bool executed = false;
	Dungeon* dungeon = nullptr;
};