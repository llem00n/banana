#ifndef BNN_DETAIL_CONTENTS_INL
#define BNN_DETAIL_CONTENTS_INL

bnn::detail::Contents::Contents()
	: i(nullptr)
	, d(nullptr)
	, b(nullptr)
	, s(nullptr)
	, a(nullptr)
	, type(Type::None)
{}

bnn::detail::Contents::Contents(const bnn::detail::Contents& contents)
	: i(contents.i != nullptr ? new types::int_type(*contents.i) : nullptr)
	, d(contents.d != nullptr ? new types::double_type(*contents.d) : nullptr)
	, b(contents.b != nullptr ? new types::bool_type(*contents.b) : nullptr)
	, s(contents.s != nullptr ? new types::string_type(*contents.s) : nullptr)
	, a(contents.a != nullptr ? new std::vector<banana>(*contents.a) : nullptr)
	, type(contents.type)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::__None& n) 
	: i(nullptr)
	, d(nullptr)
	, b(nullptr)
	, s(nullptr)
	, a(nullptr)
	, type(Type::None)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::__Array& a) 
	: i(nullptr)
	, d(nullptr)
	, b(nullptr)
	, s(nullptr)
	, a(new types::array_type(0))
	, type(Type::Integer)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::int_type& i)
	: i(new types::int_type(i))
	, d(nullptr)
	, b(nullptr)
	, s(nullptr)
	, a(nullptr)
	, type(Type::Integer)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::double_type& d)
	: i(nullptr)
	, d(new types::double_type(d))
	, b(nullptr)
	, s(nullptr)
	, a(nullptr)
	, type(Type::Double)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::bool_type& b)
	: i(nullptr)
	, d(nullptr)
	, b(new types::bool_type(b))
	, s(nullptr)
	, a(nullptr)
	, type(Type::Boolean)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::string_type& s)
	: i(nullptr)
	, d(nullptr)
	, b(nullptr)
	, s(new types::string_type(s))
	, a(nullptr)
	, type(Type::String)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::cstring_type& cs)
	: i(nullptr)
	, d(nullptr)
	, b(nullptr)
	, s(new types::string_type(cs))
	, a(nullptr)
	, type(Type::String)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::array_type& a)
	: i(nullptr)
	, d(nullptr)
	, b(nullptr)
	, s(nullptr)
	, a(new std::vector<banana>(a))
	, type(Type::Array)
{}

bnn::detail::Contents::Contents(const bnn::detail::types::init_list_type& il)
	: i(nullptr)
	, d(nullptr)
	, b(nullptr)
	, s(nullptr)
	, a(new std::vector<banana>(il))
	, type(Type::Array)
{}

bnn::detail::Contents::~Contents()
{}

#endif // !BNN_DETAIL_CONTENTS_INL