#ifndef HOTELFACTORY_H
#define HOTELFACTORY_H
#include "Hotel.h"
#include <string>

using namespace std;


class HotelFactory
{
    public:
        HotelFactory(string fileName);
        virtual ~HotelFactory();
        Hotel * createHotel();

    protected:

    private:
        string _fileName;
};

#endif // HOTELFACTORY_H
