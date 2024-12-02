#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include<cctype>
#include </Users/saianish/Desktop/2-1/C++/Project/admin.cpp>
#include <thread>
#include <chrono>
#include </Users/saianish/Desktop/2-1/C++/Project/gps_test.cpp>


using namespace std;
extern map<string, vector<pair<string, int> > > graph;


const string bookingFile = "/Users/saianish/Desktop/2-1/C++/Project/bookings.txt";
const string customerFile = "/Users/saianish/Desktop/2-1/C++/Project/customers.txt";

class Booking {
public:
    string customerName;
    string destination;
    string fromPlace;
    string fromDate;
    string toDate;
    string vehicleType;

    Booking() = default;

    Booking(string name, string from, string dest, string fromD, string toD, string vehicle)
        : customerName(name), fromPlace(from), destination(dest), fromDate(fromD), toDate(toD), vehicleType(vehicle) {}

    void display() const {
        cout << "Customer Name: " << customerName << endl;
        cout << "From Place: " << fromPlace << endl;
        cout << "Destination: " << destination << endl;
        cout << "From Date: " << fromDate << endl;
        cout << "To Date: " << toDate << endl;
        cout << "Vehicle Type: " << vehicleType << endl;
    }
};

class Customer {
public:
    string c_name;
    string c_no;
    string password;

    void display() const {
        cout << "Customer Name: " << c_name << endl;
        cout << "Customer Number: " << c_no << endl; // Ensure c_no displays here
    }
};

bool isValidPhoneNumber(const string& phoneNumber) {
    return phoneNumber.length() == 10 && all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit);
}

void saveCustomer(const Customer& customer) {
    ofstream file(customerFile, ios::app);
    if (file) {
        file << customer.c_name << "," << customer.password << "," << customer.c_no << endl;
        file.close();
    } else {
        cerr << "Error saving customer information!" << endl;
    }
}

bool isCustomerValid(const string& name, const string& password, Customer& loggedInCustomer) {
    ifstream file(customerFile);
    string line;

    if (file) {
        while (getline(file, line)) {
            istringstream ss(line);
            string storedName, storedPassword, storedNumber;
            getline(ss, storedName, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedNumber, ',');

            if (storedName == name && storedPassword == password) {
                // Set the loggedInCustomer details
                loggedInCustomer.c_name = storedName;
                loggedInCustomer.password = storedPassword;
                loggedInCustomer.c_no = storedNumber;
                return true;
            }
        }
    }
    return false;
}

void Customer_Login(Customer& loggedInCustomer) {
    cin.ignore();
    cout << "Enter customer name: ";
    getline(cin, loggedInCustomer.c_name);

    cout << "Enter password: ";
    getline(cin, loggedInCustomer.password);

    if (isCustomerValid(loggedInCustomer.c_name, loggedInCustomer.password, loggedInCustomer)) {
        cout << "Login Successful!" << endl;
        loggedInCustomer.display(); // Check if c_no is correctly set
    } else {
        cout << "Login Unsuccessful! Invalid Credentials!" << endl;
        loggedInCustomer.c_name = ""; // Reset logged-in status if login fails
    }
}

Customer* Customer_Register() {
    Customer* c = new Customer();
    cin.ignore();
    cout << "Enter customer name: ";
    getline(cin, c->c_name);

    cout << "Enter new password: ";
    getline(cin, c->password);

    do {
        cout << "Enter 10-digit phone number: ";
        cin >> c->c_no;
    } while (!isValidPhoneNumber(c->c_no));

    saveCustomer(*c);
    cout << "Customer registered successfully!" << endl;
    return c;
}

bool isValidDate(const string& date) {
    if (date.size() != 10 || date[2] != '/' || date[5] != '/') {
        return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (isLeap && month == 2) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}

void bookFleet(const Customer& loggedInCustomer) {
    if (loggedInCustomer.c_name.empty()) {
        cout << "You need to log in to book a fleet." << endl;
        return;
    }

    string fromPlace, destination, fromDate, toDate, vehicleType;

    cout << "Enter from place: ";
    cin >> fromPlace;

    cout << "Enter destination: ";
    cin >> destination;

    do {
        cout << "Enter from date (dd/mm/yyyy): ";
        cin >> fromDate;
    } while (!isValidDate(fromDate));

    do {
        cout << "Enter to date (dd/mm/yyyy): ";
        cin >> toDate;
    } while (!isValidDate(toDate));

    cout << "Choose vehicle type (Trailer, Truck Tanker): ";
    cin >> vehicleType;

    ofstream file(bookingFile, ios::app);
    if (file) {
        file << loggedInCustomer.c_name << "," << fromPlace << "," << destination << ","
             << fromDate << "," << toDate << "," << vehicleType << endl;
        file.close();
        cout << "Booking successful!" << endl;

        // Call the shortest path function to display the route
        cout << "Path from " << fromPlace << " to " << destination << ":" << endl;
        dijkstra(graph, fromPlace, destination);  // This is an example; replace with your actual function call
    } else {
        cerr << "Error opening file!" << endl;
    }
}

void location(){
    const string filename = "gps_data.txt";

    // while (true) {
        readLocationFromFile(filename);
    //     this_thread::sleep_for(chrono::seconds(1));
    // }
}

void viewPastBookings(const Customer& loggedInCustomer) {
    ifstream file(bookingFile);
    string line;

    cout << "Past Bookings for " << loggedInCustomer.c_name << ":" << endl;
    bool hasBookings = false;

    if (file) {
        while (getline(file, line)) {
            istringstream ss(line);
            string custName, fromPlace, dest, fromDate, toDate, vehicleType;
            getline(ss, custName, ',');
            getline(ss, fromPlace, ',');
            getline(ss, dest, ',');
            getline(ss, fromDate, ',');
            getline(ss, toDate, ',');
            getline(ss, vehicleType, ',');

            if (custName == loggedInCustomer.c_name) {
                hasBookings = true;
                Booking booking(custName, fromPlace, dest, fromDate, toDate, vehicleType);
                booking.display();
                cout << "-------------------------" << endl;
            }
        }
        file.close();

        if (!hasBookings) {
            cout << "No past bookings found for " << loggedInCustomer.c_name << "." << endl;
        }
    } else {
        cerr << "Error opening file!" << endl;
    }
}



void displayCustomerMenu(Customer& loggedInCustomer) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n";
        cout << "1. View Customer Details\n";
        cout << "2. Book Fleet\n";
        cout << "3. View Past Bookings\n";
        cout << "4. Know Your Fleet Loaction\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loggedInCustomer.display();
                break;
            case 2:
                bookFleet(loggedInCustomer);
                break;
            case 3:
                viewPastBookings(loggedInCustomer);
                break;
            case 4:
                location();
                break;
            case 5:
                cout << "Logging out...\n";
                loggedInCustomer.c_name.clear();
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 5);
}

void mainMenu() {
    Customer loggedInCustomer;
    int choice;

    do {
        cout << "\nMain Menu:\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Customer* newCustomer = Customer_Register();
                delete newCustomer; 
                break;
            }
            case 2:
                Customer_Login(loggedInCustomer);
                if (!loggedInCustomer.c_name.empty()) {
                    displayCustomerMenu(loggedInCustomer);
                }
                break;
            case 3:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 3);
}


// int main() {
//     loadGraphFromFile(graph, filename);
//     mainMenu();
//     return 0;
// }


