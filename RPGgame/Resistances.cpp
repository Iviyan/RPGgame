#include "Resistances.h"

Attack* Resistances::HandleAttack(Attack* attack) {
	switch (attack->damageType) {
		case DamageType::SlashAttack:
			attack->power *= SlashAttackMultiplier;
			break;
		case DamageType::StabAttack:
			attack->power *= StabAttackMultiplier;
			break;
		case DamageType::ColdAttack:
			attack->power *= ColdAttackMultiplier;
			break;
		case DamageType::FireAttack:
			attack->power *= FireAttackMultiplier;
			break;
		case DamageType::LightningAttack:
			attack->power *= LightningAttackMultiplier;
			break;
		case DamageType::SacredMagicAttack:
			attack->power *= SacredMagicAttackMultiplier;
			break;
	}
	return attack;
}