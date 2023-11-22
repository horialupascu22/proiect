    #include <string> // Include for std::string
    #include <iostream>
    #include <string.h> // Prefer cstring over string.h
    #include "event.h"
    #include "ticket.h"
    #include "customer.h"
    //#include "sales_report.h"
    //#include "venue.h"
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
            // Creating tickets
            Ticket ticket1(100, "ABCD1234");
            Ticket ticket2(101, "XYZ5678");
            Ticket defaultTicket; // Using the default constructor

            // Using the overloaded << operator to print ticket details
            cout << "Ticket 1 Details:" << endl;
            cout << ticket1 << endl;

            cout << "Ticket 2 Details:" << endl;
            cout << ticket2 << endl;

            cout << "Default Ticket Details:" << endl;
            cout << defaultTicket << endl;

            // Using the overloaded >> operator to input ticket details
            cout << "Enter details for a new ticket:" << endl;
            Ticket newTicket;
            cin >> newTicket;
            cout << "New Ticket Details:" << endl;
            cout << newTicket << endl;

            // Demonstrating the + operator and increment operator
            ticket1 = ticket1 + 10.0; // Increasing the price
            ++ticket2; // Incrementing the price

            // Using the == operator to check for equality
            if (ticket1 == ticket2) {
                cout << "Ticket 1 and Ticket 2 have the same ticket code." << endl;
            }
            else {
                cout << "Ticket 1 and Ticket 2 have different ticket codes." << endl;
            }

            // Using the < operator to compare tickets
            if (ticket1 < ticket2) {
                cout << "Ticket 1 is cheaper than Ticket 2." << endl;
            }
            else {
                cout << "Ticket 1 is not cheaper than Ticket 2." << endl;
            }

            // Using the cast operator to bool
            if (static_cast<bool>(ticket1)) {
                cout << "Ticket 1 is a VIP ticket." << endl;
            }
            else {
                cout << "Ticket 1 is not a VIP ticket." << endl;
            }

            // Using the ! operator
            if (!defaultTicket) {
                cout << "Default ticket is free." << endl;
            }

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
