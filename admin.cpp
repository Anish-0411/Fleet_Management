#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <climits>
using namespace std;
 map<string, vector<pair<string, int> > > graph;
string filename = "/Users/saianish/Desktop/2-1/C++/Project/graph_data.txt";
//---------------------------------LOGIN------------------------------------//
void Admin_Login(string name, string password) {
    cin.ignore();
    cout << "Enter Admin name: ";
    getline(cin, name);

    cout << "Enter password: ";
    getline(cin,password);

    if (name=="Admin123"&&password=="Admin@#123") {
        cout << "Login Successful!" << endl;
    } else {
        cout << "Login Unsuccessful! Invalid Credentials!" << endl;
        name = ""; // Reset logged-in status if login fails
    }
}

//-------------------------------------Route Management-------------------------------------//

#include <chrono>
#include <thread>

// Function to track route with percentage progress
void trackRoute(const map<string, vector<pair<string, int> > >& graph, const string& startCity, const string& endCity) {
    if (graph.find(startCity) == graph.end() || graph.find(endCity) == graph.end()) {
        cout << "One of the cities not found in the graph.\n";
        return;
    }

    // Find the shortest distance (as you've done with Dijkstra) or just simulate for simplicity
    int totalDistance = 0;
    for (const auto& neighbor : graph.at(startCity)) {
        if (neighbor.first == endCity) {
            totalDistance = neighbor.second;
            break;
        }
    }
    if (totalDistance == 0) {
        cout << "No direct route found between " << startCity << " and " << endCity << ".\n";
        return;
    }

    // Simulate route tracking progress
    for (int progress = 0; progress <= 100; progress += 10) {
        cout << "Tracking route from " << startCity << " to " << endCity << ": " << progress << "% completed.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Slow down for visibility
    }

    cout << "Destination " << endCity << " reached!\n";
}

bool routeExists(const map<string, vector<pair<string, int> > >& graph, const string& city1, const string& city2) {
    if (graph.find(city1) != graph.end()) {
        for (const auto& neighbor : graph.at(city1)) {
            if (neighbor.first == city2) {
                return true;
            }
        }
    }
    return false;
}

void addRoute(map<string, vector<pair<string, int> > >& graph, const string& city1, const string& city2, int distance, bool suppressWarning = false) {
    if (routeExists(graph, city1, city2)) {
        if (!suppressWarning) {
            cout << "Warning: Route between " << city1 << " and " << city2 << " already exists. Not adding duplicate route." << endl;
        }
    } else {
        graph[city1].push_back(make_pair(city2, distance));
        graph[city2].push_back(make_pair(city1, distance));
        if (!suppressWarning) {
            cout << "Route added between " << city1 << " and " << city2 << "." << endl;
        }
    }
}

// Function to display the graph
void displayGraph(const map<string, vector<pair<string, int> > >& graph) {
    for (const auto& city : graph) {
        cout << city.first << ": ";
        for (const auto& neighbor : city.second) {
            cout << "(" << neighbor.first << ", " << neighbor.second << " kilometers) ";
        }
        cout << endl;
    }
}

// Function to save the graph to a file
void saveGraphToFile(const map<string, vector<pair<string, int> > >& graph, const string& filename) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const auto& city : graph) {
            for (const auto& neighbor : city.second) {
                outfile << city.first << " " << neighbor.first << " " << neighbor.second << endl;
            }
        }
        outfile.close();
        cout << "Graph saved to file." << endl;
    } else {
        cout << "Error opening file to save graph." << endl;
    }
}


void loadGraphFromFile(map<string, vector<pair<string, int> > >& graph, const string& filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string city1, city2;
        int distance;
        while (infile >> city1 >> city2 >> distance) {
            // Suppress warnings while loading from file
            addRoute(graph, city1, city2, distance, true);
        }
        infile.close();
        cout << "Graph loaded from file." << endl;
    } else {
        cout << "Error opening file to load graph, or file doesn't exist." << endl;
    }
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(const map<string, vector<pair<string, int> > >& graph, const string& startCity, const string& endCity) {
    // Check if start and end cities exist in the graph
    if (graph.find(startCity) == graph.end()) {
        cout << "Start city not found in the graph.\n";
        return;
    }
    if (graph.find(endCity) == graph.end()) {
        cout << "End city not found in the graph.\n";
        return;
    }

    // Min-heap priority queue
    priority_queue<pair<int, string>, vector<pair<int, string> >, greater<pair<int, string> > > pq;

    // Distance map to store shortest distance from startCity to each city
    map<string, int> distances;
    
    // Parent map to reconstruct the path
    map<string, string> parents;

    // Initialize distances to infinity
    for (const auto& city : graph) {
        distances[city.first] = INT_MAX;
    }
    distances[startCity] = 0;

    // Add the start city to the priority queue
    pq.push(make_pair(0, startCity));

    while (!pq.empty()) {
        string currentCity = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        // Explore neighbors of the current city
        for (const auto& neighbor : graph.at(currentCity)) {
            string nextCity = neighbor.first;
            int edgeWeight = neighbor.second;
            int newDist = currentDist + edgeWeight;

            // If a shorter path to nextCity is found
            if (newDist < distances[nextCity]) {
                distances[nextCity] = newDist;
                parents[nextCity] = currentCity;
                pq.push(make_pair(newDist, nextCity));
            }
        }
    }

    // Output the shortest path and distance
    if (distances[endCity] == INT_MAX) {
        cout << "No path found between " << startCity << " and " << endCity << ".\n";
    } else {
        cout << "Shortest distance between " << startCity << " and " << endCity << ": " << distances[endCity] << " kilometers.\n";

        // Reconstruct the path
        vector<string> path;
        for (string at = endCity; at != ""; at = parents[at]) {
            path.push_back(at);
            if (at == startCity) break;  // Stop when we reach the start city
        }

        cout << "Path: ";
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }
}



