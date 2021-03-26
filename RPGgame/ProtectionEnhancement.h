#pragma once

#include "Enhancement.h"

enum class ProtectionEnhancementType
{
	GeneralProtection, // = Physical and magical protections
	PhysicalProtection, // = Slash and stub protections
	MagicalProtection, // = All magic protections
	SlashAttackProtection,
	StabAttackProtection,
	ColdProtection,
	FireProtection,
	LightningProtection,
	SacredMagicProtection,
};

class ProtectionEnhancement : public Enhancement
{
public:
	ProtectionEnhancementType ProtectionType;

	ProtectionEnhancement(ProtectionEnhancementType protectionType, double multiplier) : ProtectionType(protectionType), Enhancement(EnhancementType::Protection, multiplier) {}
};

