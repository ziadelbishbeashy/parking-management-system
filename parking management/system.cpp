#include "system.h"
#include <fstream>
#include <iostream>
using namespace std;


//void continueWithAnyKey() {
//	cout << "\nPress any key to continue...";
//	cin.ignore();
//	cin.get();
//	system("cls");
//}

parkingsystem::parkingsystem() {
	parking = nullptr;
	totalslots = 0;
	parkedCount = 0;
	
	//queue initialization
	queueFront = 0;
	queueRear = -1;

	//stack initialization
	stackTop = -1;
}
parkingsystem::~parkingsystem() {
	delete[]parking;  // clean up dynamic array

}
void parkingsystem::initialize(int slots) {
	totalslots = slots;
	parking = new parkingSlot[totalslots];
	for (int i = 0; i < totalslots; i++) {
		parking[i].ptr = nullptr;
		parking[i].occupied = false;
	}
}

void parkingsystem::addslots(int extraslots) {
	int newtotal = totalslots + extraslots;
	parkingSlot* newparking = new parkingSlot[newtotal];

	//copy old parking data

	for (int i = 0; i < totalslots; i++) {
		newparking[i] = parking[i];
	}

	//intialize new slots 
	for (int i = totalslots; i < newtotal; i++) {
		newparking[i].ptr = nullptr;
		newparking[i].occupied = false;
	}

	//delete old array
	delete[]parking;

	//new array and update slot count 
	parking = newparking;
	totalslots = newtotal;

	cout << extraslots << "slots added. total slots now :" << totalslots << endl;
}

bool parkingsystem::parkVehicle(vehicle* v) {
	for (int i = 0; i < totalslots; i++) {
		if (!parking[i].occupied) {
			parking[i].ptr = v;
			parking[i].occupied = true;
			parkedCount++;
			cout << "vehicle parked in slot " << (i + 1) << endl;
			return true;
		}
	}
	cout << " no available slots! \n";
	return false;
}
bool parkingsystem::removeVehicle(int slotid) {
	if (slotid < 1 || slotid >totalslots || !parking[slotid - 1].occupied) {
		cout << "invalid or empty slots.\n";
		return false;
	}
	delete parking[slotid - 1].ptr;
	parking[slotid - 1].ptr = nullptr;
	parking[slotid - 1].occupied = false;
	parkedCount--;

	cout << "vehicle removed from slot " << slotid << endl;
	return true;
}

void parkingsystem::viewAll() {
	cout << "\n==== Currently parked vehicles ====\n";
	bool found = false;

	for (int i = 0; i < totalslots; i++) {
		if (parking[i].occupied) {
			cout << "Slot " << i + 1 << ":\n";
			parking[i].ptr->displayinfo();
			cout << "-----------------------\n";
			found = true;
			
		}
	}
	//continueWithAnyKey();
	if (!found) {
		cout << "No vehicles parked currently.\n";
	}
}
void parkingsystem::reset() {
	for (int i = 0; i < totalslots; i++) {
		if (parking[i].occupied) {
			delete parking[i].ptr;
			parking[i].ptr = nullptr;
			parking[i].occupied = false;
		}
	}
	parkedCount = 0;
	cout << "All parking slots have been cleared.\n";
	//continueWithAnyKey();
}
void parkingsystem::savesystem() {
	ofstream file ("parking_data.txt");

	if (!file) {
		cout << "error saving parking data \n";
		return;
	}
	file << totalslots << endl;
	for (int i = 0; i < totalslots; i++) {
		if (parking[i].occupied && parking[i].ptr != nullptr) {
			file << i << " " << parking[i].ptr->gettype() << " " << parking[i].ptr->getlicense() << " " << parking[i].ptr->getentry() << endl;
		  }
	}
	file.close();
	cout << "parking data saved\n";
	//continueWithAnyKey();
}
void parkingsystem::loadsystem() {
	ifstream file("parking_data.txt");
	if (!file) {
		cout << "no saved parking data found. \n";
		return;
	}
	int slotid;
	string type, license, time;

	file >> totalslots; //read total number of slots

	if (parking != nullptr) { // free the memory before reading from file
		delete[]parking;
	}
	
	parking = new parkingSlot[totalslots];
	
	//intialize all slots

	for (int i = 0; i < totalslots; i++) {
		parking[i].ptr = nullptr;
		parking[i].occupied = false;
	}

	//read saved data 
	// ws to discard whitspaces chars while reading
	while (file >> slotid >> type >> license >> ws && getline(file, time)) {
		vehicle* v = nullptr;

		//recreate correct vehicle type (we assume dummy values for some details)
		if (type == "car") {
			v = new car(license, time, false);
		}
		else if (type == "bike") {
			v = new bike(license, time, false);
		}
		else if (type == "truck") {
			v = new truck(license, time, 5.0);
		}
		
		// Place it in the corresponding parking slot
		if (v != nullptr && slotid >= 0 && slotid < totalslots) {
			parking[slotid].ptr = v;
			parking[slotid].occupied = true;
			parkedCount++;
		}
	}
	file.close();
	cout << "parking data loaded succesfully \n";
	//continueWithAnyKey();

}
bool parkingsystem::isQueueEmpty() {
	// Check if the queue is empty based on the circular queue logic
	return queueFront == (queueRear + 1) % max_queue_size;
}


void parkingsystem::enqueue(vehicle* v) {
	
		// Check if the queue is full
		if ((queueRear + 1) % max_queue_size == queueFront) {
			cout << "Queue is full. Cannot enqueue vehicle.\n";
			return;
		}

		// Circular increment for queueRear
		queueRear = (queueRear + 1) % max_queue_size;
		waitQueue[queueRear] = v;
        cout << "Vehicle with plate [" << v->getlicense() << "] added to waiting queue.\n";
	

}

vehicle* parkingsystem::dequeue() {
	if (isQueueEmpty()) {
		cout << "Queue is empty. Cannot dequeue vehicle.\n";
		return nullptr;
	}

	vehicle* temp = waitQueue[queueFront];
	queueFront = (queueFront + 1) % max_queue_size;

	if (queueFront == (queueRear + 1) % max_queue_size) {
		queueFront = queueRear = -1;
	}

	return temp;
}


void parkingsystem::viewqueue() {
	if (isQueueEmpty()) {
		cout << "No vehicles in the waiting queue.\n";
		return;
	}

	cout << "Vehicles in the waiting queue:\n";
	for (int i = queueFront; i != queueRear; i = (i + 1) % max_queue_size) {
		cout << " - " << waitQueue[i]->getlicense() << "\n";
	}
	cout << "Total vehicles waiting: " << (queueRear - queueFront + max_queue_size) % max_queue_size << endl;
}

