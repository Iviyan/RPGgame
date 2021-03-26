#pragma once

#include <string>

using std::string;

class Skill
{
public:
	string Name;
	string Description = {};

	Skill(string name, string description) : Name(name), Description(description) {}

	virtual ~Skill() {}
};