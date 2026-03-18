#ifndef SUITEROOM_H_INCLUDED
#define SUITEROOM_H_INCLUDED
#include "Room.h"

using namespace std;

class SuiteRoom : public Room
{
public:
    SuiteRoom(const std::string& destination, const std::string& hotel, const std::string& roomType,
              double price, int capacity, int availability, const std::vector<std::string>& amenities, double rating)
        : Room(destination, hotel, roomType, price, capacity, availability, amenities, rating) {}
    ~SuiteRoom() override {}
    void displayRoomDetails() const override
    {
        Room::displayRoomDetails();
        cout << "Free Ice Cream and Snacks upon arrival!" << endl;
    }
    double calculateDiscountedPrice() const override
    {
        return price * 0.88;
    }
};


#endif // SUITEROOM_H_INCLUDED
