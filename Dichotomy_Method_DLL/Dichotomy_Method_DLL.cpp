#include "Dichotomy_Method_DLL.h"
Dichotomy_Method::Dichotomy_Method() : I_Num_Method()
{
}
long double Dichotomy_Method::Solve(double(*Fun_ptr)(double), double a, double b, double eps, double x0, unsigned int& N)
{
	double t, f1, f2, x;
	do
	{
		f1 = Fun_ptr(a);
		t = (a + b) / 2.0;
		f2 = Fun_ptr(t);
		if (f1*f2 <= 0) b = t;
		else a = t;
		N++;
	} while (fabs(b - a)>eps);
	x = (a + b) / 2.0;
	return x;
}
I_Num_Method* GetMethod()
{
	I_Num_Method* ptr = nullptr;
	ptr = new Dichotomy_Method();
	return ptr;
}
