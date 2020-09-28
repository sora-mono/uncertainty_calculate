#pragma once
#include <iostream>
class reality
{
private:
	long double real;
	long effective_digits;	//����Ȼ���壬1Ϊ��ȷ����λ��-1Ϊ��ȷ��ʮ��λ����Զ������0��ÿ��һλС��-1����֮ͬ��
public:
	reality(const long effective_digits1 = LDBL_DIG, const long double real1 = 0);
	reality(const reality& node);
	bool set_effective_digits_natural(const long ed);		//����Ϊ��Ȼ����
	inline void set_effective_digits_inside(const long ed) { effective_digits = ed; recalculate_real(); }		//����Ϊ�����ڲ�����
	inline long get_effective_digits_inside() const { return effective_digits; }		//���س����ڲ��������Чλ��
	inline long double get_real() const { return real; }
	long get_effective_digits_natural() const;		//������Ȼ������Чλ��
	bool recalculate_real();	//������Чλ�����¼���ֵ
	reality operator+(const reality& node) const;
	reality operator-(const reality& node) const;
	reality operator*(const reality& node) const;
	reality operator/(const reality& node) const;
	reality operator^(const long index) const;
	bool operator==(const reality& node)const;
};