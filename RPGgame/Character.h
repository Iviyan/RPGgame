#pragma once

#include <string>
#include "Inventory.h"
#include "Artifact.h"
#include "Skills.h"
#include "Attacks.h"
#include "Resistances.h"
#include "Buff.h"
#include <vector>

using std::string;
using std::vector;

class Character
{
public:
	string Name;
	bool IsDead() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	int GetLevel() const;
	int GetAttack() const;
	int GetProtection() const;
	Resistances GetResistances() const;
	int GetMagicPower() const;
	//int GetIntellect() const;
	int GetGold() const;
	int GetMana() const;
	int GetMaxMana() const;
	Inventory& GetInventory();
	vector<Artifact*>& GetArtifactsList();

	vector<ActiveSkill*> GetActiveSkills();
	vector<ActiveSkill*>& GetOwnActiveSkills();
	vector<PassiveSkill*>& GetPassiveSkills();

	Buff DoBuff(BuffSkill* skill);

	/// <returns>���������� ����, ��� -1, ���� ����� ���� ������������</returns>
	int GetAttack(Attack*& attack, vector<Buff>* buffs = nullptr);

	/// <returns>true - �������� ���, false - �������� ����</returns>
	bool ReduceHealth(int value);
	/// <param name="value">���-�� / -1 - ��</param>
	void RestoreHealth(int value = -1);

	/// <returns>true - ���� ������� ���������, false - ���� ������������./returns>
	bool TakeMana(int value);
	/// <param name="value">���-�� / -1 - ��</param>
	void RestoreMana(int value = -1);

	/// <returns>true - ������ ����������, false - ������������./returns>
	bool TakeGold(int value);
	void AddGold(int value);

	Character(
		string name,
		int level,
		int initialHealth, int healthPerLevel,
		int initialAttack, int attackPerLevel,
		int initialProtection, int protectionPerLevel,
		Resistances resistances,
		int initialMagicPower, int magicPowerPerLevel,
		int initialMana, int manaPerLevel,
		int gold,
		vector<ActiveSkill*> activeSkills = {},
		vector<PassiveSkill*> passiveSkills = {},
		Inventory inventory = {}
	);

protected:
	int level = 1;
	int health, maxOwnHealth, maxHealth, healthPerLevel;
	int attack, ownAttack, attackPerLevel; // ���������� �����
	int protection, ownProtection, protectionPerLevel;
	Resistances resistances;
	int magicPower, ownMagicPower, magicPowerPerLevel; // ���������� �����
	int mana, maxOwnMana, maxMana, manaPerLevel;

	int gold = 0;
	Inventory inventory;
	vector<ActiveSkill*> activeSkills;
	vector<PassiveSkill*> passiveSkills;

	bool isDead = false;
	virtual void Die();

	void UpdateArtifactDependentProperties();

	friend class GroupMember;
};

