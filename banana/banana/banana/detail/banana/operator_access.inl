bnn::banana& bnn::banana::operator[](const int& i) {
	if (get_type() & banana::Type::Array)
		return contents.a->at(i);
	else
		throw detail::exceptions::use_error("operator[](const int&)", "array");
}

bnn::banana& bnn::banana::operator[](const std::string& key) {
	if (get_type() == banana::Type::Array) {
		auto len = size();
		for (size_t i = 0; i < len; i++)
			if ((contents.a->at(i).get_type() & banana::Type::Array) && (contents.a->at(i).size() == 2) && (std::string(contents.a->at(i)[0]) == key))
				return contents.a->at(i)[1];

		contents.a->push_back(banana({key, banana()}));
		return contents.a->at(len)[1];
	} else {
		throw detail::exceptions::use_error("operator[](const std::string&)", "array");
	}
}

bnn::banana& bnn::banana::operator[](const char* key) {
	return this->operator[](std::string(key));
}