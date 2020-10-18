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
	cout << "\t\t\t\t\t——不确定度计算v1.0.0——" << endl;
	cout << "*输入\"h\"或\"help\"或\"帮助\"以获取帮助" << endl;
	cout << "*输入clear以清除所有已存储变量" << endl;
	//cout << "输入show以显示所有已储存变量" << endl;
	cout << "*由于技术力有限（懒得继续折腾还不会用stl的哈希表），本程序可用的标识符为26个字母大小写" << endl;
	cout << "*如果为赋值请输入如下形式（空格和制表符不影响输入）：" << endl;
	cout << " A = 33.23+35.56+34.52|0.05 " << endl;
	cout << " A = 33.42|0.01 " << endl;
	cout << "*前者|左侧为测量数据，右侧为仪器不确定度" << endl;
	cout << "*后者|左侧为真实值，右侧为不确定度" << endl;
	cout << "*如果为计算请输入以下形式：A*B+C/D*k，前面可加\"A = \"字样" << endl;
	cout << "!!!警告，本程序暂不支持两个非不确定量进行乘法以外的运算" << endl;
	cout << endl << "\t\t\t\t\t\t\t\t\t\t\t——sora_mono" << endl;
	cout << endl;
}

node* analysis_input()
{
	string str;
	node* p = nullptr;
	cout << "请输入表达式" << endl << ">";
	getline(cin, str);
	if (str == "h" | str == "help" || str == "帮助")
	{
		help();
		return nullptr;
	}
	if (str == "clear")
	{
		clear_object_space();
		return nullptr;
	}
	//if (str == "show")
	//{
	//	show();
	//	return nullptr;
	//}
	size_t index;
	while ((index = str.find(' ')) != string::npos)		//去除空格
	{
		str.replace(index, 1, "");
	}
	while ((index = str.find('\t')) != string::npos)	//去除制表符
	{
		str.replace(index, 1, "");
	}
	if (index = str.find('|') == string::npos)//没有'|'
	{
		if (index = str.find('=') != string::npos)//有赋值操作
		{
			bool is_operation = false;
			for (size_t i = 0; i < str.length(); i++)	//判断是否出现运算符，以确定为赋值语句还是表达式
			{
				switch (str[i])
				{
				case'+':
				case'-':
				case'*':
				case'/':
				case'^':is_operation = true;
				default:
					break;
				}
			}
			if (is_operation)
			{
				int index_temp = 0;
				string str_temp = str.substr(index + 1);
				input_analysis analysis_obj(str_temp);
				p = analysis_obj.calculate_reserve_polish_expression();
				p->remark = str[0];
				delete_node(get_object_space(str[0]));
				get_object_space(str[0]) = p;	//给对应存储位置赋值
				cout << str[0] << " : ";
				if (p->type == p->DIGIT||p->type == p->DIGIT_NODELETE)
				{
					cout << p->digit << endl;
				}
				else
				{
					cout <<endl<< *p->p << endl;
				}
			}
			else
			{
				p = new node;
				p->type = p->DIGIT_NODELETE;
				char c;
				sscanf_s(str.c_str(), "%c=%lf", &c,1, &p->digit);
				p->remark = c;
				get_object_space(c) = p;
				cout << c << " : " << p->digit << endl;
			}
		}
		else	//没有赋值操作
		{
				input_analysis analysis_obj(str);
				p = analysis_obj.calculate_reserve_polish_expression();
				cout << "结果：";
				if (p->type == p->DIGIT || p->type == p->DIGIT_NODELETE)
				{
					cout << p->digit << endl;
				}
				else
				{
					cout <<endl<< *p->p << endl;
				}
		}
	}
	else	//有'|'，是赋值式
	{
		if (str.find('+') == string::npos)//直接赋值表达式
		{
			char c;
			long effective_digits, fin_digits, fin;
			long double real, uncertain;
			sscanf_s(str.c_str(), "%c=%lf|%lf", &c, 1, &real, &uncertain);
			get_uncertain_digits(uncertain, fin, fin_digits);
			effective_digits = fin_digits;
			p = new node;
			p->type = p->OPERATION_NODELETE;
			p->p = new operation(real, effective_digits, fin, fin_digits);
			p->remark = str[0];
			delete_node(get_object_space(c));
			get_object_space(c) = p;
			cout << c << " : " << *p->p << endl;
		}
		else	//给一串数字计算不确定度
		{
			char c;
			long effective_digits,fin;
			long double temp_long_double, uncertain_measurement_calculated, uncertain_instrument, real;
			c = str[0];
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
			uncertain_measurement_calculated = uncertain_measurement_calculate(vec);
			get_uncertain_digits(uncertain_instrument, fin, effective_digits);	//获取精确度
			p = new node;
			p->type = p->OPERATION_NODELETE;
			p->p = new operation(real, effective_digits, uncertain_instrument, uncertain_measurement_calculated);
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