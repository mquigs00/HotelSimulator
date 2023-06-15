#include "Party.h"

Party::Party(string name, int numberInParty, string checkInDate)
{
    _name = name;
    _numberInParty = numberInParty;
    _checkInDate = checkInDate;
}

// gets the name of the party
string Party::getName()
{
    return _name;
}

// gets the number of guests oin the party
int Party::getGuestNumber()
{
    return _numberInParty;
}

// gets the check in date of the party
string Party::getCheckInDate()
{
    return _checkInDate;
}

/*
Assigns the party a room

@param assignedRoom - the available room to give them
*/
void Party::setRoom(Room * assignedRoom)
{
    _assignedRoom = assignedRoom;
}

// returns the party's assigned room
Room * Party::getRoom()
{
    return _assignedRoom;
}

/*
Adds a purchase to the party's list of purchases

@param purchase- the purchase to be added
*/
void Party::addCharge(Purchase * purchase)
{
    _purchases.push_back(purchase);
}

// gets the party's vector of purchases
vector<Purchase*> Party::getPurchases()
{
    return _purchases;
}

Party::~Party()
{
    //dtor
}
