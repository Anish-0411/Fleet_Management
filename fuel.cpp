#include <iostream>
#include <vector>
#include <fstream>

class Vehicle {
protected:
    double fuelEfficiency;
    std::vector<double> fuelLog;

public:
    Vehicle(double efficiency) : fuelEfficiency(efficiency) {}

    virtual double calculateFuel(double distance) {
        double fuelConsumed = distance / fuelEfficiency;
        fuelLog.push_back(fuelConsumed);
        return fuelConsumed;
    }

    void displayFuelLog() {
        double totalFuel = 0;
        for (double fuel : fuelLog) {
            totalFuel += fuel;
        }
        std::cout << "Total fuel consumed: " << totalFuel << " liters\n";
    }

    // Optional: Log fuel consumption to file
    void logToFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::app);
        for (double fuel : fuelLog) {
            file << fuel << " liters\n";
        }
        file.close();
    }
};

// Derived class example (Optional Inheritance & Polymorphism)
class Truck : public Vehicle {
public:
    Truck(double efficiency) : Vehicle(efficiency) {}

    // Override fuel calculation for trucks if needed
    double calculateFuel(double distance) override {
        double fuelConsumed = (distance / (fuelEfficiency - 2)); // assume trucks are less efficient
        fuelLog.push_back(fuelConsumed);
        return fuelConsumed;
    }
};

int main() {
    Vehicle car(15.0); // car with 15 km/l fuel efficiency
    Truck truck(8.0);  // truck with 8 km/l fuel efficiency

    // Simulate some routes
    car.calculateFuel(150); // 150 km route
    truck.calculateFuel(200); // 200 km route

    // Display fuel usage report
    car.displayFuelLog();
    truck.displayFuelLog();

    // Optional: Log to file
    car.logToFile("car_fuel_log.txt");
    truck.logToFile("truck_fuel_log.txt");

    return 0;
}


