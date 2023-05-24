#pragma once

#include <list>
#include <unordered_map>

#include "GameObject.h"

template <typename T>
using InstList = std::list<T>;

using InstMap = std::unordered_map<int, InstList<GameObject*>>;

/********************************************************************
InstLists

Class for managing lists of instances of the same type. Listed
objects must inherit common GameObject interface.
********************************************************************/
class InstLists
{
public:
	InstLists() = default;

	static InstList<GameObject*>* get(int code);
	static void add(GameObject* toAdd, int code);
	static void remove(GameObject* toRemove, int code);

	void clear() const { sMap.clear(); }

private:
	static InstMap sMap;
};