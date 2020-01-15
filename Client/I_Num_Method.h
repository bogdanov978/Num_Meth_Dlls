#pragma once
#include <cmath>
class I_Num_Method
{
public:
	virtual ~I_Num_Method()
	{}
	virtual long double Solve(double(*Fun_ptr)(double), double a, double b, double eps, double x0, unsigned int& N) = 0;
};