#include "admin.h"
#include <iostream>
#include <fstream>
#include <string>
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
		do {
			cout << "\n===== Admin Panel =====\n";
			cout << "1.view parked vehicles \n";
			cout << "2. add parking slots \n";
			cout << "3. remove vehicles \n";
			cout << "4. modify parking fees \n";
			cout << "5. reset parking slots \n";
			cout << " 6. logout \n";
			cout << "7. return to main menu \n";
			cin >> choice;
			switch (choice) {
				/*case 1 :
					viewparked();
					break;
				case 2 :
					addparking();
					break;
				case 3 :
					removevehicle();
					break;*/
			 case 4:
				modifyfees();
				break;
				/*case 5 :
					resetparking();*/
			 case 6:
				cout << "loging out \n";
				break;
			case 7:
				cout << "returning to main menu ...\n";
				return;
			default:
				cout << "invalid option. try again \n";

			}

		} while (choice != 6);

	}
	void adminmenu() {
		int x;
		cout << "1.login:\n";
		cout << "2. create admin account:\n";
		cout << "enter ur choice :";
		cin >> x; 
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
	
