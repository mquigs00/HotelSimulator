#include "Hotel.h"
#include <iostream>
#include <fstream>

Hotel::Hotel(string hotelName, string streetAddress, string city, string state, string zipcode, string phoneNumber, string faxNumber,
             int numFloors, int roomsPerFloor, int maxOccupancyPerRoom, int peakRoomRate, int offPeakRoomRate, string peakStart,
             string peakEnd, double taxRate, vector<string> amenities)
{
    _hotelName = hotelName;
    _streetAddress = streetAddress;
    _city = city;
    _state = state;
    _zipcode = zipcode;
    _phoneNumber = phoneNumber;
    _faxNumber = faxNumber;
    _numFloors = numFloors;
    _roomsPerFloor = roomsPerFloor;
    _maxOccupancyPerRoom = maxOccupancyPerRoom;
    _peakRoomRate = peakRoomRate;
    _offPeakRoomateRate = offPeakRoomRate;
    _peakStart = peakStart;
    _peakEnd = peakEnd;
    _taxRate = taxRate;
    _amenities = amenities;

    // create the rooms for each floor. Ex: Room 10, 11, 12... 20, 21, 22...
    for (int i = 1; i <= _numFloors; i++) {
        for(int j = 0; j < _roomsPerFloor; j++) {
            // concatenate the i and j values to create the room number
            string roomNumber = to_string(i) + to_string(j);
            Room * room = new Room(i, j, roomNumber);
            _availableRooms.push_back(room); // push the room to the back of the available rooms list
        }
    }
}

// Gets a pointer to an available room and removes it from the list
// @return nextRoom - the next available room in the vector
Room * Hotel::getRoom()
{
    Room * nextRoom = _availableRooms.front();   // get the available room
    _availableRooms.erase(_availableRooms.begin()); // remove it from the list
    return nextRoom;
}

// creates a bill file with the guest's and hotel's info
// @param name - last name of the party
// @param date - date of report or check out
void Hotel::createBill(string name, string date)
{
    // create bill file using guest's name and date
    string billFileName = name + date + ".bill";

    // create .bill file using guest's name and date
    ofstream billFile(billFileName);

    Party * guest = _listOfGuests.at(name); // get a pointer to the party

    if (billFile.is_open()) {
        billFile << "================================================================================ \n";
        billFile << "				    HOTEL BILL\n";
        billFile << "================================================================================ \n";
        billFile << "\n";
        billFile << _hotelName << "\n";
        billFile << _streetAddress << "\n";
        billFile << _city << ", " << _state << " " << _zipcode << "\n";
        billFile << "\n";
        billFile << "Phone: " << _phoneNumber + "\n";
        billFile << "Fax: " << _faxNumber << "\n";
        billFile << "\n";
        billFile << "Guest: " << guest->getName() << "\n";
        billFile << "\n";
        billFile << "CHARGES:\n\n";
        billFile << "Date		Description	    Amount\n";
        billFile << "----		-----------	    ------\n";

        double subtotal = 0;    // create a total for the lodging and purchases charges

        string checkInDateString = guest->getCheckInDate(); // get their check in date

        // convert dates
        DateConverter * converter = new DateConverter();
        int peakStart = converter->getDOY(_peakStart);
        int peakEnd = converter->getDOY(_peakEnd);
        int checkInDate = converter->getDOY(checkInDateString);
        int currentDate = converter->getDOY(date);

        /*
        loop through all the days they stayed in the hotel. If the date is within the peak days, add a lodging charge to the bill
        with the peak rate. Otherwise, add a lodging charge with the non-peak rate. Add all charges to the subtotal
        */
        for (int i = checkInDate; i <= currentDate; i++) {
            string lodgingDate = converter->getStringDate(i, date.substr(4,4)); // get the string version of the day of the year
            string dateWithHyphen = getDate(lodgingDate); // hyphenate it

            // if the day they're their is during the peak dates, add a charge with the peak rate
            if (peakStart <= i && i <= peakEnd) {
                billFile << dateWithHyphen << "        " << "Lodging" << "            " << "$" << _peakRoomRate << "\n";
                subtotal += _peakRoomRate;
            }
            else {
                // if it's not during the peak, add a charge with the non-peak rate
                billFile << dateWithHyphen << "        " << "Lodging" << "            " << "$" << _offPeakRoomateRate << "\n";
                subtotal += _offPeakRoomateRate;
            }
        }

        vector<Purchase*> purchases = guest->getPurchases(); // get the vector of purchases

        // loop through all of the guests purchases and add the info to a new line of the bill
        for (int i = 0; (unsigned)i < purchases.size(); i++) {
            Purchase * purchase = purchases.at(i);
            string date = purchase->getDate();
            string description = purchase->getDescription();
            double amount = purchase->getFee();
            subtotal += amount;

            // create a list of blank spaces to normalize how far apart the name is from the size
            string spaces = "";

            // for a longer name, their will be less spaces added to the spaces string so that all names are the same
            // distance from the size
            // 20 was somewhat arbitrary but it is assumed that no names will be longer than 20 characters
            for (int i = 0; i < 19-description.length(); i++) {
                spaces += " ";
            }

            billFile << getDate(date) << "        " << description << spaces << "$" << amount << "\n"; // add info to bill
        }

        double tax = subtotal * _taxRate; // calculate tax
        double total = subtotal + tax; // calculate total

        billFile << "\n                           Subtotal: $" << subtotal << "\n\n";
        billFile << "                           Tax: $" << tax << "\n";
        billFile << "                           Total: $" << total;
    }
}

