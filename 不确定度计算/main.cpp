#include"operation.h"
#include"common.h"
#include<vector>

using std::cout;
using std::endl;
using std::cin;

extern node** variables;
extern const long variables_size;

int main()
{
	variables = new node * [variables_size];
	for (int i = 0; i < variables_size; i++)
	{
		variables[i] = nullptr;
	}
	while (true)
	{
		node* p = analysis_input();
		if (p != nullptr && p->type != p->OPERATION_NODELETE)
		{
			delete p;
		}
	}
}