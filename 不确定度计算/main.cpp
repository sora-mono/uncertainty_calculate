#include"operation.h"
#include"common.h"

using std::cout;
using std::endl;
using std::cin;

int main()
{
	while (true)
	{
		operation& k = input_set();
		cout << k;
	}
}