#include "Group.h"
#include "helper.h"

void Group::AddMember(Character* character)
{
	if (character == nullptr) throw std::exception("Объект персонажа должен существовать");
	auto member = new GroupMember(character);
	members.push_back(member);
}

void Group::Step()
{
	for (GroupMember* member : members)
		member->Step();
}

void Group::EndBattle()
{
	for (GroupMember* dead : deads) {
		delete dead->character;
		delete dead;
	}
	deads.clear();
	for (GroupMember* member : members) {
		member->buffs.clear();
		member->debuffs.clear();
		member->UpdateSkills();
		member->affectedEnemies.clear();
	}
}

void Group::RestoreStats()
{
	for (GroupMember* member : members) {
		member->RestoreStats();
	}
}

vector<Buff> Group::DoBuffs()
{
	vector<Buff> buffs;
	for (GroupMember* member : members) {
		if (member->stepSkill == nullptr) continue;
		if (member->stepSkill->Type == ActiveSkillType::Buff) {
			BuffSkill* bskill = dynamic_cast<BuffSkill*>(member->stepSkill);
			Buff buff = member->DoBuff(bskill);
			BuffMembers(buff);
			buffs.push_back(buff);
			member->stepSkill = nullptr;
		}
	}
	return buffs;
}

vector<Buff> Group::DoDebuffs()
{
	vector<Buff> debuffs;
	for (GroupMember* member : members) {
		if (member->stepSkill == nullptr) continue;
		if (member->stepSkill->Type == ActiveSkillType::Debuff) {
			BuffSkill* bskill = dynamic_cast<BuffSkill*>(member->stepSkill);
			debuffs.push_back(member->DoBuff(bskill));
			member->stepSkill = nullptr;
		}
	}
	return debuffs;
}

vector<Attack*> Group::DoAttacks()
{
	vector<Attack*> attacks;
	for (auto it = members.rbegin(); it != members.rend(); it++) {
		GroupMember* member = *it;
		if (member->stepSkill == nullptr) continue;
		if (member->stepSkill->Type == ActiveSkillType::Attack) {
			AttackSkill* askill = dynamic_cast<AttackSkill*>(member->stepSkill);
			attacks.push_back(member->DoAttack(askill));
			member->stepSkill = nullptr;
		}
	}
	return attacks;
}

void Group::ChooseAttacks()
{
	for (GroupMember* member : members) {
		if (member->stepSkill != nullptr) continue;
		int skillsCount = member->availableSkills.size();
		if (skillsCount == 0) continue;

		vector<ActiveSkill*> memberSkills;
		int memberMana = member->character->GetMana();
		for (ActiveSkill* skill : member->availableSkills)
		{
			if (memberMana >= skill->ManaUsage)
				memberSkills.push_back(skill);
		}
		if (memberSkills.size() > 0) {
			auto sel = memberSkills[rnd(0, memberSkills.size() - 1)]; // TODO: улучшить этот момент
			member->ChooseSkill(sel);
		}
	}
}

void Group::BuffMembers(Buff buff)
{
	for (GroupMember* member : members)
		member->AddBuff(buff);
}

void Group::DebuffMembers(Buff buff)
{
	for (GroupMember* member : members)
		member->AddDebuff(buff);
}

vector<GroupMember*> Group::GetAttacks(vector<Attack*>& attacks)
{
	vector<GroupMember*> victims;

	for (auto it = members.rbegin(); it != members.rend(); it++) {
		GroupMember* member = *it;

		for (auto ait = attacks.begin(); ait != attacks.end();) {
			Attack* attack = *ait;

			auto debuffsEditors = attack->debuffsEditors;
			if (member->GetAttack(attack) != -1)
				for (auto& func : debuffsEditors)
					func(member, attack);

			if (attack == nullptr)
				ait = attacks.erase(ait);
			else
				ait++;
			if (member->character->IsDead())
				break;
		}
		victims.push_back(member);

		if (attacks.size() == 0)
			break;
	}

	for (Attack* attack : attacks)
		delete attack;

	return victims;
}

void Group::HideDeads()
{
	for (auto it = members.begin(); it != members.end(); ) {
		if ((*it)->character->IsDead()) {
			deads.push_back((*it));
			it = members.erase(it);
		}
		else {
			++it;
		}
	}
}

Group::Group(string name, vector<Character*> characters) : Name(name)
{
	for (Character* ch : characters)
		if (ch != nullptr)
			AddMember(ch);
}

Group::~Group()
{
	for (GroupMember* gm : deads) {
		delete gm->character;
		delete gm;
	}
	for (GroupMember* gm : members) {
		delete gm->character;
		delete gm;
	}
}
