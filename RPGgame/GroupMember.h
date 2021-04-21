#pragma once

#include "Character.h"
#include "Buff.h"
#include <set>

class GroupMember
{
public:
	struct RecoveringSkill {
		ActiveSkill* skill;
		int remainingSteps;
	};

	void AddBuff(Buff buff);
	void AddDebuff(Buff debuff);
	void Step();

	bool ChooseSkill(ActiveSkill* skill);

	Attack* DoAttack(AttackSkill* skill);
	Buff DoBuff(BuffSkill* skill);

	int GetAttack(Attack*& attack);

	Character* character;
	vector<Buff> buffs = {};
	vector<Buff> debuffs = {};
	vector<ActiveSkill*> availableSkills;
	vector<RecoveringSkill> unavailableSkills = {};
	ActiveSkill* stepSkill = nullptr;

	std::set<GroupMember*> affectedEnemies;

	void UpdateSkills();

	void RestoreStats();

	GroupMember(Character* character) : character(character), availableSkills(character->GetActiveSkills()) {}

private:
	void MarkSkilAsUsed(ActiveSkill* skill);
};

