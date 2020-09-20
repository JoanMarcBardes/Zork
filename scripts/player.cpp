#include <iostream>
#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "npc.h"
#include "player.h"

// ----------------------------------------------------
Player::Player(const char* title, const char* description, Room* room) :
Creature(title, description, room)
{
	type = PLAYER;
	knowForge = false;
}

// ----------------------------------------------------
Player::~Player()
{
}

// ----------------------------------------------------
void Player::Look(const vector<string>& args) const
{
	if(args.size() > 1)
	{
		for(list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if(Same((*it)->name, args[1]) || ((*it)->type == EXIT && Same(args[1], ((Exit*)(*it))->GetNameFrom((Room*)parent))))
			{
				(*it)->Look();
				return;
			}
		}

		for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
		{
			if (Same((*it)->name, args[1]))
			{
				(*it)->Look();
				return;
			}
		}

		if (Same(args[1], "me"))
		{
			cout << "\n" << name << "\n";
			cout << description << "\n";
		}
		else
			cout << "\n" << args[1] << " doesn't exist." <<endl;
	}
	else
	{
		parent->Look();
	}
}

// ----------------------------------------------------
bool Player::Go(const vector<string>& args)
{
	Exit* exit = GetRoom()->GetExit(args[1]);

	if(exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if(exit->locked)
	{
		cout << "\nThat exit is locked.\n";
		return false;
	}

	string blocker_name = GetRoom()->blocker_name;
	Creature* creature = (Creature*)parent->Find(blocker_name, CREATURE);

	if (creature != NULL && creature->IsAlive())
	{
		cout << "\nThe creature " << creature->name << " don't let you escape." "\n";
		return false;
	}

	cout << "\nYou take direction " << exit->GetNameFrom((Room*) parent) << "...\n";
	ChangeParentTo(exit->GetDestinationFrom((Room*) parent));
	parent->Look();

	return true;
}


// ----------------------------------------------------
bool Player::Take(const vector<string>& args)
{
	if(args.size() == 4)
	{
		Item* item = (Item*)parent->Find(args[3], ITEM);

		// we could pick something from a container in our inventory ...
		if(item == NULL)
			item = (Item*)Find(args[3], ITEM);

		if(item == NULL)
		{
			cout << "\nCannot find '" << args[3] << "' in this room or in your inventory.\n";
			return false;
		}

		if (item->locked)
		{
			cout << "\n'" << args[3] << "' is locked.\n";
			return false;
		}

		Item* subitem = (Item*)item->Find(args[1], ITEM);

		if(subitem == NULL)
		{
			cout << "\n" << item->name << " does not contain '" << args[1] << "'.\n";
			return false;
		}

		if (subitem->blocked_parent)
		{
			cout << "\n" << subitem->name << " cannot be removed from " << item->name << ".\n";
			return false;
		}

		cout << "\nYou take " << subitem->name << " from " << item->name << ".\n";
		subitem->ChangeParentTo(this);
	}
	else if(args.size() == 2)
	{
		Item* item = (Item*)parent->Find(args[1], ITEM);

		if(item == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		if (item->blocked_parent)
		{
			cout << "\nCan't take " << item->name << " is immovable.\n";
			return false;
		}

		cout << "\nYou take " << item->name << ".\n";
		item->ChangeParentTo(this);
	}

	return false;
}

// ----------------------------------------------------
void Player::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

	if(items.size() == 0)
	{
		cout << "\nYou do not own any item.\n";
		return;
	}

	for(list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		if(*it == weapon)
			cout << "\n" << (*it)->name << " (as weapon)";
		else if(*it == armour)
			cout << "\n" << (*it)->name << " (as armour)";
		else
			cout << "\n" << (*it)->name;
	}

	cout << "\n";
}

// ----------------------------------------------------
bool Player::Drop(const vector<string>& args)
{
	if(args.size() == 2)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if(item == NULL)
		{
			cout << "\nThere is no item on you with that name.\n";
			return false;
		}

		cout << "\nYou drop " << item->name << "...\n";
		item->ChangeParentTo(parent);

		return true;
	}
	else if(args.size() == 4)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if(item == NULL)
		{
			cout << "\nCan not find item '" << args[1] << "' in your inventory.\n";
			return false;
		}

		Item* container = (Item*)parent->Find(args[3], ITEM);

		if(container == NULL)
		{
			cout << "\nCan not find item '" << args[3] << "' in the room.\n";
			return false;
		}

		if(!container->CanContainItem(item->item_type))
		{
			cout << "\nThe item '" << args[3] << "' cannot contain '" << args[1] << "'\n";
			return false;
		}

		cout << "\nYou put " << item->name << " into " << container->name << ".\n";
		item->ChangeParentTo(container);

		return true;
	}
	
	return false;
}

