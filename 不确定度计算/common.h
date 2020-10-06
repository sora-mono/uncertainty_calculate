#pragma once
#include"operation.h"

struct node
{
	int type;
	enum { OPERATOR, DIGIT, OPERATION, OPERATION_NODELETE };
	union
	{
		char op;
		int digit;
		operation* p;
	};
};

long max(long a, long b);

long min(long a, long b);

long double average_calculate(long double arr[], int size);

long double uncertain_measurement_calculate(long double arr[], long double avg, int size);

operation& input_set();

operation& input_one();

operation* get_object(char ch);

void delete_node(node* p);
