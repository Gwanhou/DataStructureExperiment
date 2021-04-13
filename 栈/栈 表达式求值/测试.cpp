#include "StackBasicOperation.h"

using namespace std;

bool isNum(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

Status InsidePriority(char operatorType)
{
	switch (operatorType) {
	case '#': 	return 0;
	case '(': 	return 1;
	case '+': 	return 3;
	case '-': 	return 3;
	case '*': 	return 5;
	case '/': 	return 5;
	case '%': 	return 5;
	case '^': 	return 7;
	case ')': 	return 8;
	}
}

Status OutsidePriority(char operatorType)
{
	switch (operatorType) {
	case '#': 	return 0;
	case '(': 	return 8;
	case '+': 	return 6;
	case '-': 	return 2;
	case '*': 	return 4;
	case '/': 	return 4;
	case '%': 	return 4;
	case '^': 	return 6;
	case ')': 	return 1;
	}
}

string RPNTranslator(string s)
{
	string rpnExp = "#";
	Stack OpStack;
	InitStack(OpStack);
	char tempChar;
	for (int i = 0; i < s.length(); ++i)
	{
		if (isNum(s.at(i)))
		{
			cout << "���˵�1��if" << endl << endl;
			rpnExp += s.at(i);
			continue;
		}
		if (s.at(i) == '(')
		{
			Push(OpStack, '(');
		}
		if (StackEmpty(OpStack))
		{
			cout << "���˵�2��if" << endl << endl;
			Push(OpStack, s.at(i));
			continue;
		}
		if (s.at(i) == ')')
		{
			Status authenticator;
			cout << "���˵�3��if" << endl << endl;
			while (GetTop(OpStack) != '(')
			{
				cout << "���˵�3��if��while" << endl << endl;
				authenticator = Pop(OpStack, tempChar);
				if (authenticator == ERROR)
				{
					exit(OVERFLOW);
				}
				rpnExp += tempChar;
				cout << "��סʱ��tempchar:" << tempChar << endl;
				cout << "��סʱ��rpnexp:" << rpnExp << endl;
			}
			cout << "�ӵ�3��if��while�е���" << endl << endl;
			Pop(OpStack, tempChar);
			rpnExp += tempChar;
		}
		else
		{
			cout << "����else" << endl << endl;
			if (InsidePriority(GetTop(OpStack)) > OutsidePriority(s.at(i)))
			{
				cout << "����elseǶ�׵�if" << endl << endl;
				while (InsidePriority(GetTop(OpStack)) > OutsidePriority(s.at(i)))
				{
					cout << "����else��while" << endl << endl;
					Pop(OpStack, tempChar);
					rpnExp += tempChar;
				}
				cout << "��else��while�е���" << endl << endl;
				Push(OpStack, s.at(i));
			}
		}
		cout << "���һ��forѭ��" << endl << endl;
		cout << rpnExp << endl;
	}

	cout << "����forѭ������ʱ��rpnExpΪ��" << rpnExp << endl;

	if (StackEmpty(OpStack) == 0)
	{
		do
		{
			Pop(OpStack, tempChar);
			rpnExp += tempChar;
		} while (StackEmpty(OpStack) == 0);
	}
	return rpnExp;
}

int main()
{
	printf("������һ����׺���ʽ��\n");
	string infixExp;
	cin >> infixExp;
	string rpnExp;
	rpnExp = RPNTranslator(infixExp);
	printf("ת��Ϊ��׺���ʽ��Ľ��Ϊ��\n");
	cout << rpnExp;
}