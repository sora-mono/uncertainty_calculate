#pragma once
class uncertain
{
private:
	long double uncertain_calculated;		//原始不确定度
	long double uncertain_instrument;		//仪器不确定度
	long double uncertain_measurement;		//测量不确定度
	long uncertain_fin;						//最终不确定度的有效位
	long uncertain_fin_digits;				//不确定度有效位的位置，语义与effective_digit相同
	uncertain() { uncertain_calculated = uncertain_instrument = uncertain_measurement = uncertain_fin = uncertain_fin_digits = -1; }
	bool uncertain_calculated_cut();	//裁剪uncertainty_calculated，将结果放入uncertainty_fin并设置uncertain_fin_digits
public:
	uncertain(const long uncertain_fin1, const long uncertain_fin_digits1, const long double uncertain_calculated1 = -1, const long double uncertain_instrument1 = -1, const long double uncertain_measurement1 = -1);
	uncertain(const uncertain& node);
	inline long get_uncertain_fin() const { return uncertain_fin; }
	inline long get_uncertain_fin_digits() const { return uncertain_fin_digits; }
	inline long get_uncertain_fin_digits_for_pow()const { return uncertain_fin_digits > 0 ? uncertain_fin_digits - 1 : uncertain_fin_digits; }
	bool uncertain_calculate();		//仅计算uncertain_calculated
	bool recalculate_uncertain(const long digit);	//digits为程序内部语义，根据给定位置求新的不确定度
	uncertain operator*(const long double k)const;
	uncertain friend operator*(const long double k, const uncertain& node);
	bool operator==(const uncertain& node)const;
};

uncertain operator*(const long double k, const uncertain& node);