#include "HotelCommander.h"
#include "HotelFactory.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

HotelCommander::HotelCommander(string fileName, Hotel * hotel)
{
    _fileName = fileName;
    _hotel = hotel;
}

void HotelCommander::readCommands()
{
    ifstream actFile; // creates the in file
    actFile.open(_fileName); // gives them the names of the files

    // if the file is open, read in the commands
    if (actFile.is_open()) {
        string line;

        // while there are lines to be read, continue reading
        while (getline(actFile, line)) {
            stringstream ss(line); //convert my_string into string stream

            string command;
            getline(ss,command,':'); // get the name of the command

            vector<string> tokens;
            string token;

            while(getline(ss, token, ',')){ //use comma as delimiter for cutting string
                tokens.push_back(token);
            }
            // if the command is check in, get the necessary tokens and call check in on the hotel
            if (command.compare("CHECK_IN") == 0) {
                string name = tokens[0].substr(1); // cut off the blank space between the comma and token
                int numberInParty = stoi(tokens[1]);
                string checkInDate = tokens[2].substr(1); // cut off the blank space between the comma and token

                _hotel->checkIn(name, numberInParty, checkInDate);
            // if the command is check out, get the necessary tokens and call check out on the hotel
            }
            else if (command.compare("CHECK_OUT") == 0) {
                string name = tokens[0].substr(1);
                string checkOutDate = tokens[1].substr(1); // cut off the blank space between the comma and token

                _hotel->checkOut(name, checkOutDate);
            // if the command is charge, get the necessary tokens and call charge on the hotel
            }
            else if (command.compare("CHARGE") == 0) {
                string name = tokens[0].substr(1); // cut off the blank space between the comma and token
                string description = tokens[1].substr(1); // cut off the blank space between the comma and token
                double fee = stod(tokens[2]);
                string date = tokens[3].substr(1); // cut off the blank space between the comma and token

                _hotel->charge(name, description, fee, date);
            }
            // if the command is bill, get the necessary tokens and call bill on the hotel
            else if (command.compare("BILL") == 0) {
                string name = tokens[0].substr(1); // cut off the blank space between the comma and token
                string date = tokens[1].substr(1); // cut off the blank space between the comma and token

                _hotel->bill(name, date);
            }
            // if the command is report, get the necessary tokens and call report on the hotel
            else if (line.substr(0, 6).compare("REPORT") == 0) {
                string date = tokens[0].substr(1); // cut off the blank space between the comma and token

                _hotel->report(date);
            }
        }
    }
}

HotelCommander::~HotelCommander()
{
    //dtor
}
