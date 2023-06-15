#include <iostream>
#include "HotelCommander.h"
#include "HotelFactory.h"

using namespace std;

/*
CS174 Final
Matt Quigley
5/11/2020

This program simulates a hotel. A hotel factory class reads in a configuration file that contains the basic information about the hotel. It's
only method instantiates the hotel object with all of the info as its member data. The hotel commander then takes in the hotel object and the
name of the act, which contains all the instructions (check in, check out, charge, bill, report). People are checked into the hotel and checked out,
at which time a file is generated showing all of their charges for lodging and amenities. They can purchase hotel amenities listed in the config file.
The report method provides a file list of current guests with the number in their party, along with a list of all of the non-guest charges for that
day. The bill method creates a bill file with all of their guest's charges up to that day.
*/

int main()
{
    // instantiate factory and hotel
    HotelFactory *hf = new HotelFactory("hotel.conf");
    Hotel * hotel = hf->createHotel();

    // instantiate commander with hotel act file and the hotel
    HotelCommander * commander = new HotelCommander("hotel.act", hotel);

    // have commander execute the commands
    commander->readCommands();

    return 0;
}
