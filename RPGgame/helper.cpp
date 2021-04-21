#include "helper.h"

int ReadInt(const char* text, std::function<bool(int i, string& msg)> pred, bool nl)
{
	int val = 0;
	cout << text;
	while (1) {
		if (!(cin >> val)) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "������ �����" << std::endl << "_> ";
			continue;
		}
		cin.ignore(INT_MAX, '\n');

		string predMsg;
		if (pred != nullptr && !pred(val, predMsg)) {
			if (predMsg.empty())
				cout << "�������� ����";
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
				cout << "�������� ����";
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
		case EnhancementType::Health: cout << "��������"; break;
		case EnhancementType::MagicPower: cout << "���� �������"; break;
		case EnhancementType::Mana: cout << "����"; break;
		case EnhancementType::Attack:
		{
			AttackEnhancement* aenh = dynamic_cast<AttackEnhancement*>(enhancement);
			if (aenh == nullptr) {
				cout << "����";
				break;
			}

			switch (aenh->AttackType) {
				case AttackEnhancementType::GeneralAttack: cout << "����"; break;
				case AttackEnhancementType::PhysicalAttack: cout << "���. ����"; break;
				case AttackEnhancementType::MagicalAttack: cout << "���. ����"; break;
				case AttackEnhancementType::SlashAttack: cout << "������ ����"; break;
				case AttackEnhancementType::StabAttack: cout << "���������� ����"; break;
				case AttackEnhancementType::ColdAttack: cout << "���� �� ������"; break;
				case AttackEnhancementType::FireAttack: cout << "���� �� ����"; break;
				case AttackEnhancementType::LightningAttack: cout << "���� �� ������"; break;
				case AttackEnhancementType::SacredMagicAttack: cout << "���� �� ������ �����"; break;
			}
		}
		break;
		case EnhancementType::Protection:
		{
			ProtectionEnhancement* penh = dynamic_cast<ProtectionEnhancement*>(enhancement);
			if (penh == nullptr) {
				cout << "������";
				break;
			}

			switch (penh->ProtectionType) {
				case ProtectionEnhancementType::GeneralProtection: cout << "������"; break;
				case ProtectionEnhancementType::PhysicalProtection: cout << "���. ������"; break;
				case ProtectionEnhancementType::MagicalProtection: cout << "���. ������"; break;
				case ProtectionEnhancementType::SlashAttackProtection: cout << "������ �� ������� ����"; break;
				case ProtectionEnhancementType::StabAttackProtection: cout << "������ �� ���������� ����"; break;
				case ProtectionEnhancementType::ColdProtection: cout << "������ �� ������"; break;
				case ProtectionEnhancementType::FireProtection: cout << "������ �� ����"; break;
				case ProtectionEnhancementType::LightningProtection: cout << "������ �� ������"; break;
				case ProtectionEnhancementType::SacredMagicProtection: cout << "������ �� ������ �����"; break;
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
	cout << string(indent, ' ') << "- �������:" << endl;
	WriteEnhancements(artifact->Enhancements, indent + 1);
	cout << string(indent, ' ') << "- ��������� ������:" << endl;
	for (ActiveSkill* skill : artifact->ActiveSkills)
		cout << string(indent + 1, ' ') << "- " << skill->Name << endl;
}

void WriteActiveSkillInfo(ActiveSkill* skill) {
	cout << "*";
	switch (skill->Type) {
		case ActiveSkillType::Attack: cout << "�����"; break;
		case ActiveSkillType::Buff: cout << "����"; break;
		case ActiveSkillType::Debuff: cout << "������"; break;
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
		cout << string(indent, ' ') << "���������:" << endl;
		for (Artifact* art : artifacts) {
			cout << string(indent, ' ') << " - ";
			WriteArtifactInfo(art, indent + 2);
		}
	}

	auto askills = ch->GetActiveSkills();
	if (askills.size() > 0) {
		cout << string(indent, ' ') << "�������� ������:" << endl;
		for (ActiveSkill* askill : askills) {
			cout << string(indent, ' ') << " - ";
			WriteActiveSkillInfo(askill);
		}
	}

	auto pskills = ch->GetPassiveSkills();
	if (pskills.size() > 0) {
		cout << string(indent, ' ') << "��������� ������:" << endl;
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
		cout << ch->Name << " - ����" << endl;
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
		cout << "�������� ������:" << endl << " ";
		WriteArtifactInfo(mainWeapon, 1);
		cout << endl;
	}
	if (additionalWeapon != nullptr) {
		cout << "�������������� ������:" << endl << " ";
		WriteArtifactInfo(additionalWeapon, 1);
		cout << endl;
	}

	if (inv.GetHelmet() != nullptr) {
		cout << "����:" << endl << " ";
		WriteArtifactInfo(inv.GetHelmet(), 1);
		cout << endl;
	}
	if (inv.GetBreastplate() != nullptr) {
		cout << "���������:" << endl << " ";
		WriteArtifactInfo(inv.GetBreastplate(), 1);
		cout << endl;
	}
	if (inv.GetBoots() != nullptr) {
		cout << "�������:" << endl << " ";
		WriteArtifactInfo(inv.GetBoots(), 1);
		cout << endl;
	}
}
