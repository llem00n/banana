bnn::banana::operator bnn::detail::types::int_type() {
	if (get_type() & banana::Type::Integer)
		return *contents.i;
	else
		throw detail::exceptions::conversion_error("int");
}

bnn::banana::operator const bnn::detail::types::int_type() const {
	if (get_type() & banana::Type::Integer)
		return *contents.i;
	else
		throw detail::exceptions::conversion_error("int");
}

bnn::banana::operator bnn::detail::types::double_type() {
	if (get_type() & banana::Type::Double)
		return *contents.d;
	else if (get_type() & banana::Type::Integer)
		return detail::types::double_type(*contents.i);
	else
		throw detail::exceptions::conversion_error("int");
}

bnn::banana::operator const bnn::detail::types::double_type() const {
	if (get_type() & banana::Type::Double)
		return *contents.d;
	else if (get_type() & banana::Type::Integer)
		return detail::types::double_type(*contents.i);
	else
		throw detail::exceptions::conversion_error("int");
}

bnn::banana::operator bnn::detail::types::bool_type()
{
	if (get_type() & banana::Type::Boolean)
		return *contents.b;
	else if (get_type() & banana::Type::Integer)
		return *contents.i;
	else if (get_type() & banana::Type::Double)
		return *contents.d;
	else
		throw detail::exceptions::conversion_error("bool");
}

bnn::banana::operator const bnn::detail::types::bool_type() const
{
	if (get_type() & banana::Type::Boolean)
		return *contents.b;
	else if (get_type() & banana::Type::Integer)
		return *contents.i;
	else if (get_type() & banana::Type::Double)
		return *contents.d;
	else
		throw detail::exceptions::conversion_error("bool");
}

bnn::banana::operator bnn::detail::types::string_type()
{
	if (get_type() & banana::Type::String)
		return *contents.s;
	else
		throw detail::exceptions::conversion_error("string");
}

bnn::banana::operator const bnn::detail::types::string_type() const
{
	if (get_type() & banana::Type::String)
		return *contents.s;
	else
		throw detail::exceptions::conversion_error("string");
}

bnn::banana::operator bnn::detail::types::array_type()
{
	if (get_type() & banana::Type::Array)
		return *contents.a;
	else
		throw detail::exceptions::conversion_error("array");
}

bnn::banana::operator const bnn::detail::types::array_type() const
{
	if (get_type() & banana::Type::Array)
		return *contents.a;
	else
		throw detail::exceptions::conversion_error("array");
}