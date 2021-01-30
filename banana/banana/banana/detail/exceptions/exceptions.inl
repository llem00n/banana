bnn::detail::exceptions::exception::exception(const std::string& str)
	: error(str) 
{}

const char* bnn::detail::exceptions::exception::what() const throw() {
	return error.what();
}

bnn::detail::exceptions::conversion_error::conversion_error(const std::string& str) 
	: exception("Conversion error: the object can't be converted into " + str)
{}

bnn::detail::exceptions::use_error::use_error(const std::string& fn_name, const std::string& type_name)
	: exception("Use error: function " + fn_name + " can only be used with " + type_name) 
{}

bnn::detail::exceptions::parse_error::parse_error(
		const std::string& type,
		const std::string& token_name,
		const std::string& at) 
	: exception("Parse error: " + type + " token \"" + token_name + "\" at " + at) 
{}

bnn::detail::exceptions::parse_error::parse_error(
	const std::string& type,
	const char& token_name,
	const std::string& at)
	: exception("Parse error: " + type + " token \"" + std::string(1, token_name) + "\" at " + at) {}