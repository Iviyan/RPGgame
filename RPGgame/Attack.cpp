#include "Attack.h"

bool IsPhysicalDamage(DamageType type)
{
    return type == DamageType::SlashAttack || type == DamageType::StabAttack;
}

bool IsMagicalDamage(DamageType type)
{
    return !IsPhysicalDamage(type);
}
