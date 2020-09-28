#pragma once
#include"operation.h"


long max(long a, long b);

long min(long a, long b);

long double average_calculate(long double arr[], int size);

long double uncertain_measurement_calculate(long double arr[], long double avg, int size);

operation& input_set();

operation& input_one();

