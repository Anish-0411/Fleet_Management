#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <climits>
using namespace std;


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

void addRoute(map<string, vector<pair<string, int> > >& graph, const string& city1, const string& city2, int distance) {
    if (routeExists(graph, city1, city2)) {
        cout << "Route between " << city1 << " and " << city2 << " already exists." << endl;
    } else {
        graph[city1].push_back(make_pair(city2, distance));
        graph[city2].push_back(make_pair(city1, distance));
        cout << "Route added between " << city1 << " and " << city2 << "." << endl;
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

// Function to load the graph from a file
void loadGraphFromFile(map<string, vector<pair<string, int> > >& graph, const string& filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string city1, city2;
        int distance;
        while (infile >> city1 >> city2 >> distance) {
            addRoute(graph, city1, city2, distance);
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

int main() {
    map<string, vector<pair<string, int> > > graph;
    string filename = "graph_data.txt";

    // Load graph from file if it exists
    loadGraphFromFile(graph, filename);

    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Add a route\n";
        cout << "2. Display the graph\n";
        cout << "3. Find shortest path (Dijkstra's Algorithm)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string city1, city2;
            int distance;
            cout << "Enter first city: ";
            cin >> city1;
            cout << "Enter second city: ";
            cin >> city2;
            cout << "Enter distance between " << city1 << " and " << city2 << ": ";
            cin >> distance;

          // Add the route
            addRoute(graph, city1, city2, distance);
        } else if (choice == 2) {
            // Display the graph
            displayGraph(graph);
        } else if (choice == 3) {
            // Find shortest path
            string startCity, endCity;
            cout << "Enter the start city: ";
            cin >> startCity;
            cout << "Enter the end city: ";
            cin >> endCity;
            dijkstra(graph, startCity, endCity);
        }

    } while (choice != 4);

    // Save graph to file before exiting
    saveGraphToFile(graph, filename);

    return 0;
}


// #include <iostream>
// #include <map>
// #include <vector>
// #include <string>
// #include <fstream>
// #include <queue>
// #include <climits>  // For large integer values like INT_MAX

// using namespace std;

// // Checks if a connection between two locations already exists
// bool isConnectionPresent(const map<string, vector<pair<string, int>>>& network, const string& loc1, const string& loc2) {
//     if (network.find(loc1) != network.end()) {
//         for (const auto& destination : network.at(loc1)) {
//             if (destination.first == loc2) {
//                 return true; // A connection already exists
//             }
//         }
//     }
//     return false; // No connection found
// }

// // Adds a new connection between two locations with the specified distance
// void insertConnection(map<string, vector<pair<string, int>>>& network, const string& loc1, const string& loc2, int dist) {
//     // If the connection already exists, inform the user
//     if (isConnectionPresent(network, loc1, loc2)) {
//         cout << "Connection between " << loc1 << " and " << loc2 << " already exists." << endl;
//     } else {
//         // Add a two-way connection between the two locations
//         network[loc1].push_back(make_pair(loc2, dist));
//         network[loc2].push_back(make_pair(loc1, dist));
//         cout << "Added a route between " << loc1 << " and " << loc2 << "." << endl;
//     }
// }

// // Displays all locations and their respective connections
// void showNetwork(const map<string, vector<pair<string, int>>>& network) {
//     for (const auto& loc : network) {
//         cout << loc.first << ": ";
//         for (const auto& destination : loc.second) {
//             cout << "(" << destination.first << ", " << destination.second << " km) ";
//         }
//         cout << endl;
//     }
// }

// // Saves the network data to a file
// void storeNetworkToFile(const map<string, vector<pair<string, int>>>& network, const string& file) {
//     ofstream outfile(file);
//     if (outfile.is_open()) {
//         for (const auto& loc : network) {
//             for (const auto& destination : loc.second) {
//                 outfile << loc.first << " " << destination.first << " " << destination.second << endl;
//             }
//         }
//         outfile.close();
//         cout << "Network saved to file." << endl;
//     } else {
//         cout << "Error: Could not open file to save network." << endl;
//     }
// }

// // Loads the network data from a file
// void loadNetworkFromFile(map<string, vector<pair<string, int>>>& network, const string& file) {
//     ifstream infile(file);
//     if (infile.is_open()) {
//         string loc1, loc2;
//         int dist;
//         while (infile >> loc1 >> loc2 >> dist) {
//             insertConnection(network, loc1, loc2, dist);
//         }
//         infile.close();
//         cout << "Network loaded from file." << endl;
//     } else {
//         cout << "Error: Could not open file to load network or file does not exist." << endl;
//     }
// }

// // Implements Dijkstra's algorithm to compute the shortest path between two locations
// void shortestPath(const map<string, vector<pair<string, int>>>& network, const string& start, const string& end) {
//     // Ensure both the start and end locations exist in the network
//     if (network.find(start) == network.end()) {
//         cout << "Start location not found in the network.\n";
//         return;
//     }
//     if (network.find(end) == network.end()) {
//         cout << "End location not found in the network.\n";
//         return;
//     }

//     // Priority queue to manage exploration of the shortest path
//     priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

//     // Map to store the shortest distance to each location
//     map<string, int> shortestDistances;
    
//     // Map to track the previous locations for path reconstruction
//     map<string, string> previousLocations;

//     // Initialize all distances as infinite
//     for (const auto& loc : network) {
//         shortestDistances[loc.first] = INT_MAX;
//     }
//     shortestDistances[start] = 0;

//     // Begin from the start location
//     pq.push(make_pair(0, start));

//     while (!pq.empty()) {
//         string currentLoc = pq.top().second;
//         int currentDistance = pq.top().first;
//         pq.pop();

//         // Explore the neighbors of the current location
//         for (const auto& neighbor : network.at(currentLoc)) {
//             string nextLoc = neighbor.first;
//             int edgeLength = neighbor.second;
//             int newDistance = currentDistance + edgeLength;

//             // If a shorter path to nextLoc is found
//             if (newDistance < shortestDistances[nextLoc]) {
//                 shortestDistances[nextLoc] = newDistance;
//                 previousLocations[nextLoc] = currentLoc;
//                 pq.push(make_pair(newDistance, nextLoc));
//             }
//         }
//     }

//     // If there's no path to the end location
//     if (shortestDistances[end] == INT_MAX) {
//         cout << "No route found between " << start << " and " << end << ".\n";
//     } else {
//         cout << "Shortest distance from " << start << " to " << end << " is: " << shortestDistances[end] << " km.\n";

//         // Reconstruct the path
//         vector<string> path;
//         for (string loc = end; loc != ""; loc = previousLocations[loc]) {
//             path.push_back(loc);
//             if (loc == start) break;  // Stop when we reach the start location
//         }

//         cout << "Path: ";
//         for (int i = path.size() - 1; i >= 0; --i) {
//             cout << path[i];
//             if (i > 0) cout << " -> ";
//         }
//         cout << endl;
//     }
// }

// int main() {
//     map<string, vector<pair<string, int>>> network;
//     string file = "network_data.txt";

//     // Load network from file if available
//     loadNetworkFromFile(network, file);

//     int option;
//     do {
//         cout << "Options Menu:\n";
//         cout << "1. Add a connection\n";
//         cout << "2. View network\n";
//         cout << "3. Find shortest route\n";
//         cout << "4. Exit\n";
//         cout << "Choose an option: ";
//         cin >> option;

//         if (option == 1) {
//             string loc1, loc2;
//             int dist;
//             cout << "Enter the first location: ";
//             cin >> loc1;
//             cout << "Enter the second location: ";
//             cin >> loc2;
//             cout << "Enter the distance between " << loc1 << " and " << loc2 << ": ";
//             cin >> dist;

//             // Add the new connection
//             insertConnection(network, loc1, loc2, dist);
//         } else if (option == 2) {
//             // Display the current network
//             showNetwork(network);
//         } else if (option == 3) {
//             // Compute and display the shortest path
//             string start, end;
//             cout << "Enter the starting location: ";
//             cin >> start;
//             cout << "Enter the destination: ";
//             cin >> end;
//             shortestPath(network, start, end);
//         }

//     } while (option != 4);

//     // Save the network to file before exiting
//     storeNetworkToFile(network, file);

//     return 0;
// }