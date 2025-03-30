#include "admin.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string ADMIN_USERNAME = "ziad";
const string ADMIN_PASSWORD = "256326";

bool adminlogin() {
	string username;
	string password ;
	cout << "enter your Username \n";
	cin >> username;
	cout << "enter your password \n";
	cin >> password;
	if (ADMIN_USERNAME == username && ADMIN_PASSWORD == password ) {
		cout << "login successfuly!\n";
		return true;
	}
	else {
		cout << "incorrect passowrd or username \n";
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
void adminmenu() {
	adminlogin();
	if (!adminlogin) {
		cout << "incorrect login. returing to main menu \n";
		return;
	}
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
		case 4 :
			modifyfees();
			break;
		/*case 5 :
			resetparking();*/
		case 6 :
			cout << "loging out \n";
			break;
		case 7 :
			return;

		}
	} while (choice != 6);
}
