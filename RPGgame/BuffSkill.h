#pragma once

#include "ActiveSkill.h"
#include "Buff.h"

enum class BuffType {
	Buff,
	Debuff
};

class BuffSkill : public ActiveSkill
{
public:
	std::function<Buff(Character* character)> CreateBuff;

	BuffSkill(
		string name, string description, BuffType buffType, int stepsToRestore, int manaUsage,
		std::function<Buff(Character* character)> createBuff
	) :
		ActiveSkill(name, description, buffType == BuffType::Debuff ? ActiveSkillType::Debuff : ActiveSkillType::Buff, stepsToRestore, manaUsage), 
		CreateBuff(createBuff) {}

};

