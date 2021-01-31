#ifndef BNN_DETAIL_TYPEDEFS_HPP
#define BNN_DETAIL_TYPEDEFS_HPP

#include <string>
#include <vector>
#include <initializer_list>
#include <cstdlib>

namespace bnn
{
	class banana;

	namespace detail
	{
		namespace types
		{
			using int_type = int;
			using unsigned_type = unsigned;
			using double_type = float;
			using bool_type = bool;
			using string_type = std::string;
			using cstring_type = char*;
			using array_type = std::vector<banana>;
			using init_list_type = std::initializer_list<banana>;

			using size_type = std::size_t;
		}
	}
}

namespace bnn {
	namespace detail {
		namespace types {
			class __None {};
			class __Array {};
		}
	}

	const detail::types::__None none;
	const detail::types::__Array array;
}

#endif // !BNN_DETAIL_TYPEDFS_HPP