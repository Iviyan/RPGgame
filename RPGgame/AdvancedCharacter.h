#pragma once

#include "Character.h"

class AdvancedCharacter : public Character
{
public:
	AdvancedCharacter(
		string name,
		int level,
		int initialHealth, int healthPerLevel,
		int initialAttack, int attackPerLevel,
		int initialProtection, int protectionPerLevel,
		Resistances resistances,
		int initialMagicPower, int magicPowerPerLevel,
		int initialMana, int manaPerLevel,
		int initialGold,
		vector<ActiveSkill*> activeSkills = {},
		vector<PassiveSkill*> passiveSkills = {},
		vector<Skill*> skillsList = {},
		Inventory inventory = {}

	);

	/// <returns>Изменился уровень или нет</returns>
	bool AddExperience(int value);
	int GetExperience() const;
	int GetRequiredExperience();

protected:
	int experience = 0;
	static constexpr int initialRequiredExperience = 100;
	static constexpr int requiredExperienceMultiplier = 2;

	vector<Skill*> skillsList;

private:
	int requiredExperience = 0;
	void LevelUp();
	void NewSkill();
};