/*
Checks a new guest into the hotel

@param name - last name of the party
@param numberInParty - number of people in the party
@param checkInDate - day they're checking in

return isVacancy - can only check in if there are available rooms
*/
bool Hotel::checkIn(string name, int numberInParty, string checkInDate)
{
    bool isVacancy = !_availableRooms.empty(); // if the available rooms vector isn't empty, there is vacancy
    bool isUnique = !(_listOfGuests.find(name) != _listOfGuests.end()); // check if the name isn't already in the guest list
    bool isSmall = numberInParty <= _maxOccupancyPerRoom; // check if the party is two big to fit into a room

    //if the guest list doesn't already contain that name and there is an open room that will fit them, check them in
    if (isVacancy && isSmall) {
        // instantiate the party
        Party * party = new Party(name, numberInParty, checkInDate);

        // assign room to the party
        Room * assignedRoom = _availableRooms.front();

        // set the party's room to the vacant room
        party->setRoom(assignedRoom);

         // remove first room from available rooms list
        _availableRooms.erase(_availableRooms.begin());

        // add the party to the list of guests
        _listOfGuests.insert({name, party});
    }

    return isVacancy;
}

/*
Checks a guest out of the hotel

@param name - last name of the party
@param checkOutDate - day they're checking out

return
*/
bool Hotel::checkOut(string name, string checkOutDate)
{
    // check if guest is checked in
    bool isGuest = _listOfGuests.find(name) != _listOfGuests.end();

    // if they are a guest, they can be checked out
    if (isGuest) {
        Party * guest = _listOfGuests.at(name); // get a pointer to the party

        // convert the dates to integers
        DateConverter * converter = new DateConverter();
        string checkInDate = guest->getCheckInDate();
        int checkInDateInt = converter->getDOY(checkInDate);
        int checkOutDateInt = converter->getDOY(checkOutDate);

        // make sure check out date is before check in date
        if (checkInDateInt < checkOutDateInt) {
            // create bill file
            createBill(name, checkOutDate);

            // add the guests room back to the available rooms vector
            Room * guestRoom = guest->getRoom();
            _availableRooms.push_back(guestRoom);

            _listOfGuests.erase(name); // remove the guest from the guest list
        }
    }

    return isGuest;
}

/*
Performs a purchase for the person passed in. If they are a guest, a purchase is added to their personal vector. Otherwise, it is added to the
hotel's vector of non-guest purchases

@param name - the name of the guest
@param description - the amenity they purchased
@param fee - price
@param date - the date of the purchase
*/
bool Hotel::charge(string name, string description, double fee, string date)
{
    bool isAmenity = find(_amenities.begin(), _amenities.end(), description) != _amenities.end(); // check if the amenity listed is on the amenity list

    // if it is an amenity offered by the hotel, complete the purchase
    if (isAmenity) {
        Purchase * charge = new Purchase(name, description, fee, date); // instantiate a purchase

        // check if the person is a guest
        if (_listOfGuests.find(name) != _listOfGuests.end()) {
            // if so, add it to their bill
            Party * guest = _listOfGuests.at(name);
            guest->addCharge(charge);
        }
        else {
            // if not, add the amount to a list of non-quest purchases
            _nonGuestPurchases.push_back(charge);
        }
    }
}

/*
Gets the users bill

@param name - the name of the guest
@param currentDate - the date
@return isGuest - true if the guest is in the guest list
*/
bool Hotel::bill(string name, string currentDate)
{
    bool isGuest = _listOfGuests.find(name) != _listOfGuests.end();

    if (isGuest) {
        createBill(name, currentDate);
    }

    return isGuest;
}