//-------------------------------------Fleet Management-------------------------------------//


// void addVehicle(){
//     cout<<"Add";

// }
// void removeVehicle(){
//     cout<<"Remove";
//     // cout << "Enter vehicle number to remove: ";
//     // cin.ignore(); // Clear buffer before reading vehicle_no
//     // getline(cin, vehicle_no); // Allow spaces in the vehicle number
//     // remove_vehicle(vehicle_no);
// }
// void displayAllVehicles(){
//     cout<<"Display";
// }





// int main() {
//     map<string, vector<pair<string, int> > > graph;


//     // Load graph from file if it exists
//     loadGraphFromFile(graph, filename);

//     int choice;
//     do {
//         cout << "Menu:\n";
//         cout << "1. Add a route\n";
//         cout << "2. Display the graph\n";
//         cout << "3. Find shortest path (Dijkstra's Algorithm)\n";
//         cout << "4. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         if (choice == 1) {
//             string city1, city2;
//             int distance;
//             cout << "Enter first city: ";
//             cin >> city1;
//             cout << "Enter second city: ";
//             cin >> city2;
//             cout << "Enter distance between " << city1 << " and " << city2 << ": ";
//             cin >> distance;

//           // Add the route
//             addRoute(graph, city1, city2, distance);
//         } else if (choice == 2) {
//             // Display the graph
//             displayGraph(graph);
//         } else if (choice == 3) {
//             // Find shortest path
//             string startCity, endCity;
//             cout << "Enter the start city: ";
//             cin >> startCity;
//             cout << "Enter the end city: ";
//             cin >> endCity;
//             dijkstra(graph, startCity, endCity);
//         }

//     } while (choice != 4);

//     // Save graph to file before exiting
//     saveGraphToFile(graph, filename);

//     return 0;
// }



// int main() {
//     map<string, vector<pair<string, int> > > graph;
//     string filename = "graph_data.txt";

//     // Load graph from file if it exists
//     loadGraphFromFile(graph, filename);

//     int mainChoice;
//     do {
//         cout << "Main Menu:\n";
//         cout << "1. Route Management\n";
//         cout << "2. Fleet Management\n";
//         cout << "3. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> mainChoice;

//         if (mainChoice == 1) {
//             int routeChoice;
//             do {
//                 cout << "\nRoute Management Menu:\n";
//                 cout << "1. Add Route\n";
//                 cout << "2. Display Routes\n";
//                 cout << "3. Find Shortest Path (Dijkstra's Algorithm)\n";
//                 cout << "4. Exit to Main Menu\n";
//                 cout << "Enter your choice: ";
//                 cin >> routeChoice;

//                 if (routeChoice == 1) {
//                     string city1, city2;
//                     int distance;
//                     cout << "Enter first city: ";
//                     cin >> city1;
//                     cout << "Enter second city: ";
//                     cin >> city2;
//                     cout << "Enter distance between " << city1 << " and " << city2 << ": ";
//                     cin >> distance;

//                     // Add the route
//                     addRoute(graph, city1, city2, distance);
//                 } else if (routeChoice == 2) {
//                     // Display the graph
//                     displayGraph(graph);
//                 } else if (routeChoice == 3) {
//                     // Find shortest path
//                     string startCity, endCity;
//                     cout << "Enter the start city: ";
//                     cin >> startCity;
//                     cout << "Enter the end city: ";
//                     cin >> endCity;
//                     dijkstra(graph, startCity, endCity);
//                 }

//             } while (routeChoice != 4);
//         } else if (mainChoice == 2) {
//             int fleetChoice;
//             do {
//                 cout << "\nFleet Management Menu:\n";
//                 cout << "1. Add Vehicle\n";
//                 cout << "2. Remove Vehicle\n";
//                 cout << "3. Display All Vehicles\n";
//                 cout << "4. Exit to Main Menu\n";
//                 cout << "Enter your choice: ";
//                 cin >> fleetChoice;

//                 if (fleetChoice == 1) {
//                     addVehicle();
//                 } else if (fleetChoice == 2) {
//                     removeVehicle();
//                 } else if (fleetChoice == 3) {
//                     displayAllVehicles();
//                 }

//             } while (fleetChoice != 4);
//         }
//     } while (mainChoice != 3);

//     // Save the graph to file before exiting
//     saveGraphToFile(graph, filename);

//     return 0;
// }

// int main() {
//     map<string, vector<pair<string, int> > > graph;
//     // addRoute(graph, "CityA", "CityB",999000000);  // Add routes as needed

//     // Track route from CityA to CityB
//     trackRoute(graph, "delhi","mumbai");

//     return 0;
// }