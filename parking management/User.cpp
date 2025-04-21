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
        system("cls");
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
                bool isElectric=false;
               
                v = new car(plate, time, isElectric);
            }
            else if (type == 2) {
                bool bikeType = false;
               
                v = new bike(plate, time, bikeType);
            }
            else if (type == 3) {
                double capacity = 5.0;
               
                v = new truck(plate, time, capacity);
            }
            else {
                cout << "Invalid vehicle type.\n";
                return;
            }


            v->setlicense(plate);
            v->input();

            cout << "1. Park Now\n2. View Slots\nChoice: ";
            int opt;
            cin >> opt;

            if (opt == 1) {
                parking.parkVehicle(v);
                
            }
            else if (opt == 2) {
              parking.viewslots();
            }
            break;
        }
        case 2:
            int slot;
            cout << "enter slot number to remove vehicle :";
            cin >> slot;
            parking.removeVehicle(slot);
            break;
        case 3:
           parking.viewslots(); // View slots
            break;

        case 4:
            parking.undolastaction(); // Stack-based undo
            break;

        case 5:
            parking.savesystem(); // Save
            break;

        case 6:
            parking.loadsystem(); // Load
            break;

        case 7:
            cout << "Exiting user menu...\n";
            break;

        default:
            cout << "Invalid option. Try again.\n";
        }

        cout << "\nPress any key to continue...";
        cin.ignore(); cin.get();


        }  while (choice != 7);
    } 
