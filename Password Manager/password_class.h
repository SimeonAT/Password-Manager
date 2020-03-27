#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Contains definitions and implementations for the password class. */
class Password {
public:
	Password(string passcode, string password_name = "none", string username = "none"){
		this->passcode = passcode;
		this->password_name = password_name;
		this->username = username;
	}
	~Password() {}
	friend ostream& operator << (ostream& cout, const Password& pass); 

	// Setters 
	void set_name(string name) { this->password_name = name; };
	void set_username(string username) { this->username = username;  };
	void set_password(string passcode) { this->passcode = passcode; };

	// Getters 
	string get_name() { return this->password_name; }
	string get_username() { return this->username; }
	string get_password() { return this->passcode; }

private:
	string password_name; // name of password / what it's used for 
	string username; // username to enter with password (if there is any)
	string passcode; // the actual password
};

ostream& operator << (ostream& out, const Password& pass) {
	/*Overloaded "<<" to properly show data of the Password class */
	out << "Name of password: " << pass.password_name << endl;
	out << "Username: " << pass.username << endl;
	out << "Password: " << pass.passcode << endl;

	return out; 
}


void buffer() {
	/* User reads info, presses ENTER key before console clears screen. */
	cout << "Press ENTER to continue. " << endl;
	string buffer;
	getline(cin, buffer);
}

void bufferNoPrint() {
	/* User reads info, presses ENTER key before console clears screen.
	The only difference between buffer() is that it doesn't have cout statement. */
	string buffer;
	getline(cin, buffer);
}