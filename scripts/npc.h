#ifndef __Npc__
#define __Npc__

#include "creature.h"

using namespace std;

enum RewardsType
{
	NOTHING,
	MASTER_KEY,
	POTION,
	FORGE,
	GOLD,
	ADVICE
};

enum DalogueType
{
	INTRO,
	HELP,
	IGNORE,
	HERO,
	KILLER,
	REWARD,
	MONEY,
	WISDOM,
	END
};

class Npc : public Creature
{
public:
	Npc(const char* name, const char* description, Room* room);
	~Npc();

	void Dialogue(const DalogueType dialogue_type);
	void Answers(const DalogueType dialogue_type);
	void WrongAnswer(const DalogueType dialogue_type);
	void EndDialogue();
	void GetReguards();

private:
	list<RewardsType> reguards;
	bool finish;
};

#endif //__Npc__