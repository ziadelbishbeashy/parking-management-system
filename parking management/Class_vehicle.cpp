#include "Class_vehicle.h"
#include <iostream>
vehicle::vehicle() {
	license = "UNKNOWN";
	entrytime = "00:00";
	vehicletype = "Unknown";
	status = "parked";
	parkingid = ++idcounter;

}
vehicle::vehicle(string plate, string time, string type) {
	license = plate;
	entrytime = time;
	vehicletype = type;
	status = "parked";
}
vehicle :: ~vehicle() {

}
int vehicle::idcounter = 0;  // Static member definition and initialization


int vehicle::getparkingid() {
return parkingid;
}	
void vehicle::exitparking() {
	status = "Exited";
}
string vehicle::getlicense() {
	return license;
}
string vehicle::getentry() {
	return entrytime;
}
string vehicle::gettype() {
	return vehicletype;
}
void vehicle::setentry(string time) {
	entrytime = time;
}
double vehicle::calculatefees(double hoursparked)const {
	return hoursparked * 10.0;
}

void vehicle::displayinfo() const {
	cout << "Vehicle Type: " << vehicletype << endl;
	cout << "License Plate: " << license << endl;
	cout << "Entry Time: " << entrytime << endl;
	cout << "Parking ID: " << parkingid << endl;
	
}


car::car(string plate, string time, bool electric)
	: vehicle(plate, time, "Car"), iselectric(electric) {
	parkingid = ++idcounter;
}
double car::operator*(double hours) const {
	return calculatefees(hours);
}
double car::calculatefees(double hours)const {
	double fee =hours * 15;
	if (iselectric) {
		fee *= 0.8; 
	}
	return fee;
}
void car::displaycarinfo() const {
	displayinfo();
	cout << "Electric: " << (iselectric ? "Yes" : "No") << endl;
}

bike::bike(string plate, string time, bool type) 
	: vehicle(plate, time, "Bike"),biketype(type){
	parkingid = ++idcounter;
	 
}


bool bike::isbicycle()const {
	return biketype == true;
}
double bike::operator*(double hours) const {
	return calculatefees(hours);
}
double bike::calculatefees(double hours)const {
	double fee = hours * 8;
	if (biketype == true) {
		fee *= 0.5;
			}
	return fee;
}
truck::truck(string plate, string time, double load) : vehicle(plate, time, "truck") {
	loadcapacity = load;
	parkingid = ++idcounter;
}
double truck::operator*(double hours) const {
	return calculatefees(hours);
}
double truck::calculatefees(double hours)const {
	return hours * 20 + (loadcapacity * 0.05);
}
void truck::displaytruckinfo()const {
	displayinfo();
	cout << "load capacity :" << loadcapacity << "Kg" << endl;
}
