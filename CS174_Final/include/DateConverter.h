#ifndef DATECONVERTER_H
#define DATECONVERTER_H
#include <string>
#include <vector>

using namespace std;

class DateConverter
{
    public:
        DateConverter();
        int getDOY(string date);
        string getStringDate(int dayOfYear, string year);
        virtual ~DateConverter();

    protected:

    private:
        int _startDays[12] = {0, 31, 58, 90, 120, 151, 181, 211, 242, 273, 304, 334}; // first day of each month
};

#endif // DATECONVERTER_H
