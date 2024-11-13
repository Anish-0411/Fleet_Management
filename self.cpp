#include<iostream>
#include<string>
using namespace std;


class Vehicle{
    public:
    string vehicle_name;
    string vehicle_no;
    float fuel_capacity;
    float fuel_efficiency;
    bool assignment;

    Vehicle(){
        assignment = false;
        // if(assignment==false){
        //     cout<<"Not Assigned!"<<endl;
        // }
        // else{
        //     cout<<"Assigned"<<endl;
        // }
     }
    
    void assign_details(){
        cout<<"Enter vehicle name: "<<endl;
        cin>>vehicle_name;
        cout<<"Enter vehicle number: "<<endl;
        cin>>vehicle_no;
        cout<<"Enter fuel capacity: "<<endl;
        cin>>fuel_capacity;
        cout<<"Enter fuel efficiency: "<<endl;
        cin>>fuel_efficiency;
    }
    void display(){
        cout<<"Vehicle Name: "<<vehicle_name<< endl;
        cout<<"Vehicle Number: "<<vehicle_no<< endl;
        cout<<"Vehicle fuel capacity: "<<fuel_capacity<< endl;
        cout<<"Vehicle fuel efficiency: "<<fuel_efficiency<< endl;
    }
    void get_assigned(Vehicle &v){
        cout<<"Your Fleet is Booked succesfully!"<<endl;
    }
};

void assignment(){
// Standard shipping containers: A 20-foot container can hold up to 28 tons, while a 40-foot container can hold up to 29 tons.
// Reefer shipping containers: These insulated containers can hold up to 36 tons of freight.
// Flat rack shipping containers: These containers can hold up to 30 tons of cargo.
// Multi-deck shipping containers: These containers can hold about 30 tons of cargo.
    cout<<"1. Standard(28 tons)\n2. Flat rack(30 tons)\n 3. Multi-deck(30 tons)\n 4. Reefer(36 tons)\n";
    cout<<"Enter the Capacity you want: "<<endl;
    int cap;
    cin>>cap;
    switch (cap)
    {
    case 1:
        // v.get_assigned(v1);
        cout<<"stan";
        break;
    case 2:
        cout<<"flat";
        break;
    case 3:
        cout<<"multi";
        break;
    case 4:
        cout<<"reefer";
        break;

    default:
        cout<<"Enter the correct capacity you want!"<<endl;
    }
}

int main(){
    Vehicle v1,v2;
    v1.assign_details();
    v1.display();
    v2.assign_details();
    v2.display();
    return 0;
}
