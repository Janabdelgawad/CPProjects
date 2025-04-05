#include "UserInterface.h"

int main() {
	UserInterface ui("user.txt");
	ui.showMainMenu();
	return 0;
}

/*
Add more features: Like password reset, user profiles, or different user roles.
Explore databases: SQLite would be a good next step for storing user data more securely.
Learn about file locking: For handling multiple users accessing the file simultaneously.
*/