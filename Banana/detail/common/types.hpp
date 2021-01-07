#ifndef BNN_TYPES_HPP
#define BNN_TYPES_HPP

#include <string>
#include <vector>
#include <initializer_list>

namespace bnn
{
	class banana;

	namespace
	{
		struct Types
		{
			Types() : i(0) {};
			Types(const int& i) : i(i) {};
			Types(const double& d) : d(d) {};
			Types(const bool& b) : b(b) {};
			Types(const std::string& s) : s(s) {};
			Types(const char* s) : s(s) {};
			Types(const std::vector<banana> v) : v(v) {};
			Types(const std::initializer_list<banana> l) : v(l) {};
			~Types() {};

			int i;
			double d;
			bool b;
			std::string s;
			std::vector<banana> v;
		};
	}
}

#endif // !BNN_TYPES_HPP
