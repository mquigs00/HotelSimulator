#include "Room.h"

Room::Room(int floor, int room, string roomNumber)
{
    _floor = floor;
    _room = room;
    _roomNumber = roomNumber;
}

int Room::getFloor()
{
    return _floor;
}

int Room::getRoom()
{
    return _room;
}

string Room::getRoomNumber()
{
    return _roomNumber;
}

Room::~Room()
{
    //dtor
}
