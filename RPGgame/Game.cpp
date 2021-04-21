#include "Game.h"
#include "lib/json.hpp"

using json = nlohmann::json;

void Game::SaveToFile()
{
	json j;

	j["TripsToTheForestCount"] = TripsToTheForestCount;
	j["CompletedDungeons"] = CompletedDungeons;

	auto jg = j["group"];
	jg["name"] = group->Name;
	auto gm = json::array();
	
	for (GroupMember* member : group->members) {

	}
	jg["members"] = gm;
}
