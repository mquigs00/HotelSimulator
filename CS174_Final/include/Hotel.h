#ifndef HOTEL_H
#define HOTEL_H
#include <string>
#include <vector>
#include "Party.h"
#include <map>
#include "Room.h"
#include "Purchase.h"
#include <algorithm>


using namespace std;

class Hotel
{
    public:
        Hotel(string hotelName, string streetAddress, string city, string state, string zipcode, string phoneNumber, string faxNumber,
             int numFloors, int roomsPerFloor, int maxOccupancyPerRoom, int peakRoomRate, int offPeakRoomRate, string peakStart,
             string peakEnd, double taxRate, vector<string> amenities);
        string getName();
        string getAddress();
        string getPhoneNumber();
        string getFaxNumber();
        int getNumFloors();
        int getRoomsPerFloor();
        int getMaxOccupancyPerRoom();
        string getRoomRates();
        string getPeakDates();
        double getTaxRate();
        void getAmenities();
        bool rentRoom();
        Room * getRoom();
        bool checkIn(string name, int numberInParty, string checkInDate);
        bool checkOut(string name, string checkOutDate);
        bool charge(string name, string description, double fee, string date);
        bool bill(string name, string currentDate);
        void report(string date);
        void addPurchases(Purchase * purchase);
        void createBill(string name, string date);
        void convertDate();
        string getDate(string date);
        virtual ~Hotel();
        friend ostream& operator<<(ostream& os, const Hotel& hotel);

    protected:

    private:
        string _hotelName;
        string _streetAddress;
        string _city;
        string _state;
        string _zipcode;
        string _phoneNumber;
        string _faxNumber;
        int _numFloors;
        int _roomsPerFloor;
        int _maxOccupancyPerRoom;
        int _peakRoomRate;
        int _offPeakRoomateRate;
        string _peakStart;
        string _peakEnd;
        double _taxRate;
        vector<string> _amenities;
        vector<Room*> _availableRooms;
        int _numRoomsAvailable = _roomsPerFloor * _numFloors;
        map<string, Party*> _listOfGuests;
        vector<Purchase*> _nonGuestPurchases;
};

#endif // HOTEL_H
