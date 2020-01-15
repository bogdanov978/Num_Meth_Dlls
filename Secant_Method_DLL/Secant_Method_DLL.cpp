#include "Secant_Method_DLL.h"
Secant_Method::Secant_Method() : I_Num_Method()
{
}
long double Secant_Method::Solve(double(*Fun_ptr)(double), double a, double b, double eps, double x0, unsigned int& N)
{
	while (fabs(b - a) >= eps)
	{
		N++;
		a = b - (b - a) * Fun_ptr(b) / (Fun_ptr(b) - Fun_ptr(a));
		b = a + (a - b) * Fun_ptr(a) / (Fun_ptr(a) - Fun_ptr(b));
	}
	return b;
}
I_Num_Method* GetMethod()
{
	I_Num_Method* ptr = nullptr;
	ptr = new Secant_Method();
	return ptr;
}


