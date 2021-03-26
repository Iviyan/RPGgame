#include "GameSkills.h"
#include "helper.h"

PassiveSkill PhysicalCrit
(
	string("Критический удар"),
	string("Если здоровье противника меньше 40% и атака физ. характера, вероятность 50% нанести 2x урона"),
	PassiveSkillAbilities::EditingReceivedByEnemyAttack,
	{}, {},
	[](const Character* ch, Attack* attack, Enhancements* enhs) {
		if (IsPhysicalDamage(attack->damageType) && ch->GetHealth() / ch->GetMaxHealth() <= 0.4)
			attack->power *= 2;
	}
);

PassiveSkill Evasion
(
	string("Уклонение"),
	string("Шанс уклониться от: режущей атаки - 20%, от пронзающей атаки - 30%, отодиночных атак магии огня и холода - 10%"),
	PassiveSkillAbilities::EditingReceivedAttack,
	{},
	[](const Character* ch, Attack* attack) {
		switch (attack->damageType) {
			case DamageType::SlashAttack: if (chance(2, 10)) attack->power = 0; break;
			case DamageType::StabAttack: if (chance(3, 10)) attack->power = 0; break;
			case DamageType::FireAttack: if (attack->attackType == AttackType::Single && chance(1, 10)) attack->power = 0; break;
			case DamageType::ColdAttack: if (attack->attackType == AttackType::Single && chance(1, 10)) attack->power = 0; break;
		}
	}
);

PassiveSkill HealthPower
(
	string("Сила здоровья"),
	string("Если здоровье больше 50%, атаки магией усиливаются на 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		if (IsMagicalDamage(attack->damageType) && ch->GetHealth() / ch->GetMaxHealth() >= 0.5)
			attack->power *= 1.5;
	}
);

PassiveSkill WindBarrier
(
	string("Ветряной барьер"),
	string("Отклоняет атаки, снижая их эффективность. Особенно эффективно против пронзающих атак (-70%), а также против огненных (-30%)"),
	PassiveSkillAbilities::EditingReceivedAttack,
	{},
	[](const Character* ch, Attack* attack) {
		switch (attack->damageType) {
			case DamageType::StabAttack: attack->power *= 0.3; break;
			case DamageType::FireAttack: attack->power *= 0.7; break;
		}
	}
);

PassiveSkill LightBarrierBuff
(
	string("Барьер света"),
	string("Ослабляет получаемые атаки на 40%"),
	PassiveSkillAbilities::EditingReceivedAttack,
	{},
	[](const Character* ch, Attack* attack) {
		 attack->power *= 0.6; 
	}
);

PassiveSkill BattleCryBuff
(
	string("Боевой клич"),
	string("Увеличивает атаку членов команды на 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		 attack->power *= 1.5; 
	}
);