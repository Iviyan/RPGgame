#pragma once

#include "ActiveSkill.h"
class AttackSkill : public ActiveSkill
{
public:
	std::function<Attack* (GroupMember* character)> CreateAttack;

	AttackSkill(
		string name, string description, int stepsToRestore, int manaUsage,
		std::function<Attack* (GroupMember* character)> createAttack
	) :
		ActiveSkill(name, description, ActiveSkillType::Attack, stepsToRestore, manaUsage), CreateAttack(createAttack) {}
};

