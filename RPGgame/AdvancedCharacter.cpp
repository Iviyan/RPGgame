#include "AdvancedCharacter.h"
#include <algorithm>
#include "helper.h"

AdvancedCharacter::AdvancedCharacter
(
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
    vector<Skill*> skillsList, 
    Inventory inventory
)
    :
    Character(name, level, initialHealth, healthPerLevel,
        initialAttack, attackPerLevel,
        initialProtection, protectionPerLevel,
        resistances,
        initialMagicPower, magicPowerPerLevel,
        initialMana, manaPerLevel,
        gold,
        activeSkills,
        passiveSkills,
        inventory),
    skillsList(skillsList)
{
    for (int i = 1; i < level; i++)
        NewSkill();
};

bool AdvancedCharacter::AddExperience(int value)
{
    experience += value;

    int requiredExperience = GetRequiredExperience();

    int levelsUp = 0;
    while (experience >= requiredExperience) {
        LevelUp();
        levelsUp++;
    }

    return levelsUp;
}

int AdvancedCharacter::GetExperience() const
{
    return experience;
}

int AdvancedCharacter::GetRequiredExperience()
{
    if (requiredExperience == 0) {
        requiredExperience = initialRequiredExperience;
        for (int i = 1; i < level; i++) requiredExperience *= requiredExperienceMultiplier;
    }
    return requiredExperience;
}

void AdvancedCharacter::LevelUp()
{
    experience -= GetRequiredExperience();
    level++;
    health = maxOwnHealth += healthPerLevel;
    attack += attackPerLevel;
    protection += protectionPerLevel;
    magicPower += magicPowerPerLevel;
    mana = maxOwnMana += manaPerLevel;

    NewSkill();

    requiredExperience *= requiredExperienceMultiplier;
}

void AdvancedCharacter::NewSkill()
{
    if (skillsList.size() > 0) {
        int options = (std::min)(2u, (unsigned int)skillsList.size() - 1);
        int sel = rnd(0, options);
        auto it = skillsList.begin() + sel;
        Skill* skill = *it;
        ActiveSkill* askill = dynamic_cast<ActiveSkill*>(skill);
        PassiveSkill* pskill = dynamic_cast<PassiveSkill*>(skill);
        if (askill != nullptr) activeSkills.push_back(askill);
        else if (pskill != nullptr) passiveSkills.push_back(pskill);
        skillsList.erase(it);
    }
}
