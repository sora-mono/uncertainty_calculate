#include"operation.h"
#include"common.h"
#include<iomanip>

using std::setprecision;

operation::operation(long double real, long effective_digits, long uncertain_fin, long uncertain_digits) :realpart(effective_digits, real), uncertainpart(uncertain_fin, uncertain_digits, -1, -1, -1)
{
	realpart.set_effective_digits_inside(uncertainpart.get_uncertain_fin_digits());
}

operation::operation(long double real, long effective_digits, long double uncertain_instrument, long double uncertain_measurement) : realpart(effective_digits, real), uncertainpart(-1, -1, -1, uncertain_instrument, uncertain_measurement)
{
	realpart.set_effective_digits_inside(uncertainpart.get_uncertain_fin_digits());
}

operation::operation(const operation& node) : realpart(node.realpart), uncertainpart(node.uncertainpart)
{

}

operation::operation(const reality& real, const uncertain uncer) : realpart(real), uncertainpart(uncer)
{
	realpart.set_effective_digits_inside(uncertainpart.get_uncertain_fin_digits());
}

operation operation::operator+ (const operation& node) const
{
	reality temp_reality = realpart + node.realpart;
	long double uncertain_fin1 = uncertainpart.get_uncertain_fin();
	long uncertain_fin_digits1 = uncertainpart.get_uncertain_fin_digits_for_pow();
	long double uncertain_fin2 = node.uncertainpart.get_uncertain_fin();
	long uncertain_fin_digits2 = node.uncertainpart.get_uncertain_fin_digits_for_pow();
	long digits = min(uncertain_fin_digits1, uncertain_fin_digits2);
	uncertain_fin1 *= pow(long double(10), uncertain_fin_digits1 - digits);
	uncertain_fin2 *= pow(long double(10), uncertain_fin_digits2 - digits);
	long double result = sqrt(uncertain_fin1 * uncertain_fin1 + uncertain_fin2 * uncertain_fin2);
	uncertain temp_uncertain = uncertain(-1, -1, result * pow(long double(10), long double(digits)));
	return operation(temp_reality, temp_uncertain);
}

operation operation::operator- (const operation& node) const
{
	reality temp_reality = realpart - node.realpart;
	long double uncertain_fin1 = uncertainpart.get_uncertain_fin();
	long uncertain_fin_digits1 = uncertainpart.get_uncertain_fin_digits_for_pow();
	long double uncertain_fin2 = node.uncertainpart.get_uncertain_fin();
	long uncertain_fin_digits2 = node.uncertainpart.get_uncertain_fin_digits_for_pow();
	long digits = min(uncertain_fin_digits1, uncertain_fin_digits2);
	uncertain_fin1 *= pow(long double(10), uncertain_fin_digits1 - digits);
	uncertain_fin2 *= pow(long double(10), uncertain_fin_digits2 - digits);
	long double result = sqrt(uncertain_fin1 * uncertain_fin1 + uncertain_fin2 * uncertain_fin2);
	uncertain temp_uncertain = uncertain(-1, -1, result * pow(long double(10), long double(digits)));
	return operation(temp_reality, temp_uncertain);
}

operation operation::operator* (const operation& node) const
{
	reality temp_reality = realpart * node.realpart;
	long double real = temp_reality.get_real();
	long double uncertain1 = uncertainpart.get_uncertain_fin() * pow(long double(10), uncertainpart.get_uncertain_fin_digits_for_pow());
	long double uncertain2 = node.uncertainpart.get_uncertain_fin() * pow(long double(10), node.uncertainpart.get_uncertain_fin_digits_for_pow());
	long double result = real * sqrt(pow(uncertain1 / realpart.get_real(), 2) + pow(uncertain2 / node.realpart.get_real(), 2));
	uncertain temp_uncertain = uncertain(-1, -1, result);
	return operation(temp_reality, temp_uncertain);
}

operation operation::operator*(const long double k)const
{
	reality temp_reality = reality(realpart.get_effective_digits_inside(), k * realpart.get_real());
	temp_reality.recalculate_real();
	uncertain temp_uncertain = uncertain(-1, -1, uncertainpart.get_uncertain_fin() * k * pow(long double(10), uncertainpart.get_uncertain_fin_digits_for_pow()));
	return operation(temp_reality, temp_uncertain);
}

operation operation::operator/ (const operation& node) const
{
	reality temp_reality = realpart / node.realpart;
	long double real = temp_reality.get_real();
	long double uncertain1 = uncertainpart.get_uncertain_fin() * pow(long double(10), uncertainpart.get_uncertain_fin_digits_for_pow());
	long double uncertain2 = node.uncertainpart.get_uncertain_fin() * pow(long double(10), node.uncertainpart.get_uncertain_fin_digits_for_pow());
	long double result = real * sqrt(pow(uncertain1 / realpart.get_real(), 2) + pow(uncertain2 / node.realpart.get_real(), 2));
	uncertain temp_uncertain = uncertain(-1, -1, result);
	return operation(temp_reality, temp_uncertain);
}

bool operation::operator==(const operation& node)const
{
	if (realpart == node.realpart && uncertainpart == node.uncertainpart)
	{
		return true;
	}
	else
	{
		return false;
	}
}

operation operation::operator^(const long double k)const
{
	reality temp_reality = reality(-99, pow(realpart.get_real(), k));
	long double uncertain_fin = uncertainpart.get_uncertain_fin() * pow(long double(10), uncertainpart.get_uncertain_fin_digits_for_pow());
	uncertain_fin = uncertain_fin * k * temp_reality.get_real()/realpart.get_real();
	uncertain temp_uncertain = uncertain(-1, -1, uncertain_fin);
	return operation(temp_reality, temp_uncertain);
}

operation operator*(const long double k, const operation& node)
{
	return node.operator*(k);
}

operation ln(const operation& node)
{
	long double real = node.realpart.get_real();
	reality temp_reality = reality(node.realpart.get_effective_digits_inside(), log(node.realpart.get_real()));
	long double uncertain_fin = node.uncertainpart.get_uncertain_fin() * pow(long double(10), node.uncertainpart.get_uncertain_fin_digits_for_pow());
	uncertain_fin /= node.realpart.get_real();
	uncertain temp_uncertain = uncertain(-1, -1, uncertain_fin);
	return operation(temp_reality, temp_uncertain);
}

operation sin(const operation& node)
{
	long double real = node.realpart.get_real();
	reality temp_reality = reality(node.realpart.get_effective_digits_inside(), sin(real));
	long double uncertain_fin = node.uncertainpart.get_uncertain_fin() * pow(long double(10), node.uncertainpart.get_uncertain_fin_digits_for_pow());
	uncertain_fin *= abs(cos(real));
	uncertain temp_uncertain = uncertain(-1, -1, uncertain_fin);
	return operation(temp_reality, temp_uncertain);
}

operation operator^(const long double k, const operation& node)
{
	return node.operator^(k);
}

ostream& operator<<(ostream& out, const operation& node)
{
	using std::endl;
	out << "真实值 = " << node.realpart.get_real() << "\t有效位数 = " << node.realpart.get_effective_digits_natural();
	out << "\t不确定度 = " << node.uncertainpart.get_uncertain_fin() * pow(10, node.uncertainpart.get_uncertain_fin_digits_for_pow()) << endl;
	return out;
}