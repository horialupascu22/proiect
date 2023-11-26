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

    void copyTicketCode(const char* code) {
        delete[] ticketCode;
        ticketCode = new char[strlen(code) + 1];
        strcpy_s(ticketCode, strlen(code) + 1, code);
    }

public:
    Ticket() : seatNumber(new int(0)), ticketCode(new char[1]), price(0.0), isVIP(false) {
        ticketCode[0] = '\0';
        totalTicketsIssued++;
    }

    Ticket(int number, const char* code) : seatNumber(new int(number)), ticketCode(nullptr), price(0.0), isVIP(false) {
        copyTicketCode(code);
        totalTicketsIssued++;
    }

    Ticket(const Ticket& other) : seatNumber(new int(*other.seatNumber)), ticketCode(nullptr), price(other.price), isVIP(other.isVIP) {
        copyTicketCode(other.ticketCode);
        memcpy(availableDates, other.availableDates, 5 * sizeof(int));
        totalTicketsIssued++;
    }

    Ticket& operator=(const Ticket& other) {
        if (this != &other) {
            *seatNumber = *other.seatNumber;
            copyTicketCode(other.ticketCode);
            price = other.price;
            isVIP = other.isVIP;
            memcpy(availableDates, other.availableDates, 5 * sizeof(int));
        }
        return *this;
    }

    ~Ticket() {
        delete seatNumber;
        delete[] ticketCode;
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

        cout << "Enter ticket code: ";
        is >> codeBuffer;

        cout << "Enter seat number: ";
        is >> seatNum;

        delete[] ticket.ticketCode;
        ticket.ticketCode = new char[strlen(codeBuffer) + 1];
        strcpy_s(ticket.ticketCode, strlen(codeBuffer) + 1, codeBuffer);

        delete ticket.seatNumber;
        ticket.seatNumber = new int(seatNum);

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
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
        os << "Ticket Code: " << (ticket.ticketCode ? ticket.ticketCode : "N/A") << "\n";
        os << "Seat Number: " << (ticket.seatNumber ? *ticket.seatNumber : 0) << "\n";
        os << "Price: $" << ticket.price << "\n";
        os << "VIP Status: " << (ticket.isVIP ? "Yes" : "No") << "\n";
        return os;
    }
};

int Ticket::totalTicketsIssued = 0;