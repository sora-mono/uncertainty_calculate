#pragma once
class uncertain
{
private:
	long double uncertain_calculated;		//ԭʼ��ȷ����
	long double uncertain_instrument;		//������ȷ����
	long double uncertain_measurement;		//������ȷ����
	long uncertain_fin;						//���ղ�ȷ���ȵ���Чλ
	long uncertain_fin_digits;				//��ȷ������Чλ��λ�ã�������effective_digit��ͬ
	uncertain() { uncertain_calculated = uncertain_instrument = uncertain_measurement = uncertain_fin = uncertain_fin_digits = -1; }
	bool uncertain_calculated_cut();	//�ü�uncertainty_calculated�����������uncertainty_fin������uncertain_fin_digits
public:
	uncertain(const long uncertain_fin1, const long uncertain_fin_digits1, const long double uncertain_calculated1 = -1, const long double uncertain_instrument1 = -1, const long double uncertain_measurement1 = -1);
	uncertain(const uncertain& node);
	inline long get_uncertain_fin() const { return uncertain_fin; }
	inline long get_uncertain_fin_digits() const { return uncertain_fin_digits; }
	inline long get_uncertain_fin_digits_for_pow()const { return uncertain_fin_digits > 0 ? uncertain_fin_digits - 1 : uncertain_fin_digits; }
	bool uncertain_calculate();		//������uncertain_calculated
	bool recalculate_uncertain(const long digit);	//digitsΪ�����ڲ����壬���ݸ���λ�����µĲ�ȷ����
	uncertain operator*(const long double k)const;
	uncertain friend operator*(const long double k, const uncertain& node);
	bool operator==(const uncertain& node)const;
};

uncertain operator*(const long double k, const uncertain& node);