#pragma once
#include <string>
#include "User.h"
#include <vector>
#include <fstream>

class FileStorage {
private:
	std::string filename{};
public:
	//constructor
	FileStorage(const std::string& filePath);
	//methods
	void saveUser(const User& user);
	std::vector<User> loadAllUsers()const;
	bool userExists(const std::string& username) const;
	void initialize() const;
};