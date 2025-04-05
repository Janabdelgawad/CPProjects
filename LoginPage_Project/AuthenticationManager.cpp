#include "AuthenticationManager.h"
#include <iostream>
#include <regex>
#include "FileStorage.h"

//constructor/destructor implementation
AuthenticationManager::AuthenticationManager(const std::string& filePath)
	:fileStorage(filePath), loggedInUser(nullptr){}

AuthenticationManager::~AuthenticationManager() {
	if (loggedInUser) {
		delete loggedInUser;
		loggedInUser = nullptr;
	}
}

//validation implementation
bool AuthenticationManager::isUsernameValid(const std::string& username) const {
	std::regex usernamePattern("^[a-zA-z0-9_]{8,}$");
	return std::regex_match(username, usernamePattern);
}

bool AuthenticationManager::isPasswordValid(const std::string& password) const {
	std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-z])(?=.*\\d)(?=.*[@#$%^&+=!]).{8,15}$");
	return std::regex_match(password, passwordPattern);
}

bool AuthenticationManager::userExists(const std::string& username) const {
	return fileStorage.userExists(username);
}

//registeration and login methods implementation
bool AuthenticationManager::registerUser(const std::string& username, const std::string& password) {
	if (!isUsernameValid(username)) {
		return false;
	}
	if (!isPasswordValid(password)) {
		return false;
	}
	if (fileStorage.userExists(username)) {
		return false;
	}
	User newUser(username, password);
	fileStorage.saveUser(newUser);
	return true;
}

bool AuthenticationManager::loginUser(const std::string& username, const std::string& password) {
	std::vector<User> users = fileStorage.loadAllUsers();

	for (const User& user : users) {
		if (user.getUsername() == username && user.validatePassword(password)) {
			loggedInUser = new User(username, user.toString(), true);
			return true;
		}
	}
	return false;
}

//no logout option yet
void AuthenticationManager::logoutUser() {
	if (loggedInUser != nullptr) {
		delete loggedInUser;
		loggedInUser = nullptr;
		std::cout << "You have logged out successfully.\n";
	} else {
		std::cerr << "Error: No user is currently logged in.\n";
	}
}

//getter method
//bool AuthenticationManager::isUserLoggedin();