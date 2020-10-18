#include "input_analysis.h"
#include"common.h"

using std::cout;
using std::endl;

node* input_analysis::calculate_reserve_polish_expression()
{
	str_to_reserve_polish_expression();
	stack<node*> st;
	for (size_t i = 0; i < str.size(); i++)
	{
		switch (str[i])
		{
		case' ':
		case'\t':continue; break;
		case'*':
		{
			node* obj2 = st.top();
			st.pop();
			node* obj1 = st.top();
			st.pop();
			if (obj1->type == obj1->DIGIT && obj2->type == obj2->DIGIT)
			{
				node* obj = new node;
				obj->type = obj->DIGIT;
				obj->digit = obj1->digit * obj2->digit;
				obj->remark = '(' + obj1->remark + ")*(" + obj2->remark + ')';
				cout << obj->remark << " = " << obj->digit << endl;
				delete_node(obj1);
				delete_node(obj2);
				st.push(obj);
			}
			else if ((obj1->type == obj1->OPERATION||obj1->type == obj1->OPERATION_NODELETE) && (obj2->type == obj2->OPERATION||obj2->type == obj2->OPERATION_NODELETE))
			{
				node* obj = new node;
				obj->type = obj->OPERATION;
				obj->p = new operation(*obj1->p * *obj2->p);
				obj->remark = '(' + obj1->remark + ")*(" + obj2->remark + ')';
				cout << obj->remark << " = " << *obj->p << endl;
				delete_node(obj1);
				delete_node(obj2);
				st.push(obj);
			}
			else
			{
				long double digit;
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
				obj->remark = '(' + obj1->remark + ")*(" + obj2->remark + ')';
				cout << obj->remark << " = " << *obj->p << endl;
				st.push(obj);
			}
			break;
		}
		case'-':
		{
			node* obj2 = st.top();
			st.pop();
			node* obj1 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj1->p - *obj2->p);
			obj->remark = '(' + obj1->remark + ")-(" + obj2->remark + ')';
			cout << obj->remark << " = " << *obj->p << endl;
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
			break;
		}
		case'+':
		{
			node* obj2 = st.top();
			st.pop();
			node* obj1 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj1->p + *obj2->p);
			obj->remark = '(' + obj1->remark + ")+(" + obj2->remark + ')';
			cout << obj->remark << " = " << *obj->p << endl;
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
			break;
		}
		case'/':
		{
			node* obj2 = st.top();
			st.pop();
			node* obj1 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj1->p / *obj2->p);
			obj->remark = '(' + obj1->remark + ")/(" + obj2->remark + ')';
			cout << obj->remark << " = " << *obj->p << endl;
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
			break;
		}
		case'^':
		{
			node* obj2 = st.top();
			st.pop();
			node* obj1 = st.top();
			st.pop();
			node* obj = new node;
			obj->type = obj->OPERATION;
			obj->p = new operation(*obj1->p ^ obj2->digit);
			obj->remark = '(' + obj1->remark + ")^(" + obj2->remark + ')';
			cout << obj->remark << " = " << *obj->p << endl;
			delete_node(obj1);
			delete_node(obj2);
			st.push(obj);
			break;
		}
		default:
			node* p;
			p = new node;
			if (isdigit(str[i]))
			{
				sscanf_s(&str.c_str()[i], "%lf", &p->digit);
				p->type = p->DIGIT;
				p->remark = str[i];
				while (i + 1 < str.size() && (isdigit(str[i + 1]) || str[i + 1] == '.'))
				{
					i++;
					p->remark += str[i];
				}
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
	node* temp = st.top();
	return temp;
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
		case'*':
		case'/':
		case'+':
		case'-':temp += ' '; break;
		default:
			break;
		}
		switch (str[i])
		{
		case'^':
		{
			if (!st.empty() && st.top() == '^')
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
			while (!st.empty() && st.top() != '(')
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
			temp += str[i];
			break;
		}
	}
	while (!st.empty())
	{
		temp += ' ';
		temp += st.top();
		st.pop();
	}
	str = temp;
	return true;
}