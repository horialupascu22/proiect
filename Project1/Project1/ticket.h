#pragma once
#include <string> // Include for std::string
#include <iostream>
#include <string.h> // Prefer cstring over string.h
using namespace std;
class Ticket {
private:
    int* seatNumber;            // Dynamically allocated seat number
    char* ticketCode;           // Dynamically allocated string for the ticket code
    double price;               // Price of the ticket
    bool isVIP;                 // Indicates if the ticket is for VIP seating
    int availableDates[5];      // Static array of dates when the ticket is valid

    static int totalTicketsIssued; // Static variable to track total tickets issued
    const int maxAvailableDates;   // Constant for the maximum number of available dates

public:
    Ticket(int number, const char* code) : maxAvailableDates(5) {
        seatNumber = new int(number);
        ticketCode = new char[strlen(code) + 1];
        strcpy_s(ticketCode, strlen(code) + 1, code);
        // Initialize other members as needed
        totalTicketsIssued++; // Increment the static counter for each Ticket instance created
    }
    Ticket& operator=(const Ticket& other) {
        if (this != &other) { // Protect against self-assignment
            // Free existing resources
            delete seatNumber;
            delete[] ticketCode;

            seatNumber = nullptr;
            ticketCode = nullptr;

            // Allocate new memory and copy the data
            seatNumber = new int(*(other.seatNumber));
            ticketCode = new char[strlen(other.ticketCode) + 1];
            strcpy_s(ticketCode, strlen(other.ticketCode) + 1, other.ticketCode);

            // Copy other members
            price = other.price;
            isVIP = other.isVIP;
            memcpy(availableDates, other.availableDates, 5 * sizeof(int));
        }
        return *this;
    }
    Ticket() : seatNumber(new int(0)), ticketCode(new char[1]), price(0.0), isVIP(false), maxAvailableDates(5) {
        ticketCode[0] = '\0';  // Setting ticketCode to an empty string
        // Initialize availableDates with default values if necessary
        totalTicketsIssued++; // Increment the static counter
    }
    ~Ticket() {
        delete seatNumber;
        delete[] ticketCode;
    }

    void printNumber() const {
        if (seatNumber != nullptr && *seatNumber != 0) {
            cout << "Seat Number: " << *seatNumber << std::endl;
            throw exception("The seat is taken!");
        }
        else {
            throw exception("The seat is free");
        }
        // The following line will never be reached due to the exceptions thrown above
        cout << "Ticket Code: " << ticketCode << std::endl;
    }
    int& operator[](int index) {
        if (index < 0 || index >= maxAvailableDates) {
            throw std::out_of_range("Index out of range");
        }
        return availableDates[index];
    }

    // Mathematical Operator +
    Ticket operator+(double increase) {
        Ticket temp = *this;
        temp.price += increase;
        return temp;
    }

    // Increment Operator ++
    Ticket& operator++() {
        price += 1.0;
        return *this;
    }

    // Cast Operator to bool (VIP status)
    explicit operator bool() const {
        return isVIP;
    }

    // Negation Operator !
    bool operator!() const {
        return price == 0.0;
    }

    // Conditional Operator <
    bool operator<(const Ticket& other) const {
        return this->price < other.price;
    }

    // Equality Operator ==
    bool operator==(const Ticket& other) const {
        return strcmp(this->ticketCode, other.ticketCode) == 0;
    }


    static int getTotalTicketsIssued() {
        return totalTicketsIssued;
    }

    int getMaxAvailableDates() const {
        return maxAvailableDates;
    }
    void printDetails() const {
        cout << "Ticket Code: " << (ticketCode ? ticketCode : "N/A") << endl;
        cout << "Seat Number: " << (seatNumber ? *seatNumber : 0) << endl;
        cout << "Price: $" << price << endl;
        cout << "VIP Status: " << (isVIP ? "Yes" : "No") << endl;
        // Include availableDates information if needed
    }

    // New Method: Update the ticket price
    void updatePrice(double newPrice) {
        price = newPrice;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
        os << "Ticket Code: " << (ticket.ticketCode ? ticket.ticketCode : "N/A") << "\n";
        os << "Seat Number: " << (ticket.seatNumber ? *ticket.seatNumber : 0) << "\n";
        os << "Price: $" << ticket.price << "\n";
        os << "VIP Status: " << (ticket.isVIP ? "Yes" : "No") << "\n";
        // Include availableDates information if needed
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Ticket& ticket) {
        char codeBuffer[100];
        int seatNum;

        // Ask for and read in ticket code
        cout << "Enter ticket code: ";
        is >> codeBuffer;

        // Ask for and read in seat number
        cout << "Enter seat number: ";
        is >> seatNum;

        // Delete and reallocate memory for ticketCode
        delete[] ticket.ticketCode;
        ticket.ticketCode = nullptr; // Set to nullptr immediately after deletion
        ticket.ticketCode = new char[strlen(codeBuffer) + 1];
        strcpy_s(ticket.ticketCode, strlen(codeBuffer) + 1, codeBuffer);

        // Delete and reallocate memory for seatNumber
        delete ticket.seatNumber;
        ticket.seatNumber = nullptr; // Set to nullptr immediately after deletion
        ticket.seatNumber = new int(seatNum);

        return is;
    }

};

int Ticket::totalTicketsIssued = 0; // Initialize static member