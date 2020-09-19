#include <iostream>
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "item.h"

// ----------------------------------------------------
Item::Item(const char* title, const char* description, Entity* parent, ItemType item_type, ItemType container_of) :
Entity(title, description, parent), item_type(item_type),container_of(container_of), locked(false), key(NULL)
{
	type = ITEM;
	min_value = max_value = 0;
}

// ----------------------------------------------------
Item::~Item()
{}

// ----------------------------------------------------
void Item::Look() const
{
	cout << "\n" << name << "\n";
	cout << description << "\n";

	list<Entity*> stuff;
	FindAll(ITEM, stuff);

	if(stuff.size() > 0)
	{
		cout << "It contains: " << "\n";
		for(list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
			cout << (*it)->name << "\n";
	}

	if (item_type == WEAPON || item_type == ARMOUR)
	{
		item_type == WEAPON ? cout << "Attack: " : cout << "Protection: ";
		cout << min_value << "-" << max_value << endl;
	}
}

// ----------------------------------------------------
int Item::GetValue() const
{
	return Roll(min_value, max_value);
}

// ----------------------------------------------------
void Item::AddValue(int plus)
{
	min_value += plus;
	max_value += plus;
}

// ----------------------------------------------------
bool Item::CanContainItem(ItemType item_type) const
{
	return container_of == item_type;
}
