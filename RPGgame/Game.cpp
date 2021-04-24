#include "Game.h"
#include <fstream>
#include "rapidJson.h"

void Game::SaveToFile(const string& fileName)
{
	Document jd(Type::kObjectType);
	auto& allocator = jd.GetAllocator();

	jd.AddMember("TripsToTheForestCount", TripsToTheForestCount, allocator);
	jd.AddMember("CompletedDungeons", CompletedDungeons, allocator);

	Value jgroup(Type::kObjectType);
	group->ExportData(jgroup, allocator);
	jd.AddMember("Group", jgroup, allocator);

	Value jdungeons(Type::kArrayType);
	for (Dungeon* dungeon : dungeons) {
		Value jdungeon(Type::kObjectType);
		dungeon->ExportInitialData(jdungeon, allocator);
		jdungeons.PushBack(jdungeon, allocator);
	}
	jd.AddMember("Dungeons", jdungeons, allocator);

	std::ofstream os(fileName);
	OStreamWrapper osw(os);
	PrettyWriter<OStreamWrapper> writer(osw);
	jd.Accept(writer);
	os.close();
}
