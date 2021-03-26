#pragma once

#include "Group.h"

enum class BattleResult {
	Win,
	Dead,
	// TODO: добавить побег
};

class ConsoleBattle
{
public:
	Group* group1;
	Group* group2;
	int step = 0;
	bool drop = true;

	BattleResult Start();

	ConsoleBattle(Group* g1, Group* g2, bool allowDrop = true) : group1(g1), group2(g2), drop(allowDrop) {}
};

