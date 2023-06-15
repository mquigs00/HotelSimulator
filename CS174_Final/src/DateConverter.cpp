#include "DateConverter.h"
#include <string>

using namespace std;

DateConverter::DateConverter()
{

}

/*
converts a string date into an integer representing its day of the year (from 1-365)

@param date - the string date (ex: 03022016)
*/
int DateConverter::getDOY(string date)
{
    // split the different parts of the date
    int dayOM = stoi(date.substr(0,2)); // day of month
    int month = stoi(date.substr(2,2));

    // peak dates only have day and month, otherwise also get year
    if (date.length() == 8) {
        int year = stoi(date.substr(4,4));
    }

    // the day of the year is equal to the start day of the respective month plus the day of the month
    // sub one from month because they are elements in a vector and therefore jan = 0, feb = 1...
    int dayOfYear = _startDays[month-1] + dayOM;

    return dayOfYear;
}

/*
converts an integer representing a day of the year back into it's string date

@param dayOfYear - an integer for the day of the year(1-365)
@param year - the year
*/
string DateConverter::getStringDate(int dayOfYear, string year)
{
    int i = 0;
    int firstDayOfMonth = 0;

    // search through the first day of month vector till we find the start date that is less than the day of year
    while (dayOfYear > _startDays[i]) {
        firstDayOfMonth = _startDays[i];
        i++;
    }

    int dayOM = dayOfYear-firstDayOfMonth; // the day of the month is just the day of year minus the first day of the month
    string day = to_string(dayOM); // convert to string

    // the day of month is 1 character like 1,2,3.. we must add a 0 in front of it for concistency
    if (day.length() == 1) {
        day = "0" + day;
    }

    int m = i;
    string month = to_string(m); // convert to string

    // the month is 1 character like 1,2,3.. we must add a 0 in front of it for concistency
    if (month.length() == 1){
        month = "0" + month;
    }

    // concatenate values together to get the string date
    string dateString = day + month + year;

    return dateString;
}

DateConverter::~DateConverter()
{
    //dtor
}
