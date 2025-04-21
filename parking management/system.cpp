#include"system.h" ﻿
#include <fstream>
#include <iostream>


using namespace std;


parkingsystem::parkingsystem() {}
parkingsystem::parkingsystem(int cap) {
	parking = nullptr;
	totalslots = cap > 0 ? cap : 10;
	parkedCount = 0;


	initialize(totalslots); //

	//queue initialization
	queueFront = 0;
	queueRear = -1;

	waitQueue = new vehicle * [queuesize];
	for (int i = 0; i < queuesize; i++) {
		waitQueue[i] = nullptr;
	}

	//stack initialization
	stackTop = -1;

	loadsystem();
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

	for (int i = 0; i < totalslots && i < newtotal; i++) {
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


void parkingsystem::parkVehicle(vehicle* v) {
	if (parking == nullptr) {
		cout << "error : parking system is not initialized. \n";
		return; // avoid crashing if parking is not initialized 
	}
	bool parked = false;


	for (int i = 0; i < totalslots; i++) {
		if (!parking[i].occupied) {
			parking[i].ptr = v;
			parking[i].occupied = true;
			parkedCount++;

			if (undotop < 99) {
				undotop++;
				undostack[undotop] = { 'P', v, i };  // 'P' for Park
			}
			cout << "vehicle parked in slot " << (i + 1) << endl;
			savesystem();

			parked = true;
			return;
		}
	}
	if (!parked) {
		cout << "no available slots !\n";
		enqueue(v);
		cout << "you will be notified when a slot is available " << endl;
	}

}
bool parkingsystem::removeVehicle(int slotid) {
	if (slotid < 1 || slotid > totalslots || !parking[slotid ].occupied) {
		cout << "Invalid or empty slot.\n";
		return false;
	}

	// Save pointer before deleting for undo functionality
	vehicle* removedVehicle = parking[slotid].ptr;

	// Push the removed vehicle to the undo stack
	pushUndo(removedVehicle);

	// Clean up memory and update state
	delete parking[slotid].ptr;
	parking[slotid ].ptr = nullptr;
	parking[slotid ].occupied = false;
	parkedCount--;

	cout << "Vehicle removed from slot " << slotid << endl;

	if (!isQueueEmpty()) {
		vehicle* next = dequeue();
		parking[slotid ].ptr = next;
		parking[slotid ].occupied = true;
		parkedCount++;
		cout << "Vehicle from queue with plate [" << next->getlicense() << "] parked in slot " << slotid << endl;
		pushUndo(next);
	}

	savesystem();
	return true;

}


void parkingsystem::viewAll() {
	cout << "\n==== Currently parked vehicles ====\n";
	bool found = false;

	for (int i = 0; i < totalslots; i++) {
		// Skip if slot is not occupied or vehicle pointer is null
		if (!parking[i].occupied || parking[i].ptr == nullptr) {
			continue;
		}

		cout << "Slot " << i + 1 << ":\n";
		parking[i].ptr->displayinfo();
		cout << "-----------------------\n";
		found = true;
	}

	if (!found) {
		cout << "No vehicles parked currently.\n";
	}
}

void parkingsystem::reset() {
	// 1. Clear and delete parked vehicles
	if (parking != nullptr) {
		for (int i = 0; i < totalslots; i++) {
			if (parking[i].occupied && parking[i].ptr != nullptr) {
				delete parking[i].ptr; // Deallocate memory
				parking[i].ptr = nullptr;
				parking[i].occupied = false;
			}
		}
		delete[] parking; // Delete parking array
		parking = nullptr;
	}

	// 2. Reset parking system state
	totalslots = 0;
	parkedCount = 0;

	// 3. Reset undo stack
	stackTop = -1;
	for (int i = 0; i < 100; i++) {
		undoStack[i] = nullptr;
	}

	// 4. Reset queue
	if (waitQueue != nullptr) {
		for (int i = 0; i < queuesize; i++) {
			if (waitQueue[i] != nullptr) {
				delete waitQueue[i];
				waitQueue[i] = nullptr;
			}
		}
		delete[] waitQueue;
		waitQueue = nullptr;
	}
	queueFront = 0;
	queueRear = -1;
	savesystem();
	cout << "System has been successfully reset.\n";
}

// function to save the current system state to file
void parkingsystem::savesystem() {
	ofstream file("parking_data.txt");

	if (!file) {
		cout << "error saving parking data \n";
		return;
	}
	// save total number of parking slots
	file << totalslots << endl;

	//save all parked vehicles with their slot index 

	for (int i = 0; i < totalslots; i++) {
		if (parking[i].occupied && parking[i].ptr != nullptr) {
			file << i << " " << parking[i].ptr->gettype() << " " << parking[i].ptr->getlicense() << " " << parking[i].ptr->getentry() << endl;
		}
	}

	file.close();
	cout << "parking data saved\n";

}
void parkingsystem::loadsystem() {
	ifstream file("parking_data.txt");

	// Check if file couldn't be opened or is empty
	if (!file || file.peek() == EOF) {
		cout << "No saved parking data found. Using default settings.\n";
		return;
	}

	int slotid;
	string type, license, time;

	// Read total number of slots from file
	file >> totalslots;

	// Free previously allocated memory if any
	if (parking != nullptr) {
		delete[] parking;
	}

	// Allocate new array for parking slots
	parking = new parkingSlot[totalslots];

	// Initialize all slots as empty
	for (int i = 0; i < totalslots; i++) {
		parking[i].ptr = nullptr;
		parking[i].occupied = false;
	}

	parkedCount = 0; // Reset parked count before loading

	// Read vehicle data line by line
	while (file >> slotid >> type >> license >> ws && getline(file, time)) {
		vehicle* v = nullptr;

		// Create appropriate object based on vehicle type
		if (type == "Car") {
			v = new car(license, time, false);
		}
		else if (type == "Bike") {
			v = new bike(license, time, false);
		}
		else if (type == "Truck") {
			v = new truck(license, time, 5.0); // Assume dummy load capacity
		}

		// Place vehicle in correct slot if within valid range
		parking[slotid].ptr = v;
		parking[slotid].occupied = true;
		parkedCount++;

	}

	file.close(); // Always close the file when done
	cout << "Parking data loaded successfully.\n";
}

bool parkingsystem::isQueueEmpty() {
	// Check if the queue is empty based on the circular queue logic
	return queueFront == (queueRear + 1) % max_queue_size;
}


void parkingsystem::enqueue(vehicle* v) {

	// Check if the queue is full
	if ((queueRear + 1) % max_queue_size == queueFront && waitQueue[queueRear] != nullptr) {
		cout << "Queue is full. Cannot enqueue vehicle.\n";
		return;
	}
	// If queue is empty
	if (queueRear == -1 && queueFront == 0) {
		queueFront = queueRear = 0;
	}
	else {
		queueRear = (queueRear + 1) % queuesize;
	}
	waitQueue[queueRear] = v;
	cout << "Vehicle with plate [" << v->getlicense() << "] added to waiting queue.\n";


}

vehicle* parkingsystem::dequeue() {
	if (isQueueEmpty()) {
		cout << "Queue is empty. Cannot dequeue vehicle.\n";
		return nullptr;
	}

	vehicle* temp = waitQueue[queueFront];
	waitQueue[queueFront] = nullptr;  // Clear the slot after dequeuing

	// Only one element was in the queue
	if (queueFront == queueRear) {
		queueFront = 0;
		queueRear = -1;
	}
	else {
		queueFront = (queueFront + 1) % queuesize;
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

bool parkingsystem::isStackEmpty() {
	return undotop == -1;  // Check if the undo stack is empty
}

void parkingsystem::pushUndo(vehicle* v) {
	if (undotop < 99) {
		undotop++;  // Increment stack top
		undoStack[undotop] = v;  // Push vehicle onto the stack
		cout << "Action has been added to the undo stack.\n";
	}
	else {
		cout << "Undo stack is full.\n";
	}
}

vehicle* parkingsystem::popUndo() {
	if (!isStackEmpty()) {
		vehicle* v = undoStack[undotop--];  // Pop vehicle from the stack
		cout << "Undo operation successful.\n";
		return v;
	}
	cout << "Nothing to undo.\n";
	return nullptr;  // Return nullptr if no action to undo
}

void parkingsystem::undolastaction() {
	vehicle* v = popUndo();  // Pop the last action from the undo stack

	if (v != nullptr) {
		// If it was a removal, repark the vehicle in the first available slot
		bool reparked = false;
		for (int i = 0; i < totalslots; i++) {
			if (!parking[i].occupied) {
				parking[i].ptr = v;
				parking[i].occupied = true;
				parkedCount++;
				cout << "Vehicle reparked in slot " << i + 1 << endl;
				reparked = true;
				break;  // Exit loop once the vehicle is reparked
			}
		}

		if (!reparked) {
			cout << "No available slots to undo the removal.\n";
		}

		// Save the system state after re-parking the vehicle
		savesystem();  // Call savesystem to save the current state to the file
	}
	else {
		cout << "No action to undo.\n";
	}
}



void parkingsystem::Viewqueue() {
	cout << "\n===== Waiting Queue =====\n";
	if (isQueueEmpty()) {
		cout << "Queue is empty.\n";
		return;
	}
	for (int i = queueFront; i <= queueRear; ++i) {
		cout << "Queued Vehicle " << (i - queueFront + 1) << ": ";
		waitQueue[i]->displayinfo();
		cout << "---------------------\n";
	}
}
void parkingsystem::viewslots() {
	for (int i = 0; i < 100; i++) {
		if (parking[i].ptr == nullptr) {
			cout << "Slot " << i + 1 << " is available." << endl;
		}
		else {
			cout << "Slot " << i + 1 << " is occupied by "
				<< parking[i].ptr->getlicense() << " ("
				<< parking[i].ptr->gettype() << ")" << endl;
		}
	}
}