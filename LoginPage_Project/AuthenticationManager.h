#pragma once
#include "User.h"
#include "fileStorage.h"

class AuthenticationManager {
private:
	FileStorage fileStorage;//manages file operations
	User* loggedInUser; //pointer to store logged-in user
public:
	//constructor
	AuthenticationManager(const std::string& filepath);
	~AuthenticationManager();
	//registeration and login methods
	bool registerUser(const std::string& username, const std::string& password);
	bool loginUser(const std::string& username, const std::string& password);
	void logoutUser();

	//validation methods
	bool isUsernameValid(const std::string& username) const;
	bool isPasswordValid(const std::string& password) const;

	//getter method
	//bool isUserLoggedin(); USE IT IN THE UI TO DISPLAY CHANGES and PREVENT UNAUTHORIZED ACTION (ONLY LOGGED IN USERS CAN DO STH)
};
