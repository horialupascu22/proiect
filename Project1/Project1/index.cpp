#include <string> // Include for std::string
#include <iostream>
#include <string.h> 
#include "event.h"
#include "ticket.h"
#include "customer.h"

using namespace std;


int main() {

    try {
        Event event1;
        cout << "Enter details for event1:" << endl;
        cin >> event1;
        cout << "Event 1 Details:" << endl;
        cout << event1 << endl;

        Event event2("Festival", 20220730, 1000, true);
        cout << "Event 2 Details:" << endl;
        cout << event2 << endl;

        // Demonstrate other overloaded operators
        event1 = event1 + 50;  // Increase event capacity
        ++event1;              // Increment capacity
        if (!event1) {
            cout << "Event 1 has no capacity." << endl;
        }
        if (event1 < event2) {
            cout << "Event 1 has less capacity than Event 2." << endl;
        }
        if (event1 == event2) {
            cout << "Event 1 and Event 2 have the same name." << endl;
        }

        // Display updated event details
        cout << "Updated Event 1 Details:" << endl;
        cout << event1 << endl;

    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }



    /*
    * Event event2("Festival", 20220730, 1000, true);
  //   std::cout << "Event 2 Details:" << std::endl;
     event2.displayEventDetails();
   // Printing the initial event name
   //std::cout << "Initial Event Name: " << myEvent.getEventName() << std::endl;

   // Changing the event name
  // myEvent.setEventName("");

   // Printing the new event name
   //std::cout << "New Event Name: " << myEvent.getEventName() << std::endl;

   // Printing the static event counter
   //std::cout << "Number of Event instances: " << Event::getEventCounter() << std::endl;
   //cout << "details event:" << endl;
    //   myEvent.displayEventDetails();
   try {
       Event myEvent("Hello", 5000);
       // Create an Event instance
      // Event myEvent("Summer Festival", 5000);
       //Event myEvent("", 5000);
       // Try to set the event name to an empty string
       //myEvent.setEventName("");
      // event2.setEventName("");
       // If the exception is not thrown, this line will be executed
      cout << "Event name set to an empty string successfully." <<endl;
   }
   catch (const exception& e) {
       // Catch and handle the exception
       cerr << "Exception caught: " << e.what() <<endl;
   }
    */

    try {
        // Creating Ticket objects
        Ticket ticket1(25, "ABC123");
        Ticket ticket2(30, "XYZ456");

        // Print details of tickets
        cout << "Ticket 1 Details:\n" << ticket1 << endl;
        cout << "Ticket 2 Details:\n" << ticket2 << endl;

        // Using the + operator to increase the price
        Ticket ticket3 = ticket1 + 20.0; // Increases ticket1's price by 20
        cout << "Ticket 3 (increased price) Details:\n" << ticket3 << endl;

        // Using ++ operator (both prefix and postfix)
        ++ticket2; // Prefix increment
        ticket2++; // Postfix increment
        cout << "Ticket 2 (after incrementing price) Details:\n" << ticket2 << endl;

        // Using the cast operator to bool
        cout << "Ticket 1 is " << (static_cast<bool>(ticket1) ? "" : "not ") << "a VIP ticket.\n";

        // Using the negation operator !
        if (!ticket1) {
            cout << "Ticket 1 is free.\n";
        }

        // Using the conditional operator <
        if (ticket1 < ticket2) {
            cout << "Ticket 1 is cheaper than Ticket 2.\n";
        }
        else {
            cout << "Ticket 1 is not cheaper than Ticket 2.\n";
        }

        // Using the equality operator ==
        if (ticket1 == ticket3) {
            cout << "Ticket 1 and Ticket 3 have the same ticket code.\n";
        }
        else {
            cout << "Ticket 1 and Ticket 3 have different ticket codes.\n";
        }

        // Using the indexing operator []
        cout << "Available Date for Ticket 1: " << ticket1[0] << endl; // Accessing the first date in availableDates

    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }

    try {
        Customer customer1("John Doe", "john@example.com", 30);
        Customer customer2; // Using the default constructor

        cout << "Customer 1 Details:" << endl;
        cout << customer1 << endl;

        cout << "Enter details for Customer 2:" << endl;
        cin >> customer2;
        cout << "Customer 2 Details:" << endl;
        cout << customer2 << endl;

        // Demonstrating the copy assignment operator
        Customer customer3 = customer1; // Using the copy constructor
        Customer customer4;
        customer4 = customer2; // Using the copy assignment operator
        cout << "Customer 3 (copy of Customer 1) Details:" << endl;
        cout << customer3 << endl;
        cout << "Customer 4 (assigned from Customer 2) Details:" << endl;
        cout << customer4 << endl;

    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }


}
