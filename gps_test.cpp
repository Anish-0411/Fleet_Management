#include <iostream>
#include <fstream>
#include <string>
// #include <thread>
// #include <chrono>

using namespace std;

void readLocationFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        // Parse the latitude and longitude from the line
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string latitude = line.substr(0, commaPos);
            string longitude = line.substr(commaPos + 1);
            cout << "Latitude: " << latitude << ", Longitude: " << longitude << endl;
        } else {
            cerr << "Error: Invalid data format in file" << endl;
        }
    }

    inputFile.close();
}

// int main() {
//     const string filename = "gps_data.txt";
//     while (true) {
//         readLocationFromFile(filename);
//         this_thread::sleep_for(chrono::seconds(1));
//     }
//     return 0;
// }