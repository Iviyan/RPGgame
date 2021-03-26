#include <Windows.h>
#include <iostream>
#include "Heroes.h"
#include "helper.h"
#include "Game.h"
#include "ConsoleBattle.h"

#include "GameArtifacts.h"
#include "Enemies.h"
#include "Dungeons.h"
#include "DungeonMap.h"

using namespace std;

void GoForest(Game* game);
void GoDungeon(Game* game, Dungeon* dungeon);
void ShowInventory(Game* game);
void Shop(Game* game);
void MercenaryShop(Game* game);
void ArtifactsShop(Game* game);
void DungeonsShop(Game* game);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Game game;
	Hero* hero = nullptr;

	string name;

	name = ReadString("Введите имя героя: ", [](string s, string& msg) { bool empty = s.empty(); if (empty) msg = "Имя не может быть пустым"; return !empty; }, true);

	cout << "- Наконец-то я начал свой путь героя. Я пойду по стопам отца, а так же и деда. Хмм, кем же мне стать? Мать была волшебницей, так что у меня есть зачатки к магии и волшебству, когда отец научил боевому искусству.\n" << endl;

	int heroClass_ = ReadInt(
		"Выберите класс героя:\n"
		"1) Воин\n"
		"2) Маг\n"
		"3) Лучник\n"
		"> ",
		[](int i, string& msg) { bool inRange = i >= 1 && i <= 3; if (inRange) msg = "Число должно быть в диапазоне от 1 до 3"; return inRange; },
		true
	);

	switch (heroClass_) {
		case 1:
			hero = new Warrior(name);
			cout << "- Пойду по стопам отца, все же считаю, что маг из меня не очень, мать мало чему меня научила.\n" << endl;
			break;
		case 2:
			hero = new Mage(name);
			cout << "- Мать была ко мне ближе, и дольше чем отец, он рано покинул меня, хоть и успел кое-чему научить.\n" << endl;
			break;
		case 3:
			hero = new Archer(name);
			cout << "- В детстве у меня был друг, который отлично стрелял из лука. Вроде, он научил меня неплохо стрелять. Так почему бы не продолжить начатое?\n" << endl;
			break;
	}
	game.hero = hero;

	cout << "-Теперь в путь, моя задача стать более сильным героем!\n" << endl;

	cout << "-> ";
	WriteCharacterStats(hero);
	cout << "L - уровень" << endl;
	cout << "Exp - опыт" << endl;
	cout << "H - здоровье" << endl;
	cout << "Pr - защита" << endl;
	cout << "PD - физический урон" << endl;
	cout << "MD - магический урон" << endl;
	cout << "Mn - мана" << endl;
	cout << endl;

	cout << "Золото: " << hero->GetGold() << endl << endl;

	cout << "Артефакты:" << endl;
	for (Artifact* art : hero->GetArtifactsList()) {
		cout << "- ";
		WriteArtifactInfo(art, 1);
	}
	cout << endl;

	cout << "Активные навыки:" << endl;
	for (ActiveSkill* skill : hero->GetActiveSkills()) {
		cout << "- ";
		WriteActiveSkillInfo(skill);
	}
	cout << "STR - ходов на восстановление" << endl;
	cout << endl;

	cout << "Пассивные навыки:" << endl;
	for (PassiveSkill* skill : hero->GetPassiveSkills()) {
		cout << "- ";
		WritePassiveSkillInfo(skill);
	}
	cout << endl;

	Group*& MCG = game.group;
	game.group = nullptr;

	while (1) {
		if (MCG == nullptr) {
			MCG = new Group("Команда авантюристов");
			MCG->AddMember(hero);
		}

		int action = ReadInt
		(
			"Выберите действие:\n"
			"1. Пойти в таверну (восстановить здоровье и ману членов команды)\n"
			"2. Пойти в лес\n"
			"3. Подземелья\n"
			"4. Магазин\n"
			"5. Инвентарь\n"
			"6. Информация о ГГ\n"
			"7. Подробная информация о команде\n"
			"8. Состояние команды\n"
			"> ",
			[](int i, string& msg) { return i >= 1 && i <= 8; },
			true
		);

		switch (action) {
			case 1:
			{
				game.group->RestoreStats();
				cout << "Вы успешно отдохнули в таверне, здоровье и мана членов команды восстановлены\n" << endl;
				continue;
			}

			case 2:
			{
				GoForest(&game);
			}
			break;

			case 3:
			{
				if (game.dungeons.size() == 0) {
					cout << "Сначала необходимо купить карту подземелья в магазине\n" << endl;
					continue;
				}

				cout << "0. Выход" << endl;
				int i = 1;
				for (Dungeon* d : game.dungeons)
					cout << i++ << ". " << d->Name << endl;

				int sel = ReadInt("> ", [&game](int i, string& msg) { return i >= 0 && i <= game.dungeons.size(); }, true);
				if (sel == 0) continue;
				Dungeon* dungeon = game.dungeons[sel - 1];

				cout << "> " << dungeon->Name << " <" << endl;
				cout << dungeon->Description << endl << endl;

				int conf = ReadInt("Вы уверены, что хотите войти? (1 - да, 0 - нет): ", [](int i, string& msg) { return i >= 0 && i <= 1; }, true);
				if (conf == 0) continue;

				GoDungeon(&game, dungeon);
			}
			break;

			case 4:
			{
				Shop(&game);
			}
			break;

			case 5:
			{
				ShowInventory(&game);
			}
			break;

			case 6:
			{
				cout << "-> ";
				WriteCharacterStats(hero);

				cout << "Золото: " << hero->GetGold() << endl << endl;

				cout << "Артефакты:" << endl;
				for (Artifact* art : hero->GetArtifactsList()) {
					cout << "- ";
					WriteArtifactInfo(art, 1);
				}
				cout << endl;

				cout << "Активные навыки:" << endl;
				for (ActiveSkill* skill : hero->GetActiveSkills()) {
					cout << "- ";
					WriteActiveSkillInfo(skill);
				}
				cout << endl;

				cout << "Пассивные навыки:" << endl;
				for (PassiveSkill* skill : hero->GetPassiveSkills()) {
					cout << "- ";
					WritePassiveSkillInfo(skill);
				}
				cout << endl;
			}
			break;

			case 7:
			{
				int i = 1;
				for (GroupMember* member : game.group->members) {
					cout << i++ << ". ";
					WriteCharacterInfo(member->character, 3);
					cout << endl;
				}
				cout << endl;
			}
			break;

			case 8:
			{
				int i = 1;
				for (GroupMember* member : game.group->members) {
					cout << i++ << ". ";
					WriteCharacterStats(member->character);
				}
				cout << endl;
			}
			break;
		}
	}
}

