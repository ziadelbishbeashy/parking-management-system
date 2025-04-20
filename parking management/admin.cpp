#include "admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "system.h"

using namespace std;

bool adminexist() {
	ifstream file("admin.txt");
	return file.good();
}
void createadmin() {
	ofstream file("admin.txt", ios::app);
	string username, password;

	cout << "no admin found \n";
	cout << "enter username :";
	cin >> username;
	cout << "enter password :";
	cin >> password;

	file << username << " " << password;
	file.close();

	cout << "admin account created successfully \n";
}
bool adminlogin() {
	ifstream file("admin.txt");
	string storeduser, storedpass, inputuser, inputpass;
	cout << "admin login \n";
	cout << "username:";
	cin >> inputuser;
	cout << "passowrd :";
	cin >> inputpass;
	bool found = false;


	while (file >> storeduser >> storedpass) {
		if (storeduser == inputuser && storedpass == inputpass) {
			found = true;
			break;
		}
	}

	file.close();
	if (found) {
		cout << "Login successful. Welcome, " << inputuser << "!\n";
		return true;
	}
	else {
		cout << "Invalid credentials.\n";
		return false;
	}
}

void modifyfees() {
	double carfee, bikefee, truckfee;
	cout << "Enter new car parking fees \n";
	cin >> carfee;
	cout << "Enter new bike parking fees \n";
	cin >> bikefee;
	cout << "Enter new truckfee \n";
	cin >> truckfee;

	ofstream filefee("Fee.txt");
	if (filefee) {
		filefee << carfee << " " << bikefee << " " << truckfee << endl;
	}
	else {
		cout << "Error updating fees.\n";
	}
	filefee.close();
}


void adminchoices() {
	int choice;

	// Initialize the choice to ensure the loop runs at least once
	choice = 0;

	while (choice != 8) {  // Loop continues until the user selects option 8 (exit)
		

		cout << "\n===== Admin Panel =====\n";
		cout << "1. View parked vehicles\n";
		cout << "2. Add parking slots\n";
		cout << "3. Remove vehicles\n";
		cout << "4. Modify parking fees\n";
		cout << "5. Reset parking slots\n";
		cout << "6. Undo last action\n";
		cout << "7. save system to file \n";
		cout << "8.load system from file \n";
		cout << "9. view waiting queue \n";
		cout << "10. Logout\n";
		cout << "11. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			system("cls");
			parking.viewAll();
			break;
		case 2:
			system("cls");
			int slots;
			cout << "Enter number of parking slots to initialize: ";
			cin >> slots;
			parking.addslots(slots);
			break;
		case 3:
			system("cls");
			int slotid;
			cout << "Enter slot id to remove vehicle: ";
			cin >> slotid;
			parking.removeVehicle(slotid);
			// parking.continueWithAnyKey();
			break;
		case 4:
			system("cls");
			modifyfees();
			break;
		case 5:
			system("cls");
			parking.reset();
			break;
		case 6:
			system("cls");
			parking.undolastaction();
			break;
		case 7:
			system("cls");
			parking.savesystem();
			break;
		case 8 :
			system("cls");
			parking.loadsystem();
			break;
		case 9:
			system("cls");
			parking.viewqueue();
			break;
		case 10:
			system("cls");
			cout << "Logging out...\n";
			return; // exit the function (logout)
		case 11:
			system("cls");
			cout << "Thanks for using our system.\n";
			break;
		default:
			system("cls");
			cout << "Invalid option. Try again.\n";
		}
	}
}

	
	void adminmenu() {
		int x;
		cout << "1.login:\n";
		cout << "2. create admin account:\n";
		cout << "enter ur choice :";
		cin >> x; 
		system("cls");
		switch (x) {
		case 1 :
			if (adminlogin()) {
				cout << "\n accessing admin functionalities... \n";
				adminchoices();
			}
			else {
				cout << "access denied. \n";
			}
			break;

		case 2:
			createadmin();
			break;
		default :
			cout << "invalid option \n";

	
		}
		}
	
