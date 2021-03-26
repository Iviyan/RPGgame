#pragma once

#include "AdvancedCharacter.h"
#include "GameArtifacts.h"

enum class CharacterType 
{
	Archer, Warrior, Mage
};

class Hero : public AdvancedCharacter
{
public:
	Hero(
		string name, CharacterType type,
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
		type(type),
		AdvancedCharacter(
			name, level, initialHealth, healthPerLevel,
			initialAttack, attackPerLevel,
			initialProtection, protectionPerLevel,
			resistances,
			initialMagicPower, magicPowerPerLevel,
			initialMana, manaPerLevel,
			initialGold,
			activeSkills,
			passiveSkills,
			skillsList,
			inventory)
	{};

	static constexpr int initialGold = 100;

	virtual void Die();
	void Revive();

protected:
	int deathsCount = 0;
	CharacterType type;
};

