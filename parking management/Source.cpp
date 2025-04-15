#include "Class_vehicle.h"
#include "admin.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
using namespace std;

void continueWithAnyKey() {
	cout << "\nPress any key to continue...";
	cin.ignore();
	cin.get();
	system("cls");
}
void main() {
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
		
			break;
		case 3 :
			cout << "exiting system \n";
			break;
		default :
			cout << "invalid choice please try again\n";

		}
	} while (choice != 3);
}
	