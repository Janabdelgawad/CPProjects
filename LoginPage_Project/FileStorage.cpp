#include "FileStorage.h"
#include <fstream>
#include <sstream>
#include <iostream>

//constructor implementation
FileStorage::FileStorage(const std::string& filePath) {
	filename = filePath;
	initialize();
}

//methods implementation
void FileStorage::initialize() const {
	std::ifstream file(filename);
	if (!file) {std::ofstream newFile(filename);}
}

void FileStorage::saveUser(const User& user) {
	std::ofstream file(filename, std::ios::app);
	if (!file) {
		std::cerr << "Error: Unable to open file for writing.\n";
		return;
	}
	file << user.toString() << '\n';
	file.close();
}

std::vector<User> FileStorage::loadAllUsers()const {
	std::vector<User> users;
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Error: Unable to open file for reading.\n";
		return users;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string username, hashedPassword;

		if (iss >> username >> hashedPassword) { users.emplace_back(username, hashedPassword, true); }
	}
	file.close();
	return users;
}

bool FileStorage::userExists(const std::string& username) const {
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Error: Unable to open file for checking user existence.\n";
		return false;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string storedUsername, storedHashedPassword;

		if (iss >> storedUsername >> storedHashedPassword) { 
			if (storedUsername == username) { return true; }
		}
	}
	return false;
}