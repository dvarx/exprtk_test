#include <cstdio>
#include <string>
#include <exprtk.hpp>
#include <iostream>


template <typename T>
void trig_function()
{
	typedef exprtk::symbol_table<T> symbol_table_t;
	typedef exprtk::expression<T>     expression_t;
	typedef exprtk::parser<T>             parser_t;

	std::string expression_string = "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";

	T x;

	symbol_table_t symbol_table;
	symbol_table.add_variable("x", x);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);

	FILE* fptr;
	errno_t err=fopen_s(&fptr,"C:\\Users\\dvarx\\data.dat", "w");
	if (err!=0) {
		char buffer[256];
		strerror_s(buffer, 256, err);
		printf("An error occurred opening the file: %s",buffer);
	}

	for (x = T(-5); x <= T(+5); x += T(0.001))
	{
		T y = expression.value();
		fprintf_s(fptr,"%19.15f\t%19.15f\n", x, y);
	}

	fclose(fptr);
}

int main()
{
	trig_function<double>();
	printf("Hello");
	return 0;
}