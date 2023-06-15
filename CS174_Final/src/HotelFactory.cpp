#include "HotelFactory.h"
#include <fstream>
#include <iostream>

using namespace std;

HotelFactory::HotelFactory(string fileName)
{
    _fileName = fileName;
}

Hotel * HotelFactory::createHotel()
{
    ifstream inFile; // creates the in file
    inFile.open(_fileName); // gives them the names of the files

    // if the file is open, get the hotel's information
    if (inFile.is_open()) {
        string hotelName;
        getline(inFile, hotelName); // get the hotel name
        string streetAddress;
        getline(inFile, streetAddress); // get the hotel address
        string city;
        getline(inFile, city); // get the hotel's city
        string state;
        getline(inFile, state); // get the hotel state
        string zipcode;
        getline(inFile, zipcode); // get the hotel's zipcode
        string phoneNumber;
        getline(inFile, phoneNumber); // get the hotel phone number
        string faxNumber;
        getline(inFile, faxNumber); // get the hotel fax number
        string numFloorsString;
        getline(inFile, numFloorsString); // get the hotel's number of floors
        int numFloors = stoi(numFloorsString.c_str()); // convert it to it
        string roomsPerFloorString;
        getline(inFile, roomsPerFloorString); // get the hotel's rooms per floor
        int roomsPerFloor = stoi(roomsPerFloorString.c_str()); // convert it to int
        string maxOccupancyPerRoomString;
        getline(inFile, maxOccupancyPerRoomString); // get the hotel's max occupancy per room
        int maxOccupancyPerRoom = stoi(maxOccupancyPerRoomString.c_str()); // convert to int
        string peakRoomRateString;
        getline(inFile, peakRoomRateString); // get the hotel's peak room rate
        int peakRoomRate = stoi(peakRoomRateString.c_str());
        string offPeakRoomRateString;
        getline(inFile, offPeakRoomRateString); // get the hotel's off peak room rate
        int offPeakRoomRate = stoi(offPeakRoomRateString.c_str());
        string peakStart;
        getline(inFile, peakStart); // get the peak start date
        peakStart = peakStart.substr(3,2) + peakStart.substr(0,2); // swap the front and back, so the day is first and month is second
        string peakEnd;
        getline(inFile, peakEnd); // get the peak end
        peakEnd = peakEnd.substr(3,2) + peakEnd.substr(0,2); // swap the front and back, so the day is first and month is second
        string taxRateString;
        getline(inFile, taxRateString); // get the tax rate
        double taxRate = stod(taxRateString.c_str()); // convert it to double
        vector<string> amenities; // create a vector of amenities

        string line;

        int i = 0;
        // loop through the rest of the lines and add anything left into the amenities vector
        while (getline(inFile, line)) {
            amenities.insert(amenities.begin() + i, line); // insert the amenity at the front of the vector
            i++;
        }

        // pass all of the received values into the hotel constructor
        Hotel * _hotel = new Hotel(hotelName, streetAddress, city, state, zipcode, phoneNumber, faxNumber, numFloors, roomsPerFloor, maxOccupancyPerRoom,
                               peakRoomRate, offPeakRoomRate, peakStart,peakEnd, taxRate, amenities);

        inFile.close(); // close the file

        return _hotel;
    }
    else {
        cout << "Unable to open file";  // otherwise, alert the user that the files couldn't be opened
    }
}

HotelFactory::~HotelFactory()
{
}
