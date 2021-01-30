bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::Contents& rhs) {
	set_type(rhs.type);

	i.reset(rhs.i != nullptr ? new types::int_type(*rhs.i) : nullptr);
	d.reset(rhs.d != nullptr ? new types::double_type(*rhs.d) : nullptr);
	b.reset(rhs.b != nullptr ? new types::bool_type(*rhs.b) : nullptr);
	s.reset(rhs.s != nullptr ? new types::string_type(*rhs.s) : nullptr);
	a.reset(rhs.a != nullptr ? new std::vector<banana>(*rhs.a) : nullptr);

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::__None& n) {
	set_type(Type::None);

	i.reset(nullptr);
	d.reset(nullptr);
	b.reset(nullptr);
	s.reset(nullptr);
	a.reset(nullptr);

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::int_type& rhs) {
	set_type(Type::Integer);

	i.reset(new types::int_type(rhs));
	d.reset(nullptr);
	b.reset(nullptr);
	s.reset(nullptr);
	a.reset(nullptr);

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::double_type& rhs) {
	set_type(Type::Double);

	i.reset(nullptr);
	d.reset(new types::double_type(rhs));
	b.reset(nullptr);
	s.reset(nullptr);
	a.reset(nullptr);

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::bool_type& rhs) {
	set_type(Type::Double);

	i.reset(nullptr);
	d.reset(nullptr);
	b.reset(new types::bool_type(rhs));
	s.reset(nullptr);
	a.reset(nullptr);

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::string_type& rhs) {
	set_type(Type::String);

	i.reset(nullptr);
	d.reset(nullptr);
	b.reset(nullptr);
	s.reset(new types::string_type(rhs));
	a.reset(nullptr);

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::cstring_type& rhs) {
	set_type(Type::String);

	i.reset(nullptr);
	d.reset(nullptr);
	b.reset(nullptr);
	s.reset(new types::string_type(rhs));
	a.reset(nullptr);

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::array_type& rhs) {
	set_type(Type::Array);

	i.reset(nullptr);
	d.reset(nullptr);
	b.reset(nullptr);
	s.reset(nullptr);
	a.reset(new types::array_type(rhs));

	return *this;
}

bnn::detail::Contents& bnn::detail::Contents::operator=(const bnn::detail::types::init_list_type& rhs) {
	set_type(Type::Array);

	i.reset(nullptr);
	d.reset(nullptr);
	b.reset(nullptr);
	s.reset(nullptr);
	a.reset(new types::array_type(rhs));

	return *this;
}