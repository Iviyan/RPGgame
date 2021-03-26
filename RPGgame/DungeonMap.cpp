#include "DungeonMap.h"

Dungeon* DungeonMap::GetDungeon()
{
	if (!executed)
		dungeon = getDungeon();
	return dungeon;
}
