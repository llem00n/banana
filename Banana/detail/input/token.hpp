#ifndef BNN_TOKEN_HPP
#define BNN_TOKEN_HPP

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include "../common/common.hpp"

namespace bnn
{
	class banana;

	namespace
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
				Double        = 1 << 9, 
				Boolean       = 1 << 10,
				End           = 1 << 11,
				Constructable = Array|String|None|Integer|Double|Boolean,
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

#endif