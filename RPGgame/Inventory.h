#pragma once

#include "WeaponSlot.h"
#include "Enhancements.h"
#include <functional>

class Character;

class Inventory
{
public:
	Artifact* GetMainWeapon();
	Artifact* GetAdditionalWeapon();
	Artifact* GetHelmet();
	Artifact* GetBreastplate();
	Artifact* GetBoots();

	const vector<Artifact*>& GetItems();
	void AddItem(Artifact* artifact);

	/// <summary>
	/// <para>���� ���������� ����� ��������, ����� ������, � ���� ��� �����, ���������� ������.</para>
	/// <para>���� ���������� ������, � ���� �� ��� ������� - ������ ����������� � ������ ����.</para>
	/// <para>���� ���������� ������, � ��� ����� ������, ���� ���������� �������������� ������, ����, ���� ��� ���������, ���.</para>
	/// </summary>
	/// <returns>������ ����������, ��� ���� ��������</returns>
	vector<Artifact*> Use(int itemIndex);

	/// <returns>��������� ��������, ��� ���� ���� ��� ������ - nullptr</returns>
	Artifact* UseAsMainWeapon(int itemIndex);

	/// <returns>��������� ��������, ��� ���� ���� ��� ������ - nullptr</returns>
	Artifact* UseAsAdditionalWeapon(int itemIndex);

	vector<Artifact*>& GetArtifactsList();
	Enhancements& GetEnhancements();
	Enhancements GetEnhancementsC();

	std::function<void()> OnUpdate = nullptr;

	Inventory(WeaponSlot weapon = {}, Artifact* helmet = nullptr, Artifact* breastplate = nullptr, Artifact* boots = nullptr);

private:
	WeaponSlot weapon;
	Artifact* helmet = nullptr;
	Artifact* breastplate = nullptr;
	Artifact* boots = nullptr;

	vector<Artifact*> items;

	vector<Artifact*> activeArtifactsList;
	Enhancements activeArtifactsEnhancements;
	void updateActiveArtifactsList();
};

