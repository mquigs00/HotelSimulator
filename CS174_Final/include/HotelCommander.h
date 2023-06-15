#ifndef HOTELCOMMANDER_H
#define HOTELCOMMANDER_H
#include <string>
#include "Hotel.h"

using namespace std;

class HotelCommander
{
    public:
        HotelCommander(string fileName, Hotel * hotel);
        void readCommands();
        virtual ~HotelCommander();

    protected:

    private:
        string _fileName;
        Hotel * _hotel;
};

#endif // HOTELCOMMANDER_H
