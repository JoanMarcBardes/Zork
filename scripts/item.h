#ifndef __Item__
#define __Item__

#include <string>
#include "entity.h"

class Room;

using namespace std;

enum ItemType
{
	COMMON,
	WEAPON,
	ARMOUR,
	MAGIC,
	NONE
};

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, ItemType item_type = COMMON, ItemType container_of = NONE);
	~Item();

	void Look() const;
	int GetValue() const;
	void AddValue(int plus);
	bool CanContainItem(ItemType item_type) const;

public :
	int min_value;
	int max_value;
	ItemType item_type;
	ItemType container_of;
};

#endif //__Item__