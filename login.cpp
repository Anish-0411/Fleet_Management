#include<iostream>
#include </Users/saianish/Desktop/2-1/C++/Project/customer.cpp>
// #include </Users/saianish/Desktop/2-1/C++/Project/admin.cpp>
#include </Users/saianish/Desktop/2-1/C++/Project/vehicle.cpp>


#include <unistd.h>

using namespace std;
int main(){
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current working directory: " << cwd << std::endl;
    }
       loadGraphFromFile(graph, filename);
    int n;
    do{
        cout<<"1.Customer\n2.Admin\n3.Exit"<<endl;
        cin>>n;
        
        switch (n)
        {
        case 1:{
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
            break;
        
        case 2:{
            cout<<"Admin Login"<<endl;
            
            string name,password;
            bool login;
            
            cin.ignore();
            while(login!=true){
        
                cout<<"Login "<<endl;
                cout << "Enter Admin name: ";
                getline(cin, name);

                cout << "Enter password: ";
                getline(cin,password);

                if (name=="Admin123"&&password=="Admin@#123") {
                    cout << "Login Successful!" << endl;
                    login = true;
                } else {
                    cout << "Login Unsuccessful! Invalid Credentials!" << endl;
                    name = ""; // Reset logged-in status if login fails
                    login=false;
                }
            }


            map<string, vector<pair<string, int> > > graph;
            string filename = "graph_data.txt";

            // Load graph from file if it exists
            loadGraphFromFile(graph, filename);
        
        int mainChoice;
        do {
            cout << "Main Menu:\n";
            cout << "1. Route Management\n";
            cout << "2. Fleet Management\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> mainChoice;

            if (mainChoice == 1) {
                int routeChoice;
                do {
                    cout << "\nRoute Management Menu:\n";
                    cout << "1. Add Route\n";
                    cout << "2. Display Routes\n";
                    cout << "3. Find Shortest Path (Dijkstra's Algorithm)\n";
                    cout << "4. Exit to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> routeChoice;

                    if (routeChoice == 1) {
                        string city1, city2;
                        int distance;
                        cout << "Enter first city: ";
                        cin >> city1;
                        cout << "Enter second city: ";
                        cin >> city2;
                        cout << "Enter distance between " << city1 << " and " << city2 << ": ";
                        cin >> distance;

                        addRoute(graph, city1, city2, distance);
                    } else if (routeChoice == 2) {
                        displayGraph(graph);
                    } else if (routeChoice == 3) {
                        string startCity, endCity;
                        cout << "Enter the start city: ";
                        cin >> startCity;
                        cout << "Enter the end city: ";
                        cin >> endCity;
                        dijkstra(graph, startCity, endCity);
                    }

                } while (routeChoice != 4);
            } else if (mainChoice == 2) {
                 Vehicle vehicle;
                vehicle.admin_menu();
            }
        } while (mainChoice != 3);

        saveGraphToFile(graph, filename);
            }
            break;
        case 3:
            cout<<"Exiting..."<<endl;
            break;
        default:
            cout<<"Enter the Correct Choice!"<<endl;
            break;
        }
    }while(n!=3);

    return 0;
}
