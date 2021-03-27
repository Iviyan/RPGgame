#pragma once

#include "PassiveSkill.h"

struct Buff {
	PassiveSkill* buff = nullptr;
	/// <summary><para>���-�� ���������� �����.</para><para>-1 = �������������.</para></summary>
	int remainingSteps = 0;

	Buff() {}
	Buff(PassiveSkill* buff, int remainingSteps) : buff(buff), remainingSteps(remainingSteps) {}
};