/*
Gets a report of the hotel, including its name, the date, the list of guests, their size, and a list of non-guest purchases

@param date - the date when the report written
*/
void Hotel::report(string date)
{
    // create a file with the name of the hotel and data
    ofstream reportFile("hotel.report");

    // also include current guests, number in parties, and
    // list of non-guest purchases
    reportFile << "================================================================================ \n";
    reportFile << "				    HOTEL Report\n";
    reportFile << "================================================================================ \n";
    reportFile << "\n";
    reportFile << _hotelName << "\n";
    reportFile << getDate(date) << "\n\n";
    reportFile << "Current Guest: \n";

    map<string, Party*>::iterator it; // create an iterator for the guest list

    // loop through all of the guests getting their name
    for (it = _listOfGuests.begin(); it != _listOfGuests.end(); it++) {
        Party * guest = _listOfGuests.at(it->first);
        string name = guest->getName();

        // create a list of blank spaces to normalize how far apart the name is from the size
        string spaces = "";

        // for a longer name, their will be less spaces added to the spaces string so that all names are the same
        // distance from the size
        // 20 was somewhat arbitrary but it is assumed that no names will be longer than 20 characters
        for (int i = 0; i < 20-name.length(); i++) {
            spaces += " ";
        }

        reportFile << name << spaces << "Size: " << guest->getGuestNumber() << "\n"; // add the info to the report
    }

    reportFile << "\nNon-Guest Purchases: \n";

    /*
    loop through all of the non-guest purchases and add their info to the report
    */
    for (int i = 0; (unsigned)i < _nonGuestPurchases.size(); i++) {
        Purchase * purchase = _nonGuestPurchases.at(i); // get the next purchase in the list
        string purchaseDate = purchase->getDate(); // get its date
        string name = purchase->getName();
        string description = purchase->getDescription();

        // create a list of blank spaces to normalize how far apart the name is from the size
        string nameSpaces = "";

        // for a longer name, their will be less spaces added to the spaces string so that all names are the same
        // distance from the description
        for (int i = 0; i < 17-name.length(); i++) {
            nameSpaces += " ";
        }

        // if the purchase date is the same as the day of the report, list it on the report
        if (purchaseDate.compare(date) == 0) {
            reportFile << "Name: " << name << nameSpaces << "Description: " << description << "\n";
        }
    }
}

// gets the hotel's name
string Hotel::getName()
{
    return _hotelName;
}

// gets the hotel's address
string Hotel::getAddress()
{
    string address = _streetAddress + " " + _city + ", " + _state + " " + _zipcode;
    return address;
}

// gets the hotel's phone number
string Hotel::getPhoneNumber()
{
    return _phoneNumber;
}

// gets the hotel's fax number
string Hotel::getFaxNumber()
{
    return _faxNumber;
}

// gets the hotel's number of floors
int Hotel::getNumFloors()
{
    return _numFloors;
}

// gets the hotel's rooms per floor
int Hotel::getRoomsPerFloor()
{
    return _roomsPerFloor;
}

// gets the hotel's max occupancy per room
int Hotel::getMaxOccupancyPerRoom()
{
    return _maxOccupancyPerRoom;
}

// gets the hotel's room rates
string Hotel::getRoomRates()
{
    string rates = "Off-Peak: $" + to_string(_offPeakRoomateRate) + "     Peak: $" + to_string(_peakRoomRate);
    return rates;
}

// returns a hyphenated date
string Hotel::getDate(string date)
{
    string dateWithHyphens = date.substr(0,2) + "-" + date.substr(2,2) + "-" + date.substr(4,4); // break apart the day, month, and year with hyphens
    return dateWithHyphens;
}

// prints out the hotels info
ostream& operator<<(ostream& os, const Hotel& hotel)
{
    os << hotel._hotelName << endl;
    os << hotel._streetAddress << endl;
    os << hotel._city << endl;
    os << hotel._state << endl;
    os << hotel._zipcode << endl;
    os << hotel._phoneNumber << endl;
    os << hotel._faxNumber << endl;
    os << hotel._numFloors << endl;
    os << hotel._roomsPerFloor << endl;
    os << hotel._maxOccupancyPerRoom << endl;
    os << hotel._peakRoomRate << endl;
    os << hotel._offPeakRoomateRate << endl;
    os << hotel._peakStart << endl;
    os << hotel._peakEnd << endl;
    os << hotel._taxRate << endl;

    // loops through all the amenities and adds them to the os
    for (int i = 0; (unsigned)i < hotel._amenities.size(); i++) {
        os << hotel._amenities[i] << endl;
    }

    return os;
}

Hotel::~Hotel()
{
    // delete all of the instantiated rooms
    for (int i = 0; i < _availableRooms.size(); i++) {
        delete _availableRooms.at(i);
    }
}
