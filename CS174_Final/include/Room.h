#ifndef ROOM_H
#define ROOM_H
#include <string>

using namespace std;

class Room
{
    public:
        Room(int floor, int room, string roomNumber);
        int getFloor();
        int getRoom();
        string getRoomNumber();
        virtual ~Room();

    protected:

    private:
        int _floor;
        int _room;
        string _roomNumber;
};

#endif // ROOM_H
