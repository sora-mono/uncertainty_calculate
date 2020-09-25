#pragma once
class uncertain
{
private:
	long double uncertain_calculated;		//原始不确定度
	long double uncertain_instrument;		//仪器不确定度
	long double uncertain_measurement;		//测量不确定度
	long uncertain_fin;						//最终不确定度的有效位
	long uncertain_fin_digits;				//不确定度有效位的位置，语义与effective_digit相同
public:
	uncertain(long double uncertain_calculated1 = -1,long uncertain_fin1 = -1, long uncertain_fin_digits1 = -1, long double uncertain_instrument1 = -1, long double uncertain_measurement1 = -1);
	uncertain(uncertain& node);
	bool uncertain_calculate();		//仅计算uncertain_calculated
	bool uncertain_calculated_cut();//裁剪uncertainty_calculated，将结果放入uncertainty_fin并设置uncertain_fin_digits
	bool recalculate_uncertain(long digit);	//digits为程序内部语义，根据给定位置求新的不确定度
};