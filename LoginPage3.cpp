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
	std::cin >> input;
	return input;
}

void registerUser() {
	std::string username{ getInput("Enter Username: ") };
	std::string password{ getInput("\nEnter Password: ") };
	std::string hashedPassword{ hashPassword(password) };
	//open file in append mode so new users wouldnt overwrite existing ones
	std::ofstream file("user.txt", std::ios::app);

	if (file.is_open()) {
		file << username << " " << hashedPassword << '\n';
		file.close();
		std::cout << "User registered successfully!\n";
	}
	else {
		std::cout << "Error: Couldn't open the file.\n";
	}
}

bool logUser(const std::string& username, const std::string& password) {
	std::ifstream file("user.txt");
	std::string storedUsername, storedHashedPassword;

	if (!file.is_open()) {
		std::cout << "Error: Could not open file.\n";
		return false;
	}
	std::string hashedPassword{ hashPassword(password) }; //hash entered password
	while (file >> storedUsername >> storedHashedPassword) {
		if (storedUsername == username && storedHashedPassword == hashedPassword) {
			file.close();
			return true;
		}

	}
	file.close();
	return false;
}

void handleLogin() {
	std::string username{ getInput("Enter Username: ") };
	std::string password{ getInput("\nEnter Password: ") };

	if (logUser(username, password)) { std::cout << "Login successful! Welcome, " << username << "!\n"; }
	else { std::cout << "Invalid username or password. Try again.\n"; }
}

void showMenu() {
	int choice;
	std::string username, password;

	while (true) {
		std::cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
		std::cin >> choice;

		if (choice == 1) { registerUser(); }
		else if (choice == 2) { handleLogin(); }
		else if (choice == 3) { std::cout << "Exiting program...\n"; break; }
		else { std::cout << "Invalid choice. please enter 1,2, or 3.\n"; }
	}
}


int main() {
	showMenu();
	return 0;
}