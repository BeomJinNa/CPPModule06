#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"

int	main(void)
{
	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < 15; ++i)
	{
		Base* base = generate();

		std::cout << "Test " << i << std::endl;
		std::cout << "Pointer : ";
		identify(base);
		std::cout << "Reference : ";
		identify(*base);

		delete base;
	}

	return (0);
}
