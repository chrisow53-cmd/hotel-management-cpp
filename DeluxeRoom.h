#ifndef DELUXEROOM_H_INCLUDED
#define DELUXEROOM_H_INCLUDED
#include "Room.h"

using namespace std;

class DeluxeRoom : public Room
{
public:
    DeluxeRoom(const std::string& destination, const std::string& hotel, const std::string& roomType,
               double price, int capacity, int availability, const std::vector<std::string>& amenities, double rating)
        : Room(destination, hotel, roomType, price, capacity, availability, amenities, rating) {}
    ~DeluxeRoom() override {}
    void displayRoomDetails() const override
    {
        Room::displayRoomDetails();
        cout << "Free Welcome Drink upon arrival!" << endl;
    }
    double calculateDiscountedPrice() const override
    {
        return price * 0.92;
    }
};

#endif // DELUXEROOM_H_INCLUDED
