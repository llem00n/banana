#ifndef BNN_TOKEN_HPP
#define BNN_TOKEN_HPP

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

#include "../common/busy_characters.hpp"
#include "../exceptions/exceptions.hpp"

namespace bnn
{
	class banana;

	namespace detail
	{
		struct Token {
			enum Type { 
				Array         = 1 << 0, 
				Colon         = 1 << 1, 
				Comma         = 1 << 2, 
				WhiteSpace    = 1 << 3, 
				NewLine       = 1 << 4,
				String        = 1 << 5, 
				Undefined     = 1 << 6, 
				None          = 1 << 7, 
				Integer       = 1 << 8, 
				Unsigned      = 1 << 9,
				Double        = 1 << 10, 
				Boolean       = 1 << 11,
				End           = 1 << 12,
				Constructable = Array|String|None|Integer|Unsigned|Double|Boolean,
			};

			Token(std::string s, Type t) : str(s), type(t) {};
			Token() : str(""), type(Type::Undefined) {};

			void optimize_type();

			static Token get_token(char*& cursor);

			std::string str;
			Type type;
		};
	}
}

std::istream& operator>>(std::istream& in, bnn::banana& rhs);

#endif