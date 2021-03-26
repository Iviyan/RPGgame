#include "Inventory.h"

Artifact* Inventory::GetMainWeapon()
{
	return weapon.GetMainWeapon();
}

Artifact* Inventory::GetAdditionalWeapon()
{
	return weapon.GetAdditionalWeapon();
}

Artifact* Inventory::GetHelmet()
{
	return helmet;
}

Artifact* Inventory::GetBreastplate()
{
	return breastplate;
}

Artifact* Inventory::GetBoots()
{
	return boots;
}

const vector<Artifact*>& Inventory::GetItems()
{
	return items;
}

void Inventory::AddItem(Artifact* artifact)
{
	items.push_back(artifact);
}

vector<Artifact*> Inventory::Use(int itemIndex)
{
	Artifact* artifact = items.at(itemIndex);
	items.erase(items.begin() + itemIndex);
	vector<Artifact*> _artifact(2);
	switch (artifact->Type)
	{
		case ArtifactType::Hand:
			if (weapon.GetMainWeapon() == nullptr) {
				_artifact.push_back(weapon.SetMainWeapon(artifact));
				break;
			}
			if (weapon.GetAdditionalWeapon() == nullptr && !weapon.IsTwoHanded()) {
				_artifact.push_back(weapon.SetAdditionalWeapon(artifact));
				break;
			}
			if (weapon.IsTwoHanded()) {
				_artifact.push_back(weapon.SetMainWeapon(artifact));
				break;
			}
			break;
		case ArtifactType::TwoHanded:
		{
			auto _artifacts = weapon.UseTwoHandedWeapon(artifact);
			_artifact.push_back(std::get<0>(_artifacts));
			_artifact.push_back(std::get<1>(_artifacts));
		}
		break;
		case ArtifactType::Helmet:
			_artifact.push_back(helmet);
			helmet = artifact;
			break;
		case ArtifactType::Breastplate:
			_artifact.push_back(breastplate);
			breastplate = artifact;
			break;
		case ArtifactType::Boot:
			_artifact.push_back(boots);
			boots = artifact;
			break;
	}

	_artifact.erase(std::remove(_artifact.begin(), _artifact.end(), nullptr), _artifact.end());
	for (Artifact* art : _artifact)
		items.push_back(art);

	updateActiveArtifactsList();

	return _artifact;
}

Artifact* Inventory::UseAsMainWeapon(int itemIndex)
{
	Artifact* artifact = items.at(itemIndex);
	items.erase(items.begin() + itemIndex);
	Artifact* _artifact = weapon.SetMainWeapon(artifact);
	if (_artifact != nullptr)
		items.push_back(_artifact);

	updateActiveArtifactsList();

	return _artifact;
}

Artifact* Inventory::UseAsAdditionalWeapon(int itemIndex)
{
	Artifact* artifact = items.at(itemIndex);
	items.erase(items.begin() + itemIndex);
	Artifact* _artifact = weapon.SetAdditionalWeapon(artifact);
	if (_artifact != nullptr)
		items.push_back(_artifact);

	updateActiveArtifactsList();

	return _artifact;
}

vector<Artifact*>& Inventory::GetArtifactsList()
{
	return activeArtifactsList;
}

Enhancements& Inventory::GetEnhancements()
{
	return activeArtifactsEnhancements;
}

Enhancements Inventory::GetEnhancementsC()
{
	return activeArtifactsEnhancements;
}

Inventory::Inventory(WeaponSlot weapon, Artifact* helmet, Artifact* breastplate, Artifact* boots)
	: weapon(weapon), helmet(helmet), breastplate(breastplate), boots(boots)
{
	updateActiveArtifactsList();
}

void Inventory::updateActiveArtifactsList()
{
	activeArtifactsList = vector<Artifact*>();
	if (GetMainWeapon() != nullptr) activeArtifactsList.push_back(GetMainWeapon());
	if (GetAdditionalWeapon() != nullptr) activeArtifactsList.push_back(GetAdditionalWeapon());
	if (helmet != nullptr) activeArtifactsList.push_back(helmet);
	if (breastplate != nullptr) activeArtifactsList.push_back(breastplate);
	if (boots != nullptr) activeArtifactsList.push_back(boots);

	activeArtifactsEnhancements = Enhancements();
	for (Artifact* art : activeArtifactsList)
		activeArtifactsEnhancements.AddEnhancements(art->Enhancements);

	if (OnUpdate != nullptr) OnUpdate();
}
