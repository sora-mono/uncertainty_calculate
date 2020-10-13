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

void delete_node(node* p)
{
	if (p->type != p->OPERATION_NODELETE)
	{
		delete p->p;
	}
	delete p;
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

node* analysis_input()
{
	string str;
	node* p = nullptr;
	cout << "请输入表达式" << endl;
	cout << "如果为赋值请输入如下形式（空格和制表符不影响输入）：" << endl << "A,-2 = 33.23+35.56+34.52|0.05 " << endl << "A,-2 = 33.42|0.01 " << endl;
	cout << "前者逗号后为精确程度，|后为仪器不确定度，等于号后为已有值" << endl;
	cout << "后者逗号后为精确程度，|左右两侧为真实值和不确定度" << endl;
	cout << "如果为计算请输入以下形式：A*B+C/D*k，前面可加\"A = \"字样";
	cin >> str;
	size_t index;
	while (index = str.find(' ') != string::npos)		//去除空格
	{
		str.replace(index, 1, "");
	}
	while (index = str.find('\t') != string::npos)	//去除制表符
	{
		str.replace(index, 1, "");
	}
	if (index = str.find(',') == string::npos)//没有逗号，是计算式
	{
		if (index = str.find('=') != string::npos)//有赋值操作
		{
			int index_temp = 0;
			string str_temp = str.substr(index + 1);
			input_analysis analysis_obj(str_temp);
			p = analysis_obj.calculate_reserve_polish_expression();
			p->type = p->OPERATION_NODELETE;
			get_object_space(str[0]) = p;	//给对应存储位置赋值
			cout << str[0] << " : " << *p->p << endl;
		}
		else	//没有赋值操作
		{
			input_analysis analysis_obj(str);
			p = analysis_obj.calculate_reserve_polish_expression();
			cout << "结果：" << *p->p << endl;
		}
	}
	else	//有逗号，是赋值式
	{
		if (str.find('+') == string::npos)//直接赋值表达式
		{
			char c;
			long effective_digits, fin_digits, fin;
			long double real, uncertain;
			sscanf_s(str.c_str(), "%c,%ld=%lf|%lf", &c, 1, &effective_digits, &real, &uncertain);
			get_uncertain_digits(uncertain, fin, fin_digits);
			node* p = new node;
			p->type = p->OPERATION_NODELETE;
			p->p = new operation(real, effective_digits, fin, fin_digits);
			get_object_space(c) = p;
			cout << c << " = " << *p->p << endl;
		}
		else	//给一串数字计算不确定度
		{
			char c;
			long effective_digits;
			long double temp_long_double, uncertain_measurement, uncertain_instrument, real;
			sscanf_s(str.c_str(), "%c,%ld", &c, 1, &effective_digits);
			sscanf_s(str.c_str(), "%*s|%lf", &uncertain_instrument);
			string str_format = "";
			vector<long double> vec;
			index = str.find('=');
			do
			{
				index++;
				sscanf_s(&str.c_str()[index], "%lf", &temp_long_double);
				vec.push_back(temp_long_double);
			} while (index = str.find('+', index + 1) != string::npos);
			real = average_calculate(vec);
			uncertain_measurement = uncertain_measurement_calculate(vec);
			node* p = new node;
			p->type = p->OPERATION_NODELETE;
			p->p = new operation(real, effective_digits, uncertain_instrument, uncertain_measurement);
			get_object_space(c) = p;
			cout << c << " = " << *p->p << endl;
		}
	}
	return p;
}

void get_uncertain_digits(long double uncertain, long& fin, long& fin_digits)
{
	fin_digits = 0;
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