#pragma once
#include "Artifact.h"

class WeaponSlot
{
public:
	bool IsTwoHanded();
	Artifact* GetMainWeapon();
	Artifact* GetAdditionalWeapon();
	
	// ≈сли артефакт уже присутствует - возвращает его и устанавливает новый
	Artifact* SetMainWeapon(Artifact* weapon);
	Artifact* SetAdditionalWeapon(Artifact* weapon);
	std::tuple<Artifact*, Artifact*> UseTwoHandedWeapon(Artifact* weapon);

	WeaponSlot() {}
	WeaponSlot(Artifact* mainWeapon) : mainWeapon(mainWeapon) {}
	WeaponSlot(Artifact* mainWeapon, Artifact* additionalWeapon) : mainWeapon(mainWeapon), additionalWeapon(additionalWeapon) {}
private:
	Artifact* mainWeapon = nullptr;
	Artifact* additionalWeapon = nullptr;
};

