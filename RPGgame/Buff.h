#pragma once

#include "PassiveSkill.h"

struct Buff {
	PassiveSkill* buff = nullptr;
	/// <summary><para>Кол-во оставшихся ходов.</para><para>-1 = неограниченно.</para></summary>
	int remainingSteps = 0;

	Buff() {}
	Buff(PassiveSkill* buff, int remainingSteps) : buff(buff), remainingSteps(remainingSteps) {}
};