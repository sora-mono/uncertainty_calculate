//本程序所有real值均不自动舍入，需要手动调用函数根据需要设置有效位数或重新计算real值，因此必须写解析代码！！！！！
//#include<iostream>
//#include<cmath>
//#include<string>
//
//using namespace std;
//
//class uncertainty
//{
//private:
//	long double real;					//实数部分
//	long effective_digits;				//有效位数(精确到个位为0，每多一位小数-1，反之同理）
//	long uncertain_digits;				//最终不确定度的10次幂指数
//	int uncertain_fin;					//最终不确定度
//	long double uncertain;				//粗算不确定度（未归为一位）
//	long double uncertain_measurement;	//测量不确定度
//	long double uncertain_instrument;	//仪器不确定度
//	inline long min(long a, long b) { return a < b ? a : b; }
//	inline long max(long a, long b) { return a > b ? a : b; }
//public:
//	uncertainty(const long effective_digits, const long double uncertain1 = 0, const long double real1 = 0, const long double uncertain_measurement1 = -1, const long double uncertain_instrumentty1 = -1);
//	uncertainty(const uncertainty& node);
//	void set_effective_digits_number(int ed);	//设置有效位数，ed为有效位数，参数是标准语义，不是effective_digits的语义
//	void recalculate_real_digits();				//根据新有效位数重新计算真实值
//	void sync_real_uncertain_fin();				//同步real与uncertain_fin的有效位数
//	long get_effective_digits_number() const;			//获取当前有效数字(标准语义)
//	void array_calculate(long double arr[], int n, int uncertain_instrument1, int effective_digits1);
//	void calculate_uncertain();
//	uncertainty operator+(uncertainty& node);
//	uncertainty operator-(uncertainty& node);
//	uncertainty operator*(uncertainty& node);
//	uncertainty operator/(uncertainty& node);
//	uncertainty operator=(uncertainty& node);
//	bool operator==(uncertainty& node);
//	uncertainty operator^(uncertainty& node);
//	friend uncertainty ln(uncertainty& node);
//	friend uncertainty sin(uncertainty& node);
//};
//
//uncertainty::uncertainty(const long effective_digits1, const long double uncertain1, const long double real1, const long double uncertain_measurement1, const long double uncertain_instrument1)
//{
//	real = real1;
//	effective_digits = effective_digits1;
//	uncertain = uncertain1;
//	uncertain_measurement = uncertain_measurement1;
//	uncertain_instrument = uncertain_instrument1;
//	calculate_uncertain();
//	recalculate_real_digits();
//	sync_real_uncertain_fin();
//}
//
//uncertainty::uncertainty(const uncertainty& node)
//{
//	real = node.real;
//	effective_digits = node.effective_digits;
//	uncertain_digits = node.uncertain_digits;
//	uncertain_fin = node.uncertain_fin;
//	uncertain = node.uncertain;
//	uncertain_measurement = node.uncertain_measurement;
//	uncertain_instrument = node.uncertain_instrument;
//}
//
//void uncertainty::set_effective_digits_number(int ed)
//{
//	effective_digits = ed;
//}
//
//long uncertainty::get_effective_digits_number() const
//{
//	long double real = this->real;
//	long digit = 0;
//	if (real < 1)
//	{
//		while (real < 1)
//		{
//			real *= 10;
//			digit--;
//		}
//	}
//	else
//	{
//		while (real >= 10)
//		{
//			real /= 10;
//			digit++;
//		}
//	}
//	return digit - effective_digits + 1;
//}
//
//void uncertainty::recalculate_real_digits()
//{
//
//}
//
//void uncertainty::sync_real_uncertain_fin()
//{
//
//}
//
//void uncertainty::array_calculate(long double arr[], int n, int uncertain_instrument1, int effective_digits1)
//{
//	long double uncertain_calculate1, sum = 0, average;
//	for (size_t i = 0; i < n; i++)
//	{
//		sum += arr[i];
//	}
//	average = sum / n;
//	sum = 0;
//	for (size_t i = 0; i < n; i++)
//	{
//		sum += (arr[i] - average) * (arr[i] - average);
//	}
//	uncertain_calculate1 = sqrt(sum / (n * (n - 1)));
//	uncertain_measurement = uncertain_calculate1;
//	uncertain_instrument = uncertain_instrument1;
//	calculate_uncertain();
//	recalculate_real_digits();
//	sync_real_uncertain_fin();
//}
//
//void uncertainty::calculate_uncertain()
//{
//	long double uncertain;
//	if (uncertain_instrument < 0 || uncertain_measurement < 0)
//	{
//		return;
//	}
//	else
//	{
//		uncertain = sqrt(uncertain_instrument * uncertain_instrument + uncertain_measurement * uncertain_measurement / 3);
//		uncertainty::uncertain = uncertain;
//		int digit = 0;
//		while (uncertain < 1)
//		{
//			uncertain *= 10;
//			digit++;
//		}
//		while (uncertain >= 10)
//		{
//			uncertain /= 10;
//			digit--;
//		}
//		uncertain_fin = int(uncertain);
//		if (abs(uncertain_fin - uncertain) < LDBL_DIG - 1)
//		{
//			uncertain_fin++;
//			if (uncertain_fin == 10)
//			{
//				uncertain_fin = 1;
//				digit++;
//			}
//		}	//到此不确定度的计算和取舍完成
//		if (digit<effective_digits)		//real与uncertainty_fin有效位数对齐
//		{
//			uncertain_fin = 1;
//			uncertain_digits = effective_digits;
//		}
//		else if (digit>effective_digits)
//		{
//			uncertain_digits = digit;
//			effective_digits = digit;
//			real *= pow(long double(10), 1-digit);
//			int real_temp = int(real + 0.0000001);			//加一个很小的数以防浮点数存储误差导致差1
//			if (real_temp%10 == 5)
//			{
//				if ((real_temp%100-real_temp%10) %20 == 0)
//				{
//					real_temp -= 5;
//				}
//				else
//				{
//					real_temp -= 5;
//					real_temp += 10;
//				}
//			}
//			else if (real_temp%10<5)
//			{
//				real_temp -= real_temp % 10;
//			}
//			else
//			{
//				real_temp += 10;
//				real_temp -= real_temp % 10;
//			}
//			real = real_temp * (pow(long double(10), digit - 1)+0.0000001);		//加数理由同上
//		}
//	}
//}
//
//uncertainty uncertainty::operator+(uncertainty& node)
//{
//	long double uncertain_temp, real_temp;
//	real_temp = real + node.real;
//	uncertain_temp = sqrt(node.uncertain_fin * node.uncertain_fin + uncertain_fin * uncertain_fin);
//	return uncertainty(max(node.effective_digits, effective_digits), uncertain_temp, real_temp);
//}
//
//uncertainty uncertainty::operator-(uncertainty& node)
//{
//	long double uncertain_temp, real_temp;
//	real_temp = real - node.real;
//	uncertain_temp = sqrt(node.uncertain_fin * node.uncertain_fin + uncertain_fin * uncertain_fin);
//	return uncertainty(max(node.effective_digits, effective_digits), uncertain_temp, real_temp);
//}
//
//uncertainty uncertainty::operator*(uncertainty& node)
//{
//	long double uncertain_temp, real_temp;
//	real_temp = real * node.real;
//	uncertain_temp = real_temp * sqrt((uncertain_fin / real) * (uncertain_fin / real) + (node.uncertain_fin / node.real) * (node.uncertain_fin / node.real));
//}
//
//
int main()
{

}