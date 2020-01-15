#include "Newton_Method_DLL.h"
Newton_Method::Newton_Method() : I_Num_Method()
{
}
long double Newton_Method::Solve(double(*Fun_ptr)(double), double a, double b, double eps, double x0, unsigned int& N)
{
	double x, df, h;
	x = x0;
	h = 0.001;	
	while(fabs(Fun_ptr(x)) >= eps)
	{
		df = (Fun_ptr(x + h) - Fun_ptr(x)) / h;
		x = x - Fun_ptr(x) / df;
		N++;
	}
	return x;
}
I_Num_Method* GetMethod()
{
	I_Num_Method* ptr = nullptr;
	ptr = new Newton_Method();
	return ptr;
}

