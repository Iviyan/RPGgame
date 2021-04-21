#pragma once

#include "Skill.h"
#include <functional>
#include "Attacks.h"

enum class ActiveSkillType {
	Attack,
	Buff,
	Debuff
};

class Character;

class ActiveSkill : public Skill
{
public:
	ActiveSkillType Type;
	int StepsToRestore;
	int ManaUsage;
protected:
	ActiveSkill(
		string name, string description, ActiveSkillType type, int stepsToRestore, int manaUsage
	) :
		Skill(name, description),
		Type(type), StepsToRestore(stepsToRestore), ManaUsage(manaUsage) {}
};