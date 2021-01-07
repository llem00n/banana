bnn::banana::banana()
	: type(bnn::Type::None)
{}

bnn::banana::banana(const bnn::banana& bn)
	: type(bn.get_type())
	, data(bn.data)
{}

bnn::banana::banana(const int& i)
	: type(bnn::Type::Integer)
	, data(i)
{}

bnn::banana::banana(const double& d)
	: type(bnn::Type::Double)
	, data(d)
{}

bnn::banana::banana(const bool& b)
	: type(bnn::Type::Boolean)
	, data(b)
{}

bnn::banana::banana(const std::string& s)
	: type(bnn::Type::String)
	, data(s)
{}

bnn::banana::banana(const char* s)
	: type(bnn::Type::String)
	, data(s)
{}

bnn::banana::banana(const std::vector<banana>& v)
	: type(bnn::Type::Array)
	, data(v)
{}

bnn::banana::banana(const std::initializer_list<banana>& l)
	: type(bnn::Type::Array)
	, data(l)
{}

void bnn::banana::set_type(bnn::Type t)
{
	if (type == t) return;

	type = t;

	if (type == bnn::Type::String)
	{
		data.v.clear();
	}
	else if (type == bnn::Type::Array)
	{
		data.s.clear();
	}
	else
	{
		data.s.clear();
		data.v.clear();
	}
}

inline bnn::Type bnn::banana::get_type() const
{
	return type;
}

void bnn::banana::push_back(const bnn::banana& bn)
{
	if (type == bnn::Type::Array || type == bnn::Type::None)
	{
		if (type == bnn::Type::None) set_type(bnn::Type::Array);
		data.v.push_back(bn);
	}
	else
	{
		std::cerr << "\"void bnn::banana::push_back(const bnn::banana&)\" error: the object is not an array\n";
		throw std::runtime_error("\"void bnn::banana::push_back(const bnn::banana&)\" error: the object is not an array\n");
	}
}

std::size_t bnn::banana::size() const
{
	if (type == bnn::Type::Array)
		return data.v.size();
	else
		return 1;
}

std::string bnn::banana::to_string() const
{
	if (type == bnn::Type::None)
		return "none";
	else if (type == bnn::Type::String)
		return take_in_quotes() ? '"' + data.s + '"' : data.s;
	else if (type == bnn::Type::Integer)
		return std::to_string(data.i);
	else if (type == bnn::Type::Double)
		return std::to_string(data.d);
	else if (type == bnn::Type::Boolean)
		return data.b ? "true" : "false";
	else if (type == bnn::Type::Array)
	{
		std::string res;
		res = "[";
		auto len = size() - 1;
		for (int i = 0; i < len; i++)
			res += data.v[i].to_string() + ',';
		res += data.v[len].to_string() + ']';
		return res;
	}
	return "";
}

