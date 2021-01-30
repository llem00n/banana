bnn::banana& bnn::banana::operator=(const bnn::banana& rhs) {
	set_type(rhs.get_type());
	contents = rhs.contents;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bnn::detail::types::int_type& rhs) {
	set_type(banana::Type::Integer);
	contents = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bnn::detail::types::double_type& rhs) {
	set_type(banana::Type::Double);
	contents = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bnn::detail::types::bool_type& rhs) {
	set_type(banana::Type::Boolean);
	contents = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bnn::detail::types::string_type& rhs) {
	set_type(banana::Type::String);
	contents = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bnn::detail::types::cstring_type& rhs) {
	set_type(banana::Type::String);
	contents = std::string(rhs);
	return *this;
}

bnn::banana& bnn::banana::operator=(const bnn::detail::types::array_type& rhs) {
	set_type(banana::Type::Array);
	contents = rhs;
	return *this;
}

bnn::banana& bnn::banana::operator=(const bnn::detail::types::init_list_type& rhs) {
	set_type(banana::Type::Array);
	contents = rhs;
	return *this;
}