#include "GameSkills.h"

AttackSkill FistPunch
(
	string("���� �������"), // ���
	string("������� 1*PD"), // ��������
	0, // ����� �� ��������������
	0, // ������������� ����
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack(), 0);
	}
);

AttackSkill DaggerStrike
(
	string("���� ��������"),
	string("������� 1.3P*PD"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack() * 1.3, 0);
	}
);

AttackSkill SwordSlash
(
	string("���� �����"),
	string("������� 150% �������� �����"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::SlashAttack, gm->character->GetAttack() * 1.5, 0);
	}
);

AttackSkill FireAnArrow
(
	string("������� �� ����"),
	string("������� 150% ����������� �����"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack() * 1.5, 0);
	}
);

AttackSkill Fireball
(
	string("�������� ���"),
	string("����� �� �������, ������� 1*MD ������ 5 �����������"),
	1,
	80,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::FireAttack, gm->character->GetMagicPower(), 80, 5);
	}
);

AttackSkill LightningStrike
(
	string("���� ������"),
	string("������� 1*MD ������ �� 3 �����������"),
	1,
	60,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::LightningAttack, gm->character->GetMagicPower(), 60, 3);
	}
);

AttackSkill Freeze
(
	string("���������"),
	string("������� 1*MD ������� � ������������ 15 ����������� �� 2 ����, ������ �� ����� �� 80%"),
	4,
	100,
	[](GroupMember* gm) {
		SplashAttack* sa = new SplashAttack(gm, DamageType::ColdAttack, gm->character->GetMagicPower(), 100, 15);
		sa->debuffsEditors.push_back(
			[](GroupMember* gm, Attack* attack)
			{
				gm->AddDebuff(Buff(&Freezing, 2));
			}
		);
		return sa;
	}
);

AttackSkill SacredLight
(
	string("��������� ����"),
	string("������� 1*MD ������ ������ �� ���� �����������"),
	2,
	60,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::SacredMagicAttack, gm->character->GetMagicPower(), 60, -1);
	}
);

BuffSkill LightBarrier
(
	string("������ �����"),
	string("������ ������ ����� �� 1 ���, ��������� ���������� ���� �� 40%"),
	BuffType::Buff,
	1,
	60,
	[](Character* ch) {
		return Buff(&LightBarrierBuff, 1);
	}
);

BuffSkill BattleCry
(
	string("������ ����"),
	string("����� ������ ����, ���������� ����� ������ ������� �� 50% �� 1 ���"),
	BuffType::Buff,
	3,
	40,
	[](Character* ch) {
		return Buff(&Inspiration, 1);
	}
);

AttackSkill RainOfArrows
(
	string("����� �� �����"),
	string("������� 1*MD ����������� ����� 10 �����������"),
	2,
	70,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::StabAttack, gm->character->GetMagicPower(), 70, 10);
	}
);

//Zombie
AttackSkill Bite
(
	string("����"),
	string("������� 1*MD ����������� ����� � ����������� ����������"),
	0,
	0,
	[](GroupMember* gm) {
		SingleAttack* sa = new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack(), 0);
		sa->debuffsEditors.push_back(
			[](GroupMember* gm, Attack* attack) 
			{ 
				gm->AddDebuff(Buff(&Poisoning, 2));
			}
		);
		return sa;
	}
);

AttackSkill StoneSpears
(
	string("�������� �����"),
	string("������� 1.2*MD ����������� ����� 6 �����������"),
	2,
	70,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::StabAttack, gm->character->GetMagicPower() * 1.2, 70, 6);
	}
);

BuffSkill Healing
(
	string("���������"),
	string("��������������� 60% �������� ������ �������"),
	BuffType::Buff,
	3,
	50,
	[](Character* ch) {
		return Buff(&LightBarrierBuff, 1);
	}
);

BuffSkill BlessingOfTheGodOfWar
(
	string("������������� ���� �����"),
	string("� ���������� ��������� ������������� ����� ������� ������� �� 60% ������ �����"),
	BuffType::Buff,
	3,
	40,
	[](Character* ch) {
		return Buff(&Strengthening, 1);
	}
);

AttackSkill LightningStorm
(
	string("����� ������"),
	string("������� 1*MD ������ �� 7 �����������"),
	2,
	90,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::LightningAttack, gm->character->GetMagicPower(), 90, 7);
	}
);

AttackSkill SpearAttack
(
	string("����� ������"),
	string("������� 1.5*MD ����������� �����"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack(), 0);
	}
);