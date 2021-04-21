#include "GameArtifacts.h"

vector<Artifact*> ArtifactsForSale
{
	&IronSword,
	&IronDagger,
	&OakStaff,
	&ShieldOfLight,
	&Hauberk,
	&IronHelmet,
	&LightBoots
};

Artifact IronSword
(
	std::string("Железный меч"),
	ArtifactType::Hand,
	100, // стоимость продажи
	vector<Enhancement*> { new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.1), new AttackEnhancement(AttackEnhancementType::SlashAttack, 1.3) },
	vector<ActiveSkill*>({ (ActiveSkill*)&SwordSlash })
);

Artifact IronDagger
(
	std::string("Железный кинжал"),
	ArtifactType::Hand,
	100,
	vector<Enhancement*> { new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.1), new AttackEnhancement(AttackEnhancementType::StabAttack, 1.3) },
	vector<ActiveSkill*>({ (ActiveSkill*)&DaggerStrike })
);

Artifact WoodenBow
(
	std::string("Деревянный лук"),
	ArtifactType::Hand,
	100,
	vector<Enhancement*> { new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.1), new AttackEnhancement(AttackEnhancementType::StabAttack, 1.4) },
	vector<ActiveSkill*>({ (ActiveSkill*)&FireAnArrow })
);

Artifact OakStaff
(
	std::string("Дубовый посох"),
	ArtifactType::Hand,
	100,
	vector<Enhancement*> { new AttackEnhancement(AttackEnhancementType::MagicalAttack, 1.1), new AttackEnhancement(AttackEnhancementType::LightningAttack, 1.4) },
	vector<ActiveSkill*>({ (ActiveSkill*)&LightningStrike })
);

Artifact SwordOfLight
(
	std::string("Меч света"),
	ArtifactType::Hand,
	150, // стоимость продажи
	vector<Enhancement*> { new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.1), new AttackEnhancement(AttackEnhancementType::SacredMagicAttack, 1.3) },
	vector<ActiveSkill*>({ (ActiveSkill*)&SacredLight })
);

Artifact ShieldOfLight
(
	std::string("Щит света"),
	ArtifactType::Hand,
	200, // стоимость продажи
	vector<Enhancement*>
	{
		new ProtectionEnhancement(ProtectionEnhancementType::GeneralProtection, 1.5),
		new AttackEnhancement(AttackEnhancementType::SacredMagicAttack, 1.2),
		new Enhancement(EnhancementType::Health, 1.4)
	},
	vector<ActiveSkill*>({ (ActiveSkill*)&LightBarrier })
);

Artifact StoneGolemCoreBreastplate
(
	std::string("Нагрудник из ядра каменного голема"),
	ArtifactType::Breastplate,
	500, // стоимость продажи
	vector<Enhancement*>
	{
		new Enhancement(EnhancementType::Health, 1.5),
		new Enhancement(EnhancementType::Mana, 1.4),
		new ProtectionEnhancement(ProtectionEnhancementType::GeneralProtection, 1.5),
		new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.2),
	},
	vector<ActiveSkill*>()
);

Artifact IronShield
(
	std::string("Металлический щит"),
	ArtifactType::Hand,
	100, // стоимость продажи
	vector<Enhancement*>
	{
		new ProtectionEnhancement(ProtectionEnhancementType::GeneralProtection, 1.3),
		new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.1),
		new Enhancement(EnhancementType::Health, 1.1)
	},
	vector<ActiveSkill*>()
);

Artifact Hauberk
(
	std::string("Кольчуга"),
	ArtifactType::Breastplate,
	150, // стоимость продажи
	vector<Enhancement*>
	{
		new ProtectionEnhancement(ProtectionEnhancementType::PhysicalProtection, 1.4),
		new ProtectionEnhancement(ProtectionEnhancementType::MagicalProtection, 1.1),
		new Enhancement(EnhancementType::Health, 1.2)
	},
	vector<ActiveSkill*>()
);

Artifact IronHelmet
(
	std::string("Железный шлем"),
	ArtifactType::Helmet,
	100, // стоимость продажи
	vector<Enhancement*>
	{
		new ProtectionEnhancement(ProtectionEnhancementType::GeneralProtection, 1.2),
		new Enhancement(EnhancementType::Health, 1.1),
		new Enhancement(EnhancementType::Attack, 1.1)
	},
	vector<ActiveSkill*>()
);

Artifact LightBoots
(
	std::string("Лёгкие ботинки"),
	ArtifactType::Boot,
	100, // стоимость продажи
	vector<Enhancement*>
	{
		new ProtectionEnhancement(ProtectionEnhancementType::GeneralProtection, 1.1),
		new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.2),
		new Enhancement(EnhancementType::Health, 1.1)
	},
	vector<ActiveSkill*>()
);

Artifact LightingSpear
(
	std::string("Электрическое копье"),
	ArtifactType::TwoHanded,
	500, // стоимость продажи
	vector<Enhancement*> {
	new AttackEnhancement(AttackEnhancementType::PhysicalAttack, 1.5),
		new AttackEnhancement(AttackEnhancementType::LightningAttack, 1.4)
},
vector<ActiveSkill*>({ /*(ActiveSkill*)*/&SpearAttack, &LightningStorm })
);