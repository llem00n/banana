#include <iostream>
#include <fstream>

#include "banana.hpp"

int main()
{
	bnn::banana bn = bnn::banana::parse(std::ifstream("test.txt"));

	std::cout << bn.to_string() << '\n';
}