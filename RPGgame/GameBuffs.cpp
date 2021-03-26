#include "GameSkills.h"

PassiveSkill Inspiration
(
	string("Воодушевление"),
	string("Усиливает атаку на 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		attack->power *= 1.5;
	}
);

PassiveSkill HealingBuff
(
	string("Усцеление"),
	string("Исцеляет 60% здоровья"),
	PassiveSkillAbilities::StepTriggering,
	{}, {}, {}, {},
	[](Character* ch) {
		ch->RestoreHealth(ch->GetMaxHealth() * 0.6);
	}
);

PassiveSkill Strengthening
(
	string("Усиление"),
	string("Усиливает атаку на 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		attack->power *= 1.5;
	}
);