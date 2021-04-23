#pragma once

#include "Enhancement.h"
#include "Attack.h"
#include <string>
#include <vector>
#include "ActiveSkill.h"
#include <map>

using std::string;
using std::vector;

enum class ArtifactType { Hand, TwoHanded, Helmet, Breastplate, Boot };

class Artifact
{
public:
	string Name;
	ArtifactType Type;
	int Cost;
	vector<Enhancement*> Enhancements;
	vector<ActiveSkill*> ActiveSkills;

	Artifact(string name, ArtifactType type, int cost, vector<Enhancement*> enhancements, vector<ActiveSkill*> activeSkills = {});

	static std::map<string, Artifact*> Artifacts;
};