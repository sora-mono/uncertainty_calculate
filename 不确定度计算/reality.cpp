#include "reality.h"
#include "common.h"
#include <string>
#include <cmath>

reality::reality(const long effective_digits1, const long double real1)
{
	real = real1;
	effective_digits = effective_digits1;
}

reality::reality(const reality& node)
{
	real = node.real;
	effective_digits = node.effective_digits;
}

long reality::get_effective_digits_natural() const
{
	char temp[20];
	snprintf(temp, 20, "%.12lf", real);
	int i, j, k = -1;
	for (i = 0, j = 0; i < 20 && temp[i] != '\0'; i++)
	{
		if (temp[i] == '.')
		{
			j = i;
			continue;
		}
		if (k == -1 && temp[i] != '.' && temp[i] != '0'&& temp[i]!='-')
		{
			k = i;
		}
	}
	return k < j&& effective_digits < 0 ? j - k - effective_digits : j - k - effective_digits + 1;
}

bool reality::recalculate_real()
{
	long off = effective_digits > 0 ? 2 - effective_digits : 1 - effective_digits;
	long double temp = real * pow(long double(10), off);
	temp > 0 ? temp += 1e-10 : temp -= 1e-10;
	long temp1 = long(temp);
	long last_digit = temp1 % 10;
	temp1 -= last_digit;
	if (last_digit < 5)
	{
	}
	else if (last_digit > 5)
	{
		temp1 += 10;
	}
	else
	{
		if (temp1 % 100 % 20 == 10)
		{
			temp1 += 10;
		}
	}
	real = temp1 * pow(long double(10), -off);
	return true;
}

bool reality::set_effective_digits_natural(const long ed)
{
	long natural_digits = get_effective_digits_natural();
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

reality reality::operator+(const reality& node) const
{
	long this_effective_digits_inside = get_effective_digits_inside();
	long node_effective_digits_inside = node.get_effective_digits_inside();
	if (this_effective_digits_inside == node_effective_digits_inside)
	{
		return reality(-99, real + node.real);
	}
	else
	{
		reality temp = reality(-99, real + node.real);
		//temp.recalculate_real();
		return temp;
	}
}

reality reality::operator-(const reality& node) const
{
	long this_effective_digits_inside = get_effective_digits_inside();
	long node_effective_digits_inside = node.get_effective_digits_inside();
	if (this_effective_digits_inside == node_effective_digits_inside)
	{
		return reality(-99, real - node.real);
	}
	else
	{
		reality temp = reality(-99, real - node.real);
		//temp.recalculate_real();
		return temp;
	}
}

reality reality::operator*(const reality& node)const
{
	long this_effective_digits_natural = get_effective_digits_natural();
	long node_effective_digits_natural = node.get_effective_digits_natural();
	reality temp = reality(-99, real * node.real);
	//temp.set_effective_digits_natural(min(this_effective_digits_natural, node_effective_digits_natural));
	return temp;
}

reality reality::operator/(const reality& node)const
{
	long this_effective_digits_natural = get_effective_digits_natural();
	long node_effective_digits_natural = node.get_effective_digits_natural();
	reality temp = reality(-99, real / node.real);
	//temp.set_effective_digits_natural(min(this_effective_digits_natural, node_effective_digits_natural));
	return temp;
}

reality reality::operator^(const long index)const
{
	reality temp = reality(get_effective_digits_inside(), pow(real, index));
	//long this_effective_digits_natural = get_effective_digits_natural();
	//temp.set_effective_digits_natural(this_effective_digits_natural);
	return temp;
}

bool reality::operator==(const reality& node)const
{
	if (effective_digits == node.effective_digits && abs(real - node.real) <= 1e-8)
	{
		return true;
	}
	else
	{
		return false;
	}
}

