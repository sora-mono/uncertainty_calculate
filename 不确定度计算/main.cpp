#include"operation.h"
#include"common.h"

using std::cout;
using std::endl;
using std::cin;

extern node**p;

int main()
{
	p = new node * [60];
	cout << "由于技术力有限（懒得继续折腾），本程序在输入算式步骤仅能接受一位数字" << endl;
	while (true)
	{
		operation& x = input_one();
		operation& y = input_one();
		cout << "x + y = \n" << x + y;
		cout << "x-y = \n" << x - y;
		cout << "x*y = \n" << x * y;
		cout << "x/y = \n" << x / y;
		cout << "3*y = \n" << 3 * y;
		cout << "x^1/3 = \n" << (x ^ (long double(1) / 3));
		cout << "lnx = \n" << ln(x);
		cout << "siny = \n" << sin(y);
	}
}