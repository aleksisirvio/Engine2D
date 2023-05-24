#include "Updatable.h"
#include "Room.h"

int Updatable::sKey = -1;

/********************************************************************
Updatable::Updatable

Add to instance list when created.
********************************************************************/
Updatable::Updatable()
{
	Room::getActive()->getLists()->add(this, sKey);
}

/********************************************************************
Updatable::~Updatable

Remove from instance list when destroyed.
********************************************************************/
Updatable::~Updatable()
{
	Room::getActive()->getLists()->remove(this, sKey);
}