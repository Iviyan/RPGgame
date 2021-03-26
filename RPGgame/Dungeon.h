#pragma once

#include "Group.h"

struct Reward {
	int Experience = 0;
	int Gold = 0;
	vector<Artifact*> Artifacts;

	string Message;

	Reward() {}
	Reward(int experience, int gold, vector<Artifact*> artifacts, string message) :
		Experience(experience), Gold(gold), Artifacts(artifacts), Message(message) {}
};

class Dungeon
{
public:
	string Name;
	string Description;
	vector<Group*> Floors;
	Reward Rewards;

	bool Completed = false;

	Dungeon(string name, string description, vector<Group*> floors, Reward rewards = {}) :
		Name(name), Description(description), Floors(floors), Rewards(rewards) {}
};

