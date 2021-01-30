#ifndef BNN_DETAIL_EXCEPTIONS_EXCEPTIONS_HPP
#define BNN_DETAIL_EXCEPTIONS_EXCEPTIONS_HPP

#include <exception>
#include <stdexcept>
#include <string>

namespace bnn
{
	namespace detail
	{
		namespace exceptions
		{
			struct exception : std::exception {
				exception(const std::string& str);

				const char* what() const throw();

			public:
				std::runtime_error error;
			};

			struct conversion_error : public exception {
				conversion_error(const std::string& str);
			};

			struct use_error : public exception {
				use_error(const std::string& fn_name, const std::string& type_name);
			};

			struct parse_error : public exception {
				parse_error(const std::string& type, const std::string& token_name, const std::string& at);
				parse_error(const std::string& type, const char& token_name, const std::string& at);
			};
		}
	}
}

#include "exceptions.inl"

#endif // !BNN_DETAIL_EXCEPTIONS_EXCEPTIONS_HPP