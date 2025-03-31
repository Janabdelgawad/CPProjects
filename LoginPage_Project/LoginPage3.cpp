#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <unordered_map>
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
	if (!file.is_open()) {
		std::cout << "Error: Could not open file.\n";
		return false;
	}


	std::unordered_map<std::string ,std::string> storedData;
	std::string line, storedUsername, storedHashedPassword;
	std::string hashedPassword{ hashPassword(password) }; //hash entered password

	//read file and store data in the map
	while (std::getline(file, line)) {
		size_t separator{ line.find(' ') };
		if (separator != std::string::npos) {
			storedUsername = line.substr(0, separator);
			storedHashedPassword = line.substr(separator + 1);
			storedData[storedUsername] = storedHashedPassword;
		}
	}
	file.close();

	if (storedData.find(username) != storedData.end() && storedData[username] == hashedPassword) { return true; }

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
/*
4. Error Handling
What happens if users.txt doesn’t exist yet?

What if the file gets corrupted?

How does your code behave when given unexpected inputs (e.g., spaces in usernames)?

5. Edge Cases
What happens if a user enters an empty username or password?

Can two users register with the same username? If so, is that intended?

What happens if the file contains incorrectly formatted data?*/
