#include "GameSkills.h"

PassiveSkill Inspiration
(
	string("�������������"),
	string("��������� ����� �� 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		attack->power *= 1.5;
	}
);

PassiveSkill HealingBuff
(
	string("���������"),
	string("�������� 60% ��������"),
	PassiveSkillAbilities::StepTriggering,
	{}, {}, {}, {},
	[](Character* ch) {
		ch->RestoreHealth(ch->GetMaxHealth() * 0.6);
	}
);

PassiveSkill Strengthening
(
	string("��������"),
	string("��������� ����� �� 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		attack->power *= 1.5;
	}
);