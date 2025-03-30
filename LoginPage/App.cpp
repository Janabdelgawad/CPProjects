#include "app.h"
#include <iostream>

int app(int x, int y) {
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;

	std::cout << "Enter another number: ";
	int y{};
	std::cin >> y;

	return x + y;
}
