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
	/// <para>Если выбирается любой артефакт, кроме оружия, а слот уже занят, происходит замена.</para>
	/// <para>Если выбирается оружие, и одна из рук пустует - оружие вставляется в пустой слот.</para>
	/// <para>Если выбирается оружие, и оба слота заняты, либо заменяется дополнительное оружие, либо, если это двуручное, оба.</para>
	/// </summary>
	/// <returns>Список артефактов, что были заменены</returns>
	vector<Artifact*> Use(int itemIndex);

	/// <returns>Заменённый артефакт, или если слот был пустой - nullptr</returns>
	Artifact* UseAsMainWeapon(int itemIndex);

	/// <returns>Заменённый артефакт, или если слот был пустой - nullptr</returns>
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

