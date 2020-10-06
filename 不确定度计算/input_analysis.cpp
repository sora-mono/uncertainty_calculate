#include "input_analysis.h"
#include"common.h"

node* input_analysis::calculate_reserve_polish_expression()
{
	stack<node*> st;
	for (size_t i = 0; i < str.size(); i++)
	{
		switch (str[i])
		{
		case'*':
		{
			node* obj1 = st.top();
			st.pop();
			node* obj2 = st.top();
			st.pop();
			if (obj1->type == obj1->DIGIT && obj2->type == obj2->DIGIT)
			{
				node* obj = new node;
				obj->type = obj->DIGIT;
				obj->digit = obj1->digit * obj2->digit;
				delete_node(obj1);
				delete_node(obj2);
				st.push(obj);
			}
			else if (obj1->type == obj1->OPERATION && obj2->type == obj2->OPERATION)
			{
				node* obj = new node;
				obj->type = obj->OPERATION;
				obj->p = new operation(*obj1->p * *obj2->p);
				delete_node(obj1);
				delete_node(obj2);
				st.push(obj);
			}
			else
			{
				long digit;
				operation* p;
				if (obj1->type == obj1->DIGIT)
				{
					digit = obj1->digit;
					p = obj2->p;
				}
				else
				{
					digit = obj2->digit;
					p = obj1->p;
				}
				node* obj = new node;
				obj->type = obj->OPERATION;
				obj->p = new operation(*p * digit);
				st.push(obj);
			}
			break;
		}
		case'-':
		{
			node* obj1 = st.top();
			st.pop();
			node* obj2 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj2->p - *obj1->p);
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
			break;
		}
		case'+':
		{
			node* obj1 = st.top();
			st.pop();
			node* obj2 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj2->p + *obj1->p);
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
			break;
		}
		case'/':
		{
			node* obj1 = st.top();
			st.pop();
			node* obj2 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj2->p / *obj1->p);
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
			break;
		}
		case'^':
		{
			node* obj1 = st.top();
			st.pop();
			node* obj2 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj2->p ^ obj1->digit);
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
		}
		default:
			node* p;
			p = new node;
			if (isdigit(str[i]))
			{
				p->digit = str[i] - '0';
				p->type = p->DIGIT;
			}
			else
			{
				p->p = get_object(str[i]);
				p->type = p->OPERATION_NODELETE;
			}
			st.push(p);
			break;
		}
	}
	return st.top();
}

bool input_analysis::str_to_reserve_polish_expression()
{
	stack<char> st;
	string temp;
	for (size_t i = 0; i < str.size(); i++)
	{
		switch (str[i])
		{
		case'^':
		{
			if (st.top() == '^')
			{
				temp += st.top();
				st.pop();
				st.push(str[i]);
			}
			else
			{
				st.push(str[i]);
			}
			break;
		}
		case'*':
		case'/':
		{
			while (!st.empty() && st.top() != '+' && st.top() != '-' && st.top() != '(')
			{
				temp += st.top();
				st.pop();
			}
			st.push(str[i]);
			break;
		}
		case'+':
		case'-':
		{
			while (!st.empty() && st.top() != '(')
			{
				temp += st.top();
				st.pop();
			}
			st.push(str[i]);
			break;
		}
		case'(':st.push(str[i]); break;
		case')':
		{
			while (st.top() != '(')
			{
				temp += st.top();
				st.pop();
			}
			st.pop();
			break;
		}
		case'\t':
		case' ':continue; break;
		default:
			st.push(str[i]);
			break;
		}
	}
	while (!st.empty())
	{
		temp += st.top();
		st.pop();
	}
	str = temp;
	return true;
}