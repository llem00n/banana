bnn::detail::Contents::Type bnn::detail::Contents::get_type() const {
	return type;
}

void bnn::detail::Contents::set_type(bnn::detail::Contents::Type type) {
	if (this->type & type)
		return;

	this->type = type;
	i.reset(type & Type::Integer ? (new types::int_type(0)) : nullptr);
	d.reset(type & Type::Double ? (new types::double_type(0.f)) : nullptr);
	b.reset(type & Type::Boolean ? (new types::bool_type(false)) : nullptr);
	s.reset(type & Type::String ? (new types::string_type("")) : nullptr);
	a.reset(type & Type::Array ? (new types::array_type({})) : nullptr);
}