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
	cout << "��������������" << endl;
	long num;
	cin >> num;
	long double* temp = new long double[num];
	cout << "�����뾫ȷ�̶�" << endl << "��ȷ����λ������1��ʮ��λ������-1���Դ�����" << endl;
	long effective_digits_inside;
	cin >> effective_digits_inside;
	cout << "������������ȷ����" << endl;
	long double uncertain_instrument;
	cin >> uncertain_instrument;
	cout << "�������������" << endl;
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
	cout << "��������������ģʽ��1Ϊ������ʵֵ����ʵֵ��ȷ�̶ȡ�������ȷ���ȡ�������ȷ���ȣ�2Ϊ������ʵֵ����ʵֵ��ȷ�̶ȡ�������ɵĲ�ȷ���ȡ���ȷ���Ⱦ�ȷ�̶�" << endl;
	cout << "��ȷ����λΪ1��ʮ��λΪ-1���Դ�����" << endl;
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
			cout << "��������ʵֵ����ʵֵ��ȷ�̶ȡ�������ȷ���ȡ�������ȷ����" << endl;
			cin >> real >> effective_digits >> uncertain_measurement >> uncertain_instrument;
			k = new operation(real, effective_digits, uncertain_instrument, uncertain_measurement);
			break;
		case 2:
			cout << "��������ʵֵ����ʵֵ��ȷ�̶ȡ�������ɵĲ�ȷ����(������һλ���֣�����ȷ���Ⱦ�ȷ�̶�" << endl;
			long uncertain_fin, uncertain_digits;
			cin >> real >> effective_digits >> uncertain_fin >> uncertain_digits;
			k = new operation(real, effective_digits, uncertain_fin, uncertain_digits);
			break;
		default:
			cout << "��ѡ�����֧�ֵ�ѡ�����";
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