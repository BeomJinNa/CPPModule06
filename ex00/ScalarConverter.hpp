#pragma once
#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

class ScalarConverter
{
	public: ~ScalarConverter(void);

		static void	Convert(const std::string& input);
	private:
		ScalarConverter(void);
		ScalarConverter(const ScalarConverter& source);
		ScalarConverter&	operator=(const ScalarConverter& source);
};

enum eDetectedType
{
	TYPE_Char,
	TYPE_Int,
	TYPE_Float,
	TYPE_Double,
	TYPE_Inf,
	TYPE_NegativeInf,
	TYPE_NaN,
	TYPE_Unknown,
	TYPE_NumberOfTypes
};

enum eParsingStage
{
	STAGE_0_Before_Number,
	STAGE_1_Before_Dot,
	STAGE_2_On_Dot,
	STAGE_3_After_Dot
};

struct Value
{
	eDetectedType	type;
	union			ValueType
	{
		char		Char;
		int			Int;
		float		Float;
		double		Double;
	}				u_value;
};
#endif
