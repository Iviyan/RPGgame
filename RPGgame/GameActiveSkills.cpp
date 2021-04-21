#include "GameSkills.h"

AttackSkill FistPunch
(
	string("Удар кулаком"), // имя
	string("Наносит 1*PD"), // описание
	0, // ходов на восстановление
	0, // использование маны
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack(), 0);
	}
);

AttackSkill DaggerStrike
(
	string("Удар кинжалом"),
	string("Наносит 1.3P*PD"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack() * 1.3, 0);
	}
);

AttackSkill SwordSlash
(
	string("Удар мечом"),
	string("Наносит 150% режущего урона"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::SlashAttack, gm->character->GetAttack() * 1.5, 0);
	}
);

AttackSkill FireAnArrow
(
	string("Выстрел из лука"),
	string("Наносит 150% пронзающего урона"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack() * 1.5, 0);
	}
);

AttackSkill Fireball
(
	string("Огненный шар"),
	string("Атака по площади, наносит 1*MD первым 5 противникам"),
	1,
	80,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::FireAttack, gm->character->GetMagicPower(), 80, 5);
	}
);

AttackSkill LightningStrike
(
	string("Удар молнии"),
	string("Наносит 1*MD молнии по 3 противникам"),
	1,
	60,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::LightningAttack, gm->character->GetMagicPower(), 60, 3);
	}
);

AttackSkill Freeze
(
	string("Заморозка"),
	string("Наносит 1*MD холодом и замораживает 15 противников на 2 хода, снижая их атаки на 80%"),
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
	string("Священный свет"),
	string("Наносит 1*MD святой магией по всем противникам"),
	2,
	60,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::SacredMagicAttack, gm->character->GetMagicPower(), 60, -1);
	}
);

BuffSkill LightBarrier
(
	string("Барьер света"),
	string("Создаёт барьер света на 1 ход, снижающий получаемый урон на 40%"),
	BuffType::Buff,
	1,
	60,
	[](Character* ch) {
		return Buff(&LightBarrierBuff, 1);
	}
);

BuffSkill BattleCry
(
	string("Боевой клич"),
	string("Издаёт боевой клич, повышающий атаку членов команды на 50% на 1 ход"),
	BuffType::Buff,
	3,
	40,
	[](Character* ch) {
		return Buff(&Inspiration, 1);
	}
);

AttackSkill RainOfArrows
(
	string("Дождь из стрел"),
	string("Наносит 1*MD пронзающего урона 10 противникам"),
	2,
	70,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::StabAttack, gm->character->GetMagicPower(), 70, 10);
	}
);

//Zombie
AttackSkill Bite
(
	string("Укус"),
	string("Наносит 1*MD пронзающего урона и накладывает отравление"),
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
	string("Каменные копья"),
	string("Наносит 1.2*MD пронзающего урона 6 противникам"),
	2,
	70,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::StabAttack, gm->character->GetMagicPower() * 1.2, 70, 6);
	}
);

BuffSkill Healing
(
	string("Исцеление"),
	string("Восстанавливает 60% здоровья членов команды"),
	BuffType::Buff,
	3,
	50,
	[](Character* ch) {
		return Buff(&LightBarrierBuff, 1);
	}
);

BuffSkill BlessingOfTheGodOfWar
(
	string("Благословение бога войны"),
	string("В результате наложение благословения члены команды наносят на 60% больше урона"),
	BuffType::Buff,
	3,
	40,
	[](Character* ch) {
		return Buff(&Strengthening, 1);
	}
);

AttackSkill LightningStorm
(
	string("Шторм молний"),
	string("Наносит 1*MD молнии по 7 противникам"),
	2,
	90,
	[](GroupMember* gm) {
		return new SplashAttack(gm, DamageType::LightningAttack, gm->character->GetMagicPower(), 90, 7);
	}
);

AttackSkill SpearAttack
(
	string("Атака копьём"),
	string("Наносит 1.5*MD пронзающего урона"),
	0,
	0,
	[](GroupMember* gm) {
		return new SingleAttack(gm, DamageType::StabAttack, gm->character->GetAttack(), 0);
	}
);