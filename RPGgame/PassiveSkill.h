#pragma once

#include <functional>
#include "Skill.h"
#include "Attacks.h"
#include "Enhancements.h"

using std::function;
#define ENUM_FLAG_OPERATORS(T)                                                                                                                                            \
    inline T operator~ (T a) { return static_cast<T>( ~static_cast<std::underlying_type<T>::type>(a) ); }                                                                       \
    inline T operator| (T a, T b) { return static_cast<T>( static_cast<std::underlying_type<T>::type>(a) | static_cast<std::underlying_type<T>::type>(b) ); }                   \
    inline T operator& (T a, T b) { return static_cast<T>( static_cast<std::underlying_type<T>::type>(a) & static_cast<std::underlying_type<T>::type>(b) ); }                   \
    inline T operator^ (T a, T b) { return static_cast<T>( static_cast<std::underlying_type<T>::type>(a) ^ static_cast<std::underlying_type<T>::type>(b) ); }                   \
    inline T& operator|= (T& a, T b) { return reinterpret_cast<T&>( reinterpret_cast<std::underlying_type<T>::type&>(a) |= static_cast<std::underlying_type<T>::type>(b) ); }   \
    inline T& operator&= (T& a, T b) { return reinterpret_cast<T&>( reinterpret_cast<std::underlying_type<T>::type&>(a) &= static_cast<std::underlying_type<T>::type>(b) ); }   \
    inline T& operator^= (T& a, T b) { return reinterpret_cast<T&>( reinterpret_cast<std::underlying_type<T>::type&>(a) ^= static_cast<std::underlying_type<T>::type>(b) ); }

enum class PassiveSkillAbilities {
	EditingCreatedAttack = 1 << 0,
	EditingReceivedAttack = 1 << 1,
	EditingReceivedByEnemyAttack = 1 << 2,
	OnReceivedByEnemyAttack = 1 << 3,
	StepTriggering = 1 << 4,
};
ENUM_FLAG_OPERATORS(PassiveSkillAbilities)

class Character;
class GroupMember;

class PassiveSkill : public Skill
{
public:
	PassiveSkillAbilities SkillAbilities;

	function<void(const Character* character, Attack* attack)> EditCreatedAttack;
	//function<Attack(const Character* character, Attack* attack, vector<function<void(Character* character)>> onSuccess)> EditCreatedAttack;
	function<void(const Character* character, Attack* attack)> EditReceivedAttack;
	function<void(const Character* character, Attack* attack, Enhancements* enhancements)> EditReceivedByEnemyAttack;
	function<void(GroupMember* character, Attack* attack)> OnReceivedByEnemyAttack;
	function<void(Character* character)> OnStep;

	PassiveSkill(
		string name, string description, PassiveSkillAbilities skillAbilities,
		function<void(const Character* character, Attack* attack)> editCreatedAttack = {},
		//function<Attack(Character* character, Attack* attack, vector<function<void(Character* character)>> onSuccess)> editCreatedAttack = {},
		function<void(const Character* character, Attack* attack)> editReceivedAttack = {},
		function<void(const Character* character, Attack* attack, Enhancements* enhancements)> editReceivedByEnemyAttack = {},
		function<void(GroupMember* character, Attack* attack)> onReceivedByEnemyAttack = {},
		function<void(Character* character)> onStep = {}
	) :
		Skill(name, description),
		SkillAbilities(skillAbilities),
		EditCreatedAttack(editCreatedAttack),
		EditReceivedAttack(editReceivedAttack),
		EditReceivedByEnemyAttack(editReceivedByEnemyAttack),
		OnReceivedByEnemyAttack(onReceivedByEnemyAttack),
		OnStep(onStep) {}
};

