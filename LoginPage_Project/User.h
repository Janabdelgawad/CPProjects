#pragma once
#include <string>

class User {
private:
	std::string username{};
	std::string hashedPassword{};
public:
	//constructors
	User(const std::string& username, const std::string& rawPassword);
	User(const std::string& username, const std::string& hashedPassword, bool alreadyHashed);
	//methods
	std::string getUsername() const;
	bool validatePassword(const std::string& passwordToCheck) const;
	std::string toString() const;
	//static methods
	static std::string hashPassword(const std::string& password);
};
