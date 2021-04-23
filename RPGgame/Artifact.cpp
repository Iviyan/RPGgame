#include "Artifact.h"

Artifact::Artifact(string name, ArtifactType type, int cost, vector<Enhancement*> enhancements, vector<ActiveSkill*> activeSkills)
	: Name(name), Type(type), Cost(cost), Enhancements(enhancements), ActiveSkills(activeSkills)
{
	Artifacts[name] = this;
}

std::map<string, Artifact*> Artifact::Artifacts;