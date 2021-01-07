#ifndef BNN_BANANA_HPP
#define BNN_BANANA_HPP

#include <stdexcept>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "detail/common/types.hpp"
#include "detail/common/common.hpp"
#include "detail/input/token.hpp"

namespace bnn
{
	class banana
	{
	public:
		enum Type
		{
			None = 1 << 0,
			Integer = 1 << 1,
			Double = 1 << 2,
			Boolean = 1 << 3,
			String = 1 << 4,
			Array = 1 << 5,
			Printable = None | Integer | Double | Boolean | String | Array,
		};

	public:
		banana();
		banana(const banana& bn);
		banana(const int& i);
		banana(const double& d);
		banana(const bool& b);
		banana(const std::string& s);
		banana(const char* s);
		banana(const std::vector<banana>& v);
		banana(const std::initializer_list<banana>& l);

	public:
		void set_type(Type t);
		Type get_type() const;

		void push_back(const banana& bn);

		std::size_t size() const;

		std::string to_string() const;

		static banana parse(const char* str);
		static banana parse(const std::ifstream& fin);
		static banana parse(const std::string& str);

	public:
		banana& operator=(const banana& rhs);
		banana& operator=(const int& rhs);
		banana& operator=(const double& rhs);
		banana& operator=(const bool& rhs);
		banana& operator=(const std::string& rhs);
		banana& operator=(const char* rhs);
		banana& operator=(const std::vector<banana>& rhs);
		banana& operator=(const std::initializer_list<banana>& rhs);

	public:
		banana& operator[](const int& i);
		banana& operator[](const std::string& key);
		banana& operator[](const char* key);

	public:
		operator int();
		operator const int() const;

		operator double();
		operator const double() const;

		operator bool();
		operator const bool() const;

		operator std::string();
		operator const std::string() const;

	private:
		inline bool take_in_quotes() const;
		static banana create_from_token(Token token);

	private:
		Type type;
		Types data;
	};
}

std::ostream& operator<<(std::ostream& out, const bnn::banana& rhs);

#include "detail/banana.inl"
#include "detail/input/parser.inl"
#include "detail/output/output.inl"

#endif // !BNN_BANANA_HPP
