#include <cctype>
#include <iostream>
#include <sstream>
#include "ScalarConverter.hpp"

namespace
{
	eDetectedType	detectType(const std::string& input);
	void			printConvertedChar(const Value& input);
	template <typename T>
	void			printIfCharPrintable(T value);
	void			printConvertedInt(const Value& input);
	void			printConvertedFloat(const Value& input);
	void			printConvertedDouble(const Value& input);
}

void	ScalarConverter::Convert(const std::string& input)
{
	static const std::string	typeString[TYPE_NumberOfTypes]
		= {"char", "int", "float", "double", "inf", "-inf", "nan", "unknown"};
	Value	value;

	value.type = detectType(input);

	std::cout << "\033[33mDetected Type\033[32m " << typeString[value.type]
			  << "\033[0m" << std::endl;

	std::string	bufferString(input);
	if (value.type == TYPE_Float)
		bufferString.erase(bufferString.length() - 1);
	std::istringstream	iss(bufferString);

	if (iss.fail())
	{
		std::cerr << "converting error! (string stream)" << std::endl;
		return ;
	}

	switch (value.type)
	{
		case TYPE_Char:
			iss >> value.u_value.Char;
			break;
		case TYPE_Int:
			iss >> value.u_value.Int;
			break;
		case TYPE_Float:
			iss >> value.u_value.Float;
			break;
		case TYPE_Double:
			iss >> value.u_value.Double;
			break;
		default:
			break;
	}

	std::cout << "char: ";
	printConvertedChar(value);
	std::cout << "int: ";
	printConvertedInt(value);
	std::cout << "float: ";
	printConvertedFloat(value);
	std::cout << "double: ";
	printConvertedDouble(value);
}

namespace
{
	eDetectedType	detectType(const std::string& input)
	{
		static const std::string	specialCasesTable[8]
			= {"nan", "nanf", "inf", "+inf", "inff", "+inff", "-inf", "-inff"};
		static const eDetectedType	returnCasedTable[8]
			= {TYPE_NaN, TYPE_NaN, TYPE_Inf, TYPE_Inf, TYPE_Inf,
			   TYPE_Inf, TYPE_NegativeInf, TYPE_NegativeInf};
		std::string	converted = input;

		if (converted.length() == 1 && std::isdigit(converted[0]) == false)
			return (TYPE_Char);

		for (size_t i = 0; i < converted.length(); ++i)
			converted[i] = std::tolower(converted[i]);

		for (int i = 0; i < 8; ++i)
			if (converted == specialCasesTable[i])
				return (returnCasedTable[i]);

		eParsingStage	parsingStage = STAGE_0_Before_Number;
		for (size_t index = 0; index < converted.length(); ++index)
		{
			if (converted[index] != '.' && converted[index] != 'f'
			 && converted[index] != '+' && converted[index] != '-'
			 && std::isdigit(converted[index]) == false)
				return (TYPE_Unknown);

			if (parsingStage != STAGE_1_Before_Dot && converted[index] == '.')
				return (TYPE_Unknown);
			if (index != converted.length() - 1 && converted[index] == 'f')
				return (TYPE_Unknown);
			if (index != 0 && (converted[index] == '+' || converted[index] == '-'))
				return (TYPE_Unknown);

			if (parsingStage == STAGE_2_On_Dot && std::isdigit(converted[index]))
				parsingStage = STAGE_3_After_Dot;
			if (parsingStage == STAGE_1_Before_Dot && converted[index] == '.')
				parsingStage = STAGE_2_On_Dot;
			if (parsingStage == STAGE_0_Before_Number && std::isdigit(converted[index]))
				parsingStage = STAGE_1_Before_Dot;
		}

		if (parsingStage == STAGE_0_Before_Number || parsingStage == STAGE_2_On_Dot)
			return (TYPE_Unknown);
		if (converted[converted.length() - 1] == 'f')
			return (TYPE_Float);
		if (parsingStage == STAGE_1_Before_Dot)
			return (TYPE_Int);
		if (parsingStage == STAGE_3_After_Dot)
			return (TYPE_Double);

		return (TYPE_Unknown);
	}

