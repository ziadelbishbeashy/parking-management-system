#include "Class_vehicle.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
using namespace std;
void main() {
	int choice;
	string plate, time;
	cout << setw(15) << right << "welcome to our car parking system \n";
	cout << setw(15) << right << "**************************************\n";
	cout << "select vehicle type : (1 for car / 2 for bike / 3 truck ) \n";
	cin >> choice;
	cout << "enter license plate :";
	cin >> plate;
	cout << "enter entry time (HH::MM AM/PM) :";
	cin >> time;

	if (choice == 1) { //car
		bool iselctric;
		cout << "is the car electric (1 for yes , o for no) :";
		cin >> iselctric;
		car c(plate, time, iselctric);
		c.displayinfo();
		double hours;
		cout << "enter parked hours :";
		cin >> hours;
		cout << "total fee :" << c.calculatefees(hours) << endl;

	}
	else if (choice == 2) {  // Bike
		bool isBicycle;
		cout << "Is it a bicycle? (1 for Yes, 0 for No): ";
		cin >> isBicycle;
		bike b(plate, time, isBicycle);
		if (isBicycle == true) {
			b.isbicycle();
		}

		cout << "\nBike Details:\n";
		b.displayinfo();

		double hours;
		cout << "Enter parked hours: ";
		cin >> hours;

		cout << "Total Fee: $" << b.calculatefees(hours) << endl;


	}

 else if (choice == 3) {
	 double load;
	 cout << "Enter truck load capacity (kg): ";
	 cin >> load;
	 double hours;
	 truck t(plate, time, load);
	 cout << "Enter parked hours: ";
	 cin >> hours;
	 t.displayinfo();
	 cout << "Total Fee: $" << t.calculatefees(hours)<< endl;

	}
 else {
	 cout << "Invalid choice! Please restart the program.\n";
	}

}