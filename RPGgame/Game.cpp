#include "Game.h"
#include <fstream>

//#include "lib/json.hpp"
//using json = nlohmann::json;

#include "rapidJson.h"


void Game::SaveToFile(const string& fileName)
{
	/*json j;

	j["TripsToTheForestCount"] = TripsToTheForestCount;
	j["CompletedDungeons"] = CompletedDungeons;

	json jg ;
	jg["name"] = L"Команда авантюристов";//group->Name;
	auto gm = json::array();
	
	for (GroupMember* member : group->members) {

	}
	//jg["members"] = gm;
	j["group"] = jg;

	std::ofstream os(fileName);
	os << j.dump(4);
	os.close();*/

	Document jd(Type::kObjectType);
	auto& allocator = jd.GetAllocator();

	jd.AddMember("TripsToTheForestCount", TripsToTheForestCount, allocator);
	jd.AddMember("CompletedDungeons", CompletedDungeons, allocator);

	Value jgroup(Type::kObjectType);
	jgroup.AddMember("Name", group->Name, allocator);
	Value jgmembers(Type::kArrayType);
	for (GroupMember* member : group->members) {
		Value jmember(Type::kObjectType);
		member->character->ExportInitialData(jmember, allocator);
		jgmembers.PushBack(jmember, allocator);
	}
	jgroup.AddMember("Members", jgmembers, allocator);
	jd.AddMember("Group", jgroup, allocator);

	std::ofstream os(fileName);
	OStreamWrapper osw(os);
	PrettyWriter<OStreamWrapper> writer(osw);
	jd.Accept(writer);
	os.close(); 
}
