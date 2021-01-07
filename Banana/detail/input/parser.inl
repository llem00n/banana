void bnn::Token::optimize_type()
{
	if (type == Type::Undefined)
	{
		std::istringstream iss(str);
		double x; int y;
		std::string intersection;
		std::set_intersection(str.begin(), str.end(), busy_characters.begin(), busy_characters.end(), std::back_inserter(intersection));

		if (str == "none")
			type = Type::None;
		else if (str == "false" || str == "true")
			type = Type::Boolean;
		else if (iss >> y)
			type = Type::Integer;
		else if (iss >> x)
			type = Type::Double;
		else if (intersection.size() == 0)
			type = Type::String;
	}
}

bnn::Token bnn::Token::get_token(char*& cursor)
{
	Token token("", Token::Type::Undefined);
	if (*cursor == ',')
		token = Token(",", Token::Type::Comma);
	else if (*cursor == '\n')
		token = Token("__", Token::Type::NewLine);
	else if (*cursor == ':')
		token = Token(":", Token::Type::Colon);
	else if (std::isspace(*cursor))
		token = Token("_", Token::Type::WhiteSpace);
	else if (*cursor == '[' || *cursor == '{' || *cursor == '(')
	{
		token = Token("", Token::Type::Array);
		std::string brackets(1, *cursor);
		while (*cursor && brackets.size())
		{
			cursor++;
			if (*cursor == '[' || *cursor == '{' || *cursor == '(') brackets += *cursor;
			if (*cursor == ']' || *cursor == '}' || *cursor == ')')
			{
				char last_bracket = brackets[brackets.size() - 1];
				if (
					(*cursor == ']' && last_bracket == '[')
					|| (*cursor == '}' && last_bracket == '{')
					|| (*cursor == ')' && last_bracket == '(')
					&& (token.str.size() > 0)
					) brackets.pop_back();
				else
				{
					std::cerr << "\"Token get_token(char*&)\" error: unexpected " + std::string(1, *cursor) + " in array of " + token.str + '\n';
					throw std::runtime_error("\"Token get_token(char*&)\" error: unexpected " + std::string(1, *cursor) + " in array of " + token.str + '\n');
				}
			}
			if (brackets.size() > 0)
				token.str += *cursor;
		}
		if (brackets.size() > 0 && !*cursor)
		{
			std::cerr << "\"Token get_token(char*&)\" error: expexted a closing bracket for array of " + token.str + '\n';
			throw std::runtime_error("\"Token get_token(char*&)\" error: expexted a closing bracket for array of " + token.str + '\n');
		}
	}
	else if (*cursor == ']' || *cursor == '}' || *cursor == ')')
	{
		std::cerr << "\"Token get_token(char*&)\" error: unexpected token: " + std::string(1, *cursor) + "\n";
		throw std::runtime_error("\"Token get_token(char*&)\" error: unexpected token: " + std::string(1, *cursor) + "\n");
	}
	else if (*cursor == '\'' || *cursor == '"')
	{
		enum class QuotesType { Single, Double };
		QuotesType quotes_type = *cursor == '\'' ? QuotesType::Single : QuotesType::Double;
		token = Token("", Token::Type::String);
		while (*cursor)
		{
			cursor++;
			if (
				(*cursor == '\'' && quotes_type == QuotesType::Single)
				|| (*cursor == '"' && quotes_type == QuotesType::Double)
				) break;

			token.str += *cursor;
		}
	}
	else
	{
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
	std::stringstream str_stream;
	str_stream << fin.rdbuf();
	std::string str = str_stream.str();
	return parse(str);
}