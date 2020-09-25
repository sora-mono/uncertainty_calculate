#include "reality.h"
#include <string>
#include <cmath>

reality::reality(long effective_digits1, long double real1)
{
	real = real1;
	effective_digits = effective_digits1;
}

reality::reality(reality& node)
{
	real = node.real;
	effective_digits = node.effective_digits;
}

long reality::get_natural_digits() const
{
	char temp[20];
	snprintf(temp, 20, "%19lf", real);
	int i, j;
	for (i = 0, j = 0; i < 20; i++)
	{
		if (temp[i] == '.')
		{
			j = i;
			continue;
		}
		if (temp[i] != '.' && temp[i] != '0')
		{
			break;
		}
	}
	return j - i - effective_digits + 1;
}

bool reality::recalculate_real()
{
	long off = -effective_digits + 1;
	long double temp = real * pow(long double(10), off);
	long temp1 = long(temp + 1e-10);
	long last_digit = temp1 % 10;
	temp1 -= last_digit;
	temp -= last_digit;
	if (last_digit < 5)
	{
	}
	else if (last_digit > 5)
	{
		temp += 10;
	}
	else
	{
		if (temp1 % 100 % 20 == 10)
		{
			temp += 10;
		}
	}
	temp /= 10;
	real = temp;
	return true;
}

bool reality::set_effective_digits_natural(const long ed)
{
	long natural_digits = get_natural_digits();
	long pure_effective_digits = effective_digits;
	if (ed == natural_digits)
	{
		return true;
	}
	else if (ed > natural_digits)
	{
		effective_digits -= ed - natural_digits;
		if (pure_effective_digits > 0 && effective_digits <= 0)
		{
			effective_digits--;
		}
	}
	else
	{
		effective_digits += natural_digits - ed;
		if (pure_effective_digits < 0 && effective_digits >= 0)
		{
			effective_digits++;
		}
		recalculate_real();
	}
	return true;
}