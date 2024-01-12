#include "Serializer.hpp"
#include "Data.hpp"

uintptr_t	Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*	Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}

Serializer::Serializer(void) {}
Serializer::Serializer(const Serializer& source) { (void)source; }
Serializer&	Serializer::operator=(const Serializer& source) { if (this != &source) {} return (*this); }
Serializer::~Serializer(void) {}
