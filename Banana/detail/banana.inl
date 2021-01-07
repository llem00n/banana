bnn::banana::banana()
	: type(banana::Type::None)
{}

bnn::banana::banana(const bnn::banana& bn)
	: type(bn.get_type())
	, data(bn.data)
{}

bnn::banana::banana(const int& i)
	: type(banana::Type::Integer)
	, data(i)
{}

bnn::banana::banana(const double& d)
	: type(banana::Type::Double)
	, data(d)
{}

bnn::banana::banana(const bool& b)
	: type(banana::Type::Boolean)
	, data(b)
{}

bnn::banana::banana(const std::string& s)
	: type(banana::Type::String)
	, data(s)
{}

bnn::banana::banana(const char* s)
	: type(banana::Type::String)
	, data(s)
{}

bnn::banana::banana(const std::vector<banana>& v)
	: type(banana::Type::Array)
	, data(v)
{}

bnn::banana::banana(const std::initializer_list<banana>& l)
	: type(banana::Type::Array)
	, data(l)
{}

void bnn::banana::set_type(bnn::banana::Type t)
{
	if (get_type() & t) return;

	type = t;

	if (get_type() & banana::Type::String)
	{
		data.v.clear();
	}
	else if (get_type() & banana::Type::Array)
	{
		data.s.clear();
	}
	else
	{
		data.s.clear();
		data.v.clear();
	}
}

inline bnn::banana::Type bnn::banana::get_type() const
{
	return type;
}

void bnn::banana::push_back(const bnn::banana& bn)
{
	if ((get_type() & banana::Type::Array) || (get_type() & banana::Type::None))
	{
		if (get_type() & banana::Type::None)
			set_type(banana::Type::Array);
		
	}
	else
	{
		banana temp_bn = *this;
		set_type(banana::Type::Array);
		*this = { temp_bn };
	}
	data.v.push_back(bn);
}

std::size_t bnn::banana::size() const
{
	if (get_type() & banana::Type::Array)
		return data.v.size();
	else
		return 1;
}

bnn::banana& bnn::banana::operator=(const bnn::banana& rhs)
{
	set_type(rhs.get_type());
	data = rhs.data;
	return *this;
}

bnn::banana& bnn::banana::operator=(const int& rhs)
{
	set_type(banana::Type::Integer);
	data.i = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const double& rhs)
{
	set_type(banana::Type::Double);
	data.d = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bool& rhs)
{
	set_type(banana::Type::Boolean);
	data.b = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const std::string& rhs)
{
	set_type(banana::Type::String);
	data.s = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const char* rhs)
{
	set_type(banana::Type::String);
	data.s = std::string(rhs);
	return *this;
}

bnn::banana& bnn::banana::operator=(const std::vector<banana>& rhs)
{
	set_type(banana::Type::Array);
	data.v = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const std::initializer_list<banana>& rhs)
{
	set_type(banana::Type::Array);
	data.v = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator[](const int& i)
{
	if (get_type() & banana::Type::Array)
		return data.v[i];
	else
	{
		std::cerr << "\"bnn::banana::operator[](int)\" error: the object is not an array\n";
		throw std::runtime_error("\"bnn::banana::operator[](int)\" error: the object is not an array\n");
	}
}

bnn::banana& bnn::banana::operator[](const std::string& key)
{
	if (get_type() == banana::Type::Array)
	{
		auto len = size();
		for (int i = 0; i < len; i++)
			if ((data.v[i].get_type() & banana::Type::Array) && (data.v[i].size() == 2) && (std::string(data.v[i][0]) == key))
				return data.v[i][1];
		data.v.push_back(banana({ key, banana() }));
		return data.v[len][1];
	}
	else
	{
		std::cerr << "\"bnn::banana::operator[](int)\" error: the object is not an array\n";
		throw std::runtime_error("\"bnn::banana::operator[](int)\" error: the object is not an array\n");
	}
}

bnn::banana& bnn::banana::operator[](const char* key)
{
	return this->operator[](std::string(key));
}

bnn::banana::operator int()
{
	if (get_type() & banana::Type::Integer)
		return data.i;
	else
	{
		std::cerr << "\"bnn::banana::operator int()\" error: can't convert the object to int\n";
		throw std::runtime_error("\"bnn::banana::operator int()\" error: can't convert the object to int\n");
	}
}

bnn::banana::operator const int() const
{
	if (get_type() & banana::Type::Integer)
		return data.i;
	else
	{
		std::cerr << "\"bnn::banana::operator const int() const\" error: can't convert the object to int\n";
		throw std::runtime_error("\"bnn::banana::operator const int() const\" error: can't convert the object to int\n");
	}
}

bnn::banana::operator double()
{
	if (get_type() & banana::Type::Double)
		return data.d;
	else
	{
		std::cerr << "\"bnn::banana::operator double()\" error: can't convert the object to double\n";
		throw std::runtime_error("\"bnn::banana::operator double()\" error: can't convert the object to double\n");
	}
}

bnn::banana::operator const double() const
{
	if (get_type() & banana::Type::Double)
		return data.d;
	else
	{
		std::cerr << "\"bnn::banana::operator const double() const\" error: can't convert the object to double\n";
		throw std::runtime_error("\"bnn::banana::operator const double() const\" error: can't convert the object to double\n");
	}
}

bnn::banana::operator bool()
{
	if (get_type() & banana::Type::Boolean)
		return data.b;
	else
	{
		std::cerr << "\"bnn::banana::operator bool()\" error: can't convert the object to boolean\n";
		throw std::runtime_error("\"bnn::banana::operator bool()\" error: can't convert the object to boolean\n");
	}
}

bnn::banana::operator const bool() const
{
	if (get_type() & banana::Type::Boolean)
		return data.b;
	else
	{
		std::cerr << "\"bnn::banana::operator const bool() const\" error: can't convert the object to double\n";
		throw std::runtime_error("\"bnn::banana::operator const bool() const\" error: can't convert the object to bool\n");
	}
}

bnn::banana::operator std::string()
{
	if (get_type() & banana::Type::String)
		return data.s;
	else
	{
		std::cerr << "\"bnn::banana::operator std::string()\" error: can't convert the object to std::string\n";
		throw std::runtime_error("\"bnn::banana::operator std::string()\" error: can't convert the object to std::string\n");
	}
}

bnn::banana::operator const std::string() const
{
	if (get_type() & banana::Type::String)
		return data.s;
	else
	{
		std::cerr << "\"bnn::banana::operator std::string()\" error: can't convert the object to std::string\n";
		throw std::runtime_error("\"bnn::banana::operator std::string()\" error: can't convert the object to std::string\n");
	}
}