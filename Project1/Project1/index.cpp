#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "Ticket.h" // Include your Ticket class header
#include "event.h"  // Include your Event class header
#include "customer.h"  // Include your Customer class header

using namespace std;

int main() {
    bool running = true; // Control the main loop
    char choice; // User's menu choice
    vector<Ticket> tickets; // Vector to store multiple tickets
    vector<Event> events; // Vector to store multiple events
    vector<Customer> customers; // Vector to store multiple customers

    while (running) {
        cout << "\nMain Menu:\n";
        cout << "1. Ticket Menu\n";
        cout << "2. Event Menu\n";
        cout << "3. Customer Menu\n";
        cout << "4. Exit Program\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer after input

        switch (choice) {
        case '1': // Ticket Menu
        {
            bool ticketRunning = true; // Control the ticket menu loop
            char ticketChoice; // User's menu choice for tickets

            while (ticketRunning) {
                cout << "\nTicket Menu:\n";
                cout << "1. Enter details for a new ticket\n";
                cout << "2. Show all ticket details\n";
                cout << "3. Serialize all tickets to file\n";
                cout << "4. Deserialize tickets from file\n";
                cout << "5. Exit to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> ticketChoice;

                switch (ticketChoice) {
                case '1': // Enter details for a new ticket
                {
                    cin.ignore(); // Clear newline character from the input buffer
                    Ticket newTicket;
                    cout << "Enter details for a new ticket:" << endl;
                    cin >> newTicket;
                    tickets.push_back(newTicket); // Add new ticket to vector
                    break;
                }
                case '2': // Show all ticket details
                    for (const auto& ticket : tickets) {
                        cout << ticket << endl;
                    }
                    break;
                case '3': // Serialize all tickets to file
                {
                    ofstream outFile("ticket_data.bin", ios::binary);
                    if (!outFile) {
                        cerr << "Error opening 'ticket_data.bin' for writing." << endl;
                        break;
                    }
                    for (const auto& ticket : tickets) {
                        ticket.serialize(outFile);
                    }
                    outFile.close();
                    cout << "All tickets serialized to 'ticket_data.bin'" << endl;
                    break;
                }
                case '4': // Deserialize tickets from file
                {
                    ifstream inFile("ticket_data.bin", ios::binary);
                    if (!inFile) {
                        cerr << "Error opening 'ticket_data.bin' for reading." << endl;
                        break;
                    }
                    tickets.clear();

                    Ticket tempTicket;
                    while (tempTicket.deserialize(inFile)) {
                        tickets.push_back(tempTicket);
                    }
                    inFile.close();
                    cout << "Tickets deserialized from 'ticket_data.bin'" << endl;
                    break;
                }
                case '5': // Exit to Main Menu
                    ticketRunning = false;
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                }
            }
            break;
        }
        case '2': // Event Menu
        {
            bool eventRunning = true; // Control the event menu loop
            char eventChoice; // User's menu choice for events

            while (eventRunning) {
                cout << "\nEvent Menu:\n";
                cout << "1. Enter details for a new event\n";
                cout << "2. Show all event details\n";
                cout << "3. Serialize all events to file\n";
                cout << "4. Deserialize events from file\n";
                cout << "5. Exit to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> eventChoice;

                switch (eventChoice) {
                case '1': // Enter details for a new event
                {
                    cin.ignore(); // Clear newline character from the input buffer
                    Event newEvent;
                    cout << "Enter details for a new event:" << endl;
                    cin >> newEvent;
                    events.push_back(newEvent); // Add new event to vector
                    break;
                }
                case '2': // Show all event details
                    for (const auto& event : events) {
                        cout << event << endl;
                    }
                    break;
                case '3': // Serialize all events to file
                {
                    ofstream outFile("event_data.txt");
                    if (!outFile) {
                        cerr << "Error opening 'event_data.txt' for writing." << endl;
                        break;
                    }
                    for (const auto& event : events) {
                        event.serialize(outFile);
                    }
                    outFile.close();
                    cout << "All events serialized to 'event_data.txt'" << endl;
                    break;
                }
                case '4': // Deserialize events from file
                    // TODO: Implement deserialization logic
                    cout << "Deserialization not implemented yet." << endl;
                    break;
                case '5': // Exit to Main Menu
                    eventRunning = false;
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                }
            }
            break;
        }
        case '3': // Customer Menu
        {
            bool customerRunning = true; // Control the customer menu loop
            char customerChoice; // User's menu choice for customers

            while (customerRunning) {
                cout << "\nCustomer Menu:\n";
                cout << "1. Enter details for a new customer\n";
                cout << "2. Show all customer details\n";
                cout << "3. Serialize all customers to file\n";
                cout << "4. Deserialize customers from file\n";
                cout << "5. Exit to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> customerChoice;

                switch (customerChoice) {
                case '1': // Enter details for a new customer
                {
                    cin.ignore(); // Clear newline character from the input buffer
                    Customer newCustomer;
                    cout << "Enter details for a new customer:" << endl;
                    cin >> newCustomer;
                    customers.push_back(newCustomer); // Add new customer to vector
                    break;
                }
                case '2': // Show all customer details
                    for (const auto& customer : customers) {
                        cout << customer << endl;
                    }
                    break;
                case '3': // Serialize all customers to file
                {
                    ofstream outFile("customer_data.txt");
                    if (!outFile) {
                        cerr << "Error opening 'customer_data.txt' for writing." << endl;
                        break;
                    }
                    for (const auto& customer : customers) {
                        customer.serialize(outFile);
                    }
                    outFile.close();
                    cout << "All customers serialized to 'customer_data.txt'" << endl;
                    break;
                }
                case '4': // Deserialize customers from file
                    // TODO: Implement deserialization logic
                    cout << "Deserialization not implemented yet." << endl;
                    break;
                case '5': // Exit to Main Menu
                    customerRunning = false;
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                }
            }
            break;
        }
        case '4': // Exit Program
            running = false;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    }

    return 0;
}
