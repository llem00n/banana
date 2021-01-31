#ifndef BNN_DETAIL_OUTPUT_HPP
#define BNN_DETAIL_OUTPUT_HPP

#include <iostream>

namespace bnn {
	class banana;
}

inline std::ostream& operator<<(std::ostream& out, const bnn::banana& rhs);

#endif