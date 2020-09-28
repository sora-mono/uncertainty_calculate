#include"uncertain.h"
#include"common.h"
#include<cmath>
#include<iostream>

using std::cout;
using std::endl;

uncertain::uncertain(const long uncertain_fin1, const  long uncertain_fin_digits1, const long double uncertain_calculated1, const  long double uncertain_instrument1, const long double uncertain_measurement1)
{
	uncertain_calculated = uncertain_calculated1;
	uncertain_fin = uncertain_fin1;
	uncertain_fin_digits = uncertain_fin_digits1;
	uncertain_instrument = uncertain_instrument1;
	uncertain_measurement = uncertain_measurement1;
	if (uncertain_fin == -1)
	{
		if (!uncertain_calculate())
		{
			cout << "不确定度计算出错，请检查输入数值" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

uncertain::uncertain(const uncertain& node)
{
	uncertain_calculated = node.uncertain_calculated;
	uncertain_fin = node.uncertain_fin;
	uncertain_fin_digits = node.uncertain_fin_digits;
	uncertain_instrument = node.uncertain_instrument;
	uncertain_measurement = node.uncertain_measurement;
}

bool uncertain::uncertain_calculate()
{
	if (uncertain_measurement != -1 && uncertain_instrument != -1)
	{
		uncertain_calculated = sqrt(uncertain_measurement * uncertain_measurement + uncertain_instrument * uncertain_instrument / 3);
		uncertain_measurement = uncertain_instrument = -1;
	}
	if (!uncertain_calculated_cut())
	{
		cout << "不确定度近似过程出错，请检查输入数据" << endl;
		exit(EXIT_FAILURE);
	}
	else return true;
}

bool uncertain::uncertain_calculated_cut()
{
	if (uncertain_calculated < 0)
	{
		return false;
	}
	long double uncertain_calculated_temp = uncertain_calculated;
	long digit;
	if (uncertain_calculated_temp < 1)
	{
		digit = 0;
		while (uncertain_calculated_temp < 1)
		{
			uncertain_calculated_temp *= 10;
			digit--;
		}
	}
	else
	{
		digit = 1;
		while (uncertain_calculated_temp >= 10)
		{
			uncertain_calculated_temp /= 10;
			digit++;
		}
	}
	if (uncertain_calculated_temp - long(uncertain_calculated_temp) > 1e-10)
	{
		uncertain_calculated_temp++;
		if (uncertain_calculated_temp >= 10)
		{
			digit++;
			uncertain_calculated_temp = 1;
		}
	}
	uncertain_fin = long(uncertain_calculated_temp + 1e-10);
	uncertain_fin_digits = digit;
	uncertain_calculated = -1;
	return true;
}

bool uncertain::recalculate_uncertain(const long digit)
{
	if (digit <= uncertain_fin_digits)
	{
		return true;
	}
	else
	{
		uncertain_fin = 1;
		uncertain_fin_digits = digit;
		return true;
	}
}

uncertain uncertain::operator*(const long double k)const
{
	return uncertain(-1, -1, k * uncertain_fin * pow(10, uncertain_fin_digits)+1e-10);
}

uncertain operator*(const long double k, const uncertain& node)
{
	return node.operator*(k);
}

bool uncertain::operator==(const uncertain& node)const
{
	if (uncertain_fin_digits == node.uncertain_fin_digits &&abs(uncertain_fin-node.uncertain_fin)<=1e-8)
	{
		return true;
	}
	else
	{
		return false;
	}
}