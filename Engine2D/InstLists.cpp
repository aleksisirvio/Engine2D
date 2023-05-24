#include "InstLists.h"

InstMap InstLists::sMap;

/********************************************************************
InstLists::get

Returns the instance list with the corresponding key.
********************************************************************/
InstList<GameObject*>* InstLists::get(int code)
{
	if (!sMap.count(code))
		return nullptr;

	return &sMap.at(code);
}

/********************************************************************
InstLists::add

Adds a game object into the instance list with the corresponding
code.
********************************************************************/
void InstLists::add(GameObject* toAdd, int code)
{
	if (sMap.count(code))
		sMap.at(code).push_back(toAdd);
	else
		sMap.insert({ code, {toAdd} });
}

/********************************************************************
InstLists::remove

Removes a game object from the instance list with the corresponding
code.
********************************************************************/
void InstLists::remove(GameObject* toRemove, int code)
{
	if (sMap.count(code))
		sMap.at(code).remove(toRemove);
}
