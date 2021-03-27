#include "GameSkills.h"

PassiveSkill Poisoning
(
	string("����������"),
	string("�������� 10H ������ ���"),
	PassiveSkillAbilities::StepTriggering,
	{}, {}, {}, {},
	[](Character* ch) {
		ch->ReduceHealth(10); // TODO: �������� ��� ����� � ������� ��������� ����� ��� ������� ���
	}
);

PassiveSkill Freezing
(
	string("���������"),
	string("������� ����� �� 80%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		attack->power *= 0.2;
	}
);