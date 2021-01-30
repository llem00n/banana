std::ostream& operator<<(std::ostream& out, const bnn::banana& rhs)
{
	out << rhs.to_string();

	return out;
}

std::string bnn::banana::to_string() const
{
	if (get_type() & banana::Type::None)
		return "none";
	else if (get_type() & banana::Type::String)
		return take_in_quotes() ? '"' + *contents.s + '"' : *contents.s;
	else if (get_type() & banana::Type::Integer)
		return std::to_string(*contents.i);
	else if (get_type() & banana::Type::Double)
		return std::to_string(*contents.d);
	else if (get_type() & banana::Type::Boolean)
		return *contents.b ? "true" : "false";
	else if (get_type() & banana::Type::Array)
	{
		std::string res;
		res = "[";
		auto len = size() - 1;
		for (size_t i = 0; i < len; i++)
			res += contents.a->at(i).to_string() + ',';
		res += contents.a->at(len).to_string() + ']';
		return res;
	}
	return "";
}

bool bnn::banana::take_in_quotes() const
{
	if (get_type() & banana::Type::String)
	{
		if (std::find_if(contents.s->begin(), contents.s->end(), [](unsigned char c) { return !std::isdigit(c); }) == contents.s->end())
			return true;
		for (auto& c : *contents.s)
			if (std::find(busy_characters.begin(), busy_characters.end(), c) != busy_characters.end())
				return true;
		if (*contents.s == "false" || *contents.s == "true" || *contents.s == "none")
			return true;
	}

	return false;
}