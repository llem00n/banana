#ifndef BNN_DETAIL_BANANA_HPP
#define BNN_DETAIL_BANANA_HPP

#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>

#include "../input/input.hpp"
#include "../common/typedefs.hpp"
#include "../contents/contents.hpp"
#include "../exceptions/exceptions.hpp"

namespace bnn
{
	class banana {
	public:
		typedef detail::Contents::Type Type;

	public:
		banana();
		banana(const banana& bn);
		banana(const detail::types::__None& n);
		banana(const detail::types::__Array& a);
		banana(const detail::types::int_type& i);
		banana(const detail::types::double_type& d);
		banana(const detail::types::bool_type& b);
		banana(const detail::types::string_type& s);
		banana(const detail::types::cstring_type& s);
		banana(const detail::types::array_type& v);
		banana(const detail::types::init_list_type& l);

	public:
		banana& operator=(const banana& rhs);
		banana& operator=(const detail::types::int_type& rhs);
		banana& operator=(const detail::types::double_type& rhs);
		banana& operator=(const detail::types::bool_type& rhs);
		banana& operator=(const detail::types::string_type& rhs);
		banana& operator=(const detail::types::cstring_type& rhs);
		banana& operator=(const detail::types::array_type& rhs);
		banana& operator=(const detail::types::init_list_type& rhs);

	public:
		operator detail::types::int_type();
		operator const detail::types::int_type() const;

		operator detail::types::double_type();
		operator const detail::types::double_type() const;

		operator detail::types::bool_type();
		operator const detail::types::bool_type() const;

		operator detail::types::string_type();
		operator const detail::types::string_type() const;

		operator detail::types::array_type();
		operator const detail::types::array_type() const;

	public:
		void push_back(const banana& bn);
		void pop_back();
		banana& front();
		banana& back();
		detail::types::bool_type is_none() const;
		detail::types::bool_type empty() const;
		detail::types::size_type size() const;
		detail::types::size_type max_size() const;
		void clear();

	public:
		std::string to_string() const;

	private:
		bool take_in_quotes() const;

	public:
		static banana parse(const char* str);
		static banana parse(const std::istream& fin);
		static banana parse(const std::string& str);

	private:
		static banana parse_array(const char* str);

	public:
		/*banana& operator+();
		banana& operator+(const banana& rhs);

		banana& operator+=(const banana& rhs);*/

	public:
		banana& operator[](const int& i);
		banana& operator[](const std::string& key);
		banana& operator[](const char* key);

	public:
		Type get_type() const;

	private:
		void set_type(Type type);

	private:
		static banana create_from_token(detail::Token token);

	private:
		Type type;
		detail::Contents contents;
	};
};

#include "banana.inl"
#include "constructors.inl"
#include "operator_assigment.inl"
#include "operator_conversion.inl"
#include "operator_access.inl"
#include "seq_container_methods.inl"
#include "type_management.inl"
#include "output.inl"
#include "input.inl"

#endif // !BNN_BANANA_HPP
