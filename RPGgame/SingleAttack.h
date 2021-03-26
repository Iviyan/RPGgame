#pragma once

#include "Attack.h"

class SingleAttack : public Attack
{
public:
	SingleAttack(GroupMember* attacker, DamageType damageType, int damage, int manaUsage) : Attack(attacker, AttackType::Single, damageType, damage, manaUsage) {}
};