void GoForest(Game* game) {
	cout << "Вы наткнулись на группу монстров\n" << endl;

	Group En("Группа монстров");

	int MCGMembersCount = game->group->members.size();
	int MCGLevelsSum = 0;
	int MCGMaxLevel = 0;
	for (GroupMember* gm : game->group->members) {
		int lvl = gm->character->GetLevel();
		MCGLevelsSum += lvl;
		if (MCGMaxLevel < lvl) MCGMaxLevel = lvl;
	}
	double MCGAverageLevel = MCGLevelsSum / MCGMembersCount;

	int enemiesCount = (std::max)(1, rnd((std::max)(MCGMembersCount - 3, 0), MCGMembersCount + 3));

	for (int i = 0; i < enemiesCount; i++) {
		Character* en = nullptr;
		int enemyType = rnd(1, 3);
		int enemyLevel = chance(1, 2) ? rnd((std::max)((int)MCGAverageLevel - 4, 1), MCGAverageLevel + 2) : rnd(1, MCGMaxLevel);

		switch (enemyType) {
			case 1: en = new Zombie(string("Зомби"), enemyLevel); break;
			case 2: en = new Skeleton(string("Скелет"), enemyLevel); break;
			case 3: en = new Goblin(string("Гоблин"), enemyLevel); break;
		}
		En.AddMember(en);
	}

	ConsoleBattle cb(game->group, &En);
	auto res = cb.Start();

	if (res == BattleResult::Dead) {
		cout << "Возвращение в таверну, члены команды потеряны, золото сброшено до 100...\n" << endl;
		delete game->group;
		game->group = nullptr;
		game->hero->Revive();
	}
	else {
		cout << "Возвращение в город...\n" << endl;
	}
}

