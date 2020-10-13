#pragma once
#include"operation.h"
#include"common.h"
#include<iostream>
#include<string>
#include<stack>

using std::stack;
using std::string;

class input_analysis
{
private:
	string str;
	bool str_to_reserve_polish_expression();
public:
	input_analysis(string str) { input_analysis::str = str; }
	input_analysis(char* str) { input_analysis::str = str; }
	node* calculate_reserve_polish_expression();
};

