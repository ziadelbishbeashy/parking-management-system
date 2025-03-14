#ifndef vehicle_h
#define vehicle_h
#include <iostream>
#include <string>
using namespace std;
class vehicle
{
protected :
	string license;
	string entrytime;
	string vehicletype;
public :
	vehicle(string plate, string time, string type);
	virtual ~vehicle();
	string getlicense();
	string getentry();
	string gettype();

	void setentry(string time);
	virtual double calculatefees(double hours) const;

	virtual void displayinfo() const;

};
class car : public vehicle {
private :
	bool iselectric;
public :
	car(string plate, string time, bool electric);
	double calculatefees(double hours) const override;
	void displaycarinfo()const;
	double operator*(double hours) const;
};

class bike : public vehicle {
private:
	bool biketype;
public:
	bike(string plate, string time, bool biketype);
	double calculatefees(double hours) const override;
	bool isbicycle()const;
	double operator*(double hours) const;

};
class truck : public vehicle {
private :
	double loadcapacity;
public :
	truck(string plate, string time, double load);
	double calculatefees(double hours)const override;
	void displaytruckinfo()const;
	double operator*(double hours)const;
};
#endif 
