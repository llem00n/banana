#ifndef BNN_TOKEN_HPP
#define BNN_TOKEN_HPP

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include "common.hpp"

namespace bnn
{
	class banana;

	namespace
	{
		struct Token {
			enum class Type { Array, Colon, Comma, WhiteSpace, String, Undefined, None, Integer, Double, Boolean };

			Token(std::string s, Type t) : str(s), type(t) {};
			Token() : str(""), type(Type::Undefined) {};

			void optimize_type();

			static Token get_token(char*& cursor);

			std::string str;
			Type type;
		};
	}
}

#include "token.inl"

#endif