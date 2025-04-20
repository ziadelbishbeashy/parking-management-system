#include "system.h"
#include <fstream>
#include <iostream>
using namespace std;


parkingsystem::parkingsystem(int cap) {
	parking = nullptr;
	totalslots = 0;
	parkedCount = 0;
	
	//queue initialization
	queueFront = 0;
	queueRear = -1;
	queuesize = 20;
	waitQueue = new vehicle * [queuesize];
	for (int i = 0; i < queuesize; i++) {
		waitQueue[i] = nullptr;
	}

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
			pushUndo(v); //add the parked vehicle to the stack
			savesystem();
			return true;
		}
	}
	
	cout << " no available slots! \n";
	enqueue(v);
	return false;
}
bool parkingsystem::removeVehicle(int slotid) {
	if (slotid < 1 || slotid > totalslots || !parking[slotid - 1].occupied) {
		cout << "Invalid or empty slot.\n";
		return false;
	}

	// Save pointer before deleting for undo functionality
	vehicle* removedVehicle = parking[slotid - 1].ptr;

	// Push the removed vehicle to the undo stack
	pushUndo(removedVehicle);

	// Clean up memory and update state
	delete parking[slotid - 1].ptr;
	parking[slotid - 1].ptr = nullptr;
	parking[slotid - 1].occupied = false;
	parkedCount--;

	cout << "Vehicle removed from slot " << slotid << endl;

	if (!isQueueEmpty()) {
		vehicle* next = dequeue();
		parking[slotid - 1].ptr = next;
		parking[slotid - 1].occupied = true;
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
	savesystem();
}
//
//void parkingsystem::viewslots() const {
//	cout << "\n--- Parking Slots Status ---\n";
//	for (int i = 0; i < capacity; ++i) {
//		cout << "Slot " << i + 1 << ": ";
//		if (parking[i] == nullptr) {
//			cout << "Empty\n";
//		}
//		else {
//			cout << "Occupied by vehicle with plate: " << parkingSlots[i]->getPlate() << "\n";
//		}
//	}
//	cout << "-----------------------------\n";
//}
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
		if ((queueRear + 1) % max_queue_size == queueFront && queueRear != -1) {
			cout << "Queue is full. Cannot enqueue vehicle.\n";
			return;
		}
		// If queue is empty
		if (queueRear == -1) {
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

bool parkingsystem::isStackEmpty() {
	return stackTop == -1; // the stack is empty
}

void parkingsystem::pushUndo(vehicle* v) {
	if (stackTop < 99) {
		undoStack[++stackTop] = v;  // Push vehicle onto the stack
		cout << "Action has been added to the undo stack.\n";
	}
	else {
		cout << "Undo stack is full.\n";
	}
}

vehicle* parkingsystem::popUndo() {
	if (!isStackEmpty()) {
		vehicle* v = undoStack[stackTop--];  // Pop vehicle from the stack
		cout << "Undo operation successful.\n";
		return v;
	}
	cout << "Nothing to undo.\n";
	return nullptr;  // Return nullptr if no action to undo
}
void parkingsystem::undolastaction() {
	vehicle* v = popUndo();
	if (v != nullptr) {
		//if it was a removal , repark the vehicle in the first available slot 
		for (int i = 0; i < totalslots; i++) {
			if (!parking[i].occupied) {
				parking[i].ptr = v;
				parking[i].occupied = true;
				parkedCount++;
				cout << "vehicle reparked in slot " << i + 1 << endl;
				return;
			}
		}
		cout << "no available slots to undo the removal \n";
	}
	savesystem();
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
