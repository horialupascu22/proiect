#pragma once
#include <string>
#include <iostream>
#include <cstring>

class Customer {
private:
    char* customerName;
    long* customerId;
    char email[100];
    int age;
    int purchasedTickets[10];
    static int totalCustomers;
    const int maxTicketsPerCustomer;

public:
    Customer(const char* name, const char* email, int age) : maxTicketsPerCustomer(10), customerId(new long(0)) {
        customerName = new char[strlen(name) + 1];

        // Corrected usage of strcpy_s
        strcpy_s(customerName, strlen(name) + 1, name);
        strcpy_s(this->email, 100, email); // The size of the email buffer is 100

        this->age = age;
        totalCustomers++;
    }
    Customer() : maxTicketsPerCustomer(10), customerId(new long(0)) {
        customerName = new char[1];
        customerName[0] = '\0'; // Empty string

        email[0] = '\0'; // Empty email
        age = 0; // Default age
        // Initialize other members as needed
        totalCustomers++;
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
        strcpy_s(this->email, 100, newEmail);
    }

    // Method to display customer information
    void displayCustomerInfo() const {
        std::cout << "Name: " << customerName << "\nEmail: " << email << "\nAge: " << age << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Customer& customer) {
        os << "Name: " << customer.customerName << "\n";
        os << "Email: " << customer.email << "\n";
        os << "Age: " << customer.age << "\n";
        // Include other details if needed
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Customer& customer) {
        char nameBuffer[100];
        char emailBuffer[100];
        int age;

        cout << "Enter customer name: ";
        is >> nameBuffer;
        cout << "Enter customer email: ";
        is >> emailBuffer;
        cout << "Enter customer age: ";
        is >> age;

        // Make sure to deallocate old data before assigning new
        delete[] customer.customerName;
        customer.customerName = new char[strlen(nameBuffer) + 1];
        strcpy_s(customer.customerName, strlen(nameBuffer) + 1, nameBuffer);

        customer.setEmail(emailBuffer);
        customer.age = age;
        // Handle other fields as needed
        return is;
    }
    Customer& operator=(const Customer& other) {
        if (this != &other) { // Protect against self-assignment
            delete[] customerName; // Free existing resources
            delete customerId;

            customerName = new char[strlen(other.customerName) + 1];
            strcpy_s(customerName, strlen(other.customerName) + 1, other.customerName);

            *customerId = *(other.customerId);
            strcpy_s(email, 100, other.email);
            age = other.age;
            memcpy(purchasedTickets, other.purchasedTickets, 10 * sizeof(int));
            // maxTicketsPerCustomer and totalCustomers do not need to be copied as they are constant/static
        }
        return *this;
    }
};

int Customer::totalCustomers = 1000;