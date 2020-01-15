//для корректной сборки решения необходимо указать путь к папке с файлом I_Num_Method.h в:"Свойства Проекта->C/C++->Общие->Дополнительные каталоги включаемых файлов"
//для каждого из проектов: Dichotomy_Method_DLL, Newton_Method_DLL, Secant_Method_DLL
// предполагается, что выбор начального приближения (отрезка) осуществляется пользователем, например, при помощи графиков функций в файле grafs.png
#include <iostream>
#include <windows.h>
#include "I_Num_Method.h"
#define _GET_METHOD_NAME "GetMethod"
typedef I_Num_Method* (*GETMETHOD)();
using std::cin;
using std::cout;
using std::endl;
double Fun1(double x)
{
	return log10(x) + 2 * x - 5;
}
double Fun2(double x)
{
	return sin(x) + log(x);
}
double Fun3(double x)
{
	return log10(2 * x) - (1 / x);
}
double Fun4(double x)
{
	return pow(2, -x) + 0.5*x*x - 10;
}
double Fun5(double x)
{
	return cos(x) + log(x);
}
int main()
{
	HINSTANCE hinstLib = NULL;//дескриптор dll
	GETMETHOD Get_Method = NULL;//указатель, содержащий адрес функции, возвращающей объект производного класса (соотв. численный метод)
	I_Num_Method* method = nullptr;//указатель на базовый класс
	char com, subcom;// переменные, хранящие выбор метода и функции
	double a, b, eps, x0;//границы отрезка, точность, начальное приближение
	double X1, X2, Y1, Y2;// значение найденного корня, значение уточненного корня(для определения погрешности), F(X1), F(X2) соответственно
	unsigned int N; // число выполненных итераций
	double(*Fun_ptr)(double) = nullptr;//указатель на выбранную функцию f(x)
	cout.precision(10);
	do
	{
		cout << "1-Newton_Method_DLL" << endl
			 << "2-Secant_Method_DLL" << endl
			 << "3-Dichotomy_Method_DLL" << endl
			 << "4-Exit" << endl;
		(cin >> com).get();
		//загрузка выбранной dll:
		if (com == '1')
		{
			hinstLib = LoadLibrary(TEXT("Newton_Method_DLL"));
		}
		if (com == '2')
		{
			hinstLib = LoadLibrary(TEXT("Secant_Method_DLL"));
		}
		if (com == '3')
		{
			hinstLib = LoadLibrary(TEXT("Dichotomy_Method_DLL"));
		}
		if(hinstLib != NULL)
		{
			Get_Method = (GETMETHOD)GetProcAddress(hinstLib, _GET_METHOD_NAME);//получение адреса функции
			method = Get_Method();//получение объекта
			do
			{
				a = 0;
				b = 0;
				eps = 0;
				x0 = 0;
				N = 0;
				Fun_ptr = nullptr;
				cout <<"1 - f1: log10(x) + 2 * x - 5" << endl
					<< "2 - f2: sin(x) + log(x)" << endl
					<< "3 - f3: log10(2 * x) - (1 / x)" << endl
					<< "4 - f4: pow(2, -x) + 0.5*x*x - 10" << endl
					<< "5 - f5: cos(x) + log(x)" << endl
					<< "6 - Free Library" << endl;
				(cin >> subcom).get();
				if (com == '1' && subcom != '6')//для метода Ньютона требуется ввод начального приближения
				{
					cout << "x0 ";
					(cin >> x0).get();
					cout << "eps ";
					(cin >> eps).get();
				}
				if ((com == '2' || com == '3') && subcom != '6')// ввод границ отрезка
				{
					cout << "a ";
					(cin >> a).get();
					cout << "b ";
					(cin >> b).get();
					cout << "eps ";
					(cin >> eps).get();
				}				
				switch (subcom)//присваивание указателю адреса выбранной функции
				{
				case '1':
					Fun_ptr = &Fun1;
					break;
				case '2':
					Fun_ptr = &Fun2;
					break;
				case '3':
					Fun_ptr = &Fun3;
					break;
				case '4':
					Fun_ptr = &Fun4;
					break;
				case '5':
					Fun_ptr = &Fun5;
					break;
				default:
					Fun_ptr = nullptr;
				};				
				if (Fun_ptr != nullptr)
				{
					X1 = method->Solve(Fun_ptr, a, b, eps, x0, N);//получение корня
					Y1 = Fun_ptr(X1);
					cout << endl
						<< "X1 = " << X1 << endl
						<< "Y1 =" << Y1 << endl
						<< "N = " << N << endl;
					//уточнение корня:
					a = X1 - (eps + 1e-12);//границы отрезка-окрестность найденного корня
					b = X1 + (eps + 1e-12);//
					eps = eps * eps;//увеличение требуемой точности
					x0 = X1;//за начальное приближение берется найденный корень
					X2 = method->Solve(Fun_ptr, a, b, eps, x0, N);// получение уточненного корня
					Y2 = Fun_ptr(X2);
					// оценка разности X1 и "истинного" значения
					cout << "X2 = " << X2 << endl
						<< "X2 - X1 = " << fabs( fabs(X2) - fabs(X1) ) << endl
						<< "Y2 ="  << Y2 << endl
						<< "Y2 - Y1 = " << fabs(fabs(Y2) - fabs(Y1)) << endl						
						<< endl;
				}
			} while (subcom != '6');
			delete method; // освобождение ресурсов, выделенных под объект
			FreeLibrary(hinstLib);//выгрузка библиотеки
			hinstLib = NULL;
		}
		else if(com != '4')
		{
			cout << "cant find dll!" << endl;
		}		
	} while (com != '4');
	system("pause");
	return 0;
}

