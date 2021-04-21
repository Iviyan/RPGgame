#include "helper.h"

int ReadInt(const char* text, std::function<bool(int i, string& msg)> pred, bool nl)
{
	int val = 0;
	cout << text;
	while (1) {
		if (!(cin >> val)) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Ошибка ввода" << std::endl << "_> ";
			continue;
		}
		cin.ignore(INT_MAX, '\n');

		string predMsg;
		if (pred != nullptr && !pred(val, predMsg)) {
			if (predMsg.empty())
				cout << "Неверный ввод";
			else
				cout << predMsg;
			cout << std::endl << "> ";
			continue;
		}

		if (nl) cout << std::endl;
		return val;
	}
}

string ReadString(const char* text, std::function<bool(string s, string& msg)> pred, bool nl)
{
	string val;;
	cout << text;
	while (1) {
		std::getline(cin, val);

		string predMsg;
		if (pred != nullptr && !pred(val, predMsg)) {
			if (predMsg.empty())
				cout << "Неверный ввод";
			else
				cout << predMsg;
			cout << std::endl << "> ";
			continue;
		}

		if (nl) cout << std::endl;
		return val;
	}
}

int rnd(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);
	return uni(rng);
}

bool chance(int count, int of) {
	return rnd(count, of) <= count;
}
bool chance(int of) {
	return rnd(1, of) == 1;
}

using std::endl;

void WriteEnhancement(Enhancement* enhancement) {
	switch (enhancement->Type)
	{
		case EnhancementType::Health: cout << "Здоровье"; break;
		case EnhancementType::MagicPower: cout << "Урон ммагией"; break;
		case EnhancementType::Mana: cout << "Мана"; break;
		case EnhancementType::Attack:
		{
			AttackEnhancement* aenh = dynamic_cast<AttackEnhancement*>(enhancement);
			if (aenh == nullptr) {
				cout << "Урон";
				break;
			}

			switch (aenh->AttackType) {
				case AttackEnhancementType::GeneralAttack: cout << "Урон"; break;
				case AttackEnhancementType::PhysicalAttack: cout << "Физ. урон"; break;
				case AttackEnhancementType::MagicalAttack: cout << "Маг. урон"; break;
				case AttackEnhancementType::SlashAttack: cout << "Режуий урон"; break;
				case AttackEnhancementType::StabAttack: cout << "Пронзающий урон"; break;
				case AttackEnhancementType::ColdAttack: cout << "Урон от холода"; break;
				case AttackEnhancementType::FireAttack: cout << "Урон от огня"; break;
				case AttackEnhancementType::LightningAttack: cout << "Урон от молнии"; break;
				case AttackEnhancementType::SacredMagicAttack: cout << "Урон от святой магии"; break;
			}
		}
		break;
		case EnhancementType::Protection:
		{
			ProtectionEnhancement* penh = dynamic_cast<ProtectionEnhancement*>(enhancement);
			if (penh == nullptr) {
				cout << "Защита";
				break;
			}

			switch (penh->ProtectionType) {
				case ProtectionEnhancementType::GeneralProtection: cout << "Защита"; break;
				case ProtectionEnhancementType::PhysicalProtection: cout << "Физ. защита"; break;
				case ProtectionEnhancementType::MagicalProtection: cout << "Маг. защита"; break;
				case ProtectionEnhancementType::SlashAttackProtection: cout << "Защита от режущих атак"; break;
				case ProtectionEnhancementType::StabAttackProtection: cout << "Защита от пронзающих атак"; break;
				case ProtectionEnhancementType::ColdProtection: cout << "Защита от холода"; break;
				case ProtectionEnhancementType::FireProtection: cout << "Защита от огня"; break;
				case ProtectionEnhancementType::LightningProtection: cout << "Защита от молнии"; break;
				case ProtectionEnhancementType::SacredMagicProtection: cout << "Защита от святой магии"; break;
			}
		}
		break;
	}
	cout << " " << enhancement->Multiplier * 100 << "%";
}

void WriteEnhancements(vector<Enhancement*>& enhancements, int indent) {
	for (Enhancement* enh : enhancements) {
		cout << string(indent, ' ') << "- ";
		WriteEnhancement(enh);
		cout << endl;
	}
}

void WriteArtifactInfo(Artifact* artifact, int indent) {
	cout/* << string(indent, ' ')*/ << artifact->Name << endl;
	cout << string(indent, ' ') << "- Эффекты:" << endl;
	WriteEnhancements(artifact->Enhancements, indent + 1);
	cout << string(indent, ' ') << "- Связанные навыки:" << endl;
	for (ActiveSkill* skill : artifact->ActiveSkills)
		cout << string(indent + 1, ' ') << "- " << skill->Name << endl;
}

