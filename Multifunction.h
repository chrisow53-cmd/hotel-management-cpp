#ifndef MULTIFUNCTION_H_INCLUDED
#define MULTIFUNCTION_H_INCLUDED

#include "Room.h"
#include "User.h"
#include "Booking.h"
#include "Date.h"

using namespace std;

class Multifunction
{
private:
    vector<User> users;
    vector<Room*> rooms;
    vector<Booking> bookings;
    User* loggedInUser = nullptr;

    void loadRooms()
    {
        ifstream file("Room.csv");
        if (!file)
        {
            throw runtime_error("Room.csv file not found.");
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);

            string destination, hotel, roomType, priceStr, capacityStr, availabilityStr, amenitiesStr, ratingStr;

            if (getline(ss, destination, ';') &&
                    getline(ss, hotel, ';') &&
                    getline(ss, roomType, ';') &&
                    getline(ss, priceStr, ';') &&
                    getline(ss, capacityStr, ';') &&
                    getline(ss, availabilityStr, ';') &&
                    getline(ss, amenitiesStr, ';') &&
                    getline(ss, ratingStr, ';'))
            {

                double price, rating;
                int capacity, availability;

                stringstream priceStream(priceStr);
                priceStream >> price;

                stringstream capacityStream(capacityStr);
                capacityStream >> capacity;

                stringstream availabilityStream(availabilityStr);
                availabilityStream >> availability;

                stringstream ratingStream(ratingStr);
                ratingStream >> rating;

                vector<string> amenities;
                stringstream amenitiesStream(amenitiesStr);
                string amenity;
                while (getline(amenitiesStream, amenity, '|'))
                {
                    amenities.push_back(amenity);
                }

                if (roomType == "Standard")
                {
                    rooms.push_back(new StandardRoom(destination, hotel, roomType, price, capacity, availability, amenities, rating));
                }
                else if (roomType == "Deluxe")
                {
                    rooms.push_back(new DeluxeRoom(destination, hotel, roomType, price, capacity, availability, amenities, rating));
                }
                else if (roomType == "Suite")
                {
                    rooms.push_back(new SuiteRoom(destination, hotel, roomType, price, capacity, availability, amenities, rating));
                }

            }
        }
    }


    int initializeUsers()
    {
        ifstream file("User.csv");
        if (!file.is_open())
        {
            cerr << "Failed to open the file. Ensure 'User.csv' exists and is accessible." << endl;
            return 1;
        }

        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string username, password, name, email, couponCode;

            getline(ss, username, ';');
            getline(ss, password, ';');
            getline(ss, name, ';');
            getline(ss, email, ';');
            getline(ss, couponCode, ';');

            users.emplace_back(username, password, name, email, couponCode);
        }

        file.close();
        return 0;
    }
    void viewRoomBookingHistory()
    {
        if (!loggedInUser)
        {
            cout << "You must be logged in to view booking history.\n";
            return;
        }

        bool foundBooking = false;
        cout << "\n----- Booking History -----\n";

        for (const auto& booking : bookings)
        {
            cout << "Booking ID: " << booking.getBookingID() << endl;
            cout << "Hotel: " << booking.getHotel() << endl;
            cout << "Room Type: " << booking.getRoomType() << endl;
            cout << "Destination: " << booking.getDestination() << endl;
            cout << "Check-In Date: ";
            booking.getCheckInDate();
            cout<<endl;
            cout << "Check-Out Date: ";
            booking.getCheckOutDate();
            cout << "Total Price: RM" << fixed << setprecision(2) << booking.getTotalPrice() << endl;
            cout << "Number of Rooms: " << booking.getNumRooms() << endl;
            cout << "------------------------------\n";
            foundBooking = true;
        }

        if (!foundBooking)
        {
            cout << "No bookings found for this user.\n";
        }
    }

    void filterRooms()
    {
        string destination;
        cout << "Enter destination to display rooms for: ";
        cin >> destination;

        vector<Room*> destinationRooms;
        for (const auto& room : rooms)
        {
            if (room->getDestination() == destination)
            {
                destinationRooms.push_back(room);
            }
        }

        if (destinationRooms.empty())
        {
            cout << "No rooms found for destination: " << destination << endl;
            return;
        }

        int choice;
        cout << "Filter Rooms By:\n";
        cout << "1. Price Range\n";
        cout << "2. Room Type\n";
        cout << "3. Rating\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            double minPrice, maxPrice;
            cout << "Enter minimum price: ";
            cin >> minPrice;
            cout << "Enter maximum price: ";
            cin >> maxPrice;

            bool roomsFound = false;
            for (const auto& room : destinationRooms)
            {
                if (room->getPrice() >= minPrice && room->getPrice() <= maxPrice)
                {
                    room->displayRoomDetails();
                    cout << endl;
                    roomsFound = true;
                }
            }

            if (!roomsFound)
            {
                cout << "No rooms found within the price range: RM" << minPrice << " - RM" << maxPrice << endl;
            }
            break;
        }

        case 2:
        {
            string roomType;
            cout << "Enter a room type to filter: ";
            cin >> roomType;

            bool roomsFound = false;
            for (const auto& room : destinationRooms)
            {
                if (room->getRoomType() == roomType)
                {
                    room->displayRoomDetails();
                    cout << endl;
                    roomsFound = true;
                }
            }

            if (!roomsFound)
            {
                cout << "No rooms found with the type: " << roomType << endl;
            }
            break;
        }


        case 3:
        {
            double rating;
            cout << "Enter a rating to find (1-5): ";
            cin >> rating;

            bool roomsFound = false;
            for (const auto& room : destinationRooms)
            {
                if (room->getRating() == rating)
                {
                    room->displayRoomDetails();
                    cout << endl;
                    roomsFound = true;
                }
            }

            if (!roomsFound)
            {
                cout << "No rooms found with a rating of " << rating << " or higher.\n";
            }
            break;
        }

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    void bookRoom()
    {
        string destination;
        cout << "Enter destination to view available hotels: ";
        cin >> destination;

        vector<Room*> availableRooms;
        for (const auto& room : rooms)
        {
            if (room->getDestination() == destination)
            {
                availableRooms.push_back(room);
            }
        }

        if (availableRooms.empty())
        {
            cout << "No available rooms at the selected destination.\n";
            return;
        }

        cout << "Available Hotels and Rooms:\n";
        for (size_t i = 0; i < availableRooms.size(); ++i)
        {
            cout << "[" << i + 1 << "] ";
            availableRooms[i]->displayRoomDetails();
            cout << endl;
        }

        int roomChoice;
        cout << "Enter the number corresponding to the room you want to book: ";
        cin >> roomChoice;

        if (roomChoice < 1 || roomChoice > static_cast<int>(availableRooms.size()))
        {
            cout << "Invalid choice.\n";
            return;
        }

        Room* selectedRoom = availableRooms[roomChoice - 1];

        int numRooms, numGuests;
        while (true)
        {
            cout << "Enter number of guests: ";
            cin >> numGuests;

            if (numGuests <= 0)
            {
                cout<<"Error: The number of guests cannot be 0\n";
            }
            else if(numGuests<= selectedRoom->getCapacity())
                break;
            else
            {
                cout << "Error: The number of guests exceeds the room's capacity of " << selectedRoom->getCapacity() << " guests. Please enter a valid number of guests.\n";
            }
        }
        while (true)
        {
            cout << "Enter number of rooms to book: ";
            cin >> numRooms;


            if (numRooms <= selectedRoom->getAvailability())
            {
                break;
            }
            else
            {
                cout << "Error: Not enough rooms available. Only " << selectedRoom->getAvailability() << " rooms are available. Please enter a valid number of rooms.\n";
            }
        }

        Date checkInDate;
        cout << "Enter Check-In Date:\n";
        int d, m, y;

        cout << "Enter Month: ";
        cin >> m;
        while (true)
        {
            try
            {
                checkInDate.setMonth(m);
                break;
            }
            catch (Date::InvalidMonth& e)
            {
                cout << "Error: " << e.getValue() << " is an invalid month. Please enter a valid month: ";
                cin >> m;
            }
        }

        cout << "Enter Year: ";
        cin >> y;
        while (true)
        {
            try
            {
                checkInDate.setYear(y);
                break;
            }
            catch (Date::InvalidYear& e)
            {
                cout << "Error: " << e.getValue() << " is an invalid year. Please enter a valid year: ";
                cin >> y;
            }
        }

        cout << "Enter Day: ";
        cin >> d;
        while (true)
        {
            try
            {
                checkInDate.setDay(d);
                break;
            }
            catch (Date::InvalidDay& e)
            {
                cout << "Error: " << e.getValue() << " is invalid for the month. Please enter a valid day: ";
                cin >> d;
            }
            catch (Date::InvalidLeap& e)
            {
                cout << "Error: " << e.getValue() << " is invalid for a leap year. Please enter a valid day: ";
                cin >> d;
            }
        }

        Date checkOutDate;
        cout << "Enter Check-Out Date:\n";
        int checkOutD, checkOutM, checkOutY;

        cout << "Enter Month: ";
        cin >> checkOutM;
        while (true)
        {
            try
            {
                checkOutDate.setMonth(checkOutM);
                break;
            }
            catch (Date::InvalidMonth& e)
            {
                cout << "Error: " << e.getValue() << " is an invalid month. Please enter a valid month: ";
                cin >> checkOutM;
            }
        }

        cout << "Enter Year: ";
        cin >> checkOutY;
        while (true)
        {
            try
            {
                checkOutDate.setYear(checkOutY);
                break;
            }
            catch (Date::InvalidYear& e)
            {
                cout << "Error: " << e.getValue() << " is an invalid year. Please enter a valid year: ";
                cin >> checkOutY;
            }
        }

        cout << "Enter Day: ";
        cin >> checkOutD;
        while (true)
        {
            try
            {
                checkOutDate.setDay(checkOutD);
                break;
            }
            catch (Date::InvalidDay& e)
            {
                cout << "Error: " << e.getValue() << " is invalid for the month. Please enter a valid day: ";
                cin >> checkOutD;
            }
            catch (Date::InvalidLeap& e)
            {
                cout << "Error: " << e.getValue() << " is invalid for a leap year. Please enter a valid day: ";
                cin >> checkOutD;
            }
        }

        if (checkOutDate <= checkInDate)
        {
            cout << "Error: Check-out date cannot be before or the same as check-in date.\n";
            return;
        }

        if (!selectedRoom->isAvailable(checkInDate, numRooms))
        {
            cout << "Selected room is not available on ";
            checkInDate.printDate();
            cout << " for " << numRooms << " rooms.\n";
            return;
        }

        if (!selectedRoom->isAvailable(checkOutDate, numRooms))
        {
            cout << "Selected room is not available on ";
            checkOutDate.printDate();
            cout << " for " << numRooms << " rooms.\n";
            return;
        }

        int totalDays = Date::getDifference(checkInDate, checkOutDate);

        if (totalDays <= 0)
        {
            cout << "Error: Invalid date range.\n";
            return;
        }

        for (int i = 0; i < totalDays; i++)
        {
            if (!selectedRoom->isAvailable(checkInDate, numRooms))
            {
                cout << "Selected room is not available on ";
                checkInDate.printDate();
                cout << " for " << numRooms << " rooms.\n";
                return;
            }
            checkInDate.nextDay();
        }
        double pricePerNight = selectedRoom->calculateDiscountedPrice();
        cout << "Discounted Price per night(might vary per room type): RM" << fixed << setprecision(2) << pricePerNight << endl;
        double subtotal = selectedRoom->calculateDiscountedPrice() * numRooms * totalDays;
        double taxes = subtotal * 0.1;
        double total = subtotal + taxes;
        cout<<"Number of Rooms booked: " << numRooms <<" Number of Days booked: "<<totalDays<<endl;

        cout << "Subtotal: RM" << fixed << setprecision(2) << subtotal << endl;
        cout << "Taxes: RM" << fixed << setprecision(2) << taxes << endl;
        cout << "Total: RM" << fixed << setprecision(2) << total << endl;

        string userCouponCode = loggedInUser->getCouponCode();
        if (!userCouponCode.empty())
        {
            cout << "Your coupon code: " << userCouponCode << endl;

            if (userCouponCode == "15PERCENT500" && total >= 500)
            {
                total *= 0.85;
                cout << "Coupon applied! 15% discount for deluxe rooms.\n";
                cout << "Final Price after coupon: RM" << fixed << setprecision(2) << total << endl;
            }
            else if (userCouponCode == "STANDARD10OFF")
            {
                total *= 0.90;
                cout << "Coupon applied! 10% OFF.\n";
                cout << "Final Price after coupon: RM" << fixed << setprecision(2) << total << endl;
            }
            else if (userCouponCode == "2RMOFF")
            {
                total -= 2;
                cout << "Coupon applied! RM 2 OFF.\n";
                cout << "Final Price after coupon: RM" << fixed << setprecision(2) << total << endl;
            }
            else if (userCouponCode == "10RMOFF")
            {
                total -= 10;
                cout << "Coupon applied! RM 10 OFF.\n";
                cout << "Final Price after coupon: RM" << fixed << setprecision(2) << total << endl;
            }
            else if (userCouponCode == "SUITE5PERCENT" && selectedRoom->getRoomType() == "Suite")
            {
                total *= 0.95;
                cout << "Coupon applied! 5% discount for suites.\n";
                cout << "Final Price after coupon: RM" << fixed << setprecision(2) << total << endl;
            }
            else
            {
                cout << "Invalid coupon or no applicable discount.\n";
            }
        }



        string paymentMethod;
        int referenceNumber;
        cout << "Choose payment method (Credit/Ewallet): ";
        cin >> paymentMethod;
        cout << "Enter Reference Number: ";
        cin >> referenceNumber;
        cout << "Processing payment via " << paymentMethod << "... Payment Successful!\n";

        try
        {
            selectedRoom->bookRooms(checkInDate, numRooms);
        }
        catch (runtime_error& e)
        {
            cout << "Booking failed: " << e.what() << endl;
            return;
        }

        Booking newBooking(
            loggedInUser->getUsername(),
            selectedRoom->getDestination(),
            selectedRoom->getHotel(),
            selectedRoom->getRoomType(),
            checkInDate.getDay(),
            checkInDate.getMonth(),
            checkInDate.getYear(),
            checkInDate.getDay(),
            checkInDate.getMonth(),
            checkInDate.getYear(),
            total,
            numRooms,
            numGuests
        );

        bookings.push_back(newBooking);

        cout << "Booking Confirmed!\n";
        newBooking.displayBookingSummary();
    }



