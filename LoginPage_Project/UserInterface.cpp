#include "UserInterface.h"
#include <iostream>

//constructor implementation
UserInterface::UserInterface(const std::string& usersFile)
	: authManager(usersFile) {};

//main methods implementation
void UserInterface::showMainMenu() {
	int choice;
	std::string input;

	while (true) {
		std::cout << "\n===== User Authentication System =====\n";
		std::cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option (1-3): ";
		std::getline(std::cin, input);

		try {
			choice = std::stoi(input);
		}
		catch (const std::exception&) {
			std::cout << "Please enter a number.\n";
			continue;
		}

		switch (choice) {
		case 1: handleRegisteration(); break;
		case 2: handleLogin();         break;
		case 3: displayMessage("Exiting program..."); return;
		default:displayMessage("Invalid choice. Please enter 1, 2, or 3.\n");
		}
	}
}

void UserInterface::handleRegisteration() {
	std::string username, password;
	bool registerationSuccessful = false;

	do {
		username = getInput("Enter Username: ");
		if (!authManager.isUsernameValid(username)) {
			displayMessage("Username must be at least 8 characters and contain only letters, numbers, and underscores.");
			continue;
		}
		if (authManager.userExists(username)) {
			displayMessage("Username already exists. Please choose another.");
			continue;
		}
		password = getInput("Enter Password: ");
		if (!authManager.isPasswordValid(password)) {
			displayMessage("Password must be at least 8 characters long.");
			continue;
		}

		registerationSuccessful = authManager.registerUser(username, password);

		if(registerationSuccessful) { displayMessage("User registered successfully!"); }
		else { displayMessage("Registration failed. Please try again."); }
		
	} while (!registerationSuccessful);
}

void UserInterface::handleLogin() {
	std::string username = getInput("Enter username: ");
	std::string password = getInput("Enter password: ");

	if (authManager.loginUser(username, password)) {
		displayMessage("Login successful! Welcome, " + username + "!");
	} else {
		displayMessage("Invalid username or password. Please try again.");
	}
}

//helper methods
std::string UserInterface::getInput(const std::string& prompt) {
	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);
	return input;
}

void UserInterface::displayMessage(const std::string& message) {
	std::cout << message << std::endl;
}