#include <iostream>
#include <fstream>
#include <string>

class Driver {
private:
    std::string driverID;
    std::string password;
public:
    Driver(std::string id, std::string pass) : driverID(id), password(pass) {}

    // Function to verify login credentials by reading from file
    bool verifyLogin(const std::string& inputID, const std::string& inputPassword) {
        std::ifstream file("drivers.txt");
        std::string id, pass;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file!" << std::endl;
            return false;
        }

        while (file >> id >> pass) {
            if (id == inputID && pass == inputPassword) {
                return true;  // Login successful
            }
        }

        return false;  // Login failed
    }

    // Function to display the driver's assigned vehicle
    void displayAssignedVehicle() {
        std::cout << "Vehicle assigned to driver ID: " << driverID << std::endl;
        // You can extend this to show actual vehicle details from another part of the project
    }

    // Static method to register a new driver and store their credentials in file
    static void registerDriver(const std::string& newID, const std::string& newPassword) {
        std::ofstream file("drivers.txt", std::ios::app);  // Append mode
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file!" << std::endl;
            return;
        }
        file << newID << " " << newPassword << std::endl;
        std::cout << "Driver registered successfully!" << std::endl;
    }
};

// int main() {
//     int choice;
//     std::string driverID, password;

//     std::cout << "Driver Login System\n";
//     std::cout << "1. Login\n";
//     std::cout << "2. Register New Driver\n";
//     std::cout << "Enter your choice: ";
//     std::cin >> choice;

//     if (choice == 1) {
//         std::cout << "Enter Driver ID: ";
//         std::cin >> driverID;
//         std::cout << "Enter Password: ";
//         std::cin >> password;

//         Driver driver(driverID, password);
//         if (driver.verifyLogin(driverID, password)) {
//             std::cout << "Login successful!" << std::endl;
//             driver.displayAssignedVehicle();  // Show assigned vehicle after login
//         } else {
//             std::cout << "Login failed! Invalid credentials." << std::endl;
//         }
//     } else if (choice == 2) {
//         std::cout << "Enter new Driver ID: ";
//         std::cin >> driverID;
//         std::cout << "Enter new Password: ";
//         std::cin >> password;

//         Driver::registerDriver(driverID, password);  // Register new driver
//     } else {
//         std::cout << "Invalid choice!" << std::endl;
//     }

//     return 0;
// }
