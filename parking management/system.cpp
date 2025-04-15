#include "system.h"
#include <iostream>
using namespace std;

system::system() {
	parking = nullptr;
	totalslots = 0;
	parkedCount = 0;
}
system::~system() {

}
void system::initialize(int slots) {
	totalslots = slots;
	parking = new parkingSlot[totalslots];
	for (int i = 0; i < totalslots; i++) {
		parking[i].ptr = nullptr;
		parking[i].occupied = false;
	}
}

bool system::parkVehicle(vehicle* v) {
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
bool system::removeVehicle(int slotid) {
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

void system::viewAll() {
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
	if (!found) {
		cout << "No vehicles parked currently.\n";
	}
}
void system::reset() {

}