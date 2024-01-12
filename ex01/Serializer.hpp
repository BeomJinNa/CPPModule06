#pragma once
#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <cstdint>

struct Data;

class Serializer
{
	public:
		static uintptr_t	serialize(Data* ptr);
		static Data*		deserialize(uintptr_t raw);
		~Serializer(void);
	private:
		Serializer(void);
		Serializer(const Serializer& source);
		Serializer&	operator=(const Serializer& source);
};
#endif
