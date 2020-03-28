#include "password_class.h"
#include <Vector>
#include <sstream>
#include <algorithm>

/* interface.cpp is the central hub of the program. Manages user interface,
   and all other external files are utilized here. */
// FORMAT: <password name> <username> <password>

int main() {
	vector<Password> passwordLibrary; // holds passwords for duration of program 

	/* - Read passwords from passwords.txt
	   - Loop through each line 
	   - Use stringstream to separate the variables each line, 
	     and add them to a new Password object */
	fstream file;
	file.open("passwords.txt");
	
	string name, username, passcode;
	if (!file) { cout << "ERROR: Can't Open File" << endl; return -1; } 
	
	string line;
	while (getline(file, line)) {
		/* If there are passwords in file, the while loop will execute */
		stringstream splitter(line);
		splitter >> name >> username >> passcode;
		passwordLibrary.push_back(Password(passcode, name, username));
	}

	file.close(); // done reading 


	/* THE INTERFACE LOOP */
	while (true) {
		cout << "Welcome to SimeonTG's Password Manager!" << endl;
		cout << "Type ADD to add a password." << endl;
		cout << "Type EDIT to edit a password." << endl;
		cout << "Type CLEAR to clear your password library." << endl;
		cout << "Type VIEW to view your password library." << endl;
		cout << "Type PASSWORD to set up as password for the password manager." << "\n\n" << endl;
		cout << "Be sure to type EXIT before leaving in order " << endl;
		cout << "to make sure that your passwords are saved." << endl;
		cout << "---------------------------------------" << endl;

		string user_input;
		cin >> user_input;
		// transform makes user_input all uppercase
		transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper); 
		cout << endl; // for formatting

		if (user_input == "EXIT") { 
			/* Before exiting, computer puts information of each password object 
			onto each line of password.txt */

			// Clear passwords.txt if passwordLibrary is empty 
			if (passwordLibrary.size() == 0) {
				file.open("passwords.txt", ios::out | ios::trunc);
				file.close();				
				return 0;
			}

			file.open("passwords.txt");
			if (file.is_open()) {
				for (int i = 0; i < passwordLibrary.size(); i++) {
					string tempName = passwordLibrary[i].get_name();
					string tempUserName = passwordLibrary[i].get_username();
					string tempPassword = passwordLibrary[i].get_password();

					file << tempName << " " << tempUserName << " " << tempPassword << endl;
				}
			}
			file.close();
			return 0; 
		}

		else if (user_input == "ADD") {
			string name, username, passcode;
			bool same = true;

			// A while loop to check if password name is the same as another password 
			while (same == true) {
				same = false;
				cout << "Enter password name: "; cin >> name;

				for (int i = 0; i < passwordLibrary.size(); i++) {
					if (name == passwordLibrary[i].get_name()) {
						same = true;
						cout << "Another password of the same name has been found." << endl;
						cout << "Please enter aother password name." << endl;
						break;
					}
				}
			}

			cout << "Enter username: "; cin >> username;
			cout << "Enter password: "; cin >> passcode;

			// Append a new Password object into passwordLibrary 
			passwordLibrary.push_back(Password(passcode, name, username));
			bufferNoPrint();
			buffer();
		}

		else if (user_input == "VIEW") {
			cout << "The size of your password library is " << passwordLibrary.size() << ". \n\n";
			// Display password library using iterators 
			vector<Password>::iterator it;
			for (it = passwordLibrary.begin(); it != passwordLibrary.end(); it++) {
				cout << *it << endl;
			}
			bufferNoPrint();
			buffer();
		}

		else if (user_input == "CLEAR") {
			cout << "Are you sure you want to CLEAR your password library? This can't be undone. " << endl;
			cout << "Type YES or NO." << endl;
			
			string user_input;
			cin >> user_input;
			transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper);

			if (user_input == "YES") {
				passwordLibrary.clear();
				cout << "Your password library has been deleted. " << endl;
				bufferNoPrint();
			}
			else if (user_input == "NO") {
				cout << "Your password library has not been deleted. " << endl;
				bufferNoPrint();
			}
			else {
				cout << "ERROR: invalid input. " << endl;
			}
			buffer();
		}

		else if (user_input == "EDIT") {
			cout << "Type the name of the password that you want to edit. \n\n";
			string passwordName; 
			cin >> passwordName;

			// Find password_name in passwordLibrary
			bool found = false;
			Password *pPassword = NULL; // Holds the address of the password we want to change 
			for (int i = 0; i < passwordLibrary.size(); i++) {
				if (passwordName == passwordLibrary[i].get_name()) {
					found = true;
					pPassword = &passwordLibrary[i];
					cout << "\nHere is information about the password: \n\n";
					cout << *pPassword << "\n\n";
				}
			}
			
			if (found == true){
				cout << "What do you want to change?" << endl;
				cout << "Enter NAME to change the name of the password. " << endl;
				cout << "Enter USERNAME to change the username of the password." << endl;
				cout << "Enter PASSWORD to change the actual password itself. \n\n";
				string whatToChange;
				cin >> whatToChange;
				transform(whatToChange.begin(), whatToChange.end(), whatToChange.begin(), ::toupper);

				if (whatToChange == "NAME") {
					cout << "Please enter the new NAME for the password: ";
					string changeName;
					cin >> changeName;
					pPassword->set_name(changeName);

				}
				else if (whatToChange == "USERNAME") {
					cout << "Please enter the new USERNAME for the password: ";
					string changeUserName;
					cin >> changeUserName;
					pPassword->set_username(changeUserName);

				}
				else if (whatToChange == "PASSWORD") {
					cout << "Please enter the new PASSWORD: ";
					string changePassword;
					cin >> changePassword;
					pPassword->set_password(changePassword);
				}
				else {
					cout << "Sorry. I didn't understand the input you typed. " << endl;
				}

			}
			else {
				cout << "Sorry.\n A password with that password name cannot be found." << endl;
			}
			pPassword = NULL;
			delete pPassword;
			bufferNoPrint(); buffer();
		}
		
		else { cout << "Please enter valid input." << endl; bufferNoPrint(); buffer(); }

		system("CLS");
	}
}