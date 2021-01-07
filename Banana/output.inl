std::ostream& operator<<(std::ostream& out, const bnn::banana& rhs)
{
	if (rhs.get_type() & bnn::banana::Type::Printable)
		out << rhs.to_string();
	else
	{
		std::cerr << "\"std::ostream& operator<<(std::ostream&, const bnn::banana&)\" error: the object is not printable\n";
		throw std::runtime_error("\"std::ostream& operator<<(std::ostream&, const bnn::banana&)\" error: the object is not printable\n");
	}

	return out;
}

std::string bnn::banana::to_string() const
{
	if (get_type() & banana::Type::None)
		return "none";
	else if (get_type() & banana::Type::String)
		return take_in_quotes() ? '"' + data.s + '"' : data.s;
	else if (get_type() & banana::Type::Integer)
		return std::to_string(data.i);
	else if (get_type() & banana::Type::Double)
		return std::to_string(data.d);
	else if (get_type() & banana::Type::Boolean)
		return data.b ? "true" : "false";
	else if (get_type() & banana::Type::Array)
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

bool bnn::banana::take_in_quotes() const
{
	if (get_type() & banana::Type::String)
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