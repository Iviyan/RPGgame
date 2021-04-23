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

void Hero::ExportInitialData(Value& j, MemoryPoolAllocator<>& allocator)
{
    Character::ExportInitialData(j, allocator);
    j.AddMember("Gold", gold, allocator);
}
