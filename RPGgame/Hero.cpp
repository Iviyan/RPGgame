#include "Hero.h"

void Hero::Die()
{
    deathsCount++;
    Character::Die();
}

void Hero::Revive()
{
    gold = initialGold;
    health = maxHealth;
    mana = maxMana;
    isDead = false;
}