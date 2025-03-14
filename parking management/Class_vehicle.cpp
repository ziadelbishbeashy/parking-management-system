#include "Class_vehicle.h"

vehicle::vehicle(string plate, string time, string type) {
	license = plate;
	entrytime = time;
	vehicletype = type;
}
vehicle :: ~vehicle() {

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
void vehicle::displayinfo()const {
	cout << "vehicle type :" << vehicletype << endl;
	cout << "license plate :" << license << endl;
	cout << "entry time :" << entrytime << endl;

}


car::car(string plate, string time, bool electric)
	: vehicle(plate, time, "Car"), iselectric(electric) {
}
double car::calculatefees(double hours)const {
	double fee = hours * 15;
	if (iselectric) {
		fee *= 0.8; 
	}
	return fee;
}
void car::displaycarinfo() const {
	cout << "Car Type: " << vehicletype << endl;
	cout << "License Plate: " << license << endl;
	cout << "Electric: " << (iselectric ? "Yes" : "No") << endl;
}

bike::bike(string plate, string time, bool type) 
	: vehicle(plate, time, "Bike"){
	bool biketype = false;
}


bool bike::isbicycle()const {
	return biketype == true;
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
}
