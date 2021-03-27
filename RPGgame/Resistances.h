#pragma once

#include "Attack.h"

class Resistances
{
public:
	float
		SlashAttackMultiplier = 1.0f,
		StabAttackMultiplier = 1.0f,
		ColdAttackMultiplier = 1.0f,
		FireAttackMultiplier = 1.0f,
		LightningAttackMultiplier = 1.0f,
		SacredMagicAttackMultiplier = 1.0f;

	Resistances() {}

	/// <summary>
	/// m - ����������� ������������� ���� ����
	/// </summary>
	Resistances(float m) : SlashAttackMultiplier(m), StabAttackMultiplier(m), ColdAttackMultiplier(m), FireAttackMultiplier(m), LightningAttackMultiplier(m), SacredMagicAttackMultiplier(m) {}

	/// <summary>
	/// <para>������������ ������������� ��� ������� ���� ����.</para>
	/// <para>1.0 = ��������� ������ ���������.</para>
	/// </summary>
	Resistances(float slashAttack, float stabAttack, float coldAttack, float fireAttack, float lightningAttack, float sacredMagicAttack)
		: SlashAttackMultiplier(slashAttack),
		StabAttackMultiplier(stabAttack),
		ColdAttackMultiplier(coldAttack),
		FireAttackMultiplier(fireAttack),
		LightningAttackMultiplier(lightningAttack),
		SacredMagicAttackMultiplier(sacredMagicAttack) {}

	Attack* HandleAttack(Attack* attack);
};

