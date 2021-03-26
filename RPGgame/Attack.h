#pragma once

#include <vector>
#include <functional>

enum class DamageType
{
	SlashAttack,
	StabAttack,
	ColdAttack,
	FireAttack,
	LightningAttack,
	SacredMagicAttack,
};

bool IsPhysicalDamage(DamageType type);
bool IsMagicalDamage(DamageType type);


enum class AttackType
{
	Single,
	Splash
};

class Character;
class Enhancements;
class Group;
class GroupMember;

class Attack
{
public:
	GroupMember* attacker;
	AttackType attackType;
	DamageType damageType;
	double power = 1.0; // множитель, на который в конечном счёте умножится кол-во урона
	int damage;
	int manaUsage;
	std::vector<std::function<void(const Character* character, Attack* attack, Enhancements* enhancements)>> receivedAttackEditors;
	std::vector<std::function<void(GroupMember* character, Attack* attack)>> debuffsEditors;
	
	Attack() = delete;
	virtual ~Attack() {}
protected:
	Attack(GroupMember* attacker, AttackType attackType, DamageType damageType, int damage, int manaUsage) :
		attacker(attacker), attackType(attackType), damageType(damageType), damage(damage), manaUsage(manaUsage) {}
};

