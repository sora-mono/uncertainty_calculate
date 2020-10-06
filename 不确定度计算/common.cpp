#include<iostream>
#include "common.h"
#include"operation.h"

using namespace std;

node** p;

long max(long a, long b)
{
	return a > b ? a : b;
}

long min(long a, long b)
{
	return a < b ? a : b;
}

long double average_calculate(long double arr[], int size)
{
	long double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}
	return sum / size;
}


long double uncertain_measurement_calculate(long double arr[], long double avg, int size)
{
	long double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += pow(arr[i] - avg, 2);
	}
	sum /= long double(size) * (long double(size) - 1);
	return sqrt(sum);
}

operation& input_set()
{
	cout << "请输入数据数量" << endl;
	long num;
	cin >> num;
	long double* temp = new long double[num];
	cout << "请输入精确程度" << endl << "精确到个位请输入1，十分位请输入-1，以此类推" << endl;
	long effective_digits_inside;
	cin >> effective_digits_inside;
	cout << "请输入仪器不确定度" << endl;
	long double uncertain_instrument;
	cin >> uncertain_instrument;
	cout << "请输入测量数据" << endl;
	for (long i = 0; i < num; i++)
	{
		cin >> temp[i];
	}
	long double avg = average_calculate(temp, num);
	long double uncertain_measurement = uncertain_measurement_calculate(temp, avg, num);
	operation* k = new operation(avg, effective_digits_inside, uncertain_instrument, uncertain_measurement);
	delete[]temp;
	return *k;
}

operation& input_one()
{
	cout << "请输入您的输入模式，1为输入真实值、真实值精确程度、测量不确定度、仪器不确定度；2为输入真实值、真实值精确程度、计算完成的不确定度、不确定度精确程度" << endl;
	cout << "精确到个位为1，十分位为-1，以此类推" << endl;
	int choice;
	long double real, uncertain_measurement, uncertain_instrument;
	long effective_digits;
	operation* k = nullptr;
	do
	{
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "请输入真实值、真实值精确程度、测量不确定度、仪器不确定度" << endl;
			cin >> real >> effective_digits >> uncertain_measurement >> uncertain_instrument;
			k = new operation(real, effective_digits, uncertain_instrument, uncertain_measurement);
			break;
		case 2:
			cout << "请输入真实值、真实值精确程度、计算完成的不确定度(仅输入一位数字）、不确定度精确程度" << endl;
			long uncertain_fin, uncertain_digits;
			cin >> real >> effective_digits >> uncertain_fin >> uncertain_digits;
			k = new operation(real, effective_digits, uncertain_fin, uncertain_digits);
			break;
		default:
			cout << "请选择程序支持的选项！！！";
			choice = -1;
		}
	} while (choice == -1);
	return *k;
}

operation* get_object(char ch)
{
	return p[ch - 'A']->p;
}

void delete_node(node* p)
{
	if (p->type!=p->OPERATION_NODELETE)
	{
		delete p->p;
	}
	delete p;
}