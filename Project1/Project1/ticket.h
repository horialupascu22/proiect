#pragma once
#include <iostream>
#include <cstring> // Use cstring for C++ style string functions
using namespace std;

class Ticket {
private:
    int* seatNumber;
    char* ticketCode;
    double price;
    bool isVIP;
    int availableDates[5];

    static int totalTicketsIssued;
    const int maxAvailableDates = 5;



public:
    // Function to copy ticket code while properly managing memory
    void copyTicketCode(const char* code) {
        delete[] ticketCode; // Delete old ticketCode
        ticketCode = new char[strlen(code) + 1]; // Allocate memory for the new code
        strcpy_s(ticketCode, strlen(code) + 1, code); // Copy the new code into ticketCode
    }
    void serialize(ofstream& out) const {
        out.write(reinterpret_cast<const char*>(&seatNumber), sizeof(seatNumber));
        int codeLength = strlen(ticketCode) + 1; // +1 for null-terminator
        out.write(reinterpret_cast<const char*>(&codeLength), sizeof(codeLength));
        out.write(ticketCode, codeLength);
        out.write(reinterpret_cast<const char*>(&price), sizeof(price));
        out.write(reinterpret_cast<const char*>(&isVIP), sizeof(isVIP));
    }

    // Deserialization
    bool deserialize(ifstream& in) {
        int codeLength;
        if (!in.read(reinterpret_cast<char*>(&codeLength), sizeof(codeLength))) {
            return false;
        }
        delete[] ticketCode;
        ticketCode = new char[codeLength];
        in.read(ticketCode, codeLength);
        in.read(reinterpret_cast<char*>(&seatNumber), sizeof(seatNumber));
        in.read(reinterpret_cast<char*>(&price), sizeof(price));
        in.read(reinterpret_cast<char*>(&isVIP), sizeof(isVIP));
        return true;
    }



    // Default constructor
    Ticket() : seatNumber(new int(0)), ticketCode(new char[1]), price(0.0), isVIP(false) {
        ticketCode[0] = '\0'; // Initialize ticketCode with an empty string
        totalTicketsIssued++; // Increment total tickets issued
    }

    // Constructor with parameters
    Ticket(int number, const char* code) : seatNumber(new int(number)), ticketCode(nullptr), price(0.0), isVIP(false) {
        copyTicketCode(code); // Copy the provided ticket code
        totalTicketsIssued++; // Increment total tickets issued
    }

    // Copy constructor
    Ticket(const Ticket& other) : seatNumber(new int(*other.seatNumber)), ticketCode(nullptr), price(other.price), isVIP(other.isVIP) {
        copyTicketCode(other.ticketCode); // Copy ticket code from other object
        memcpy(availableDates, other.availableDates, sizeof(availableDates)); // Copy available dates from other object
        totalTicketsIssued++; // Increment total tickets issued
    }


    // Assignment operator
    Ticket& operator=(const Ticket& other) {
        if (this != &other) { // Check for self-assignment
            setTicketCode(other.ticketCode); // Set the ticket code from the other object
            *seatNumber = *other.seatNumber; // Copy seat number from the other object
            price = other.price; // Copy price from the other object
            isVIP = other.isVIP; // Copy VIP status from the other object
        }
        return *this; // Return reference to the current object
    }
    void setTicketCode(const char* code) {
        delete[] ticketCode;
        if (code) {
            ticketCode = new char[strlen(code) + 1];
            strcpy_s(ticketCode, strlen(code) + 1, code); // Use strcpy_s
        }
        else {
            ticketCode = new char[1];
            ticketCode[0] = '\0';
        }
    }
    // Destructor
    ~Ticket() {
        delete seatNumber; // Free memory for seatNumber
        delete[] ticketCode; // Free memory for ticketCode
    }

    void printDetails() const {
        cout << "Ticket Code: " << (ticketCode ? ticketCode : "N/A") << endl;
        cout << "Seat Number: " << (seatNumber ? *seatNumber : 0) << endl;
        cout << "Price: $" << price << endl;
        cout << "VIP Status: " << (isVIP ? "Yes" : "No") << endl;
    }

    void updatePrice(double newPrice) {
        price = newPrice;
    }

    static int getTotalTicketsIssued() {
        return totalTicketsIssued;
    }
    friend std::istream& operator>>(std::istream& is, Ticket& ticket) {
        char codeBuffer[100];
        int seatNum;
        double ticketPrice;
        bool ticketVIP;

        cout << "Enter ticket code: ";
        is >> codeBuffer;
        ticket.setTicketCode(codeBuffer);  // Use the setTicketCode function to handle memory management

        cout << "Enter seat number: ";
        is >> seatNum;
        *ticket.seatNumber = seatNum; // Assume seatNumber is already allocated

        cout << "Enter ticket price: ";
        is >> ticketPrice;
        ticket.price = ticketPrice; // Set the ticket price

        cout << "Is this a VIP ticket? (1 for Yes, 0 for No): ";
        is >> ticketVIP;
        ticket.isVIP = ticketVIP; // Set the VIP status

        // Skip the rest of the line to avoid issues with subsequent inputs
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return is;
    }
    // Indexing Operator []
    int& operator[](int index) {
        if (index < 0 || index >= maxAvailableDates) {
            throw std::out_of_range("Index out of range");
        }
        return availableDates[index];
    }

    // Mathematical Operator +
    Ticket operator+(double amount) {
        Ticket temp = *this;
        temp.price += amount;
        return temp;
    }

    // Increment Operator ++ (Prefix)
    Ticket& operator++() {
        price += 1.0;
        return *this;
    }

    // Increment Operator ++ (Postfix)
    Ticket operator++(int) {
        Ticket temp = *this;
        ++(*this);
        return temp;
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
    friend ostream& operator<<(ostream& os, const Ticket& ticket) {
        os << "Ticket Code: " << ticket.ticketCode << "\n";
        os << "Seat Number: " << ticket.seatNumber << "\n";
        os << "Price: $" << ticket.price << "\n";
        os << "VIP Status: " << (ticket.isVIP ? "Yes" : "No") << "\n";
        return os;
    }
};

int Ticket::totalTicketsIssued = 0;
