#ifndef vehicle_h
#define vehicle_h
#include <iostream>
#include <string>
using namespace std;
class vehicle //parent class
{
protected :
	string license;
	string entrytime;
	string vehicletype;
	int parkingid;
	string status;
public :
	static int idcounter;
	vehicle();
	vehicle(string plate, string time, string type);
	virtual ~vehicle();
	string getlicense();
	string getentry();
	string gettype();
	int getparkingid();
	void setlicense(string p);
	virtual void input() = 0;
	void exitparking();
	void setentry(string time);
	virtual double calculatefees(double hours) const;

	virtual void displayinfo() const;

};
class car : public vehicle { // car inherited
private :
	bool iselectric;
public :
	void input() override;
	car(string plate, string time, bool electric);
	double calculatefees(double hours) const override;
	void displaycarinfo()const;
	double operator*(double hours) const;
};

class bike : public vehicle { //bike inherited   
private:
	bool biketype;
public:
	void input() override;
	bike(string plate, string time, bool biketype);
	double calculatefees(double hours) const override;
	bool isbicycle()const;
	double operator*(double hours) const;

};
class truck : public vehicle { //truck inherited
private :
	double loadcapacity;
public :
	void input() override;
	truck(string plate, string time, double load);
	double calculatefees(double hours)const override;
	void displaytruckinfo()const;
	double operator*(double hours)const;
};
#endif 
