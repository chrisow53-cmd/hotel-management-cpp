#ifndef STANDARDROOM_H_INCLUDED
#define STANDARDROOM_H_INCLUDED
#include "Room.h"

using namespace std;

class StandardRoom : public Room
{
public:
    StandardRoom(const string& destination, const string& hotel, const string& roomType,
                 double price, int capacity, int availability, const vector<string>& amenities, double rating)
        : Room(destination, hotel, roomType, price, capacity, availability, amenities, rating) {}
    ~StandardRoom() override {}
    void displayRoomDetails() const override
    {
        Room::displayRoomDetails();
        cout << "Average Standard Room" << endl;
    }
    double calculateDiscountedPrice() const override
    {
        return price * 0.95;
    }
};

#endif // STANDARDROOM_H_INCLUDED
