#ifndef USER_H
#define USER_H
#include "system.h"
#include<string>
using namespace std;

class User {
private:
    string username;
    string password;

public:
    User();
    User(string uname, string pwd);
    string getUsername() const;
    string getPassword() const;
    void setUsername(string name);
    void setPassword(string pass);
};

bool createUseraccount();
bool loginUser(string& loggedinusername);
void usermenu(parkingsystem& parking);
#endif
