#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <random>

#include "Hero.h"
#include "Inventory.h"

using std::cout;
using std::cin;
using std::string;

/// <summary>��������� �����. ���� ���� - �� �����, ����� ������ � ��������� ����.</summary>
/// <param name="text">�����, ����������� ����� ������.</param>
/// <param name="pred">��������, ����������� �������� �����. ���� ���������� false, �� � ����������� �� ����, ���� �� ��������� �������� ��������� msg, ������� ���� ���, ���� "�������� ����", �����, ���� ������������� �����.</param>
/// <param name="nl">���� ����������� �������� true, ����� ����� ����� �������� �������������� ������ ������.</param>
/// <returns>�������� �����</returns>
int ReadInt(const char* text, std::function<bool(int i, string& msg)> pred = nullptr, bool nl = false);

/// <summary>��������� ������</summary>
/// <param name="text">�����, ����������� ����� ������.</param>
/// <param name="pred">��������, ����������� �������� ������. ���� ���������� false, �� � ����������� �� ����, ���� �� ��������� �������� ��������� msg, ������� ���� ���, ���� "�������� ����", �����, ���� ������������� �����.</param>
/// <param name="nl">���� ����������� �������� true, ����� ����� ����� �������� �������������� ������ ������.</param>
/// <returns>�������� ������</returns>
string ReadString(const char* text, std::function<bool(string s, string& msg)> pred = nullptr, bool nl = false);


int rnd(int min, int max);

/// <summary>
/// ���� ... �� ...
/// </summary>
bool chance(int count, int of);

void WriteEnhancement(Enhancement& enhancement);
void WriteEnhancements(vector<Enhancement>& enhancements, int indent = 0);
void WriteArtifactInfo(Artifact* artifact, int indent = 0);

void WriteCharacterInfo(Character* ch, int indent = 0);
void WriteCharacterStats(Character* ch);

void WriteCharacterBattleInfo(GroupMember* gm);

void WriteActiveSkillInfo(ActiveSkill* skill);

void WritePassiveSkillInfo(PassiveSkill* skill);

void WriteInventory(Inventory& inv);