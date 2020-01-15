#pragma once
#include"I_Num_Method.h"
class Newton_Method : public I_Num_Method
{
public:
	Newton_Method();
	__declspec(dllexport) virtual long double Solve(double(*Fun_ptr)(double), double a, double b, double eps, double x0, unsigned int& N);
};
extern "C" __declspec(dllexport) I_Num_Method* GetMethod();