void GoDungeon(Game* game, Dungeon* dungeon) {
	bool priest = false;
	for (GroupMember* gm : game->group->members) {
		if (dynamic_cast<Priest*>(gm->character) != nullptr) {
			priest = true;
			break;
		}
	}

	int floor = 1;
	for (Group*& group : dungeon->Floors) {
		cout << "--- ЭТАЖ " << floor++ << " ---";
		if (group == nullptr) {
			cout << " (зачищен)";
			continue;
		}
		cout << endl;

		ConsoleBattle cb(game->group, group);
		auto res = cb.Start();

		if (res == BattleResult::Dead) {
			cout << "Возвращение в таверну, члены команды потеряны, золото сброшено до 100...\n" << endl;
			delete game->group;
			game->group = nullptr;
			game->hero->Revive();
			return;
		}

		// если сбежали...

		delete group;
		group = nullptr;

		if (floor - 1 == dungeon->Floors.size()) {
			dungeon->Completed = true;
			cout << "Подземелье успешно пройдено!" << endl << endl;

			cout << dungeon->Rewards.Message << endl << endl;

			Reward& rw = dungeon->Rewards;
			if (rw.Experience > 0) {
				cout << "Дополнительный опыт для всей команды: " << rw.Experience << endl;
				for (GroupMember* member : game->group->members) {
					AdvancedCharacter* ach = dynamic_cast<AdvancedCharacter*>(member->character);
					if (ach != nullptr)
						ach->AddExperience(rw.Experience);
				}
			}
			if (rw.Gold > 0) {
				cout << "Найден клад с золотом: " << rw.Gold << endl;
				game->hero->AddGold(rw.Gold);
			}
			if (rw.Artifacts.size() > 0) {
				cout << "Найдены артефакты:" << endl;
				for (Artifact* art : rw.Artifacts) {
					cout << "+ " << art->Name << endl;
					game->hero->GetInventory().AddItem(art);
				}
			}
			cout << endl;

			game->dungeons.erase(std::remove(game->dungeons.begin(), game->dungeons.end(), dungeon), game->dungeons.end());
			break;
		}

		for (GroupMember* member : game->group->members)
			member->character->RestoreMana();
		cout << "Мана членов команды восстановлена" << endl;

		if (priest) {
			for (GroupMember* member : game->group->members)
				member->character->RestoreHealth();
			cout << "Здоровье членов команды восстановлено" << endl;
		}
		cout << endl;

		int action = ReadInt("(1 - продолжить, 0 - вернуться в город): ");
		if (action == 0)
		{
			cout << "Возвращение в город...\n" << endl;
			return;
		}
	}
}

void ShowInventory(Game* game)
{
	Inventory& inv = game->hero->GetInventory();
	WriteInventory(inv);
	cout << endl;

	while (1) {
		int action = ReadInt
		(
			"Выберите действие:\n"
			"0. Выход\n"
			"1. Посмотреть используемые артефакты\n"
			"2. Посмотреть сумку\n"
			"3. Использовать артефакт из сумки\n"
			"> ",
			[](int i, string& msg) { return i >= 0 && i <= 3; },
			true
		);
		if (action == 0) break;

		switch (action) {
			case 1:
				WriteInventory(inv);
				cout << endl;
				break;

			case 2:
			{
				int i = 1;
				for (Artifact* art : inv.GetItems()) {
					cout << i++ << ". ";
					WriteArtifactInfo(art, 2);
					cout << endl;
				}
			}
			break;

			case 3:
			{
				const vector<Artifact*>& arts = inv.GetItems();
				int i = 1;
				for (Artifact* art : arts) {
					cout << i++ << ". " << art->Name << endl;
				}
				cout << endl;

				int artInd = ReadInt("Введите номер артефакта в сумке, который хотите испоьзовать: ",
					[&arts](int i, string& msg) { return i >= 1 && i <= arts.size(); }, true) - 1;

				vector<Artifact*> _arts;

				auto artType = inv.GetItems()[artInd]->Type;
				if (artType == ArtifactType::Hand && inv.GetMainWeapon() != nullptr && inv.GetAdditionalWeapon() != nullptr) {
					int sel = ReadInt
					(
						"Выберите артефакт, который хотите заменить:\n"
						"1. Главное оружие\n"
						"2. Дополнительное оружие\n"
						"> ",
						[](int i, string& msg) { return i >= 1 && i <= 2; },
						true
					);
					switch (sel) {
						case 1:
						{
							auto art = inv.UseAsMainWeapon(artInd);
							if (art != nullptr)
								_arts.push_back(art);
						} break;
						case 2:
						{
							auto art = inv.UseAsAdditionalWeapon(artInd);
							if (art != nullptr)
								_arts.push_back(art);
						} break;
					}
				}
				else
					_arts = inv.Use(artInd);

				if (_arts.size() > 0) {
					if (_arts.size() == 1) {
						cout << "Артефакт " << _arts[0]->Name << " возвращён в сумку" << endl;
					}
					else {
						cout << "Артефакты ";
						bool first = true;
						for (Artifact* art : _arts) {
							cout << (first ? "" : ", ") << art->Name;
							first = false;
						}
						cout << " были возвращены в сумку" << endl;
					}
					cout << endl;
				}
			}
			break;
		}
	};
}

void Shop(Game* game) {
	while (1) {
		int action = ReadInt
		(
			"Выберите действие:\n"
			"0. Выход\n"
			"1. Наёмники\n"
			"2. Артефакты\n"
			"3. Карты подземелий\n"
			"> ",
			[](int i, string& msg) { return i >= 0 && i <= 3; },
			true
		);
		if (action == 0) break;

		switch (action) {
			case 1: MercenaryShop(game); break;
			case 2: ArtifactsShop(game); break;
			case 3: DungeonsShop(game); break;
		}
	};
}

