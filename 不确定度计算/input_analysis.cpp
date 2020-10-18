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
			node* obj = new node;
			node* obj2 = st.top();
			st.pop();
			node* obj1 = st.top();
			st.pop();
			if ((obj1->type == obj1->DIGIT || obj1->type == obj1->DIGIT_NODELETE) && (obj2->type == obj2->DIGIT || obj2->type == obj2->DIGIT_NODELETE))
			{
				obj->type = obj->DIGIT;
				obj->digit = obj1->digit * obj2->digit;
			}
			else if ((obj1->type == obj1->OPERATION || obj1->type == obj1->OPERATION_NODELETE) && (obj2->type == obj2->OPERATION || obj2->type == obj2->OPERATION_NODELETE))
			{
				obj->type = obj->OPERATION;
				obj->p = new operation(*obj1->p * *obj2->p);
			}
			else
			{
				long double digit;
				operation* p;
				if (obj1->type == obj1->DIGIT || obj1->type == obj1->DIGIT_NODELETE)
				{
					digit = obj1->digit;
					p = obj2->p;
				}
				else
				{
					digit = obj2->digit;
					p = obj1->p;
				}
				obj->type = obj->OPERATION;
				obj->p = new operation(*p * digit);
			}
			obj->remark = '(' + obj1->remark + ")*(" + obj2->remark + ')';
			cout << obj->remark << " = ";
			obj->type == obj->DIGIT ? cout << obj->digit : cout << *obj->p;
			cout << endl;
			st.push(obj);
			delete_node(obj1);
			delete_node(obj2);
			break;
		}
		case'-':
		{
			node* obj2 = st.top();
			st.pop();
			node* obj1 = st.top();
			st.pop();
			node* obj = new node;
			if ((obj1->type == obj1->DIGIT || obj1->type == obj1->DIGIT_NODELETE) && (obj2->type == obj2->DIGIT || obj2->type == obj2->DIGIT_NODELETE))
			{
				obj->type = obj->DIGIT;
				obj->digit = obj1->digit - obj2->digit;
			}
			else if ((obj1->type == obj1->OPERATION || obj1->type == obj1->OPERATION_NODELETE) && (obj2->type == obj2->OPERATION || obj2->type == obj2->OPERATION_NODELETE))
			{
				obj->type = obj->OPERATION;
				obj->p = new operation(*obj1->p - *obj2->p);
			}
			else //一个为纯数值，一个为不确定量，不能运算
			{
				cout << "类型错误！纯数值不能与不确定量运算" << endl;
				//这里应有throw，但是还没学到，就先空着
				exit(-1);
			}
			obj->remark = '(' + obj1->remark + ")-(" + obj2->remark + ')';
			cout << obj->remark << " = ";
			obj->type == obj->DIGIT ? cout << obj->digit << endl : cout << *obj->p << endl;
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
			if ((obj1->type == obj1->DIGIT || obj1->type == obj1->DIGIT_NODELETE) && (obj2->type == obj2->DIGIT || obj2->type == obj2->DIGIT_NODELETE))
			{
				obj->type = obj->DIGIT;
				obj->digit = obj1->digit + obj2->digit;
			}
			else if ((obj1->type == obj1->OPERATION || obj1->type == obj1->OPERATION_NODELETE) && (obj2->type == obj2->OPERATION || obj2->type == obj2->OPERATION_NODELETE))
			{
				obj->type = obj->OPERATION;
				obj->p = new operation(*obj1->p + *obj2->p);
			}
			else //一个为纯数值，一个为不确定量，不能运算
			{
				cout << "类型错误！纯数值不能与不确定量运算" << endl;
				//这里应有throw，但是还没学到，就先空着
				exit(-1);
			}
			obj->remark = '(' + obj1->remark + ")+(" + obj2->remark + ')';
			cout << obj->remark << " = ";
			obj->type == obj->DIGIT ? cout << obj->digit << endl : cout << *obj->p << endl;
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
			if ((obj1->type == obj1->DIGIT || obj1->type == obj1->DIGIT_NODELETE) && (obj2->type == obj2->DIGIT || obj2->type == obj2->DIGIT_NODELETE))
			{
				obj->type = obj->DIGIT;
				obj->digit = obj1->digit / obj2->digit;
			}
			else if ((obj1->type == obj1->OPERATION || obj1->type == obj1->OPERATION_NODELETE) && (obj2->type == obj2->OPERATION || obj2->type == obj2->OPERATION_NODELETE))
			{
				obj->type = obj->OPERATION;
				obj->p = new operation(*obj1->p / *obj2->p);
			}
			else //一个为纯数值，一个为不确定量，不能运算
			{
				cout << "类型错误！纯数值不能与不确定量运算" << endl;
				//这里应有throw，但是还没学到，就先空着
				exit(-1);
			}
			obj->remark = '(' + obj1->remark + ")/(" + obj2->remark + ')';
			cout << obj->remark << " = ";
			obj->type == obj->DIGIT ? cout << obj->digit << endl : cout << *obj->p << endl;
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
			if ((obj1->type == obj1->DIGIT || obj1->type == obj1->DIGIT_NODELETE) && (obj2->type == obj2->DIGIT || obj2->type == obj2->DIGIT_NODELETE))
			{
				obj->type = obj->DIGIT;
				obj->digit = pow(obj1->digit, obj2->digit);
			}
			else
			{
				obj->type = obj->OPERATION;
				obj->p = new operation(*obj1->p ^ obj2->digit);
			}
			obj->remark = '(' + obj1->remark + ")^(" + obj2->remark + ')';
			cout << obj->remark << " = ";
			obj->type == obj->DIGIT ? cout << obj->digit << endl : cout << *obj->p << endl;
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
				node* temp = get_object_space(str[i]);
				p->p = temp->p;
				p->digit = temp->digit;
				p->type = temp->type;
				p->remark = temp->remark;
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