#include "WeaponSlot.h"

bool WeaponSlot::IsTwoHanded()
{
	return mainWeapon != nullptr && mainWeapon->Type == ArtifactType::TwoHanded;
}

Artifact* WeaponSlot::GetMainWeapon()
{
	return mainWeapon;
}

Artifact* WeaponSlot::GetAdditionalWeapon()
{
	return additionalWeapon;
}

Artifact* WeaponSlot::SetMainWeapon(Artifact* weapon)
{ 
	if (weapon->Type != ArtifactType::Hand)
		throw std::exception("Wrong type of artifact");

	Artifact* _leftHand = mainWeapon;
	mainWeapon = weapon;
	return _leftHand;
}

Artifact* WeaponSlot::SetAdditionalWeapon(Artifact* weapon)
{
	if (weapon->Type != ArtifactType::Hand)
		throw std::exception("Wrong type of artifact");

	Artifact* _rightHand = IsTwoHanded() ? mainWeapon : additionalWeapon;
	additionalWeapon = weapon;
	return _rightHand;
}

std::tuple<Artifact*, Artifact*> WeaponSlot::UseTwoHandedWeapon(Artifact* weapon)
{
	if (weapon->Type != ArtifactType::TwoHanded)
		throw std::exception("Wrong type of artifact");

	std::tuple<Artifact*, Artifact*> weapons(mainWeapon, additionalWeapon);
	mainWeapon = weapon;
	additionalWeapon = nullptr;
	return weapons;
}