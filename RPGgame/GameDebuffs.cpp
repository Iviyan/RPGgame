#include "GameSkills.h"

PassiveSkill Poisoning
(
	string("Отравление"),
	string("Отнимает 10H каждый ход"),
	PassiveSkillAbilities::StepTriggering,
	{}, {}, {}, {},
	[](Character* ch) {
		ch->ReduceHealth(10); // TODO: добавить тип урона и создать отдельную атаку для эффекта яда
	}
);

PassiveSkill Freezing
(
	string("Заморозка"),
	string("Снижает атаки на 80%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		attack->power *= 0.2;
	}
);