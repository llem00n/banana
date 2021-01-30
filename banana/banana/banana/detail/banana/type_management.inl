bnn::banana::Type bnn::banana::get_type() const {
	return type;
}

void bnn::banana::set_type(bnn::banana::Type type) {
	contents.set_type(type);
	this->type = type;
}