#pragma once
class uncertain
{
private:
	long double uncertain_calculated;		//ԭʼ��ȷ����
	long double uncertain_instrument;		//������ȷ����
	long double uncertain_measurement;		//������ȷ����
	long uncertain_fin;						//���ղ�ȷ���ȵ���Чλ
	long uncertain_fin_digits;				//��ȷ������Чλ��λ�ã�������effective_digit��ͬ
public:
	uncertain(long double uncertain_calculated1 = -1,long uncertain_fin1 = -1, long uncertain_fin_digits1 = -1, long double uncertain_instrument1 = -1, long double uncertain_measurement1 = -1);
	uncertain(uncertain& node);
	bool uncertain_calculate();		//������uncertain_calculated
	bool uncertain_calculated_cut();//�ü�uncertainty_calculated�����������uncertainty_fin������uncertain_fin_digits
	bool recalculate_uncertain(long digit);	//digitsΪ�����ڲ����壬���ݸ���λ�����µĲ�ȷ����
};