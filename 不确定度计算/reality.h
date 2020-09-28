#pragma once
#include <iostream>
class reality
{
private:
	long double real;
	long effective_digits;	//非自然语义，1为精确到个位，-1为精确到十分位，永远不等于0，每多一位小数-1，反之同理
public:
	reality(const long effective_digits1 = LDBL_DIG, const long double real1 = 0);
	reality(const reality& node);
	bool set_effective_digits_natural(const long ed);		//输入为自然语义
	inline void set_effective_digits_inside(const long ed) { effective_digits = ed; recalculate_real(); }		//输入为程序内部语义
	inline long get_effective_digits_inside() const { return effective_digits; }		//返回程序内部语义的有效位数
	inline long double get_real() const { return real; }
	long get_effective_digits_natural() const;		//返回自然语义有效位数
	bool recalculate_real();	//根据有效位数重新计算值
	reality operator+(const reality& node) const;
	reality operator-(const reality& node) const;
	reality operator*(const reality& node) const;
	reality operator/(const reality& node) const;
	reality operator^(const long index) const;
	bool operator==(const reality& node)const;
};