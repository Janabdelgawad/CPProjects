#include <iostream>
#include <array>

int main()
{
	constexpr std::array<char, 5> hello{ 'h', 'e', 'l', 'l', 'o' };
	std::cout << "The length is: " << std::size(hello) << '\n';
	std::cout << hello[1] << hello.at(1) << std::get<1>(hello) << '\n';
	return 0;
}