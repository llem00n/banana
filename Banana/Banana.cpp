#include <iostream>
#include <fstream>
#include <string>

#include "banana.hpp"

int main()
{
	bnn::banana bn = bnn::banana::parse(std::ifstream("file.test"));
	std::cout << bn.to_string() << '\n';
	
	return 0;
}