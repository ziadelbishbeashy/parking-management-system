#include "Class_vehicle.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
using namespace std;
void main() {
	int choice;
	string plate, time;
	cout << setw(25) << right << "welcome to our car parking system \n";
	cout << setw(25) << right << "**************************************\n";
	vehicle* v =nullptr;
	char continueChoice;
	
	do {
		cout << "\nSelect vehicle type:\n";
		cout << "1. Car\n";
		cout << "2. Bike\n";
		cout << "3. Truck\n";
		cout << "4. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;
		cout << "enter license plate :";
		cin >> plate;
		cout << "enter entry time (HH::MM AM/PM) :";
		cin >> time;

		if (choice == 1) { //car
			bool iselctric;
			cout << "is the car electric (1 for yes , o for no) :";
			cin >> iselctric;
			v= new car(plate, time, iselctric);
			

		}
		else if (choice == 2) {  // Bike
			bool isBicycle;
			cout << "Is it a bicycle? (1 for Yes, 0 for No): ";
			cin >> isBicycle;
			v = new bike(plate, time, isBicycle);

		}

		else if (choice == 3) { //truck
	
			double load;
			cout << "Enter truck load capacity (kg): ";
			cin >> load;
			v = new truck(plate, time, load);
		}
		else if (choice == 4) {
			cout << "Exiting system. Thank you!\n";
			break;
		}
		else {
			cout << "Invalid choice! Please restart the program.\n";
		}
		cout << "\n vehicle entered\n ------------\n";
		v->displayinfo();
		cout << "status: parked hours\n\n";
		double hours;
		cout << "enter parked hours:";
		cin >> hours;
		cout << "Total Fee: " << v->calculatefees(hours) << endl;

		cout << "\nDo you want to add another vehicle? (Y/N): ";
		cin >> continueChoice;

		delete v;
	   
	}

	while (continueChoice == 'Y' || continueChoice == 'y');

	cout << "\n thank you for using the parking system \n";
}