#include "ComplexNumbers.h"

ComplexNumber complexSquare(ComplexNumber num)
{
	float a, b;
	a = num.re;
	b = num.im;

	num.re = a*a - b*b;
	num.im = 2 * a*b;

	return num;
}

ComplexNumber complexSum(ComplexNumber num1, ComplexNumber num2)
{
	ComplexNumber result;

	result.re = num1.re + num2.re;
	result.im = num1.im + num2.im;

	return result;
}

float complexNorm(ComplexNumber num)
{
	float norm = num.re*num.re + num.im*num.im;
	return norm;
}