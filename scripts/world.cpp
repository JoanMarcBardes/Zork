#include <iostream>
#include "globals.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

// ----------------------------------------------------
World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* forest = new Room("Forest", "You are surrounded by tall trees. It feels like a huge forest someone could get lost easily.");
	Room* house = new Room("House", "You are inside a beautiful but small white house.");
	Room* basement = new Room("Basement", "The basement features old furniture and dim light.");
	Room* mountain = new Room("Mountain", "You are at the foot of the mountain and heard a great growl.");
	Room* topMuontain = new Room("Top Mountain", "After climbing the mountain they reach the top, where there is a beautiful view.");
	Room* cave = new Room("Cave", "You see a cave where someone seems to live, surrounded by books and scrolls.");


	Exit* exHouseForest = new Exit("west", "east", "Little path", house, forest);
	Exit* exHouseBasement = new Exit("down", "up", "Stairs", house, basement);
	Exit* exHouseCave = new Exit("up", "down", "Winding path", house, cave);
	Exit* exForestMountain = new Exit("west", "east", "Stony path", forest, mountain);
	Exit* exMountainTop = new Exit("up", "down", "Mountain trail", mountain, topMuontain);
	Exit* exTopCave = new Exit("east", "west", "Mountain trail", topMuontain, cave);
	exHouseBasement->locked = true;

	entities.push_back(forest);
	entities.push_back(house);
	entities.push_back(basement);
	entities.push_back(mountain);

	entities.push_back(exHouseForest);
	entities.push_back(exHouseBasement);
	entities.push_back(exHouseCave);
	entities.push_back(exForestMountain);
	entities.push_back(exMountainTop);
	entities.push_back(exTopCave);

	// Creatures ----
	Creature* tortoise = new Creature("Tortoise", "Big tortoise with a huge shell.", house);
	tortoise->hit_points = 6;

	Creature* cyclops = new Creature("Cyclops", "Monster whit only one eye. Looks angry", mountain);
	cyclops->hit_points = 15;

	Creature* troll = new Creature("Troll", "The final boos.", basement);
	troll->hit_points = 50;

	entities.push_back(tortoise);
	entities.push_back(cyclops);
	entities.push_back(troll);

	// Items -----
	Item* mailbox = new Item("Mailbox", "Looks like it might contain something.", house);
	Item* key = new Item("Key", "Old iron key.", mailbox);
	exHouseBasement->key = key;

	Item* sword = new Item("Sword", "A simple old and rusty sword.", forest, WEAPON);
	sword->min_value = 2;
	sword->max_value = 6;

	Item* legendarySword = new Item("LegendarySword", "A Legendary sword, looks very powerfull. Has a hole where you could place something...", topMuontain, WEAPON);
	legendarySword->min_value = 5;
	legendarySword->max_value = 10;

	Item* helmet = new Item("Helmet", "Big Helmet", cyclops, ARMOUR);
	helmet->min_value = 4;
	helmet->max_value = 6;

	Item* mace = new Item("Mace", "Wooden mace", cyclops, WEAPON);
	mace->min_value = 1;
	mace->max_value = 9;
	cyclops->AutoEquip();


	Item* sword2(sword);
	sword2->parent = tortoise;

	Item* shield = new Item("Shield", "An old wooden shield.", tortoise, ARMOUR);
	shield->min_value = 1;
	shield->max_value = 3;
	tortoise->AutoEquip();

	entities.push_back(mailbox);
	entities.push_back(sword);
	entities.push_back(shield);

	// Player ----
	player = new Player("Hero", "You are an awesome adventurer!", forest);
	player->hit_points = 25;
	entities.push_back(player);
}

// ----------------------------------------------------
World::~World()
{
	for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

// ----------------------------------------------------
bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if(args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

// ----------------------------------------------------
void World::GameLoop()
{
	clock_t now = clock();

	if((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

// ----------------------------------------------------
bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch(args.size())
	{
		case 1: // commands with no arguments ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "north") || Same(args[0], "n"))
			{
				(args.size() == 1) ? args.push_back("north") : args[1] = "north";
				player->Go(args);
			}
			else if(Same(args[0], "south") || Same(args[0], "s"))
			{
				(args.size() == 1) ? args.push_back("south") : args[1] = "south";
				player->Go(args);
			}
			else if(Same(args[0], "east") || Same(args[0], "e"))
			{
				(args.size() == 1) ? args.push_back("east") : args[1] = "east";
				player->Go(args);
			}
			else if(Same(args[0], "west") || Same(args[0], "w"))
			{
				(args.size() == 1) ? args.push_back("west") : args[1] = "west";
				player->Go(args);
			}
			else if(Same(args[0], "up") || Same(args[0], "u"))
			{
				(args.size() == 1) ? args.push_back("up") : args[1] = "up";
				player->Go(args);
			}
			else if(Same(args[0], "down") || Same(args[0], "d"))
			{
				(args.size() == 1) ? args.push_back("down") : args[1] = "down";
				player->Go(args);
			}
			else if(Same(args[0], "stats") || Same(args[0], "st"))
			{
				player->Stats();
			}
			else if(Same(args[0], "inventory") || Same(args[0], "i"))
			{
				player->Inventory();
			}
			else
				ret = false;
			break;
		}
		case 2: // commands with one argument ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "go"))
			{
				player->Go(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else if(Same(args[0], "equip") || Same(args[0], "eq"))
			{
				player->Equip(args);
			}
			else if(Same(args[0], "unequip") || Same(args[0], "uneq"))
			{
				player->UnEquip(args);
			}
			else if(Same(args[0], "examine") || Same(args[0], "ex"))
			{
				player->Examine(args);
			}
			else if(Same(args[0], "attack") || Same(args[0], "at"))
			{
				player->Attack(args);
			}
			else if(Same(args[0], "loot") || Same(args[0], "lt"))
			{
				player->Loot(args);
			}
			else
				ret = false;
			break;
		}
		case 3: // commands with two arguments ------------------------------
		{
			break;
		}
		case 4: // commands with three arguments ------------------------------
		{
			if(Same(args[0], "unlock") || Same(args[0], "unlk"))
			{
				player->UnLock(args);
			}
			else if(Same(args[0], "lock") || Same(args[0], "lk"))
			{
				player->Lock(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else
				ret = false;
			break;
		}
		default:
		ret =  false;
	}

	return ret;
}