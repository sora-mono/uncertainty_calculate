#pragma once
#include"operation.h"
#include<string>
#include<vector>

using namespace std;

struct node
{
	int type;
	enum { OPERATOR, DIGIT, OPERATION, OPERATION_NODELETE, DIGIT_NODELETE };
	string remark;
	long double digit = 0;
	operation* p = nullptr;
};

long max(long a, long b);

long min(long a, long b);

long double average_calculate(vector<long double>& vec);

long double uncertain_measurement_calculate(vector<long double>& vec);

operation*& get_object(char ch);

node*& get_object_space(char ch);

void delete_node(node*& p);

void help();

node* analysis_input();

void get_uncertain_digits(long double uncertain, long& fin, long& fin_digits);

void clear_object_space();
