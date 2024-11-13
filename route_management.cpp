#include<iostream>
#include<string>
using namespace std;

class Vehicle{
    public:
    string v_no;
    bool assignment;
     Vehicle(){
        assignment = false;
     }
    
    void add_vehicle(){
        getline(cin,v_no);
        cin>>assignment;
    }
    void get_assigned(){
    cout<<"Your Vehicle is Assigned"<<endl;
        assignment = true;
    } 

    void display(){
        cout<<v_no<<endl;
        if(assignment == true){
            cout<<"Your Vehicle is Booked!"<<endl;
        }
        else{
            cout<<"Your Vehicle is Not Assigned!"<<endl;
        }
    }
};


void assignment(Vehicle &v){
// Standard shipping containers: A 20-foot container can hold up to 28 tons, while a 40-foot container can hold up to 29 tons.
// Reefer shipping containers: These insulated containers can hold up to 36 tons of freight.
// Flat rack shipping containers: These containers can hold up to 30 tons of cargo.
// Multi-deck shipping containers: These containers can hold about 30 tons of cargo.
    int cap;
    do {
        cout<<"1. Standard(28 tons)\n2. Flat rack(30 tons)\n3. Multi-deck(30 tons)\n4. Reefer(36 tons)\n";
        cout<<"Enter the Capacity you want: "<<endl;
        cin>>cap;
        switch (cap)
        {
        case 1:
            v.get_assigned();
            cout<<"Standard\n";
            break;
        case 2:
            v.get_assigned();
            cout<<"Flat\n";
            break;
        case 3:
            v.get_assigned();
            cout<<"Multi-Deck\n";
            break;
        case 4:
            v.get_assigned();
            cout<<"Reefer\n";
            break;
        default:
            cout<<"Enter the correct capacity you want!"<<endl;
        }
    }while (cap<1||cap>4);
}

int main(){
    
    Vehicle v1;
    v1.add_vehicle();
    v1.display();
    assignment(v1);
    v1.display();
    
    return 0;
}
