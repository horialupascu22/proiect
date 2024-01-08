#pragma once
#include <string> // Include for std::string
#include <fstream> 
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
    void serializeString(ofstream& file) const {
        int length = strlen(eventName) + 1;
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(eventName, length);
    }

    // Member function to deserialize a string
    string deserializeString(ifstream& file) {
        int length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        char* buffer = new char[length];
        file.read(buffer, length);
        string str = buffer;
        delete[] buffer;
        return str;
    }
public:
    void serialize(ofstream& file) const {
        serializeString(file);
        file.write(reinterpret_cast<const char*>(eventDate), sizeof(int));
        file.write(reinterpret_cast<const char*>(&eventCapacity), sizeof(int));
        file.write(reinterpret_cast<const char*>(&isOutdoor), sizeof(bool));
        // Serialize other members as needed
    }

    void deserialize(ifstream& file) {
        string name = deserializeString(file);
        setEventName(name.c_str());
        file.read(reinterpret_cast<char*>(eventDate), sizeof(int));
        file.read(reinterpret_cast<char*>(&eventCapacity), sizeof(int));
        file.read(reinterpret_cast<char*>(&isOutdoor), sizeof(bool));
        // Deserialize other members as needed
    }
    // Constructor with deep copy for eventName
    Event(const char* name, int maxCap) : maxCapacity(maxCap) {
        eventName = new char[strlen(name) + 1];
        strcpy_s(eventName, strlen(name) + 1, name);
        eventDate = new int(maxCap);
        eventCounter++; // Increment the static counter
        // Other initializations...
    }
    Event() : eventName(nullptr), eventDate(nullptr), eventCapacity(0), isOutdoor(false), maxCapacity(1000) {
        eventName = new char[1];
        *eventName = '\0';
        eventDate = new int(0);
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
    void setEventCapacity(int capacity) {
        if (capacity <= maxCapacity) {
            eventCapacity = capacity;
        }
        else {
            throw std::runtime_error("Capacity exceeds maximum limit.");
        }
    }

    void setIsOutdoor(bool outdoor) {
        isOutdoor = outdoor;
    }
    void setEventDate(int date) {
        *eventDate = date;
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
        char nameBuffer[100];
        int date;
        int capacity;
        bool outdoor;

        std::cout << "Enter event name: ";
        is.ignore();
        is.getline(nameBuffer, 100);
        event.setEventName(nameBuffer);

        std::cout << "Enter event date (YYYYMMDD): ";
        is >> date;
        event.setEventDate(date);

        std::cout << "Enter event capacity: ";
        is >> capacity;
        event.setEventCapacity(capacity);

        std::cout << "Is it an outdoor event? (1 for yes, 0 for no): ";
        is >> outdoor;
        event.setIsOutdoor(outdoor);

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
