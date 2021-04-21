#include "ConsoleBattle.h"
#include <iostream>
#include "helper.h"
#include "Hero.h"

using std::cout;
using std::endl;

BattleResult ConsoleBattle::Start()
{
	cout << "---СРАЖЕНИЕ---" << endl << endl;

	auto& g1members = group1->members;
	cout << "Команда 1 - " << group1->Name << endl;

	int i = 0;
	for (GroupMember* member : g1members) {
		member->UpdateSkills();
		Character* ch = member->character;
		WriteCharacterStats(ch);
	}
	cout << endl;

	auto& g2members = group2->members;
	cout << "Команда 2 - " << group2->Name << endl;

	i = 0;
	for (GroupMember* member : g2members) {
		member->UpdateSkills();
		Character* ch = member->character;
		WriteCharacterStats(ch);
	}
	cout << endl;

	GroupMember* hero = *g1members.begin();
	Hero* heroc = dynamic_cast<Hero*>(hero->character);

	int step = 1;
	while (1) {
		cout << "---ХОД " << step << "---" << endl << endl;

		auto skills = hero->availableSkills;

		cout << "Выберите навык:" << endl;
		cout << "0. Пропустить ход (восстановить 25% маны, 20% здоровья)" << endl;
		i = 1;
		for (auto skill : skills) {
			cout << i++ << ". ";
			WriteActiveSkillInfo(skill);
		}
		// TODO: добавить вывод навыков с кол-вом ходов до восстановления
		int skillIndex;
		for (;;) {
			skillIndex = ReadInt("> ", [&skills](int i, string& msg) { return i >= 0 && i <= skills.size(); }, true);
			if (skillIndex != 0 && hero->availableSkills[skillIndex - 1]->ManaUsage > heroc->GetMana())
				cout << "Недостаточно маны для использования навыка" << endl;
			else
				break;
		}

		if (skillIndex > 0)
			hero->ChooseSkill(skills[skillIndex - 1]);

		group1->ChooseAttacks();
		if (skillIndex == 0)
			hero->stepSkill = nullptr;

		group2->ChooseAttacks();

		cout << "Действия 1-й команды:" << endl;

		for (GroupMember* member : group1->members) {
			if (member->stepSkill == nullptr) continue;

			switch (member->stepSkill->Type) {
				case ActiveSkillType::Buff:
				{
					BuffSkill* bskill = dynamic_cast<BuffSkill*>(member->stepSkill);
					Buff buff = member->DoBuff(bskill);
					group1->BuffMembers(buff);
					member->stepSkill = nullptr;

					cout << "- " << member->character->Name << " накладывает бафф \"" << buff.buff->Name << "\"" << endl;
				} break;
				case ActiveSkillType::Debuff:
				{
					BuffSkill* bskill = dynamic_cast<BuffSkill*>(member->stepSkill);
					Buff debuff = member->DoBuff(bskill);
					group2->DebuffMembers(debuff);
					member->stepSkill = nullptr;

					cout << "- " << member->character->Name << " накладывает дебафф \"" << debuff.buff->Name << "\" на команду противника" << endl;
				} break;
			}
		}

		vector<Attack*> g1Attacks;
		for (auto it = group1->members.rbegin(); it != group1->members.rend(); it++) {
			GroupMember* member = *it;
			if (member->stepSkill == nullptr) {
				member->character->RestoreHealth(member->character->GetMaxHealth() * 0.20);
				member->character->RestoreMana(member->character->GetMaxMana() * 0.25);
				continue;
			};
			if (member->stepSkill->ManaUsage == 0) {
				member->character->RestoreMana(member->character->GetMaxMana() * 0.15);
			}

			if (member->stepSkill->Type == ActiveSkillType::Attack) {
				AttackSkill* askill = dynamic_cast<AttackSkill*>(member->stepSkill);
				Attack* attack = member->DoAttack(askill);
				g1Attacks.push_back(attack);
				member->stepSkill = nullptr;

				cout << "- " << member->character->Name << " использует навык \"" << askill->Name << "\"" << endl;
			}
		}


		cout << "Действия 2-й команды:" << endl;

		for (GroupMember* member : group2->members) {
			if (member->stepSkill == nullptr) continue;

			if (member->stepSkill->Type == ActiveSkillType::Buff) {
				BuffSkill* bskill = dynamic_cast<BuffSkill*>(member->stepSkill);
				Buff buff = member->DoBuff(bskill);
				group2->BuffMembers(buff);
				member->stepSkill = nullptr;

				cout << "- " << member->character->Name << " накладывает бафф \"" << buff.buff->Name << "\"" << endl;
			}

			if (member->stepSkill->Type == ActiveSkillType::Debuff) {
				BuffSkill* bskill = dynamic_cast<BuffSkill*>(member->stepSkill);
				Buff debuff = member->DoBuff(bskill);
				group1->DebuffMembers(debuff);
				member->stepSkill = nullptr;

				cout << "- " << member->character->Name << " накладывает дебафф \"" << debuff.buff->Name << "\" на команду противника" << endl;
			}
		}

		vector<Attack*> g2Attacks;
		for (auto it = group2->members.rbegin(); it != group2->members.rend(); it++) {
			GroupMember* member = *it;
			if (member->stepSkill == nullptr) continue;

			if (member->stepSkill->Type == ActiveSkillType::Attack) {
				AttackSkill* askill = dynamic_cast<AttackSkill*>(member->stepSkill);
				Attack* attack = member->DoAttack(askill);
				g2Attacks.push_back(attack);
				member->stepSkill = nullptr;

				cout << "- " << member->character->Name << " использует навык \"" << askill->Name << "\"" << endl;
			}
		}

		auto g1Victims = group1->GetAttacks(g2Attacks);
		auto g2Victims = group2->GetAttacks(g1Attacks);

		group1->Step();
		group2->Step();

		cout << endl;
		cout << "Итог:" << endl;

		cout << "Команда 1:" << endl;
		i = 0;
		for (GroupMember* member : g1Victims) {
			Character* ch = member->character;
			WriteCharacterBattleInfo(member);
		}
		cout << endl;

		cout << "Команда 2:" << endl;
		i = 0;
		for (GroupMember* member : g2Victims) {
			Character* ch = member->character;
			WriteCharacterBattleInfo(member);
		}
		cout << endl;

		group1->HideDeads();
		group2->HideDeads();

		if (heroc->IsDead()) {
			cout << "Вы умерли.\n" << endl;

			group1->deads.erase(std::remove(group1->deads.begin(), group1->deads.end(), hero), group1->deads.end());

			group1->EndBattle();
			group2->EndBattle();

			return BattleResult::Dead;
		}

		if (group2->members.size() == 0) {
			cout << "Вы победили!\n" << endl;

			int _lvl = hero->character->GetLevel();
			int minExp = 0;
			int gold = 0;
			vector<Artifact*> artifacts;
			for (GroupMember* dead : group2->deads) {
				minExp += dead->character->GetLevel() * 10 / 2;
				gold += dead->character->GetGold();
				if (drop)
					for (Artifact* art : dead->character->GetArtifactsList()) {
						if (chance(5)) artifacts.push_back(art);
					}
			}

			for (GroupMember* member : group1->members) {
				AdvancedCharacter* hmember = dynamic_cast<AdvancedCharacter*>(member->character);
				if (hmember != nullptr) {
					int addExp = 0;
					for (GroupMember* enemy : member->affectedEnemies) {
						addExp += enemy->character->GetLevel() * 10;
					}
					hmember->AddExperience(minExp + addExp);
				}
			}

			heroc->AddGold(gold);

			cout << "Все члены команды получают " << minExp << " опыта + за индивидуальные заслуги (убийства и содействия)\n" << endl;

			cout << "Вы получаете:" << endl;
			cout << "+ Золото: " << gold << endl;

			if (artifacts.size() > 0) {
				cout << "+ Артефакты:" << endl;
				for (auto art : artifacts) {
					cout << " - " << art->Name << endl;
					heroc->GetInventory().AddItem(art);
				}
				artifacts.clear();
			}

			group2->EndBattle();

			for (GroupMember* dead : group1->deads) {
				for (Artifact* art : dead->character->GetArtifactsList()) {
					if (chance(4)) artifacts.push_back(art);
				}
			}

			if (artifacts.size() > 0) {
				cout << "+ Артефакты погибших товарищей:" << endl;
				for (auto art : artifacts) {
					cout << " - " << art->Name << endl;
					heroc->GetInventory().AddItem(art);
				}
				artifacts.clear();
			}

			group1->EndBattle();

			return BattleResult::Win;
		}

		step++;
	}

	return BattleResult::Win;

}
