#include "Enhancements.h"

void Enhancements::AddEnhancements(std::vector<Enhancement*>& enhancements)
{
	for (Enhancement* enh : enhancements) {
		switch (enh->Type)
		{
			case EnhancementType::Health: Health += (enh->Multiplier - 1); break;
			case EnhancementType::MagicPower: MagicPower += (enh->Multiplier - 1); break;
			case EnhancementType::Mana: Mana += (enh->Multiplier - 1); break;
			case EnhancementType::Attack:
			{
				AttackEnhancement* aenh = dynamic_cast<AttackEnhancement*>(enh);
				if (aenh == nullptr) {
					GeneralAttack += (enh->Multiplier - 1);
					break;
				}

				switch (aenh->AttackType) {
					case AttackEnhancementType::GeneralAttack: GeneralAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::PhysicalAttack: PhysicalAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::MagicalAttack: MagicalAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::SlashAttack: SlashAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::StabAttack: StabAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::ColdAttack: ColdAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::FireAttack: FireAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::LightningAttack: LightningAttack += (aenh->Multiplier - 1); break;
					case AttackEnhancementType::SacredMagicAttack: SacredMagicAttack += (aenh->Multiplier - 1); break;
				}
			}
			break;
			case EnhancementType::Protection:
			{
				ProtectionEnhancement* penh = dynamic_cast<ProtectionEnhancement*>(enh);
				if (penh == nullptr) {
					GeneralProtection += (enh->Multiplier - 1);
					break;
				}

				switch (penh->ProtectionType) {
					case ProtectionEnhancementType::GeneralProtection: GeneralProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::PhysicalProtection: PhysicalProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::MagicalProtection: MagicalProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::SlashAttackProtection: SlashAttackProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::StabAttackProtection: StabAttackProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::ColdProtection: ColdProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::FireProtection: FireProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::LightningProtection: LightningProtection += (penh->Multiplier - 1); break;
					case ProtectionEnhancementType::SacredMagicProtection: SacredMagicProtection += (penh->Multiplier - 1); break;
				}
			}
			break;
		}
	}
}

void Enhancements::EnhanceAttack(Attack* attack)
{
	switch (attack->damageType) {
		case DamageType::SlashAttack: attack->power *= SlashAttack; break;
		case DamageType::StabAttack: attack->power *= StabAttack; break;
		case DamageType::ColdAttack: attack->power *= ColdAttack; break;
		case DamageType::FireAttack: attack->power *= FireAttack; break;
		case DamageType::LightningAttack: attack->power *= LightningAttack; break;
		case DamageType::SacredMagicAttack: attack->power *= SacredMagicAttack; break;
	}
}

void Enhancements::WeakenAttack(Attack* attack)
{
	switch (attack->damageType) {
		case DamageType::SlashAttack: attack->power /= SlashAttackProtection; break;
		case DamageType::StabAttack: attack->power /= StabAttackProtection; break;
		case DamageType::ColdAttack: attack->power /= ColdProtection; break;
		case DamageType::FireAttack: attack->power /= FireProtection; break;
		case DamageType::LightningAttack: attack->power /= LightningProtection; break;
		case DamageType::SacredMagicAttack: attack->power /= SacredMagicProtection; break;
	}
}
