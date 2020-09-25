#pragma once
#include <iostream>
class reality
{
private:
	long double real;
	long effective_digits;	//����Ȼ���壬1Ϊ��ȷ����λ��-1Ϊ��ȷ��ʮ��λ����Զ������0��ÿ��һλС��-1����֮ͬ��
public:
	reality(long effective_digits1 = LDBL_DIG, long double real1 = 0);
	reality(reality& node);
	bool set_effective_digits_natural(const long ed);		//����Ϊ��Ȼ����
	inline bool set_effective_digits_inside(const long ed) { effective_digits = ed; }		//����Ϊ�����ڲ�����
	inline long get_effective_digits() const { return effective_digits; }		//���س����ڲ��������Чλ��
	inline long double get_real() { return real; }
	long get_natural_digits() const;		//������Ȼ������Чλ��
	bool recalculate_real();	//������Чλ�����¼���ֵ
};