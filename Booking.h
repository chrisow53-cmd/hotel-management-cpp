#ifndef BOOKING_H_INCLUDED
#define BOOKING_H_INCLUDED

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class Booking
{
private:
    static int bookingCounter;
    int bookingID;
    string username;
    string destination;
    string hotel;
    string roomType;
    Date checkInDate;
    Date checkOutDate;
    double totalPrice;
    int numRooms;
    int numGuests;

public:
    Booking(const string& username, const string& destination, const string& hotel, const string& roomType,
            int checkInDay, int checkInMonth, int checkInYear,
            int checkOutDay, int checkOutMonth, int checkOutYear,
            double totalPrice, int numRooms, int numGuests)
        : username(username), destination(destination), hotel(hotel), roomType(roomType),
          checkInDate(checkInDay, checkInMonth, checkInYear),
          checkOutDate(checkOutDay, checkOutMonth, checkOutYear),
          totalPrice(totalPrice), numRooms(numRooms), numGuests(numGuests)
    {
        bookingID = ++bookingCounter;
    }

    int getBookingID() const
    {
        return bookingID;
    }
    string getHotel() const
    {
        return hotel;
    }
    string getRoomType() const
    {
        return roomType;
    }
    string getDestination() const
    {
        return destination;
    }
    Date getCheckInDate() const
    {
        return checkInDate;
    }
    Date getCheckOutDate() const
    {
        return checkOutDate;
    }
    double getTotalPrice() const
    {
        return totalPrice;
    }
    int getNumRooms() const
    {
        return numRooms;
    }
    int getNumGuests() const
    {
        return numGuests;
    }

    void displayBookingSummary() const
    {
        cout << "Booking Summary:" << endl;
        cout << "Booking ID: " << bookingID << endl;
        cout << "Username: " << username << endl;
        cout << "Destination: " << destination << endl;
        cout << "Hotel: " << hotel << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Check-In: ";
        checkInDate.printDate();
        cout<<endl;
        cout << "Check-Out: ";
        checkOutDate.printDate();
        cout<<endl;
        cout << "Total Price: RM" << totalPrice << endl;
    }
};

int Booking::bookingCounter = 0;

#endif // BOOKING_H_INCLUDED
