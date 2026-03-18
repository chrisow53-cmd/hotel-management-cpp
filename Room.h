#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>
#include "Date.h"

using namespace std;

class Room
{
protected:
    string destination, hotel, roomType;
    double price;
    int capacity;
    int availability;
    vector<string> amenities;
    double rating;
    map<Date, int> availabilityByDate;

public:
    Room(const string& destination, const string& hotel, const string& roomType,
         double price, int capacity, int availability, const vector<string>& amenities, double rating)
        : destination(destination), hotel(hotel), roomType(roomType),
          price(price), capacity(capacity), availability(availability), amenities(amenities), rating(rating)
    {
        for (int year = 2025; year <= 2026; ++year)
        {
            for (int month = 1; month <= 12; ++month)
            {
                for (int day = 1; day <= 31; ++day)
                {
                    if (Date::isValidDate(day, month, year))
                    {
                        Date date(day, month, year);
                        availabilityByDate[date] = availability;
                    }
                }
            }
        }
    }

    virtual ~Room() {}

    const string& getDestination() const
    {
        return destination;
    }
    const string& getHotel() const
    {
        return hotel;
    }
    const string& getRoomType() const
    {
        return roomType;
    }
    double getPrice() const
    {
        return price;
    }
    double getRating() const
    {
        return rating;
    }
    const vector<string>& getAmenities() const
    {
        return amenities;
    }
    int getAvailability() const
    {
        return availability;
    }
    void setAvailability(int av)
    {
        availability = av;
    }
    int getCapacity() const
    {
        return capacity;
    }
    std::map<Date, int> getAvailabilityByDate() const
{
    return availabilityByDate;
}

    bool isAvailable(const Date& date, int numRooms) const
    {
        auto it = availabilityByDate.find(date);
        return it != availabilityByDate.end() && it->second >= numRooms;
    }

    void bookRooms(const Date& date, int numRooms)
    {
        auto it = availabilityByDate.find(date);
        if (it != availabilityByDate.end() && it->second >= numRooms)
        {
            it->second -= numRooms;
        }
        else
        {
            throw runtime_error("Insufficient rooms available for booking on this date.");
        }
    }

    void refundRoom(const Date& date, int numRooms)
    {
        availabilityByDate[date] += numRooms;
    }

    void addAvailability(const Date& date, int numRooms)
    {
        availabilityByDate[date] += numRooms;
    }

    virtual double calculateDiscountedPrice() const
    {
        return price;
    }


    virtual void displayRoomDetails() const
    {
        cout << "Hotel: " << hotel << "\n"
             << "Type: " << roomType << "\n"
             << "Price: " << price << "\n"
             << "Rating: " << rating << "\n"
             << "Capacity: " << capacity << " guests\n"
             << "Amenities: ";

        if (amenities.empty())
        {
            cout << "None\n";
        }
        else
        {
            for (size_t i = 0; i < amenities.size(); ++i)
            {
                cout << amenities[i];
                if (i != amenities.size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "\n";
        }
    }
};

#endif // ROOM_H_INCLUDED
