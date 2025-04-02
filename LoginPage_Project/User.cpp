#include "User.h"
#include <functional>

//constructor implementation
User::User(const std::string& username, const std::string& rawPassword) {
	this->username = username;
	this->hashedPassword = hashPassword(rawPassword);
}
User::User(const std::string& username, const std::string& hashedPassword, bool alreadyHashed) {
	this->username = username;
	this->hashedPassword = alreadyHashed ? hashedPassword : hashPassword(hashedPassword);
}
//methods implementation
std::string User::getUsername() const {
	return username;
}
bool User::validatePassword(const std::string& passwordToCheck) const {
	std::string hashedInput = hashPassword(passwordToCheck);
	return hashedInput == hashedPassword;
}
std::string User::toString() const {
	return username + ' ' + hashedPassword;
}
//static methods
std::string User::hashPassword(const std::string& password) {
	//not secure for production
	std::hash<std::string> hasher;
	size_t hashValue = hasher(password);
	return std::to_string(hashValue);
}