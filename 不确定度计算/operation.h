#pragma once
#include "reality.h"
#include "uncertain.h"

using std::ostream;

class operation
{
private:
	reality realpart;
	uncertain uncertainpart;
public:
	operation(long double real, long effective_digits, long uncertain_fin, long uncertain_digits);
	operation(long double real, long effective_digits, long double uncertain_instrument, long double uncertain_measurement);
	operation(const reality& real, const uncertain uncer);
	operation(const operation& node);
	operation operator+(const operation& node)const;
	operation operator-(const operation& node)const;
	operation operator*(const operation& node)const;
	operation operator*(const long double k)const;
	operation operator/(const operation& node)const;
	bool operator==(const operation& node)const;
	operation operator^(const long double k)const;
	friend operation operator*(const long double k, const operation& node);
	friend operation ln(const operation& node);
	friend operation sin(const operation& node);
	friend operation operator^(const long double k, const operation& node);
	friend ostream& operator<<(ostream& out, const operation & node);
};

