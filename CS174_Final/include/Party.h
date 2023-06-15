#ifndef PARTY_H
#define PARTY_H
#include <string>
#include "Room.h"
#include "Purchase.h"
#include <vector>
#include "DateConverter.h"

using namespace std;

class Party
{
    public:
        Party(string name, int numberInParty, string checkInDate);
        string getName();
        int getGuestNumber();
        string getCheckInDate();
        void setRoom(Room * givenRoom);
        Room * getRoom();
        void addCharge(Purchase * purchase);
        vector<Purchase*> getPurchases();
        vector<Purchase*> getLodgingCharges();
        void addLodging(Purchase * dayStayed);
        virtual ~Party();

    protected:

    private:
        string _name;
        int _numberInParty;
        string _checkInDate;
        string _checkOutDate;
        Room * _assignedRoom;
        int _bill;
        vector<Purchase*> _purchases;
};

#endif // PARTY_H
