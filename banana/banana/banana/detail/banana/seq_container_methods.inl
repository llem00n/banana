void bnn::banana::push_back(const bnn::banana& bn) {
	if (get_type() & Type::Array)
		contents.a->push_back(bn);
	else
		throw detail::exceptions::use_error("push_back(const bnn::banana&)", "array");
}

void bnn::banana::pop_back() {
	if (get_type() & Type::Array)
		contents.a->pop_back();
	else if (get_type() & Type::String)
		contents.s->pop_back();
	else
		throw detail::exceptions::use_error("pop_back()", "array or string");
}

bnn::banana& bnn::banana::front() {
	if (get_type() & Type::Array)
		return contents.a->front();
	else
		throw detail::exceptions::use_error("front()", "array");
}

bnn::banana& bnn::banana::back() {
	if (get_type() & Type::Array)
		return contents.a->back();
	else
		throw detail::exceptions::use_error("back()", "array");
}

bnn::detail::types::bool_type bnn::banana::is_none() const {
	return (get_type() & Type::None) ? true : false;
}

bnn::detail::types::bool_type bnn::banana::empty() const {
	if (get_type() & Type::Array)
		return contents.a->empty();
	else if (get_type() & Type::String)
		return contents.s->empty();
	else
		throw detail::exceptions::use_error("empty()", "array or string");
}

bnn::detail::types::size_type bnn::banana::size() const {
	if (get_type() & Type::Array)
		return contents.a->size();
	else if (get_type() & Type::String)
		return contents.s->size();
	else
		throw detail::exceptions::use_error("size()", "array or string");
}

bnn::detail::types::size_type bnn::banana::max_size() const {
	if (get_type() & Type::Array)
		return contents.a->max_size();
	else if (get_type() & Type::String)
		return contents.s->max_size();
	else
		throw detail::exceptions::use_error("max_size()", "array or string");
}

void bnn::banana::clear() {
	set_type(Type::None);
}