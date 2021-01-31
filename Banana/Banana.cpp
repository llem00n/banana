#include <iostream>
#include "banana/banana/banana.hpp"

int main()
{
	bnn::banana bn = bnn::banana::parse("5.5b");
	std::cout << bn << '\n';
}