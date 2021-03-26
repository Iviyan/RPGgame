#include "Character.h"
#include "Enhancements.h"
#include <algorithm>

Buff Character::DoBuff(BuffSkill* skill)
{
	Buff buff = skill->CreateBuff(this);
	if (TakeMana(skill->ManaUsage)) {
		return buff;
	}
	else {
		return Buff{ nullptr, 0 };
	}
}

int Character::GetAttack(Attack*& attack, vector<Buff>* buffs) {
	Attack _attack_ = Attack(*attack);
	Attack* attack_ = &_attack_;

	Enhancements enhancements = inventory.GetEnhancementsC();
	enhancements.WeakenAttack(attack_);

	for (PassiveSkill* pskill : passiveSkills) {
		if ((bool)(pskill->SkillAbilities & PassiveSkillAbilities::EditingReceivedAttack)) pskill->EditReceivedAttack(this, attack_);
	}
	for (Buff buff : *buffs) {
		if ((bool)(buff.buff->SkillAbilities & PassiveSkillAbilities::EditingReceivedAttack)) buff.buff->EditReceivedAttack(this, attack_);
	}
	for (auto func : attack_->receivedAttackEditors)
		func(this, attack_, &enhancements);

	resistances.HandleAttack(attack_);

	int resultDamage = (std::max)((int)(attack_->damage * attack_->power - protection), 0);
	ReduceHealth(resultDamage);

	bool avoid = attack_->power == 0;

	switch (attack->attackType) {
		case AttackType::Splash:
		{
			SplashAttack* sattack = dynamic_cast<SplashAttack*>(attack);
			if (sattack->maxEnemiesCount != -1) {
				sattack->attacksRemain--;
				if (sattack->attacksRemain <= 0) {
					delete attack;
					attack = nullptr;
				}
			}
		}
		break;
		case AttackType::Single:
		{
			delete attack;
			attack = nullptr;
		}
		break;
	}

	return avoid ? -1 : resultDamage;
}

Character::Character(
	string name, int level,
	int initialHealth, int healthPerLevel,
	int initialAttack, int attackPerLevel,
	int initialProtection, int protectionPerLevel,
	Resistances resistances,
	int initialMagicPower, int magicPowerPerLevel,
	int initialMana, int manaPerLevel,
	int gold,
	vector<ActiveSkill*> activeSkills,
	vector<PassiveSkill*> passiveSkills,
	Inventory inventory
) :
	Name(name),
	level(level),
	maxOwnHealth(initialHealth + healthPerLevel * (level - 1)), healthPerLevel(healthPerLevel),
	ownAttack(initialAttack + attackPerLevel * (level - 1)), attackPerLevel(attackPerLevel),
	ownProtection(initialProtection + protectionPerLevel * (level - 1)), protectionPerLevel(protectionPerLevel),
	resistances(resistances),
	ownMagicPower(initialMagicPower + magicPowerPerLevel * (level - 1)), magicPowerPerLevel(magicPowerPerLevel),
	maxOwnMana(initialMana + manaPerLevel * (level - 1)), manaPerLevel(manaPerLevel),
	gold(gold),
	activeSkills(activeSkills),
	passiveSkills(passiveSkills),
	inventory(inventory)
{
	health = maxHealth = maxOwnHealth;
	attack = ownAttack;
	protection = ownProtection;
	magicPower = ownMagicPower;
	mana = maxMana = maxOwnMana;

	

	UpdateArtifactDependentProperties();

	auto f = [this]() { this->UpdateArtifactDependentProperties(); };
	this->inventory.OnUpdate = f;
}

bool Character::ReduceHealth(int value)
{
	health -= value;
	if (health <= 0) {
		Die();
		return false;
	}
	return true;
}

void Character::RestoreHealth(int value)
{
	if (value == -1) {
		health = maxHealth;
		return;
	}

	if (health + value > maxHealth)
		health = maxHealth;
	else
		health += value;
}

bool Character::TakeMana(int value)
{
	if (mana - value < 0)
		return false;

	mana -= value;
	return true;
}

void Character::RestoreMana(int value)
{
	if (value == -1) {
		mana = maxMana;
		return;
	}

	if (mana + value > maxMana)
		mana = maxMana;
	else
		mana += value;
}

bool Character::TakeGold(int value)
{
	if (gold - value < 0)
		return false;

	gold -= value;
	return true;
}

void Character::AddGold(int value)
{
	gold += value;
}

void Character::Die()
{
	health = 0;
	isDead = true;
}

void Character::UpdateArtifactDependentProperties()
{
	Enhancements& enhancements = inventory.GetEnhancements();

	if (enhancements.Health != 1.0) {
		bool hs = health == maxHealth;
		maxHealth = maxOwnHealth * enhancements.Health;
		if (hs) health = maxHealth;
	}

	if (enhancements.GeneralAttack != 1.0) {
		attack = ownAttack * enhancements.GeneralAttack;
		magicPower = ownMagicPower * enhancements.GeneralAttack;
	}
	if (enhancements.PhysicalAttack != 1.0)
		attack = ownAttack * enhancements.PhysicalAttack;
	if (enhancements.MagicalAttack != 1.0)
		magicPower = ownMagicPower * enhancements.MagicalAttack;

	if (enhancements.GeneralProtection != 1.0)
		protection = ownProtection * enhancements.GeneralProtection;

	if (enhancements.Mana != 1.0) {
		bool ms = mana == maxMana;
		maxMana = maxOwnMana * enhancements.Mana;
		if (ms) mana = maxMana;
	}
}

bool Character::IsDead() const
{
	return isDead;
}

int Character::GetHealth() const
{
	return health;
}

int Character::GetMaxHealth() const
{
	return maxHealth;
}

int Character::GetLevel() const
{
	return level;
}

int Character::GetAttack() const
{
	return attack;
}

int Character::GetProtection() const
{
	return protection;
}

Resistances Character::GetResistances() const
{
	return resistances;
}

int Character::GetMagicPower() const
{
	return magicPower;
}

int Character::GetGold() const
{
	return gold;
}

int Character::GetMana() const
{
	return mana;
}

int Character::GetMaxMana() const
{
	return maxMana;
}

Inventory& Character::GetInventory()
{
	return inventory;
}

vector<Artifact*>& Character::GetArtifactsList()
{
	return inventory.GetArtifactsList();
}

vector<ActiveSkill*> Character::GetActiveSkills()
{
	vector<ActiveSkill*> skills(activeSkills);
	vector<Artifact*> artifacts = inventory.GetArtifactsList();
	for (Artifact* art : artifacts)
		skills.insert(skills.end(), art->ActiveSkills.begin(), art->ActiveSkills.end());
	return skills;
}

vector<ActiveSkill*>& Character::GetOwnActiveSkills()
{
	return activeSkills;
}

vector<PassiveSkill*>& Character::GetPassiveSkills()
{
	return passiveSkills;
}
