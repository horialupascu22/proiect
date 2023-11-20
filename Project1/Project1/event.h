#pragma once
#include <string> // Include for std::string
#include <iostream>
#include <string.h> // Prefer cstring over string.h
using namespace std;
class Event {
private:
    char* eventName;            // Dynamically allocated string for the event's name
    int* eventDate;             // Dynamically allocated integer for the event date
    int eventCapacity;          // Maximum capacity of the event
    bool isOutdoor;             // Indicates if the event is outdoor or indoor
    double ticketPrice[3];      // Static array for different ticket price tiers
    static int eventCounter; // Static field
    const int maxCapacity; // Constant field

public:
    // Constructor with deep copy for eventName
    Event(const char* name, int maxCap) : maxCapacity(maxCap) {
        eventName = new char[strlen(name) + 1];
        strcpy_s(eventName, strlen(name) + 1, name);
        eventDate = new int(maxCap);
        eventCounter++; // Increment the static counter
        // Other initializations...
    }
    Event() : eventName(nullptr), eventDate(nullptr), eventCapacity(0), isOutdoor(false), maxCapacity(0) {
        // Initialize eventName and eventDate with default values
        eventName = new char[1]; // Allocate space for at least one character
        *eventName = '\0';       // Set to empty string

        eventDate = new int(0);  // Allocate space for the date and initialize to 0

        // Initialize other members if necessary
        eventCounter++;
    }
    // Additional constructor with different parameters
    Event(const char* name, int date, int capacity, bool outdoor) : maxCapacity(capacity) {
        eventName = new char[strlen(name) + 1];
        strcpy_s(eventName, strlen(name) + 1, name);
        eventDate = new int(date);
        eventCapacity = capacity;
        isOutdoor = outdoor;
        eventCounter++;
    }

    // Copy constructor for deep copy
    Event(const Event& other) : maxCapacity(other.maxCapacity), eventCapacity(other.eventCapacity), isOutdoor(other.isOutdoor) {
        eventName = new char[strlen(other.eventName) + 1];
        strcpy_s(eventName, strlen(other.eventName) + 1, other.eventName);
        eventDate = new int(*(other.eventDate));
    }
    // Destructor to free allocated memory
    ~Event() {
        delete[] eventName;
        delete eventDate;
    }

    void setEventName(const char* newName) {
        eventName = new char[strlen(newName) + 1];
        strcpy_s(eventName, strlen(newName) + 1, newName);
        if (strlen(newName) < 1) {
            throw exception("Short name");
        }
        //delete[] eventName; // Delete the existing name
        //eventName = new char[strlen(newName) + 1]; // Allocate new memory for the new name
      //  strcpy_s(eventName, strlen(newName) + 1, newName); // Copy the new name
    }



    const char* getEventName() const {
        return eventName;
    }

    // Other methods...

    static int getEventCounter() {
        return eventCounter;
    }
    void displayEventDetails() const {
        cout << "Event Name: " << eventName << endl;
        cout << "Event Date: " << (eventDate ? *eventDate : 0) << endl;
        cout << "Event Capacity: " << eventCapacity << endl;
        cout << "Is Outdoor: " << (isOutdoor ? "Yes" : "No") << endl;
        cout << "Ticket Prices: ";
        for (int i = 0; i < 3; ++i) {
            cout << ticketPrice[i] << " ";
        }
        cout << endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Event& event) {
        os << "Event Name: " << event.eventName << "\n";
        os << "Event Date: " << (event.eventDate ? *event.eventDate : 0) << "\n";
        os << "Event Capacity: " << event.eventCapacity << "\n";
        os << "Is Outdoor: " << (event.isOutdoor ? "Yes" : "No") << "\n";
        // You can add more fields as needed
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Event& event) {
        char nameBuffer[100]; // Temporary buffer for the name
        int date;
        cout << "Enter event name: ";
        is >> nameBuffer;
        event.setEventName(nameBuffer);

        cout << "Enter event date (integer format): ";
        is >> date;
        *(event.eventDate) = date; // Assuming eventDate is already allocated

        // You can add inputs for other fields as needed
        return is;
    }
    Event& operator=(const Event& other) {
        if (this != &other) { // Protect against self-assignment
            // Free existing resources
            delete[] eventName;
            delete eventDate;

            // Copy eventName
            eventName = new char[strlen(other.eventName) + 1];
            strcpy_s(eventName, strlen(other.eventName) + 1, other.eventName);

            // Copy eventDate
            eventDate = new int(*(other.eventDate));

            // Copy other fields
            eventCapacity = other.eventCapacity;
            isOutdoor = other.isOutdoor;
            // Copy the ticketPrice array, etc.
        }
        return *this;
    }
    double& operator[](int index) {
        if (index < 0 || index >= 3) {
            throw std::out_of_range("Index out of range");
        }
        return ticketPrice[index];
    }

    // Mathematical Operator +
    Event operator+(int increase) {
        Event temp = *this;
        temp.eventCapacity += increase;
        return temp;
    }

    // Prefix Increment Operator ++
    Event& operator++() {
        ++eventCapacity;
        return *this;
    }

    // Postfix Increment Operator ++
    Event operator++(int) {
        Event temp = *this;
        ++(*this);
        return temp;
    }

    // Cast Operator to int
    explicit operator int() const {
        return eventCapacity;
    }

    // Negation Operator !
    bool operator!() const {
        return eventCapacity == 0;
    }

    // Conditional Operator <
    bool operator<(const Event& other) const {
        return this->eventCapacity < other.eventCapacity;
    }

    // Equality Operator ==
    bool operator==(const Event& other) const {
        return strcmp(this->eventName, other.eventName) == 0;
    }
};
// Initialize static member
int Event::eventCounter = 0;