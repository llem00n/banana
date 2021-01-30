bnn::banana::banana()
	: type(banana::Type::None)
	, contents(none)
{}

bnn::banana::banana(const bnn::banana& bn)
	: type(bn.get_type())
	, contents(bn.contents)
{}

bnn::banana::banana(const bnn::detail::types::__None& n)
	: type(Type::None)
	, contents(n)
{}

bnn::banana::banana(const bnn::detail::types::__Array& a)
	: type(Type::Array)
	, contents(a)
{}

bnn::banana::banana(const bnn::detail::types::int_type& i)
	: type(banana::Type::Integer)
	, contents(i)
{}

bnn::banana::banana(const bnn::detail::types::double_type& d)
	: type(banana::Type::Double)
	, contents(d)
{}

bnn::banana::banana(const bnn::detail::types::bool_type& b)
	: type(banana::Type::Boolean)
	, contents(b)
{}

bnn::banana::banana(const bnn::detail::types::string_type& s)
	: type(banana::Type::String)
	, contents(s)
{}

bnn::banana::banana(const bnn::detail::types::cstring_type& s)
	: type(banana::Type::String)
	, contents(s)
{}

bnn::banana::banana(const bnn::detail::types::array_type& v)
	: type(banana::Type::Array)
	, contents(v)
{}

bnn::banana::banana(const bnn::detail::types::init_list_type& l)
	: type(banana::Type::Array)
	, contents(l)
{}