	void	printConvertedChar(const Value& input)
	{
		switch (input.type)
		{
			case TYPE_Char:
				if (std::isprint(static_cast<unsigned char>(input.u_value.Char)))
					std::cout << input.u_value.Char << std::endl;
				else
					std::cout << "Non displayable" << std::endl;
				return ;
			case TYPE_Int:
				printIfCharPrintable<int>(input.u_value.Int);
				return ;
			case TYPE_Float:
				printIfCharPrintable<float>(input.u_value.Float);
				return ;
			case TYPE_Double:
				printIfCharPrintable<double>(input.u_value.Double);
				return ;
			default:
				std::cout << "impossible" << std::endl;
				return ;
		}
	}

	template <typename T>
	void printIfCharPrintable(T value)
	{
		if (static_cast<T>(std::numeric_limits<char>::min())
				<= value && value <=
				static_cast<T>(std::numeric_limits<char>::max()))
		{
			if (std::isprint(static_cast<unsigned char>(value)))
				std::cout << static_cast<char>(value) << std::endl;
			else
				std::cout << "Non displayable" << std::endl;
		}
		else
			std::cout << "impossible" << std::endl;
	}

	void	printConvertedInt(const Value& input)
	{
		switch (input.type)
		{
			case TYPE_Char:
				std::cout << static_cast<int>(input.u_value.Char) << std::endl;
				return ;
			case TYPE_Int:
				std::cout << input.u_value.Int << std::endl;
				return ;
			case TYPE_Float:
				if (static_cast<float>(std::numeric_limits<int>::min())
					<= input.u_value.Float && input.u_value.Float <=
					static_cast<float>(std::numeric_limits<int>::max()))
					std::cout << static_cast<int>(input.u_value.Float) << std::endl;
				else
					std::cout << "impossible" << std::endl;
				return ;
			case TYPE_Double:
				if (static_cast<double>(std::numeric_limits<int>::min())
					<= input.u_value.Double && input.u_value.Double <=
					static_cast<double>(std::numeric_limits<int>::max()))
					std::cout << static_cast<int>(input.u_value.Double) << std::endl;
				else
					std::cout << "impossible" << std::endl;
				return ;
			default:
				std::cout << "impossible" << std::endl;
				return ;
		}
	}

	void	printConvertedFloat(const Value& input)
	{
		switch (input.type)
		{
			case TYPE_Char:
				std::cout << static_cast<float>(input.u_value.Char) << std::endl;
				return ;
			case TYPE_Int:
				std::cout << static_cast<float>(input.u_value.Int) << std::endl;
				return ;
			case TYPE_Float:
				std::cout << input.u_value.Float << std::endl;
				return ;
			case TYPE_Double:
				if (static_cast<double>(std::numeric_limits<float>::min())
					<= input.u_value.Double && input.u_value.Double <=
					static_cast<double>(std::numeric_limits<float>::max()))
					std::cout << static_cast<float>(input.u_value.Double) << std::endl;
				else
					std::cout << "impossible" << std::endl;
				return ;
			case TYPE_Inf:
				std::cout << "inff" << std::endl;
				return ;
			case TYPE_NegativeInf:
				std::cout << "-inff" << std::endl;
				return ;
			case TYPE_NaN:
				std::cout << "nanf" << std::endl;
				return ;
			default:
				std::cout << "impossible" << std::endl;
				return ;
		}
	}

	void	printConvertedDouble(const Value& input)
	{
		switch (input.type)
		{
			case TYPE_Char:
				std::cout << static_cast<double>(input.u_value.Char) << std::endl;
				return ;
			case TYPE_Int:
				std::cout << static_cast<double>(input.u_value.Int) << std::endl;
				return ;
			case TYPE_Float:
				std::cout << static_cast<double>(input.u_value.Float) << std::endl;
				return ;
			case TYPE_Double:
				std::cout << input.u_value.Double << std::endl;
				return ;
			case TYPE_Inf:
				std::cout << "inf" << std::endl;
				return ;
			case TYPE_NegativeInf:
				std::cout << "-inf" << std::endl;
				return ;
			case TYPE_NaN:
				std::cout << "nan" << std::endl;
				return ;
			default:
				std::cout << "impossible" << std::endl;
				return ;
		}
	}
}

ScalarConverter::ScalarConverter(void) {}
ScalarConverter::ScalarConverter(const ScalarConverter& source) { (void)source; }
ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& source)
{ if (this != &source) {} return (*this); }
ScalarConverter::~ScalarConverter(void) {}
