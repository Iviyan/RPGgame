#include "GroupMember.h"

void GroupMember::AddBuff(Buff buff)
{
	buffs.push_back(buff);
}

void GroupMember::AddDebuff(Buff debuff)
{
	debuffs.push_back(debuff);
}

void GroupMember::Step()
{
	for (auto iter = buffs.begin(); iter != buffs.end();)
	{
		Buff& b = *iter;
		if (b.remainingSteps == -1) {
			++iter;
			continue;
		}
		if (b.remainingSteps - 1 == 0) {
			iter = buffs.erase(iter);
		}
		else {
			b.remainingSteps--;
			++iter;
		}
	}
	for (auto iter = debuffs.begin(); iter != debuffs.end();)
	{
		Buff& b = *iter;
		if (b.remainingSteps == -1) continue;
		if (b.remainingSteps - 1 == 0) {
			iter = debuffs.erase(iter);
		}
		else {
			b.remainingSteps--;
			++iter;
		}
	}
	for (auto iter = unavailableSkills.begin(); iter != unavailableSkills.end(); )
	{
		RecoveringSkill& skill = *iter;
		if (skill.remainingSteps - 1 == 0) {
			availableSkills.push_back(skill.skill);
			iter = unavailableSkills.erase(iter);
		}
		else {
			skill.remainingSteps--;
			++iter;
		}
	}

	for (Buff& buff : buffs) {
		buff.buff->OnStep(character);
	}
	for (Buff& buff : debuffs) {
		buff.buff->OnStep(character);
	}
	
}

bool GroupMember::ChooseSkill(ActiveSkill* skill)
{
	if (std::find(availableSkills.begin(), availableSkills.end(), skill) != availableSkills.end()) {
		stepSkill = skill;
		return true;
	}
	return false;
}

Attack* GroupMember::DoAttack(AttackSkill* skill)
{
	MarkSkilAsUsed(skill);

	Attack* attack = skill->CreateAttack(this);

	Enhancements& enhancements = character->inventory.GetEnhancements();
	enhancements.EnhanceAttack(attack);

	auto handler = [&](PassiveSkill* pskill) {
		if ((bool)(pskill->SkillAbilities & PassiveSkillAbilities::EditingCreatedAttack)) pskill->EditCreatedAttack(character, attack);
		if ((bool)(pskill->SkillAbilities & PassiveSkillAbilities::EditingReceivedByEnemyAttack)) attack->receivedAttackEditors.push_back(pskill->EditReceivedByEnemyAttack);
		if ((bool)(pskill->SkillAbilities & PassiveSkillAbilities::OnReceivedByEnemyAttack)) attack->debuffsEditors.push_back(pskill->OnReceivedByEnemyAttack);
	};

	for (PassiveSkill* pskill : character->passiveSkills)
		handler(pskill);

	for (Buff& buff : buffs) {
		PassiveSkill* pskill = buff.buff;
		handler(pskill);
	}
	for (Buff& debuff : debuffs) {
		PassiveSkill* pskill = debuff.buff;
		handler(pskill);
	}

	if (character->TakeMana(attack->manaUsage)) {
		return attack;
	}
	else {
		return nullptr;
	}
}

int GroupMember::GetAttack(Attack*& attack)
{
	vector<Buff> allBuffs/*(buffs.size() + debuffs.size())*/;
	allBuffs.insert(allBuffs.end(), buffs.begin(), buffs.end());
	allBuffs.insert(allBuffs.end(), debuffs.begin(), debuffs.end());
	GroupMember* attacker = attack->attacker;
	int d = character->GetAttack(attack, &allBuffs);
	if (d != -1)
		attacker->affectedEnemies.insert(this);
	return d;
}

Buff GroupMember::DoBuff(BuffSkill* skill)
{
	MarkSkilAsUsed(skill);
	return character->DoBuff(skill);
}

void GroupMember::UpdateSkills()
{
	availableSkills = character->GetActiveSkills();
	unavailableSkills.clear();
}

void GroupMember::RestoreStats()
{
	character->RestoreHealth(character->GetMaxHealth());
	character->RestoreMana(character->GetMaxMana());
}

void GroupMember::MarkSkilAsUsed(ActiveSkill* skill)
{
	if (skill->StepsToRestore > 0) {
		auto pos = std::find(availableSkills.begin(), availableSkills.end(), skill);
		if (pos != availableSkills.end()) availableSkills.erase(pos);
		unavailableSkills.push_back({ skill, skill->StepsToRestore + 1 });
	}
}
