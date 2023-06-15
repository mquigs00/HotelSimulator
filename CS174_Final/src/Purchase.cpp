#include "Purchase.h"

Purchase::Purchase(string name, string description, double fee, string date)
{
    _name = name;
    _description = description;
    _fee = fee;
    _date = date;
}

// gets the name of the person who made the purchase
string Purchase::getName()
{
    return _name;
}

// gets the amenity bought in the purchase
string Purchase::getDescription()
{
    return _description;
}

// gets the price of the purchase
double Purchase::getFee()
{
    return _fee;
}

// gets the date the purchase was made
string Purchase::getDate()
{
    return _date;
}

Purchase::~Purchase()
{
    //dtor
}
