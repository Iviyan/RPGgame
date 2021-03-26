#pragma once

#include "AttackEnhancement.h"
#include "ProtectionEnhancement.h"
#include <vector>
#include "Attack.h"

class Attack;

class Enhancements {
public:
	double
		Health = 1.0, MagicPower = 1.0, Mana = 1.0,
		GeneralAttack = 1.0,
		PhysicalAttack = 1.0,
		MagicalAttack = 1.0,
		SlashAttack = 1.0,
		StabAttack = 1.0,
		ColdAttack = 1.0,
		FireAttack = 1.0,
		LightningAttack = 1.0,
		SacredMagicAttack = 1.0,
		GeneralProtection = 1.0,
		PhysicalProtection = 1.0,
		MagicalProtection = 1.0,
		SlashAttackProtection = 1.0,
		StabAttackProtection = 1.0,
		ColdProtection = 1.0,
		FireProtection = 1.0,
		LightningProtection = 1.0,
		SacredMagicProtection = 1.0;

	void AddEnhancements(std::vector<Enhancement*>& enhancements);

	void EnhanceAttack(Attack* attack);
	void WeakenAttack(Attack* attack);
};