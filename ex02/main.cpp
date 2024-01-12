#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int	main(void)
{
	Data		test;
	uintptr_t	temp;
	Data*		ptr;

	test.data = 42;

	temp = Serializer::serialize(&test);
	ptr = Serializer::deserialize(temp);

	std::cout << "value : " << test.data << std::endl;
	std::cout << "value(ptr) : " << ptr->data << std::endl;

	return (0);
}
