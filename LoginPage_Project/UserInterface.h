#pragma once
#include "AuthenticationManager.h"
#include <string>
#include "FileStorage.h"
class UserInterface {
private:
	AuthenticationManager authManager;
	//helper methods
	std::string getInput(const std::string& prompt);
	void displayMessage(const std::string& message);
public:
	//constructor
	UserInterface(const std::string& usersFile = "user.txt");
	//Main methods
	void showMainMenu();
	void handleRegisteration();
	void handleLogin();


};