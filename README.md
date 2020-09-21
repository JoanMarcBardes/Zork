# Zork

This repository contains a code of a simple text mode conversational game, inspired on the game Zork.

## Authors ✒️
Joan Marc Bardés Vera

## GitHub 🖇️
https://github.com/JoanMarcBardes/Zork

## License 📄

This project is under the License GNU GPLv3 - see the [LICENSE.md] file for details

## Guide how to play 📖

This game is a simple conversation game, where for progress you should write the commands you like to do.
You can interact with the different items, creature, non-player character (NPC), directions... using the corresponding command.
The main goal of the game is defeat the final boss, in this case the Troll, in the minimun time posible.
For this you should get weapons, armors, increase your level and yours stats, increase the power of your weapon with magic irons, dialogue with NPC and get the maximum records and advise you can, and equip items to help you tu win.

Enjoy the game.

## Useful commands 📋

commands with no arguments:
* "info", this command prints how to play.
* "help", this command prints all the commands that can be done.
* "quit", this command close the game.
* "restart", this command restart the game.
* "look" or "l", this command print which location are they player and what have this location (items,Monsters,NPC...).
* "north" or "n", this command move the player in that direction.
* "south" or "s", this command move the player in that direction.
* "east" or "e", this command move the player in that direction.
* "west" ot "w", this command move the player in that direction.
* "up" or "u", this command move the player in that direction.
* "down" or "d", this command move the player in that direction.
* "stats" or "st", this command print stats of the player.
* "inventory" or "i", this command print the inventory of the player, and which items are equipped

commands with one argument:
* "look" or "l" [Entity], this command print information about the Entity.
* "go" [Direction], this command move the player to direction [Direction].
* "take" or "pick" [Item], this command take the object [Item] and adds to the inventory.
* "drop" or "put" [Item], this command drop the object [Item] we have in inventory.
* "equip" or "eq" [Item], this command equip the object [Item] we have in inventory.
* "unequip" or "uneq" [Item], this command unequip the object [Item] we have in inventory.
* "examine" or "ex" [Entity], this command examine the [Entity] and print info about that.
* "attack" or "at" [Creature], this command atack the [Creature] until one of two die.
* "loot" or "lt" [dead Craature], this command loot the items are wearing the [dead Craature].
* "talk" or "tk" [NPC], this command talk with [NPC].
* "drink" or "dk" [Item], this command deink the potion [Item].

commands with three arguments:
* "unlock" or "unlk" [Direction or Item] with [Item2], this command unlock a [Direction] or [Item] with [Item2]
* "lock" or "lk" [Direction or Item] with [Item2], this command lock a [Direction] or [Item] with [Item2]
* "take" or "pick" [Item] from [Item2], this command take the object [Item] from [Item2]
* "drop" or "put" [Item] into [Item2], this command put the object [Item] into [Item2]

During the course of the game you may unlock new commands, you will be informed of how to use them.

In the dialogues, you will get some pre-designed answers. You can choose them by writing the answer number "1" or the keyword "keyword".
