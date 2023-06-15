#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>

using namespace std;

class Purchase
{
    public:
        Purchase(string name, string description, double fee, string date);
        string getName();
        string getDescription();
        double getFee();
        string getDate();
        virtual ~Purchase();

    protected:

    private:
        string _name;
        string _description;
        double _fee;
        string _date;
};

#endif // PURCHASE_H
