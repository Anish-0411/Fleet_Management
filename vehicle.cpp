#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

class Vehicle {
public:
    string vehicle_name;
    string vehicle_no;
    float fuel_capacity;
    float fuel_efficiency;
    bool assignment;
    float distance_traveled;

    Vehicle() : assignment(false), distance_traveled(0) {}

    void assign_details() {
        cout << "Enter vehicle name: ";
        cin.ignore();
        getline(cin, vehicle_name);

        cout << "Enter vehicle number: ";
        getline(cin, vehicle_no);

        cout << "Enter fuel capacity: ";
        cin >> fuel_capacity;

        while (cin.fail() || fuel_capacity <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid fuel capacity: ";
            cin >> fuel_capacity;
        }

        cout << "Enter fuel efficiency: ";
        cin >> fuel_efficiency;

        while (cin.fail() || fuel_efficiency <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid fuel efficiency: ";
            cin >> fuel_efficiency;
        }

        ofstream outFile("/Users/saianish/Desktop/2-1/C++/Project/vehicles.txt", ios::app);
        if (outFile.is_open()) {
            outFile << vehicle_name << " " << vehicle_no << " " << fuel_capacity << " "
                    << fuel_efficiency << " " << assignment << endl;
            outFile.close();
            cout << "Vehicle added successfully!" << endl;
        } else {
            cout << "Error opening file!" << endl;
        }
    }

    void display() const {
        cout << "Vehicle Name: " << vehicle_name << endl;
        cout << "Vehicle Number: " << vehicle_no << endl;
        cout << "Fuel Capacity: " << fuel_capacity << " liters" << endl;
        cout << "Fuel Efficiency: " << fuel_efficiency << " km/l" << endl;
        cout << "Assignment Status: " << (assignment ? "Assigned" : "Not Assigned") << endl;
    }

    void assign_vehicle() {
        if (assignment) {
            cout << "Vehicle is already assigned!" << endl;
        } else {
            assignment = true;
            update_assignment_in_file();
            cout << "Your Fleet is Booked successfully!" << endl;
        }
    }

    void update_assignment_in_file() {
        ifstream file("vehicles.txt");
        ofstream tempFile("temp.txt");
        string name, number;
        float cap, efficiency;
        bool status;

        if (file.is_open() && tempFile.is_open()) {
            while (file >> name >> number >> cap >> efficiency >> status) {
                if (name == vehicle_name && number == vehicle_no) {
                    tempFile << name << " " << number << " " << cap << " "
                             << efficiency << " " << true << endl;
                } else {
                    tempFile << name << " " << number << " " << cap << " "
                             << efficiency << " " << status << endl;
                }
            }
            file.close();
            tempFile.close();
            remove("vehicles.txt");
            rename("temp.txt", "vehicles.txt");
        } else {
            cout << "Error opening file for updating!" << endl;
        }
    }

    bool is_assigned() {
        ifstream file("vehicles.txt");
        string name, number;
        float cap, efficiency;
        bool status;

        if (file.is_open()) {
            while (file >> name >> number >> cap >> efficiency >> status) {
                if (name == vehicle_name && number == vehicle_no) {
                    file.close();
                    return status;
                }
            }
            file.close();
        } else {
            cout << "Error opening file!" << endl;
        }
        return false;
    }

    void add_vehicle() {
        assign_details();
    }

    void remove_vehicle(const string& vehicle_no) {
        ifstream inFile("vehicles.txt");
        ofstream tempFile("temp.txt");

        string name, number;
        float cap, efficiency;
        bool status;
        bool removed = false;

        if (inFile.is_open() && tempFile.is_open()) {
            while (inFile >> name >> number >> cap >> efficiency >> status) {
                if (number != vehicle_no) {
                    tempFile << name << " " << number << " " << cap << " "
                             << efficiency << " " << status << endl;
                } else {
                    removed = true;
                }
            }
            inFile.close();
            tempFile.close();
            remove("vehicles.txt");
            rename("temp.txt", "vehicles.txt");

            if (removed) {
                cout << "Vehicle removed successfully!" << endl;
            } else {
                cout << "Vehicle not found!" << endl;
            }
        } else {
            cout << "Error opening file!" << endl;
        }
    }

    void list_vehicles() const {
        ifstream inFile("vehicles.txt");

        if (!inFile.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        string name, number;
        float cap, efficiency;
        bool status;
        bool isEmpty = true;

        cout << "--------------------- Vehicle List ---------------------" << endl;

        while (inFile >> name >> number >> cap >> efficiency >> status) {
            isEmpty = false;
            cout << "Vehicle Name: " << name << endl;
            cout << "Vehicle Number: " << number << endl;
            cout << "Fuel Capacity: " << cap << " liters" << endl;
            cout << "Fuel Efficiency: " << efficiency << " km/l" << endl;
            cout << "Assignment Status: " << (status ? "Assigned" : "Not Assigned") << endl;
            cout << "--------------------------------------------------------" << endl;
        }

        if (isEmpty) {
            cout << "No vehicles found." << endl;
        }

        inFile.close();
    }

    // Combined function to update distance and calculate efficiency for a specific vehicle
    void update_distance_and_calculate_efficiency() {
        string input_vehicle_no;
        cout << "Enter vehicle number to update distance and calculate fuel efficiency: ";
        cin.ignore(); // Clear the buffer
        getline(cin, input_vehicle_no);

        // Search for the vehicle by number
        ifstream inFile("vehicles.txt");
        ofstream tempFile("temp.txt");
        string name, number;
        float cap, efficiency;
        bool status;
        bool vehicle_found = false;

        while (inFile >> name >> number >> cap >> efficiency >> status) {
            if (number == input_vehicle_no) {
                vehicle_found = true;
                cout << "Vehicle found!" << endl;
                cout << "Enter distance traveled: ";
                float distance;
                cin >> distance;

                // Validate distance input
                while (cin.fail() || distance < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Enter a valid distance: ";
                    cin >> distance;
                }

                // Update the distance traveled and calculate fuel efficiency
                distance_traveled = distance;
                float fuel_consumed = distance_traveled / efficiency;
                cout << fixed << setprecision(2);
                cout << "Distance Traveled: " << distance_traveled << " km" << endl;
                cout << "Fuel Consumed: " << fuel_consumed << " liters" << endl;
                cout << "Calculated Fuel Efficiency: " << efficiency << " km/l" << endl;
            }

            // Write the current vehicle details back to the temp file
            tempFile << name << " " << number << " " << cap << " "
                     << efficiency << " " << status << endl;
        }

        if (!vehicle_found) {
            cout << "Vehicle not found!" << endl;
        }

        inFile.close();
        tempFile.close();
        // Replace the original file with the updated temp file
        remove("vehicles.txt");
        rename("temp.txt", "vehicles.txt");
    }

    void admin_menu() {
        int choice;
        string vehicle_no;

        do {
            cout << "1. Add Vehicle\n2. Remove Vehicle\n3. List Vehicles\n4. Fuel Efficiency\n5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    add_vehicle();
                    break;
                case 2:
                    cout << "Enter vehicle number to remove: ";
                    cin.ignore();
                    getline(cin, vehicle_no);
                    remove_vehicle(vehicle_no);
                    break;
                case 3:
                    list_vehicles();
                    break;
                case 4:
                    update_distance_and_calculate_efficiency();
                    break;
                case 5:
                    cout << "Exiting menu...\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
            }
        } while (choice != 5);
    }
};

// int main() {
//     Vehicle v;
//     v.admin_menu();
//     return 0;
// }