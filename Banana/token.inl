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