#pragma once
#include <iostream>
class reality
{
private:
	long double real;
	long effective_digits;	//非自然语义，1为精确到个位，-1为精确到十分位，永远不等于0，每多一位小数-1，反之同理
public:
	reality(long effective_digits1 = LDBL_DIG, long double real1 = 0);
	reality(reality& node);
	bool set_effective_digits_natural(const long ed);		//输入为自然语义
	inline bool set_effective_digits_inside(const long ed) { effective_digits = ed; }		//输入为程序内部语义
	inline long get_effective_digits() const { return effective_digits; }		//返回程序内部语义的有效位数
	inline long double get_real() { return real; }
	long get_natural_digits() const;		//返回自然语义有效位数
	bool recalculate_real();	//根据有效位数重新计算值
};