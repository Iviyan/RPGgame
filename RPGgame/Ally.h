#pragma once

#include "AdvancedCharacter.h"
#include "GameArtifacts.h"

class Ally : public AdvancedCharacter
{
public:
	Ally(
		string name,
		int level,
		int initialHealth, int healthPerLevel,
		int initialAttack, int attackPerLevel,
		int initialProtection, int protectionPerLevel,
		Resistances resistances,
		int initialMagicPower, int magicPowerPerLevel,
		int initialMana, int manaPerLevel,
		vector<ActiveSkill*> activeSkills = {},
		vector<PassiveSkill*> passiveSkills = {},
		vector<Skill*> skillsList = {},
		Inventory inventory = {}

	) :
		AdvancedCharacter(
			name, level, initialHealth, healthPerLevel,
			initialAttack, attackPerLevel,
			initialProtection, protectionPerLevel,
			resistances,
			initialMagicPower, magicPowerPerLevel,
			initialMana, manaPerLevel,
			0,
			activeSkills,
			passiveSkills,
			skillsList,
			inventory)
	{};
};