void MercenaryShop(Game* game) {
	while (1) {
		cout << "Золото: " << game->hero->GetGold() << endl << endl;
		int action = ReadInt
		(
			"Выберите действие:\n"
			"0. Выход\n"
			"1. Нанять паладина (прециализация на защите) - 100 * 1.5^(L-1)\n"
			"2. Нанять жреца (специализация на поддержке союзников) - 100 * 1.5^(L-1)\n"
			"> ",
			[](int i, string& msg) { return i >= 0 && i <= 2; },
			true
		);
		if (action == 0) break;

		std::function<int(int lvl)> costC = nullptr;
		switch (action) {
			case 1:
			case 2:
			{
				costC = [](int lvl) { return 100 * pow(1.5, lvl - 1); };
			} break;
		}

		while (1) {
			int lvl = ReadInt("Введите уровень наёмника (0 - выход): ", [](int i, string& msg) { return i >= 0 && i <= 20; }, true);
			if (lvl == 0) break;

			int cost = costC(lvl);

			if (game->hero->GetGold() < cost) {
				cout << "Цена: " << cost << ", недостаточно золота\n" << endl;
				continue;
			}
			cout << "Цена: " << cost << endl;
			int confirmation = ReadInt("Желаете приобрести наёмника? (1 - да, 0 - нет): ", [](int i, string& msg) { return i >= 0 && i <= 1; }, true);
			if (confirmation == 1) {
				AdvancedCharacter* mercenary = nullptr;
				switch (action) {
					case 1: mercenary = new Paladin("Паладин", lvl); break;
					case 2: mercenary = new Priest("Жрец", lvl); break;
				}
				game->group->AddMember(mercenary);
				game->hero->TakeGold(cost);

				cout << "Покупка прошла успешно\n" << endl;
				break;
			}
		}
	}
}

void ArtifactsShop(Game* game) {
	while (1) {
		cout << "Золото: " << game->hero->GetGold() << endl << endl;
		cout << "Выберите артефакт:\n0. Выход\n";
		int i = 1;
		for (Artifact* art : ArtifactsForSale)
			cout << i++ << ". " << art->Name << " - " << art->Cost << endl;
		int action = ReadInt("> ", [](int i, string& msg) { return i >= 0 && i <= ArtifactsForSale.size(); }, true);
		if (action == 0) break;

		Artifact* art = ArtifactsForSale[action - 1];

		WriteArtifactInfo(art);
		int cost = art->Cost;
		if (game->hero->GetGold() < cost) {
			cout << "Цена: " << cost << ", недостаточно золота\n" << endl;
			continue;
		}
		cout << "Цена: " << cost << endl << endl;
		int confirmation = ReadInt("Желаете приобрести артефакт? (1 - да, 0 - нет): ", [](int i, string& msg) { return i >= 0 && i <= 1; }, true);
		if (confirmation == 0) continue;

		game->hero->GetInventory().AddItem(art);
		game->hero->TakeGold(cost);

		cout << "Покупка прошла успешно\n" << endl;
	};
}

void DungeonsShop(Game* game)
{
	while (1) {
		vector<DungeonMap> dungeons;
		if (game->CompletedDungeons >= 3) {
			// Тут будет покупка генерируемых подземелий
		}
		else
			if (game->dungeons.size() == 0) {
				if (game->CompletedDungeons == 0) {
					dungeons = { DungeonMap("Первое подземелье", 200, []() { return &FirstDungeon; }) };
				}
				// == 1
				// == 2
			}

		if (dungeons.size() == 0) {
			cout << "Нет карт в продаже\n" << endl;
			break;
		}

		cout << "Золото: " << game->hero->GetGold() << endl << endl;

		cout << "Выберите карту подземелья:\n0. Выход\n";
		int i = 1;
		for (DungeonMap& dm : dungeons)
			cout << i++ << ". " << dm.Name << " - " << dm.Cost << endl;

		int action = ReadInt("> ", [&dungeons](int i, string& msg) { return i >= 0 && i <= dungeons.size(); }, true);
		if (action == 0) break;

		DungeonMap& dm = dungeons[action - 1];

		if (game->hero->GetGold() < dm.Cost) {
			cout << "Цена: " << dm.Cost << ", недостаточно золота\n" << endl;
			continue;
		}
		int confirmation = ReadInt("Желаете приобрести карту? (1 - да, 0 - нет): ", [](int i, string& msg) { return i >= 0 && i <= 1; }, true);
		if (confirmation == 0) continue;

		game->dungeons.push_back(dm.GetDungeon());
		game->hero->TakeGold(dm.Cost);

		cout << "Покупка прошла успешно\n" << endl;
		break;
	};
}
