#pragma once

enum class EnhancementType { Health, Attack, Protection, MagicPower, Mana };

class Enhancement
{
public:
	EnhancementType Type;
	double Multiplier;

	Enhancement(EnhancementType type, double multiplier) : Type(type), Multiplier(multiplier) {}

	virtual ~Enhancement() {}
};

