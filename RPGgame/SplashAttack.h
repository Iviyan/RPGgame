#pragma once

#include "Attack.h"

class SplashAttack : public Attack
{
public:
	int maxEnemiesCount;
	int attacksRemain = 1;

	/// <param name="maxEnemiesCount">Максимальное число врагов, что может задеть атака. -1 - неограниченно</param>
	SplashAttack(GroupMember* attacker, DamageType damageType, int damage, int manaUsage, int maxEnemiesCount) :
		Attack(attacker, AttackType::Splash, damageType, damage, manaUsage), maxEnemiesCount(maxEnemiesCount), attacksRemain(maxEnemiesCount) {}
};

