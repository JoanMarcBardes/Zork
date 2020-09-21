#include <iostream>
#include "globals.h"
#include "Help.h"


Help::Help()
{
}

Help::~Help()
{
}

void Help::PrintHelp() const
{
	cout << "\n## Useful commands ##";

	cout << "\n\ncommands with no arguments :";
	cout << "\n* 'quit', this command close the game.";
	cout << "\n* 'restart', this command restart the game.";
	cout << "\n* 'look' or 'l', this command print which location are they player and what have this location(items, Monsters, NPC...).";
	cout << "\n* 'north' or 'n', this command move the player in that direction.";
	cout << "\n* 'south' or 's', this command move the player in that direction.";
	cout << "\n* 'east' or 'e', this command move the player in that direction.";
	cout << "\n* 'west' ot 'w', this command move the player in that direction.";
	cout << "\n* 'up' or 'u', this command move the player in that direction.";
	cout << "\n* 'down' or 'd', this command move the player in that direction.";
	cout << "\n* 'stats' or 'st', this command print stats of the player.";
	cout << "\n* 'inventory' or 'i', this command print the inventory of the player, and which items are equipped";

	cout << "\n\ncommands with one argument :";
	cout << "\n* 'look' or 'l'[Entity], this command print information about the Entity.";
	cout << "\n* 'go'[Direction], this command move the player to direction[Direction].";
	cout << "\n* 'take' or 'pick'[Item], this command take the object[Item] and adds to the inventory.";
	cout << "\n* 'drop' or 'put'[Item], this command drop the object[Item] we have in inventory.";
	cout << "\n* 'equip' or 'eq'[Item], this command equip the object[Item] we have in inventory.";
	cout << "\n* 'unequip' or 'uneq'[Item], this command unequip the object[Item] we have in inventory.";
	cout << "\n* 'examine' or 'ex'[Entity], this command examine the[Entity] and print info about that.";
	cout << "\n* 'attack' or 'at'[Creature], this command atack the[Creature] until one of two die.";
	cout << "\n* 'loot' or 'lt'[dead Craature], this command loot the items are wearing the[dead Craature].";
	cout << "\n* 'talk' or 'tk'[NPC], this command talk with[NPC].";
	cout << "\n* 'drink' or 'dk'[Item], this command deink the potion[Item].";

	cout << "\n\ncommands with three arguments :";
	cout << "\n* 'unlock' or 'unlk'[Direction or Item] with[Item2], this command unlock a[Direction] or [Item] with[Item2]";
	cout << "\n* 'lock' or 'lk'[Direction or Item] with[Item2], this command lock a[Direction] or [Item] with[Item2]";
	cout << "\n* 'take' or 'pick'[Item] from[Item2], this command take the object[Item] from[Item2]";
	cout << "\n* 'drop' or 'put'[Item] into[Item2], this command put the object[Item] into[Item2]";

	cout << "\n\nDuring the course of the game you may unlock new commands, you will be informed of how to use them.";

	cout << "\n\nIn the dialogues, you will get some pre - designed answers.You can choose them by writing the answer number '1' or the keyword 'keyword'.\n";
}

void Help::PrintInfo() const
{
	cout << "\n## Guide how to play ##";

	cout << "\n\nThis game is a simple conversation game, where for progress you should write the commands you like to do.";
	cout << "\nYou can interact with the different items, creature, non - player character(NPC), directions... using the corresponding command.";
	cout << "\nThe main goal of the game is defeat the final boss, in this case the Troll, in the minimun time posible.";
	cout << "\nFor this you should get weapons, armors, increase your level and yours stats, increase the power of your weapon with magic irons, dialogue with NPC and get the maximum records and advise you can, and equip items to help you tu win.";

	cout << "\n\nEnjoy the game.\n";
}