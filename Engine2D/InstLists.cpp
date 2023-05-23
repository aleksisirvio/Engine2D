#include "InstLists.h"

InstMap InstLists::map;

/********************************************************************
InstLists::get

Returns the instance list with the corresponding key.
********************************************************************/
InstList<GameObject*>* InstLists::get(int code)
{
	if (!map.count(code))
		return nullptr;

	return &map.at(code);
}

/********************************************************************
InstLists::add

Adds a game object into the instance list with the corresponding
code.
********************************************************************/
void InstLists::add(GameObject* toAdd, int code)
{
	if (map.count(code))
		map.at(code).push_back(toAdd);
	else
		map.insert({ code, {toAdd} });
}

/********************************************************************
InstLists::remove

Removes a game object from the instance list with the corresponding
code.
********************************************************************/
void InstLists::remove(GameObject* toRemove, int code)
{
	if (map.count(code))
		map.at(code).remove(toRemove);
}
