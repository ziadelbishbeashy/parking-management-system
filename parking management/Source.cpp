#include "Class_vehicle.h"
#include "admin.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include "system.h"
#include "User.h"
using namespace std;

User u;

int main() {
	int choice;
	cout << setw(25) << right << "welcome to our car parking system \n";
	cout << setw(25) << right << "**************************************\n";
	do {
		cout << "1.Admin login\n";
		cout << "2.User mode \n";
		cout << "3. Exit \n";
		cin >> choice;
		switch (choice) {
		case 1:
			adminmenu();
			break;
		case 2:
		{
			int opt;
			cout << "1. Create User Account\n";
			cout << "2. Login as User\n";
			cout << "Enter your choice: ";
			cin >> opt;
			string loggedinusername;
			if (opt == 1) {
				createUseraccount();
			}
			else if (opt == 2) {
				if (loginUser(loggedinusername)) {
					usermenu(parking);  // launch full user menu
				}
				else {
					cout << "Login failed.\n";
				}
			}
			break;
		}
			break;
		case 3 :
			cout << "exiting system \n";
			break;
		default :
			cout << "invalid choice please try again\n";

		}
	} while (choice != 3);
	return 0;
}
	