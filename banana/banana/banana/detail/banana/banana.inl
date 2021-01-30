/*
bnn::banana& bnn::banana::operator+()
{
	return *this;
}

bnn::banana& bnn::banana::operator+(const bnn::banana& rhs)
{
	std::vector<banana> vec = rhs;
	for (banana& bn : vec)
		this->push_back(bn);
	return *this;
}

bnn::banana& bnn::banana::operator+=(const bnn::banana& rhs)
{
	std::vector<banana> vec = rhs;
	for (banana& bn : vec)
		this->push_back(bn);
	return *this;
}

*/