// ----------------------------------------------------
bool Player::Equip(const vector<string>& args)
{
	Item* item = (Item*)Find(args[1], ITEM);

	if(item == NULL)
	{
		cout << "\nCannot find '" << args[1] << "' is not in your inventory.\n";
		return false;
	}

	switch(item->item_type)
	{
		case WEAPON:
		weapon = item;
		break;

		case ARMOUR:
		armour = item;
		break;

		case LIGHT:
		light = item;
		break;

		default:
		cout << "\n" << item->name << " cannot be equipped.\n";
		return false;
	}
		
	cout << "\nYou equip " << item->name << "...\n";

	return true;
}

// ----------------------------------------------------
bool Player::UnEquip(const vector<string>& args)
{
	if(!IsAlive())
		return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if(item == NULL)
	{
		cout << "\n" << item->name << " is not in your inventory.\n";
		return false;
	}

	if(item == weapon)
		weapon = NULL;
	else if(item == armour)
		armour = NULL;
	else if (item == light)
		light = NULL;
	else
	{
		cout << "\n" << item->name << " is not equipped.\n";
		return false;
	}

	cout << "\nYou un-equip " << item->name << "...\n";

	return true;
}

// ----------------------------------------------------
bool Player::Examine(const vector<string>& args) const
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if(target == NULL)
	{
		cout << "\n" << args[1] << " is not here.\n";
		return false;
	}

	target->Inventory();
	target->Stats();

	return true;
}

// ----------------------------------------------------
bool Player::Attack(const vector<string>& args)
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if(target == NULL)
	{
		cout << "\n" << args[1] << " is not here.";
		return false;
	}

	combat_target = target;
	cout << "\nYou jump to attack " << target->name << "!\n";
	return true;
}

// ----------------------------------------------------
bool Player::Loot(const vector<string>& args)
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if(target == NULL)
	{
		cout << "\n" << args[1] << " is not here.\n";
		return false;
	}

	if(target->IsAlive() == true)
	{
		cout << "\n" << target->name << " cannot be looted until it is killed.\n";
		return false;
	}

	list<Entity*> items;
	target->FindAll(ITEM, items);

	if(items.size() > 0)
	{
		cout << "\nYou loot " << target->name << "'s corpse:\n";

		for(list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
		{
			Item* i = (Item*)(*it);
			cout << "You find: " << i->name << "\n";
			i->ChangeParentTo(this);
		}
	}
	else
		cout << "\nYou loot " << target->name << "'s corpse, but find nothing there.\n";

	return true;
}

