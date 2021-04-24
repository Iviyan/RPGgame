#pragma once

#include "Character.h"
#include "GroupMember.h"

class Group
{
public:
	string Name;
	vector<GroupMember*> members;

	void AddMember(Character* character);
	void ChooseAttacks();
	void BuffMembers(Buff buff);
	void DebuffMembers(Buff buff);

	void Step();

	void EndBattle();
	void RestoreStats();

	vector<Buff> DoBuffs();
	vector<Buff> DoDebuffs();
	vector<Attack*> DoAttacks();

	/// <returns>Задетые атаками союзники</returns>
	vector<GroupMember*> GetAttacks(vector<Attack*>& attacks);

	void HideDeads();

	vector<GroupMember*> deads;

	Group(string name) : Name(name) {}
	Group(string name, vector<Character*> characters);
	
	~Group();

	void ExportData(Value& jgroup, MemoryPoolAllocator<>& allocator);
};