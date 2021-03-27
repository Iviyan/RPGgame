#include "GameSkills.h"
#include "helper.h"

PassiveSkill PhysicalCrit
(
	string("����������� ����"),
	string("���� �������� ���������� ������ 40% � ����� ���. ���������, ����������� 50% ������� 2x �����"),
	PassiveSkillAbilities::EditingReceivedByEnemyAttack,
	{}, {},
	[](const Character* ch, Attack* attack, Enhancements* enhs) {
		if (IsPhysicalDamage(attack->damageType) && ch->GetHealth() / ch->GetMaxHealth() <= 0.4)
			attack->power *= 2;
	}
);

PassiveSkill Evasion
(
	string("���������"),
	string("���� ���������� ��: ������� ����� - 20%, �� ���������� ����� - 30%, ����������� ���� ����� ���� � ������ - 10%"),
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
	string("���� ��������"),
	string("���� �������� ������ 50%, ����� ������ ����������� �� 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		if (IsMagicalDamage(attack->damageType) && ch->GetHealth() / ch->GetMaxHealth() >= 0.5)
			attack->power *= 1.5;
	}
);

PassiveSkill WindBarrier
(
	string("�������� ������"),
	string("��������� �����, ������ �� �������������. �������� ���������� ������ ���������� ���� (-70%), � ����� ������ �������� (-30%)"),
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
	string("������ �����"),
	string("��������� ���������� ����� �� 40%"),
	PassiveSkillAbilities::EditingReceivedAttack,
	{},
	[](const Character* ch, Attack* attack) {
		 attack->power *= 0.6; 
	}
);

PassiveSkill BattleCryBuff
(
	string("������ ����"),
	string("����������� ����� ������ ������� �� 50%"),
	PassiveSkillAbilities::EditingCreatedAttack,
	[](const Character* ch, Attack* attack) {
		 attack->power *= 1.5; 
	}
);