void WriteActiveSkillInfo(ActiveSkill* skill) {
	cout << "*";
	switch (skill->Type) {
		case ActiveSkillType::Attack: cout << "атака"; break;
		case ActiveSkillType::Buff: cout << "бафф"; break;
		case ActiveSkillType::Debuff: cout << "дебафф"; break;
	}
	cout << "* - ";
	cout << skill->Name << ", ( " << skill->ManaUsage << "Mn, " << skill->StepsToRestore << " STR ) ( " << skill->Description << " )" << endl;;
}

void WritePassiveSkillInfo(PassiveSkill* skill) {
	cout << skill->Name << ", ( " << skill->Description << " )" << endl;
}

void WriteCharacterStats(Character* ch)
{
	AdvancedCharacter* hero = dynamic_cast<AdvancedCharacter*>(ch);
	cout << ch->Name << " ( "
		<< ch->GetLevel() << "L, ";

	if (hero != nullptr)
		cout << hero->GetExperience() << "/" << hero->GetRequiredExperience() << "Exp, ";

	if (ch->GetMaxHealth() != ch->GetHealth())
		cout << ch->GetHealth() << "/";
	cout << ch->GetMaxHealth() << "H, "

		<< ch->GetProtection() << "Pr, "
		<< ch->GetAttack() << "PD, "
		<< ch->GetMagicPower() << "MD, ";

	if (ch->GetMaxMana() != ch->GetMana())
		cout << ch->GetMana() << "/";
	cout << ch->GetMaxMana() << "Mn )" << endl;
}

void WriteCharacterInfo(Character* ch, int indent)
{
	WriteCharacterStats(ch);

	auto artifacts = ch->GetArtifactsList();
	if (artifacts.size() > 0) {
		cout << string(indent, ' ') << "Артефакты:" << endl;
		for (Artifact* art : artifacts) {
			cout << string(indent, ' ') << " - ";
			WriteArtifactInfo(art, indent + 2);
		}
	}

	auto askills = ch->GetActiveSkills();
	if (askills.size() > 0) {
		cout << string(indent, ' ') << "Активные навыки:" << endl;
		for (ActiveSkill* askill : askills) {
			cout << string(indent, ' ') << " - ";
			WriteActiveSkillInfo(askill);
		}
	}

	auto pskills = ch->GetPassiveSkills();
	if (pskills.size() > 0) {
		cout << string(indent, ' ') << "Пассивные навыки:" << endl;
		for (PassiveSkill* pskill : pskills) {
			cout << string(indent, ' ') << " - ";
			WritePassiveSkillInfo(pskill);
		}
	}
}

void WriteCharacterBattleInfo(GroupMember* gm)
{
	Character* ch = gm->character;
	if (ch->IsDead()) {
		cout << ch->Name << " - мёртв" << endl;
		return;
	}

	cout << ch->Name << " ( "
		<< ch->GetHealth() << "/" << ch->GetMaxHealth() << "H, "
		<< ch->GetMana() << "/" << ch->GetMaxMana() << "Mn )";

	if (gm->buffs.size() > 0 || gm->debuffs.size() > 0) {
		cout << " | ";
		for (Buff& buff : gm->buffs)
			cout << "+" << buff.buff->Name << "(" << buff.remainingSteps << "), ";
		for (Buff& debuff : gm->debuffs)
			cout << "-" << debuff.buff->Name << "(" << debuff.remainingSteps << "), ";
		cout << "|";
	}

	cout << endl;
}

void WriteInventory(Inventory& inv) {
	Artifact* mainWeapon = inv.GetMainWeapon();
	Artifact* additionalWeapon = inv.GetAdditionalWeapon();
	if (mainWeapon != nullptr) {
		cout << "Основное оружие:" << endl << " ";
		WriteArtifactInfo(mainWeapon, 1);
		cout << endl;
	}
	if (additionalWeapon != nullptr) {
		cout << "Дополнительное оружие:" << endl << " ";
		WriteArtifactInfo(additionalWeapon, 1);
		cout << endl;
	}

	if (inv.GetHelmet() != nullptr) {
		cout << "Шлем:" << endl << " ";
		WriteArtifactInfo(inv.GetHelmet(), 1);
		cout << endl;
	}
	if (inv.GetBreastplate() != nullptr) {
		cout << "Нагрудник:" << endl << " ";
		WriteArtifactInfo(inv.GetBreastplate(), 1);
		cout << endl;
	}
	if (inv.GetBoots() != nullptr) {
		cout << "Ботинки:" << endl << " ";
		WriteArtifactInfo(inv.GetBoots(), 1);
		cout << endl;
	}
}
