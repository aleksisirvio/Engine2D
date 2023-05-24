#include "Room.h"

// Initialize static members
RoomMap Room::sRooms;
int Room::sActive = -1;
int Room::sRoomCounter = 0;

/********************************************************************
Room::getActive

Returns a pointer to the active room.
********************************************************************/
RoomPtr Room::getActive()
{
	if (!sRooms.count(sActive))
		return nullptr;

	return sRooms.at(sActive);
}

/********************************************************************
Room::setActive

Sets the room with the given ID as active. Returns true if ID is
valid, false if not.
********************************************************************/
bool Room::setActive(int id)
{
	if (!sRooms.count(id))
		return false;

	sActive = id;
	return true;
}

/********************************************************************
Room::createRoom

Creates a new room of the given type and returns its ID. Calls an
initializer function of the room if one is given as a parameter.
********************************************************************/
int Room::createRoom(const std::function<void()>& func)
{
	auto room = std::make_shared<Room>();
	sRooms.insert({ sRoomCounter, room });

	if (func)
		func();

	return sRoomCounter++;
}

/********************************************************************
Room::deleteRoom

Deletes a room with the given ID. Returns true if deletio was
successful, false if not.
********************************************************************/
bool Room::deleteRoom(int id)
{
	if (id == sActive || !sRooms.count(id))
		return false;

	sRooms.at(id)->getInstLists()->clear();
	sRooms.erase(id);

	sRoomCounter--;
	return true;
}

/********************************************************************
Room::roomIds

Returns a container of all the IDs of existing rooms.
********************************************************************/
std::vector<int> Room::roomIds()
{
	std::vector<int> ids(sRooms.size());
	for (const auto& room : sRooms)
		ids.push_back(room.first);

	return ids;
}

/********************************************************************
Room::roomCount

Returns how many rooms exist.
********************************************************************/
unsigned int Room::roomCount()
{
	return sRooms.size();
}

/********************************************************************
Room::clearRooms

Destroys all rooms;
********************************************************************/
void Room::clearRoom()
{
	for (const auto& room : sRooms)
		deleteRoom(room.first);
}

/********************************************************************
Room::getLists

Returns all instance lists from the ACTIVE room.
********************************************************************/
InstLists* Room::getLists()
{
	return getActive()->getInstLists();
}