public:
    void run()
    {
        try
        {
            loadRooms();
            initializeUsers();
        }
        catch (const exception& e)
        {
            cerr << "Error initializing Multifunction: " << e.what() << endl;
            return;
        }

        while (true)
        {
            cout << "\n----- Login -----\n";
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            auto it = find_if(users.begin(), users.end(), [&](const User& user)
            {
                return user.getUsername() == username && user.getPassword() == password;
            });

            if (it != users.end())
            {
                loggedInUser = &(*it);
                cout << "Welcome, " << loggedInUser->getName() << "!\n";

                while (true)
                {
                    cout <<"\nMain Menu:";
                    cout<<"\n1. Display Room Types\n";
                    cout<<"2. Book Room\n";
                    cout<<"3. View Room Booking History\n";
                    cout<<"4. Filter Rooms\n";
                    cout<<"5. Refund\n";
                    cout<<"6. Logout (Login Different User)\n";
                    cout<<"7. Exit\n";
                    int choice;
                    while (true)
                    {
                        cout << "Enter your choice: ";
                        cin >> choice;

                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Error: Please enter a valid integer.\n";
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (choice == 6)
                    {
                        loggedInUser = nullptr;
                        break;
                    }

                    switch (choice)
                    {
                    case 1:
                    {
                        string destination;
                        cout << "Enter destination to display rooms for: ";
                        cin >> destination;

                        bool roomsFound = false;
                        for (const auto& room : rooms)
                        {
                            if (room->getDestination() == destination)
                            {
                                room->displayRoomDetails();
                                cout << endl;
                                roomsFound = true;
                            }
                        }

                        if (!roomsFound)
                        {
                            cout << "No rooms found for destination: " << destination << endl;
                        }
                        break;
                    }
                    case 2:
                        bookRoom();
                        break;
                    case 3:
                        viewRoomBookingHistory();
                        bookRoom();
                    case 4:
                        filterRooms();
                        break;
                    case 5:
                        processRefund();
                        break;
                    case 7:
                        cout << "Thank You for using our services" << endl;
                        exit(0);
                        break;
                    default:
                        cout << "Invalid option. Try again." << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid credentials. Try again." << endl;
            }
        }
    }

    void processRefund()
    {
        int bookingID;
        cout << "Enter booking ID to refund: ";
        cin >> bookingID;

        auto it = find_if(bookings.begin(), bookings.end(), [bookingID](const Booking& booking)
        {
            return booking.getBookingID() == bookingID;
        });

        if (it != bookings.end())
        {
            cout << "Booking found. Are you sure you want to process a refund for Booking ID: " << bookingID << "? (yes/no): ";
            string confirmation;
            cin >> confirmation;

            if (confirmation == "yes")
            {
                for (auto& room : rooms)
                {
                    if (room->getHotel() == it->getHotel() &&
                            room->getRoomType() == it->getRoomType() &&
                            room->getDestination() == it->getDestination())
                    {

                        Date current = it->getCheckInDate();
                        while (current <= it->getCheckOutDate())
                        {
                            room->refundRoom(current, it->getNumRooms());
                            current.nextDay();
                        }
                        break;
                    }
                }

                double refundAmount = it->getTotalPrice();

                bookings.erase(it);
                cout << "Refund processed successfully. Booking ID: " << bookingID << " has been removed.\n";
                cout << "Refunded Amount: RM" << fixed << setprecision(2) << refundAmount << "\n";
            }
            else
            {
                cout << "Refund process canceled.\n";
            }
        }
        else
        {
            cout << "No booking found with Booking ID: " << bookingID << ".\n";
        }
    }

};

#endif // MULTIFUNCTION_H_INCLUDED
