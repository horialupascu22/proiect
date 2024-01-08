#pragma once
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
class Customer {
private:
    char* customerName;
    long* customerId;
    char email[100];
    int age;
    int purchasedTickets[10];
    static int totalCustomers;
    const int maxTicketsPerCustomer;
    void serializeString(ofstream& file, const char* str) const {
        int length = strlen(str) + 1;
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(str, length);
    }

    string deserializeString(ifstream& file) {
        int length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        unique_ptr<char[]> buffer(new char[length]);
        file.read(buffer.get(), length);
        return string(buffer.get());
    }
public:
    void serialize(ofstream& file) const {
        serializeString(file, customerName);
        file.write(reinterpret_cast<const char*>(customerId), sizeof(long));
        file.write(email, sizeof(email));
        file.write(reinterpret_cast<const char*>(&age), sizeof(age));
        file.write(reinterpret_cast<const char*>(purchasedTickets), sizeof(purchasedTickets));
    }

    void deserialize(ifstream& file) {
        string name = deserializeString(file);
        delete[] customerName;
        customerName = new char[name.length() + 1];
        strcpy_s(customerName, name.length() + 1, name.c_str());

        // Deserialize customer ID
        file.read(reinterpret_cast<char*>(&customerId), sizeof(customerId));

        // Deserialize email
        file.read(email, sizeof(email));

        // Deserialize age
        file.read(reinterpret_cast<char*>(&age), sizeof(age));

        // Deserialize purchased tickets
        file.read(reinterpret_cast<char*>(purchasedTickets), sizeof(purchasedTickets));
    }
    Customer(const char* name, const char* email, int age)
        : customerName(new char[strlen(name) + 1]),
        customerId(new long(++totalCustomers)),
        age(age),
        maxTicketsPerCustomer(10) {
        strcpy_s(customerName, strlen(name) + 1, name); // Use strcpy_s
        strcpy_s(this->email, 100, email); // Use strcpy_s with the size of the destination buffer
    }
    Customer() : customerId(new long(++totalCustomers)), age(0), maxTicketsPerCustomer(10) {
        customerName = new char[1];
        customerName[0] = '\0'; // Initialize with an empty string
        email[0] = '\0';        // Initialize email with an empty string
        memset(purchasedTickets, 0, sizeof(purchasedTickets)); // Initialize all purchasedTickets to 0
    }

    ~Customer() {
        delete[] customerName;
        delete customerId;
    }

    void setEventName() {
        if (strlen(this->customerName) < 1) {
            throw exception("Short name for teh customer!");
        }
        // delete[] customerName;
        // customerName = new char[strlen(name) + 1];
        // strcpy_s(customerName, strlen(name) + 1, name);

    }
    void ageTest(int age)
    {
        if (this->age < 35)
            throw exception("Age innapropriate");
    }
    // Copy constructor and copy assignment operator should be defined here

    static int getTotalCustomers() {
        return totalCustomers;
    }

    int getMaxTicketsPerCustomer() const {
        return maxTicketsPerCustomer;
    }
    void setEmail(const char* newEmail) {
        strcpy_s(this->email, sizeof(this->email), newEmail); // Use the size of the email array
    }

    // Method to display customer information
    void displayCustomerInfo() const {
        cout << "Name: " << customerName << "\nEmail: " << email << "\nAge: " << age << endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Customer& customer) {
        os << "Name: " << customer.customerName << "\n";
        os << "Email: " << customer.email << "\n";
        os << "Age: " << customer.age << "\n";
        // Include other details if needed
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Customer& customer) {
        std::string nameBuffer;
        std::string emailBuffer;
        int age;

        cout << "Enter customer name: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the leftover newline
        getline(is, nameBuffer);

        cout << "Enter customer email: ";
        std::getline(is, emailBuffer);

        cout << "Enter customer age: ";
        is >> age;

        // Make sure to deallocate old data before assigning new
        delete[] customer.customerName;
        customer.customerName = new char[nameBuffer.length() + 1];
        // strcpy_s(customer.customerName, nameBuffer.c_str());
        strcpy_s(customer.customerName, strlen(nameBuffer.c_str()) + 1, nameBuffer.c_str());
        customer.setEmail(emailBuffer.c_str());
        customer.age = age;
        // Handle other fields as needed
        return is;
    }

    // Copy Constructor
    Customer(const Customer& other)
        : customerName(new char[strlen(other.customerName) + 1]),
        customerId(new long(*other.customerId)),
        age(other.age),
        maxTicketsPerCustomer(other.maxTicketsPerCustomer) {
        strcpy_s(customerName, strlen(other.customerName) + 1, other.customerName);
        strcpy_s(email, sizeof(email), other.email);
    }

    // Copy Assignment Operator
    Customer& operator=(const Customer& other) {
        if (this != &other) {
            delete[] customerName;
            delete customerId;

            customerName = new char[strlen(other.customerName) + 1];
            strcpy_s(customerName, strlen(other.customerName) + 1, other.customerName); // Use strcpy_s
            customerId = new long(*other.customerId);
            age = other.age;
            strcpy_s(email, sizeof(email), other.email); // Use strcpy_s with the size of the email array
        }
        return *this;
    }
    int& operator[](int index) {
        if (index < 0 || index >= 10) {
            throw out_of_range("Index out of range");
        }
        return purchasedTickets[index];
    }

    // Mathematical operator (+) to add tickets
    Customer& operator+(int tickets) {
        for (int i = 0; i < 10; ++i) {
            if (purchasedTickets[i] == 0) {
                purchasedTickets[i] = tickets;
                break;
            }
        }
        return *this;
    }

    // Prefix increment operator
    Customer& operator++() {
        ++age;
        return *this;
    }

    // Postfix increment operator
    Customer operator++(int) {
        Customer temp = *this;
        ++(*this);
        return temp;
    }

    // Cast operator to int (returns age)
    explicit operator int() const {
        return age;
    }

    // Negation operator (!) checks if the customer has no purchased tickets
    bool operator!() const {
        for (int ticket : purchasedTickets) {
            if (ticket != 0) return false;
        }
        return true;
    }

    // Conditional operator (<) compares ages
    bool operator<(const Customer& other) const {
        return age < other.age;
    }

    // Equality operator (==) checks if two customers have the same ID
    bool operator==(const Customer& other) const {
        return *customerId == *other.customerId;
    }
};

int Customer::totalCustomers = 1000;
