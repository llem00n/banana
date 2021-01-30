#include <iostream>
#include "banana/banana/banana.hpp"

int main()
{
	try {
		bnn::banana bn = bnn::array;
		std::cin >> bn;
		std::cout << bn << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}