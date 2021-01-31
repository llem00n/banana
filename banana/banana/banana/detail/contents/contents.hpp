#ifndef BNN_DETAIL_TYPES_HPP
#define BNN_DETAIL_TYPES_HPP

#include <string>
#include <vector>
#include <initializer_list>
#include <memory>

#include "../common/typedefs.hpp"

namespace bnn
{
	class banana;

	namespace detail
	{
		struct Contents
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
			inline Contents();
			inline Contents(const Contents& contents);
			inline Contents(const types::__None& n);
			inline Contents(const types::__Array& a);
			inline Contents(const types::int_type& i);
			inline Contents(const types::double_type& d);
			inline Contents(const types::bool_type& b);
			inline Contents(const types::string_type& s);
			inline Contents(const types::cstring_type& cs);
			inline Contents(const types::array_type& a);
			inline Contents(const types::init_list_type& a);
			inline ~Contents();

		public:
			inline Contents& operator=(const Contents& rhs);
			inline Contents& operator=(const types::__None& n);
			inline Contents& operator=(const types::int_type& rhs);
			inline Contents& operator=(const types::double_type& rhs);
			inline Contents& operator=(const types::bool_type& rhs);
			inline Contents& operator=(const types::string_type& rhs);
			inline Contents& operator=(const types::cstring_type& rhs);
			inline Contents& operator=(const types::array_type& rhs);
			inline Contents& operator=(const types::init_list_type& rhs);

		public:
			inline Type get_type() const;
			inline void set_type(Type type);

		public:
			std::unique_ptr<types::int_type> i;
			std::unique_ptr<types::double_type> d;
			std::unique_ptr<types::bool_type> b;
			std::unique_ptr<types::string_type> s;
			std::unique_ptr<std::vector<banana>> a;

		private:
			Type type;
		};
	}
}

#include "constructors.inl"
#include "operator_assigment.inl"
#include "type_management.inl"

#endif // !BNN_DETAIL_TYPES_HPP
