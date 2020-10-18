#include<iostream>
#include<vector>
#include "common.h"
#include"operation.h"
#include"input_analysis.h"

using namespace std;

node** variables;
extern const long variables_size = 256;

long max(long a, long b)
{
	return a > b ? a : b;
}

long min(long a, long b)
{
	return a < b ? a : b;
}

long double average_calculate(vector<long double>& vec)
{
	long double sum = 0;
	for (size_t i = 0; i < vec.size(); i++)
	{
		sum += vec[i];
	}
	return sum / vec.size();
}


long double uncertain_measurement_calculate(vector<long double>& vec)
{
	long double avg = average_calculate(vec);
	long double sum = 0;
	for (size_t i = 0; i < vec.size(); i++)
	{
		sum += pow(vec[i] - avg, 2);
	}
	sum /= long double(vec.size()) * (long double(vec.size()) - 1);
	return sqrt(sum);
}

operation*& get_object(char ch)
{
	return variables[ch - 'A']->p;
}

node*& get_object_space(char ch)
{
	return variables[ch - 'A'];
}

void delete_node(node*& p)
{
	if (p != nullptr && p->type == p->OPERATION)
	{
		delete p->p;
	}
	delete p;
	p = nullptr;
}

//void show()
//{
//	for (int i = 0; i < variables_size; i++)
//	{
//		if (variables[i]->)
//		{
//
//		}
//	}
//}

void help()
{
	cout << endl;
	cout << "\t\t\t\t\t������ȷ���ȼ���v1.0.0����" << endl;
	cout << "*����\"h\"��\"help\"��\"����\"�Ի�ȡ����" << endl;
	cout << "*����clear����������Ѵ洢����" << endl;
	//cout << "����show����ʾ�����Ѵ������" << endl;
	cout << "*���ڼ��������ޣ����ü������ڻ�������stl�Ĺ�ϣ������������õı�ʶ��Ϊ26����ĸ��Сд" << endl;
	cout << "*���Ϊ��ֵ������������ʽ���ո���Ʊ����Ӱ�����룩��" << endl;
	cout << " A,-2 = 33.23+35.56+34.52|0.05 " << endl;
	cout << " A,-2 = 33.42|0.01 " << endl;
	cout << "*ǰ�߶��ź�Ϊ��ȷ�̶ȣ�|��Ϊ������ȷ���ȣ����ںź�Ϊ����ֵ" << endl;
	cout << "*���߶��ź�Ϊ��ȷ�̶ȣ�|��������Ϊ��ʵֵ�Ͳ�ȷ����" << endl;
	cout << "*���Ϊ����������������ʽ��A*B+C/D*k��ǰ��ɼ�\"A = \"����" << endl;
	cout << "!!!���棬������֧�������ǲ�ȷ�������г˷����������" << endl;
	cout << endl << "\t\t\t\t\t\t\t\t\t\t\t����sora_mono" << endl;
	cout << endl;
}

node* analysis_input()
{
	string str;
	node* p = nullptr;
	cout << "��������ʽ" << endl << ">";
	getline(cin, str);
	if (str == "h" | str == "help" || str == "����")
	{
		help();
		return nullptr;
	}
	if (str == "clear")
	{
		clear_object_space();
		return nullptr;
	}
	size_t index;
	while ((index = str.find(' ')) != string::npos)		//ȥ���ո�
	{
		str.replace(index, 1, "");
	}
	while ((index = str.find('\t')) != string::npos)	//ȥ���Ʊ��
	{
		str.replace(index, 1, "");
	}
	if (index = str.find('|') == string::npos)//û��'|'���Ǽ���ʽ
	{
		if (index = str.find('=') != string::npos)//�и�ֵ����
		{
			int index_temp = 0;
			string str_temp = str.substr(index + 1);
			input_analysis analysis_obj(str_temp);
			p = analysis_obj.calculate_reserve_polish_expression();
			p->type = p->OPERATION_NODELETE;
			p->remark = str[0];
			delete_node(get_object_space(str[0]));
			get_object_space(str[0]) = p;	//����Ӧ�洢λ�ø�ֵ
			cout << str[0] << " : " << *p->p << endl;
		}
		else	//û�и�ֵ����
		{
			input_analysis analysis_obj(str);
			p = analysis_obj.calculate_reserve_polish_expression();
			cout << "�����" << *p->p << endl;
		}
	}
	else	//��'|'���Ǹ�ֵʽ
	{
		if (str.find('+') == string::npos)//ֱ�Ӹ�ֵ���ʽ
		{
			char c;
			long effective_digits, fin_digits, fin;
			long double real, uncertain;
			sscanf_s(str.c_str(), "%c,%ld=%lf|%lf", &c, 1, &effective_digits, &real, &uncertain);
			get_uncertain_digits(uncertain, fin, fin_digits);
			p = new node;
			p->type = p->OPERATION_NODELETE;
			p->p = new operation(real, effective_digits, fin, fin_digits);
			p->remark = str[0];
			delete_node(get_object_space(c));
			get_object_space(c) = p;
			cout << c << " : " << *p->p << endl;
		}
		else	//��һ�����ּ��㲻ȷ����
		{
			char c;
			long effective_digits;
			long double temp_long_double, uncertain_measurement, uncertain_instrument, real;
			sscanf_s(str.c_str(), "%c,%ld", &c, 1, &effective_digits);
			sscanf_s(str.c_str(), "%*[^|]|%lf", &uncertain_instrument);
			string str_format = "";
			vector<long double> vec;
			index = str.find('=');
			do
			{
				index++;
				sscanf_s(&str.c_str()[index], "%lf", &temp_long_double);
				vec.push_back(temp_long_double);
			} while ((index = str.find('+', index)) != string::npos);
			real = average_calculate(vec);
			uncertain_measurement = uncertain_measurement_calculate(vec);
			p = new node;
			p->type = p->OPERATION_NODELETE;
			p->p = new operation(real, effective_digits, uncertain_instrument, uncertain_measurement);
			p->remark = str[0];
			delete_node(get_object_space(c));
			get_object_space(c) = p;
			cout << c << " : " << *p->p << endl;
		}
	}
	return p;
}

void get_uncertain_digits(long double uncertain, long& fin, long& fin_digits)
{
	fin_digits = uncertain >= 1 ? 1 : 0;
	uncertain += 1e-8;
	while (uncertain >= 10)
	{
		uncertain /= 10;
		fin_digits++;
	}
	while (uncertain < 1)
	{
		uncertain *= 10;
		fin_digits--;
	}
	fin = long(uncertain + 1e-8);
}

void clear_object_space()
{
	for (int i = 0; i < variables_size; i++)
	{
		delete_node(variables[i]);
	}
}