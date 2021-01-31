bool bnn::banana::is_none() const {
	return (get_type() & Type::None) ? true : false;
}

bool bnn::banana::is_float() const {
	return (get_type() & (Type::Double)) ? true : false;
}

bool bnn::banana::is_integer() const {
	return (get_type() & (Type::Integer)) ? true : false;
}

bool bnn::banana::is_boolean() const {
	return (get_type() & (Type::Integer | Type::Double | Type::Boolean)) ? true : false;
}

bool bnn::banana::is_array() const {
	return (get_type() & Type::Array) ? true : false;
}

bool bnn::banana::is_string() const {
	return (get_type() & Type::String) ? true : false;
}