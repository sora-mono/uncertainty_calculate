#include"operation.h"
#include"common.h"
#include<vector>

using std::cout;
using std::endl;
using std::cin;

extern node** variables;
extern const long variables_size;

int main()
{
	variables = new node * [variables_size];
	cout << "由于技术力有限（懒得继续折腾），本程序在输入算式步骤仅能接受一位数字，可用的标识符为26个字母大小写" << endl;
	for (int i = 0; i < variables_size; i++)
	{
		variables[i] = nullptr;
	}
	while (true)
	{
		node*p = analysis_input();
		if (p->type!=p->OPERATION_NODELETE)
		{
			delete p;
		}
	}
}