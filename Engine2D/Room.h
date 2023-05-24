#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

#include "InstLists.h"

class Room;

using RoomPtr = std::shared_ptr<Room>;
using RoomMap = std::unordered_map<int, RoomPtr>;

/********************************************************************
Room

The game takes place in a room. Only one room can be active at a
time. Rooms have integer IDs associated with them. ID of -1 means
error.
********************************************************************/
class Room
{
public:
	Room() = default;

	// Static methods for managing all rooms
	static RoomPtr getActive();
	static bool setActive(int id);
	static int createRoom(const std::function<void()>& func = nullptr);
	static bool deleteRoom(int id);
	static std::vector<int> roomIds();
	static unsigned int roomCount();
	static void clearRoom();
	static InstLists* getLists();

	// Regular methods for managing a specific room
	float getWidth() const { return mWidth; }
	float getHeight() const { return mHeight; }
	InstLists* getInstLists() { return &mInstLists; }

private:
	static RoomMap sRooms;
	static int sActive;
	static int sRoomCounter;

	float mWidth;
	float mHeight;
	InstLists mInstLists;
};