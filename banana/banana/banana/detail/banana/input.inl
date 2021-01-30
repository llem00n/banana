void bnn::detail::Token::optimize_type() {
	if (type == Type::Undefined) {
		std::istringstream iss(str);
		int y; double z;
		std::string intersection;
		std::set_intersection(str.begin(), str.end(), busy_characters.begin(), busy_characters.end(), std::back_inserter(intersection));

		if (str == "none")
			type = Type::None;
		else if (str == "false" || str == "true")
			type = Type::Boolean;
		else if (iss >> y)
			type = Type::Integer;
		else if (iss >> z)
			type = Type::Double;
		else if (intersection.size() == 0)
			type = Type::String;
	}
}

bnn::detail::Token bnn::detail::Token::get_token(char*& cursor) {
	Token token("", Token::Type::Undefined);
	if (*cursor == ',')
		token = Token(",", Token::Type::Comma);
	else if (*cursor == '\n')
		token = Token("\\n", Token::Type::NewLine);
	else if (*cursor == ':')
		token = Token(":", Token::Type::Colon);
	else if (std::isspace(*cursor))
		token = Token("_", Token::Type::WhiteSpace);
	else if (*cursor == '[' || *cursor == '{' || *cursor == '(') {
		token = Token("", Token::Type::Array);
		std::string brackets(1, *cursor);
		while (*cursor && brackets.size()) {
			cursor++;
			if (*cursor == '[' || *cursor == '{' || *cursor == '(') 
				brackets += *cursor;
			if (*cursor == ']' || *cursor == '}' || *cursor == ')') {
				char last_bracket = brackets[brackets.size() - 1];
				if (
					(*cursor == ']' && last_bracket == '[')
					|| (*cursor == '}' && last_bracket == '{')
					|| (*cursor == ')' && last_bracket == '(')
					&& (token.str.size() > 0)
					) brackets.pop_back();
				else
					throw exceptions::parse_error("unexpected", *cursor, "");
			}
			if (brackets.size() > 0)
				token.str += *cursor;
		}
		if (brackets.size() > 0 && !*cursor)
			throw exceptions::parse_error("expected", "closing bracket", "");
	}
	else if (*cursor == ']' || *cursor == '}' || *cursor == ')')
		throw exceptions::parse_error("unexpected", *cursor, "");
	else if (*cursor == '\'' || *cursor == '"')
	{
		enum class QuotesType { Single, Double };
		QuotesType quotes_type = *cursor == '\'' ? QuotesType::Single : QuotesType::Double;
		token = Token("", Token::Type::String);
		while (*cursor) {
			cursor++;
			if (
				(*cursor == '\'' && quotes_type == QuotesType::Single)
				|| (*cursor == '"' && quotes_type == QuotesType::Double)
				) break;

			token.str += *cursor;
		}
		if (*cursor != '\'' && *cursor != '"')
			throw exceptions::parse_error("expected", "closing quote", "");
	}
	else {
		while (
				*cursor
				&& std::find(bnn::busy_characters.begin(), bnn::busy_characters.end(), *cursor) == bnn::busy_characters.end()
				) {
			token.str += *cursor;
			cursor++;
		}
		cursor--;
		token.optimize_type();
	}
	cursor++;
	return token;
}

bnn::banana bnn::banana::create_from_token(bnn::detail::Token token) {
	if (token.type == detail::Token::Type::String)
		return bnn::banana(token.str);
	if (token.type == detail::Token::Type::Integer)
		return bnn::banana(std::stoi(token.str));
	if (token.type == detail::Token::Type::Double)
		return bnn::banana(std::stof(token.str));
	if (token.type == detail::Token::Type::Boolean)
		return bnn::banana(token.str == "true" ? true : false);
	if (token.type == detail::Token::Type::Array)
		return bnn::banana::parse_array(token.str.c_str());
	return bnn::banana();
}

bnn::banana bnn::banana::parse(const char* str) {
	banana bn = banana::parse_array(str);
	return (bn.size() == 1) ? bn[0] : bn;
}

bnn::banana bnn::banana::parse(const std::string& str)
{
	return parse(str.c_str());
}

bnn::banana bnn::banana::parse(const std::istream& in)
{
	std::stringstream str_stream;
	str_stream << in.rdbuf();
	std::string str = str_stream.str();
	return parse(str);
}

bnn::banana bnn::banana::parse_array(const char* str) {
	banana bn = array;
	char* cursor = const_cast<char*>(str);
	std::vector<detail::Token> tokens;
	while (*cursor) {
		detail::Token token = detail::Token::get_token(cursor);
		if (token.type != detail::Token::Type::WhiteSpace)
			tokens.push_back(token);
	}
	tokens.push_back(detail::Token("", detail::Token::Type::End));

	size_t len = tokens.size();
	for (size_t i = 0; i < len; i++) {
		if (tokens[i].type & detail::Token::Type::Constructable) {
			bool new_line = false;
			for (size_t x = i + 1; x < len; x++) {
				if (tokens[x].type & detail::Token::Type::NewLine)
					new_line = true;
				else if ((tokens[x].type & detail::Token::Type::Comma) || (tokens[x].type & detail::Token::Type::End)) {
					bn.push_back(banana::create_from_token(tokens[i]));
					break;
				} else if ((tokens[x].type & detail::Token::Type::Constructable) && new_line) {
					bn.push_back(banana::create_from_token(tokens[i]));
					break;
				} else if (tokens[x].type & detail::Token::Type::Constructable) {
					if (tokens[x].type & detail::Token::Type::Array) {
						bn.push_back({bnn::banana::create_from_token(tokens[i]), bnn::banana::create_from_token(tokens[x])});
						tokens[i].type = detail::Token::Type::Undefined;
						tokens[x].type = detail::Token::Type::Undefined;
						break;
					} else
						throw detail::exceptions::parse_error("expected", "\",\" or \":\"", "");
				} else if (tokens[x].type & detail::Token::Type::Colon) {
					for (size_t y = x + 1; y < len; y++)
						if (tokens[y].type & detail::Token::Type::Constructable) {
							bn.push_back({banana::create_from_token(tokens[i]), banana::create_from_token(tokens[y])});
							tokens[i].type = detail::Token::Type::Undefined;
							tokens[x].type = detail::Token::Type::Undefined;
							tokens[y].type = detail::Token::Type::Undefined;
							break;
						} else if (tokens[y].type & (detail::Token::Type::Colon | detail::Token::Type::End | detail::Token::Type::Comma | detail::Token::Type::Undefined))
							throw detail::exceptions::parse_error("expected", "value", "");
						break;
				}
			}
		} else if (tokens[i].type & detail::Token::Type::Colon)
			throw detail::exceptions::parse_error("expected", "key value", "");
	}

	return bn;
}

std::istream& operator>>(std::istream& in, bnn::banana& rhs) {
	std::string s;
	std::getline(in, s);
	rhs = bnn::banana::parse(s);
	return in;
}