bnn::banana bnn::banana::parse(const char* str)
{
	banana bn;
	char* cursor = const_cast<char*>(str);
	std::vector<Token> tokens;
	while (*cursor)
	{
		Token token = Token::get_token(cursor);
		if (token.type != Token::Type::WhiteSpace) tokens.push_back(token);
	}
	tokens.push_back(Token("", Token::Type::End));

	size_t len = tokens.size();
	for (size_t i = 0; i < len; i++)
		if (tokens[i].type & Token::Type::Constructable)
		{
			bool new_line = false;
			for (size_t x = i + 1; x < len; x++)
			{
				if (tokens[x].type & Token::Type::NewLine)
					new_line = true;
				else if ((tokens[x].type & Token::Type::Comma) || (tokens[x].type & Token::Type::End))
				{
					bn.push_back(banana::create_from_token(tokens[i]));
					break;
				}
				else if ((tokens[x].type & Token::Type::Constructable) && new_line)
				{
					bn.push_back(banana::create_from_token(tokens[i]));
					break;
				}
				else if (tokens[x].type & Token::Type::Constructable)
				{
					if (tokens[x].type & Token::Type::Array)
					{
						bn.push_back({ bnn::banana::create_from_token(tokens[i]), bnn::banana::create_from_token(tokens[x]) });
						tokens[i].type = Token::Type::Undefined;
						tokens[x].type = Token::Type::Undefined;
						break;
					}
					else
					{
						std::cerr << "\"bnn::banana bnn::banana::parse(const char*)\" error: expected a comma (',') or a colon (':')\n";
						throw std::runtime_error("\"bnn::banana bnn::banana::parse(const char*)\" error: expected a comma (',') or a colon (':')\n");
					}
				}
				else if (tokens[x].type & Token::Type::Colon)
				{
					for (size_t y = x + 1; y < len; y++)
						if (tokens[y].type & Token::Type::Constructable)
						{
							bn.push_back({ banana::create_from_token(tokens[i]), banana::create_from_token(tokens[y]) });
							tokens[i].type = Token::Type::Undefined;
							tokens[x].type = Token::Type::Undefined;
							tokens[y].type = Token::Type::Undefined;
							break;
						}
						else if (tokens[y].type & (Token::Type::Colon | Token::Type::End | Token::Type::Comma | Token::Type::Undefined))
						{
							std::cerr << "\"bnn::banana bnn::banana::parse(const char*)\" error: expected a value after colon (':')\n";
							throw std::runtime_error("\"bnn::banana bnn::banana::parse(const char*)\" error: expected a value after colon (':')\n");
						}
					break;
				}
			}
		}
		else if (tokens[i].type & Token::Type::Colon)
		{
			std::cerr << "\"bnn::banana bnn::banana::parse(const char*)\" error: unexpected token. Expected a key value before the colon (':')\n";
			throw std::runtime_error("\"bnn::banana bnn::banana::parse(const char*)\" error: unexpected token. Expected a key value before the colon (':')\n");
		}
	return bn;
}

bnn::banana bnn::banana::parse(const std::string& str)
{
	return parse(str.c_str());
}

bnn::banana bnn::banana::parse(const std::ifstream& fin)
{
	std::stringstream strStream;
	strStream << fin.rdbuf();
	std::string str = strStream.str();
	return parse(str);
}

bnn::banana& bnn::banana::operator=(const bnn::banana& rhs)
{
	set_type(rhs.get_type());
	data = rhs.data;
	return *this;
}

bnn::banana& bnn::banana::operator=(const int& rhs)
{
	set_type(bnn::Type::Integer);
	data.i = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const double& rhs)
{
	set_type(bnn::Type::Double);
	data.d = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bool& rhs)
{
	set_type(bnn::Type::Boolean);
	data.b = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const std::string& rhs)
{
	set_type(bnn::Type::String);
	data.s = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const char* rhs)
{
	set_type(bnn::Type::String);
	data.s = std::string(rhs);
	return *this;
}

