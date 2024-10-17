#include <iostream>
#include <vector>
template<typename T>
void printElement(const std::vector<T>& v, int index)
{
    if (index < 0 || index >= static_cast<int>(v.size())) std::cout << "Invalid index\n";
    else std::cout << "The element has value " << v[static_cast<std::size_t>(index)] << '\n';
}
int main()
{
    std::vector v1{ 0, 1, 2, 3, 4 };
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v2{ 1.1, 2.2, 3.3 };
    printElement(v2, 0);
    printElement(v2, -1);

    return 0;
}