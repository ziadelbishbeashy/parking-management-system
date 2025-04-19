#include "User.h"
#include <iostream>
#include"system.h"
#include "Class_vehicle.h"
#include <fstream>


using namespace std;
User::User() {}
User::User(string name , string pass) {
    username = name;
    password = pass; 
}
string User::getUsername()const {
    return username;
}
string User::getPassword()const {
    return password;
}
void User::setUsername(string name) {
    username = name;
}
void User::setPassword(string pass) {
    password = pass;
}

bool createUseraccount() {
    string name, pass;
    cout << "Enter username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;

    ofstream file("user.txt", ios::app);
    if (!file) {
        return false;
    }
    file << name << " " << pass << endl;
    file.close();
    cout << "account created successfully!\n";
    return true;


}
bool loginUser(string& loggedinusername) {
    string name, pass;

    cout << "enter username :";
    cin >> name;
    cout << "enter password :";
    cin >> pass;

    ifstream file("user.txt");
    string storedname, storedpass;
    while (file >> storedname >> storedpass) {
        if (storedname == name && storedpass == pass) {
            cout << "login successfull!\n";
            loggedinusername = name;
            return true;
        }
        
    }
    cout << "Invalid credentials.\n";
    return false;
}
void usermenu(parkingsystem& parking) {
    int choice;
    do {
        cout << "\n===== USER MENU =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. View Parking Slots\n";
        cout << "4. Undo Last Removal (Stack)\n";
        cout << "5. Save System to File\n";
        cout << "6. Load System from File\n";
        cout << "7. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int type;
            cout << "Select Vehicle Type:\n1. Car\n2. Bike\n3. Truck\nChoice: ";
            cin >> type;

            string time, plate;
            cout << "Enter time entered: ";
            cin >> time;
            cout << "Enter Plate Number: ";
            cin >> plate;

            vehicle* v = nullptr;

            if (type == 1) {
                bool isElectric;
                cout << "Is the car electric? (1 for Yes, 0 for No): ";
                cin >> isElectric;
                v = new car(plate, time, isElectric);
            }
            else if (type == 2) {
                bool bikeType;
                cout << "Enter Bike Type (e.g., sports, cruiser): ";
                cin >> bikeType;
                v = new bike(plate, time, bikeType);
            }
            else if (type == 3) {
                double capacity;
                cout << "Enter Truck Load Capacity (tons): ";
                cin >> capacity;
                v = new truck(plate, time, capacity);
            }
            else {
                cout << "Invalid vehicle type.\n";
                break;
            }

            if (!parking.parkVehicle(v)) {
                delete v;  // Clean up memory if not parked or queued
            }
            break;
        }

        }
    } while (choice != 7);
}