bnn::banana& bnn::banana::operator=(const std::vector<banana>& rhs)
{
	set_type(bnn::Type::Array);
	data.v = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const std::initializer_list<banana>& rhs)
{
	set_type(bnn::Type::Array);
	data.v = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator[](const int& i)
{
	if (type == bnn::Type::Array)
		return data.v[i];
	else
	{
		std::cerr << "\"bnn::banana::operator[](int)\" error: the object is not an array\n";
		throw std::runtime_error("\"bnn::banana::operator[](int)\" error: the object is not an array\n");
	}
}

bnn::banana& bnn::banana::operator[](const std::string& key)
{
	if (type == bnn::Type::Array)
	{
		auto len = size();
		for (int i = 0; i < len; i++)
			if ((data.v[i].get_type() == bnn::Type::Array) && (data.v[i].size() == 2) && (std::string(data.v[i][0]) == key))
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
	if (type == Type::Integer)
		return data.i;
	else
	{
		std::cerr << "\"bnn::banana::operator int()\" error: can't convert the object to int\n";
		throw std::runtime_error("\"bnn::banana::operator int()\" error: can't convert the object to int\n");
	}
}

bnn::banana::operator const int() const
{
	if (type == Type::Integer)
		return data.i;
	else
	{
		std::cerr << "\"bnn::banana::operator const int() const\" error: can't convert the object to int\n";
		throw std::runtime_error("\"bnn::banana::operator const int() const\" error: can't convert the object to int\n");
	}
}

bnn::banana::operator double()
{
	if (type == Type::Double)
		return data.d;
	else
	{
		std::cerr << "\"bnn::banana::operator double()\" error: can't convert the object to double\n";
		throw std::runtime_error("\"bnn::banana::operator double()\" error: can't convert the object to double\n");
	}
}

bnn::banana::operator const double() const
{
	if (type == Type::Double)
		return data.d;
	else
	{
		std::cerr << "\"bnn::banana::operator const double() const\" error: can't convert the object to double\n";
		throw std::runtime_error("\"bnn::banana::operator const double() const\" error: can't convert the object to double\n");
	}
}

bnn::banana::operator bool()
{
	if (type == Type::Boolean)
		return data.b;
	else
	{
		std::cerr << "\"bnn::banana::operator bool()\" error: can't convert the object to boolean\n";
		throw std::runtime_error("\"bnn::banana::operator bool()\" error: can't convert the object to boolean\n");
	}
}

bnn::banana::operator const bool() const
{
	if (type == Type::Boolean)
		return data.b;
	else
	{
		std::cerr << "\"bnn::banana::operator const bool() const\" error: can't convert the object to double\n";
		throw std::runtime_error("\"bnn::banana::operator const bool() const\" error: can't convert the object to bool\n");
	}
}

bnn::banana::operator std::string()
{
	if (type == Type::String)
		return data.s;
	else
	{
		std::cerr << "\"bnn::banana::operator std::string()\" error: can't convert the object to std::string\n";
		throw std::runtime_error("\"bnn::banana::operator std::string()\" error: can't convert the object to std::string\n");
	}
}

bnn::banana::operator const std::string() const
{
	if (type == Type::String)
		return data.s;
	else
	{
		std::cerr << "\"bnn::banana::operator const std::string() const\" error: can't convert the object to std::string\n";
		throw std::runtime_error("\"bnn::banana::operator const std::string() const\" error: can't convert the object to std::string\n");
	}
}

bool bnn::banana::take_in_quotes() const
{
	if (get_type() == bnn::Type::String)
	{
		if (std::find_if(data.s.begin(), data.s.end(), [](unsigned char c) { return !std::isdigit(c); }) == data.s.end())
			return true;
		for (auto& c : data.s)
			if (std::find(busy_characters.begin(), busy_characters.end(), c) != busy_characters.end())
				return true;
		if (data.s == "false" || data.s == "true" || data.s == "none")
			return true;
	}

	return false;
}

bool bnn::banana::is_map() const
{
	if ((get_type()) == Type::Array && (data.v[0].get_type() == Type::String) && (size() == 2))
		return true;
	return false;
}

bnn::banana bnn::banana::create_from_token(bnn::Token token)
{
	if (token.type == Token::Type::String)
		return bnn::banana(token.str);
	if (token.type == Token::Type::Integer)
		return bnn::banana(std::stoi(token.str));
	if (token.type == Token::Type::Double)
		return bnn::banana(std::stod(token.str));
	if (token.type == Token::Type::Boolean)
		return bnn::banana(token.str == "true" ? true : false);
	if (token.type == Token::Type::Array)
		return bnn::banana::parse(token.str.c_str());
}

std::ostream& operator<<(std::ostream& out, const bnn::banana& rhs)
{
	if (rhs.get_type() == bnn::Type::None)
		out << "none";
	else if (rhs.get_type() == bnn::Type::Integer)
		out << int(rhs);
	else if (rhs.get_type() == bnn::Type::Double)
		out << double(rhs);
	else if (rhs.get_type() == bnn::Type::Boolean)
		out << (bool(rhs) ? "true" : "false");
	else if (rhs.get_type() == bnn::Type::String)
		out << std::string(rhs);
	else
	{
		std::cerr << "\"std::ostream& operator<<(std::ostream&, const bnn::banana&)\" error: the object is not printable\n";
		throw std::runtime_error("\"std::ostream& operator<<(std::ostream&, const bnn::banana&)\" error: the object is not printable\n");
	}

	return out;
}