// ----------------------------------------------------
bool Player::Lock(const vector<string>& args)
{
	if(!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if(exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if(exit->locked == true)
	{
		cout << "\nThat exit is already locked.\n";
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if(item == NULL)
	{
		cout << "\nItem '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if(exit->key != item)
	{
		cout << "\nItem '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
		return false;
	}

	cout << "\nYou lock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->locked = true;

	return true;
}

// ----------------------------------------------------
bool Player::UnLock(const vector<string>& args)
{
	if(!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);
	Item* chest = (Item*)parent->Find(args[1], ITEM);

	if(exit == NULL && chest == NULL)
	{
		cout << "\nDoes not exist '" << args[1] << "'.\n";
		return false;
	}

	if (exit != NULL)
	{
		if (exit->locked == false)
		{
			cout << "\nThat exit is not locked.\n";
			return false;
		}

		Item* item = (Item*)Find(args[3], ITEM);

		if (item == NULL)
		{
			cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
			return false;
		}

		if (exit->key != item)
		{
			cout << "\nKey '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
			return false;
		}

		cout << "\nYou unlock " << exit->GetNameFrom((Room*)parent) << "...\n";

		exit->locked = false;
	}
	else
	{
		if (chest->locked == false)
		{
			cout << "\nThat item is not locked.\n";
			return false;
		}

		Item* item = (Item*)Find(args[3], ITEM);

		if (item == NULL)
		{
			cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
			return false;
		}

		if (chest->key != item)
		{
			cout << "\nKey '" << item->name << "' is not the key for " << chest->name << ".\n";
			return false;
		}

		cout << "\nYou unlock " << chest->name << "...\n";

		chest->locked = false;
	}
	

	return true;
}

// ----------------------------------------------------
bool Player::Talk(const vector<string>& args)
{
	Npc *target = (Npc*)parent->Find(args[1], NPC);

	if (target == NULL)
	{
		cout << "\nCan't talk with" << args[1] << ".";
		return false;
	}

	if (!target->IsAlive())
	{
		cout << "\nCan't talk with" << args[1] << " is death.";
		return false;
	}

	target->Dialogue(INTRO);
	return true;
}

// ----------------------------------------------------
bool Player::Forge(const vector<string>& args)
{
	if (args.size() == 4)
	{
		if (!knowForge)
		{
			cout << "\n You don't know how to forge" << endl;
			return false;
		}

		Item* weapon = (Item*)Find(args[1], ITEM);

		if (weapon == NULL)
		{
			cout << "\nCan not find '" << args[1] << "' in your inventory.\n";
			return false;
		}

		if (weapon->item_type != WEAPON)
		{
			cout << "\nThis item '" << args[1] << "' cannot be forged\n";
			return false;
		}

		Item* metal = (Item*)Find(args[3], ITEM);

		if (metal == NULL)
		{
			cout << "\nCan not find '" << args[3] << "' in your inventory.\n";
			return false;
		}

		if (!weapon->CanContainItem(metal->item_type))
		{
			cout << "\nThe item '" << args[1] << "' cannot be forged with '" << args[3] << "'\n";
			return false;
		}

		cout << "\nYou forge " << weapon->name << " with " << metal->name << ".\n";
		cout << "\nNow " << weapon->name << " looks more powerful.\n";
		metal->ChangeParentTo(weapon);
		metal->blocked_parent = true;
		weapon->AddValue(5);

		return true;
	}

	return false;
}

// ----------------------------------------------------
bool Player::Drink(const vector<string>& args)
{
	Item* item = (Item*)Find(args[1], ITEM);
	if (item != NULL && item->item_type == DRINK)
	{
		hit_points = max_hit_points;
		cout << "\nYou drink a potion and restore all hit points." << endl;
		container.remove(item);
		return true;
	}
	
	cout << "\nYou have't potions in your inventory." << endl;

	return true;
}

// ----------------------------------------------------
void Player::LevelUp()
{
	cout << "\nLevel up!!";
	cout << "\nWhat skill do you want to improve:";
	cout << "\n 1. Life  2. Attack  3. Armor" << endl;

	string arg;
	cin >> arg;

	if (Same(arg, "Life") || Same(arg, "1"))
	{
		hit_points += 5;
		max_hit_points += 5;
		cout << "\nHit points increased +5." << endl;
	}
	else if (Same(arg, "Attack") || Same(arg, "2"))
	{
		min_damage += 1;
		max_damage += 2;
		cout << "\nDamage increased +(1-2)." << endl;
	}
	else if (Same(arg, "Armor") || Same(arg, "3"))
	{
		min_protection += 1;
		max_protection += 2;
		cout << "\nArmor increased +(1-2)." << endl;
	}
	cout << ">";
}

// ----------------------------------------------------
void Player::Tick()
{
	if (combat_target != NULL)
	{
		if (parent->Find(combat_target) == true)
			MakeAttack();
		else
			combat_target = NULL;

		if (combat_target != NULL && !combat_target->IsAlive()) {
			LevelUp();
			combat_target = NULL;
		} 
	}
}