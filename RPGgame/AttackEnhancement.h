#pragma once

#include "Enhancement.h"

enum class AttackEnhancementType
{
	GeneralAttack, // = Physical and magical attacks
	PhysicalAttack, // = Slash and stub attack
	MagicalAttack, // = All magic attacks
	SlashAttack,
	StabAttack,
	ColdAttack,
	FireAttack,
	LightningAttack,
	SacredMagicAttack,
};

class AttackEnhancement : public Enhancement
{
public:
	AttackEnhancementType AttackType;

	AttackEnhancement(AttackEnhancementType attackType, double multiplier) : AttackType(attackType), Enhancement(EnhancementType::Attack, multiplier) {}
};

