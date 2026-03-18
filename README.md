# C++ Hotel Reservation System

A Hotel Management System built with C++ that utilizes Object-Oriented Programming (OOP) to manage room bookings, user authentication, and persistent data storage.

## Technical Highlights

### 1. Advanced OOP & Inheritance
The system uses a sophisticated class hierarchy to manage different room types. 
* **Base Class:** `Room`
* **Derived Classes:** `StandardRoom`, `DeluxeRoom`, and `SuiteRoom`.
* **Polymorphism:** Implements `virtual` functions for calculating discounted prices and displaying room-specific details, ensuring the system can handle various room types dynamically.

### 2. Data Persistence (CSV Database)
Unlike basic console apps, this system saves data to the disk.
* Uses **File I/O** to read from and write to `Room.csv` and `User.csv`.
* Implements logic to parse semi-colon delimited data into C++ objects.

### 3. Modular System Architecture
The project is split into functional modules for high maintainability:
* `Booking.h`: Handles the reservation logic and date validation.
* `Date.h`: A custom utility class for handling stay durations.
* `Multifunction.h`: Contains core system utilities like UI menus and input validation.

## Key Features
* **User Authentication:** Secure login and registration system for customers.
* **Dynamic Room Search:** Filters rooms by destination, hotel name, and availability.
* **Automated Receipt Generation:** Calculates total costs including specific room discounts.
