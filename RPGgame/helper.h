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

/// <summary>Считывает число. Если ввод - не число, пишет ошибку и повторяет ввод.</summary>
/// <param name="text">Текст, выводящийся перед вводом.</param>
/// <param name="pred">Предикат, принимающий введённое число. Если возвращает false, то в зависимости от того, было ли присвоено значение аргументу msg, выводит либо его, либо "Неверный ввод", затем, ввод запрашивается снова.</param>
/// <param name="nl">Если установлено значение true, после ввода будет выведена дополнительная пустая строка.</param>
/// <returns>Введённое число</returns>
int ReadInt(const char* text, std::function<bool(int i, string& msg)> pred = nullptr, bool nl = false);

/// <summary>Считывает строку</summary>
/// <param name="text">Текст, выводящийся перед вводом.</param>
/// <param name="pred">Предикат, принимающий введённую строку. Если возвращает false, то в зависимости от того, было ли присвоено значение аргументу msg, выводит либо его, либо "Неверный ввод", затем, ввод запрашивается снова.</param>
/// <param name="nl">Если установлено значение true, после ввода будет выведена дополнительная пустая строка.</param>
/// <returns>Введённая строка</returns>
string ReadString(const char* text, std::function<bool(string s, string& msg)> pred = nullptr, bool nl = false);


int rnd(int min, int max);

/// <summary>
/// Шанс ... из ...
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