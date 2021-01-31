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
		inline banana();
		inline banana(const banana& bn);
		inline banana(const detail::types::__None& n);
		inline banana(const detail::types::__Array& a);
		inline banana(const detail::types::int_type& i);
		inline banana(const detail::types::double_type& d);
		inline banana(const detail::types::bool_type& b);
		inline banana(const detail::types::string_type& s);
		inline banana(const detail::types::cstring_type& s);
		inline banana(const detail::types::array_type& v);
		inline banana(const detail::types::init_list_type& l);

	public:
		inline banana& operator=(const banana& rhs);
		inline banana& operator=(const detail::types::int_type& rhs);
		inline banana& operator=(const detail::types::double_type& rhs);
		inline banana& operator=(const detail::types::bool_type& rhs);
		inline banana& operator=(const detail::types::string_type& rhs);
		inline banana& operator=(const detail::types::cstring_type& rhs);
		inline banana& operator=(const detail::types::array_type& rhs);
		inline banana& operator=(const detail::types::init_list_type& rhs);

	public:
		inline operator detail::types::int_type();
		inline operator const detail::types::int_type() const;

		inline operator detail::types::double_type();
		inline operator const detail::types::double_type() const;

		inline operator detail::types::bool_type();
		inline operator const detail::types::bool_type() const;

		inline operator detail::types::string_type();
		inline operator const detail::types::string_type() const;

		inline operator detail::types::array_type();
		inline operator const detail::types::array_type() const;

	public:
		inline void push_back(const banana& bn);
		inline void pop_back();
		inline banana& front();
		inline banana& back();
		inline detail::types::bool_type empty() const;
		inline detail::types::size_type size() const;
		inline detail::types::size_type max_size() const;
		inline void clear();

		inline bool is_none() const;
		inline bool is_float() const;
		inline bool is_integer() const;
		inline bool is_boolean() const;
		inline bool is_string() const;
		inline bool is_array() const;

	public:
		inline std::string to_string() const;

	private:
		inline bool take_in_quotes() const;

	public:
		inline static banana parse(const char* str);
		inline static banana parse(const std::istream& fin);
		inline static banana parse(const std::string& str);

	private:
		inline static banana parse_array(const char* str);

	public:
		/*banana& operator+();
		banana& operator+(const banana& rhs);

		banana& operator+=(const banana& rhs);*/

	public:
		inline banana& operator[](const int& i);
		inline banana& operator[](const std::string& key);
		inline banana& operator[](const char* key);

	private:
		inline Type get_type() const;
		inline void set_type(Type type);

	private:
		inline static banana create_from_token(detail::Token token);

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
#include "is_methods.inl"

#endif // !BNN_BANANA_HPP
