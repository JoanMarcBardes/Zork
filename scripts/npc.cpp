#include <iostream>
#include "globals.h"
#include "room.h"
#include "item.h"
#include "player.h"
#include "npc.h"


// ----------------------------------------------------
Npc::Npc(const char* title, const char* description, Room* room) :
	Creature(title, description, room, false)
{
	finish = false;
	type = NPC;
}

// ----------------------------------------------------
Npc::~Npc()
{
}

// ----------------------------------------------------
void Npc::Dialogue(DalogueType dialogue_type) 
{
	if (finish) {
		EndDialogue();
		return;
	}

	switch (dialogue_type) 
	{
		case INTRO:
			cout << "\n\nHello young traveler, would you like to hear my story ...";
			cout << "\nWell below us there is a beautiful house where I used to live, \nbut an evil troll appeared and kick me out, that's why now I live here in this cave.";
			cout << "\nCan you help me?";
			cout << "\n 1. 'Help' old man\n 2. 'Ignore' old man \n>";
			Answers(INTRO);
			break;

		case IGNORE:
			cout << "\nOh what a shame, it seemed like you were a hero... \nI'll have to keep living in this disgusting cave." << endl;
			EndDialogue();
			break;

		case HELP:
			cout << "\nThank you for being willing to help me, but what are your reasons for helping me?";
			cout << "\n 1. I'm a 'Hero' of course i'll help you\n 2. I'm a 'Killer' of monsters\n 3. I would like to earn a 'Reward' \n>";
			Answers(HELP);
			break;

		case HERO:
			cout << "\nI knew you were a Hero, so I'll help you in any way I can." << endl;
			reguards.push_back(MASTER_KEY);
			reguards.push_back(POTION);
			reguards.push_back(FORGE);
			reguards.push_back(ADVICE);
			Dialogue(END);
			break;

		case KILLER:
			cout << "\nYou like to kill monsters...";
			reguards.push_back(MASTER_KEY);
			Dialogue(END);
			break;

		case REWARD:
			cout << "\nI see it just that you want a reward, what kind of reward do you want?";
			cout << "\n 1. Give me 'Money'\n 2. Teach me your 'Wisdom' \n>";
			Answers(REWARD);
			break;

		case MONEY:
			cout << "\nI don't have much, that's all I can give you.";
			reguards.push_back(MASTER_KEY);
			reguards.push_back(GOLD);
			Dialogue(END);
			break;

		case WISDOM:
			cout << "\nWise answer, I'll teach you everything I know.";
			reguards.push_back(MASTER_KEY);
			reguards.push_back(FORGE);
			reguards.push_back(ADVICE);
			Dialogue(END);
			break;

		case END:
			GetReguards();
			EndDialogue();
			break;
	}
}

// ----------------------------------------------------
void Npc::Answers(const DalogueType dialogue_type)
{
	string answer;
	cin >> answer;

	switch (dialogue_type)
	{
	case INTRO:
		if (Same(answer, "help") || Same(answer, "1"))
			Dialogue(HELP);
		else if (Same(answer, "ignore") || Same(answer, "2"))
			Dialogue(IGNORE);
		else
			WrongAnswer(INTRO);
		break;

	case HELP:
		if (Same(answer, "hero") || Same(answer, "1"))
			Dialogue(HERO);
		else if (Same(answer, "killer") || Same(answer, "2"))
			Dialogue(KILLER);
		else if (Same(answer, "reward") || Same(answer, "3"))
			Dialogue(REWARD);
		else
			WrongAnswer(HELP);
		break;

	case REWARD:
		if (Same(answer, "money") || Same(answer, "1"))
			Dialogue(MONEY);
		else if (Same(answer, "wisdom") || Same(answer, "2"))
			Dialogue(WISDOM);
		else
			WrongAnswer(REWARD);
		break;
	}
}

// ----------------------------------------------------
void Npc::WrongAnswer(const DalogueType dialogue_type)
{
	cout << "\nSorry i don't understand you." << endl;
	Dialogue(dialogue_type);
}

// ----------------------------------------------------
void Npc::EndDialogue()
{
	finish = true;
	cout << "\nGo on with your journey, young traveler." << endl;
}

// ----------------------------------------------------
void Npc::GetReguards()
{
	vector<string> args;
	Player *player = (Player*)parent->Find(PLAYER);
	if (player == NULL)
		cout << "Don't find the player";

	for (list<RewardsType>::const_iterator it = reguards.begin(); it != reguards.cend(); ++it)
	{
		if (*it == NOTHING)
			cout << "\nYou have not got any reward...";
		else if (*it == MASTER_KEY)
		{
			cout << "\nTake this key, it can open a chest with a powerful weapon inside.\nI hope it helps you";
			Item* goldkey = (Item*)parent->Find("GoldKey", ITEM);
			goldkey->blocked_parent = false;
			args = { "Take", "GoldKey" };
			player->Take(args);
		}
		else if (*it == POTION)
		{
			cout << "\nTake this, it's a potion I've just created";
			Item* potion = (Item*)parent->Find("Potion", ITEM);
			potion->blocked_parent = false;
			args = { "Take", "Potion" };
			player->Take(args);
		}
		else if (*it == FORGE)
		{
			cout << "\nI'm going to teach you how to forge, this way you can improve your weapons.";
			cout << "\nTo forge you have to type:\n Forge [weapon] with [iron]" <<endl;
			player->knowForge = true;
		}
		else if (*it == GOLD)
		{
			cout << "\nTake this bag of money, I hope it helps you on your adventure ... (sigh)";
			Item* moneybag = (Item*)parent->Find("Moneybag", ITEM);
			moneybag->blocked_parent = false;
			args = { "Take", "Moneybag" };
			player->Take(args);
		}
		else if (*it == ADVICE)
			cout << "\nOne more thing, to defeat this troll make sure you have a lantern equipped." << endl;

		args.clear();
	}
}