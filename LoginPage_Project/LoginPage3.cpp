#include <iostream>
#include <string>
#include <fstream>
#include <functional>

std::string hashPassword(const std::string& password) {
	std::hash<std::string> hasher;
	return std::to_string(hasher(password));
}

std::string getInput(const std::string& prompt) {
	std::cout << prompt;
	std::string input;
	std::cin.clear();
	std::getline(std::cin, input);
	return input;
}

bool isValidUsername(const std::string& username) {
	if (username.length() < 3) {
		std::cout << "Username must be at least 3 characters long.\n";
		return false;
	}
	for (char c : username) {
		if (!isalnum(c) && c != '_') {
			std::cout << "Username can only contain letters, numbers, and underscores.\n";
			return false;
		}
	}
	return true;
}

bool isValidPassword(std::string& password) {
	if (password.length() < 6) {
		std::cout << "Password must be at least 6 characters long.\n";
		return false;
	}
	return true;
}

bool userExists(const std::string& username) {
	std::ifstream file("user.txt");
	if (!file.is_open()) {
		return false;
	}

	std::string storedUsername, storedHashedPassword;
	while (file >> storedUsername >> storedHashedPassword) {
		if (storedUsername == username) {
			file.close();
			return true;
		}
	}
	
	file.close();
	return false;
}

void registerUser() {
	std::string username, password;
	do {
		username = getInput("Enter Username: ");
	} while (!isValidUsername(username));

	if(userExists(username)){
		std::cout << "Username already exists.Please choose another.\n";
		return;
	}

	do {
		password = getInput("Enter Password: ");
	} while (!isValidPassword(password));

	std::string hashedPassword{ hashPassword(password) };
	std::ofstream file("user.txt", std::ios::app);
	if (file.is_open()) {
		file << username << ' ' << hashedPassword << '\n';
		file.close();
		std::cout << "User registered successfully!\n";
	}
	else {
		std::cout << "Error: Couldn't open the users file.\n";
	}

}


bool loginUser() {
	std::string username = getInput("Enter Username: ");
	std::string password = getInput("Enter Password: ");
	std::string hashedPassword{ hashPassword(password) };

	std::ifstream file("user.txt");
	if (!file.is_open()) {
		std::cout << "No users registered yet.\n";
		return false;
	}

	std::string storedUsername, storedHashedPassword;
	while (file >> storedUsername >> storedHashedPassword) {
		if (storedUsername == username && storedHashedPassword == hashedPassword) {
			file.close();
			std::cout << "Login successful! Welcome, " << username << "!\n";
			return true;
		}

	}
	file.close();
	std::cout << "Invalid username or password.Try again.\n";
	return false;
}

bool intializeSystem() {
	std::ifstream checkFile("user.txt");
	if (!checkFile.is_open()) {
		std::ofstream createFile("user.txt");
		if (!createFile.is_open()) {
			std::cout << "Error: Could not create users file.\n";
			return false;
		}
		createFile.close();
		std::cout << "New user database created.\n";
	}
	else {
		checkFile.close();
	}
	return true;
}

void showMenu() {
	if (!intializeSystem) {
		std::cout << "System initialization failed.\n";
		return;
	}

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
		case 1: registerUser(); break;
		case 2: loginUser(); break;
		case 3: std::cout << "Exiting program..\n"; return;
		default: std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
		}
	}
}


int main() {
	showMenu();
	return 0;
}
/*
Next Steps for Further Learning:

Learn about proper cryptographic libraries: Research bcrypt, Argon2, or scrypt for proper password hashing.
Explore databases: SQLite would be a good next step for storing user data more securely.
Add more features: Like password reset, user profiles, or different user roles.
Learn about file locking: For handling multiple users accessing the file simultaneously.
Study object-oriented programming: Consider refactoring this into classes for User, Authentication, etc.
*/