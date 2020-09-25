#include "uncertain.h"
#include<cmath>


uncertain::uncertain(long double uncertain_calculated1, long uncertain_fin1, long uncertain_fin_digits1, long double uncertain_instrument1, long double uncertain_measurement1)
{
	uncertain_calculated = uncertain_calculated1;
	uncertain_fin = uncertain_fin1;
	uncertain_fin_digits = uncertain_fin_digits1;
	uncertain_instrument = uncertain_instrument1;
	uncertain_measurement = uncertain_measurement1;
}

uncertain::uncertain(uncertain& node)
{
	uncertain_calculated = node.uncertain_calculated;
	uncertain_fin = node.uncertain_fin;
	uncertain_fin_digits = node.uncertain_fin_digits;
	uncertain_instrument = node.uncertain_instrument;
	uncertain_measurement = node.uncertain_measurement;
}

bool uncertain::uncertain_calculate()
{
	if (uncertain_measurement!=-1&&uncertain_instrument!=-1)
	{
		uncertain_calculated = sqrt(uncertain_measurement * uncertain_measurement + uncertain_instrument * uncertain_instrument / 3);
		return true;
		uncertain_measurement = uncertain_instrument = -1;
	}
	else
	{
		return false;
	}
}

bool uncertain::uncertain_calculated_cut()
{
	if (uncertain_calculated <0)
	{
		return false;
	}
	long double uncertain_calculated_temp = uncertain_calculated;
	long digit;
	if (uncertain_calculated_temp <1)
	{
		digit = 0;
		while (uncertain_calculated_temp<1)
		{
			uncertain_calculated_temp *= 10;
			digit--;
		}
	}
	else 
	{
		digit = 1;
		while (uncertain_calculated_temp>=10)
		{
			uncertain_calculated_temp /= 10;
			digit++;
		}
	}
	if (uncertain_calculated_temp-long(uncertain_calculated_temp)>1e-10)
	{
		uncertain_calculated_temp++;
		if (uncertain_calculated_temp >= 10)
		{
			digit++;
			uncertain_calculated_temp = 1;
		}
	}
	uncertain_fin = long(uncertain_calculated_temp+1e-10);
	uncertain_fin_digits = digit;
	uncertain_calculated = -1;
	return true;
}

bool uncertain::recalculate_uncertain(long digit)
{
	if (digit<=uncertain_fin_digits)
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