#include <iostream>
#include <cstdio>
#include <malloc.h>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 5
#define LITTLE_NUM_CAPACITY 100

//ERROR_EXIT_CODE
#define	OPERATOR_CANNOT_MATCH 10086
#define PRIORITY_CANNOT_GET 12580
#define INVALID_INPUT 888

//����ջ������Ϣ��ʾ
#define DEBUG_MODE_ON

typedef int Status;
typedef double Elemtype;

using namespace std;

typedef struct {
	char* base;
	char* top;
	int stack_size;
}OperatorStack;

typedef struct {
	Elemtype* base;
	Elemtype* top;
	int stack_size;
}NumStack;

//��ʼ��һ��ջ
Status InitStack(NumStack& s)
{
	s.base = (Elemtype*)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
	if (s.base == NULL)
	{
		perror("Unable to allocate to memory space");
		exit(OVERFLOW);
	}
	else {
		s.top = s.base;
		s.stack_size = STACK_INIT_SIZE;
		return SUCCESS;
	}
}
Status InitStack(OperatorStack& s)
{
	s.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (s.base == NULL)
	{
		perror("Unable to allocate to memory space");
		exit(OVERFLOW);
	}
	else {
		s.top = s.base;
		s.stack_size = STACK_INIT_SIZE;
		return SUCCESS;
	}
}

//���µ�Ԫ������ջ��
Status Push(NumStack& s, Elemtype e)
{
	if ((s.top - s.base) >= s.stack_size) {//����Ƿ�ջ����
		//����׷�ӿռ䣬��СΪSTACK_INCREMENT
		s.base = (Elemtype*)realloc(s.base, s.stack_size + STACK_INCREMENT);
		//���ʱ�Ƿ�ɹ����䵽���ڴ�ռ�
		if (s.base == NULL)
		{
			perror("Unable to allocate to memory space");
			exit(OVERFLOW);
		}
		//����ջ��λ�ú�ջ��С(stack_size)��¼
		s.top = s.base + s.stack_size;
		s.stack_size = s.stack_size + STACK_INCREMENT;
	}
	*s.top = e;
	s.top++;
	return SUCCESS;
}

Status Push(OperatorStack& s, char e)
{
	if ((s.top - s.base) >= s.stack_size) {//����Ƿ�ջ����
		//����׷�ӿռ䣬������СΪSTACK_INCREMENT
		s.base = (char*)realloc(s.base, s.stack_size + STACK_INCREMENT);
		//���ʱ�Ƿ�ɹ����䵽���ڴ�ռ�
		if (s.base == NULL)
		{
			perror("Unable to allocate to memory space");
			exit(OVERFLOW);
		}
		//����ջ��λ�ú�ջ��С(stack_size)��¼
		s.top = s.base + s.stack_size;
		s.stack_size = s.stack_size + STACK_INCREMENT;
	}
	*s.top = e;
	s.top++;
	return SUCCESS;
}

Status Pop(NumStack& s, Elemtype& e)
{
	if (s.top == s.base)
	{
		return ERROR;
	}
	else
	{
		s.top--;
		e = *s.top;
		return SUCCESS;
	}
}

Status Pop(OperatorStack& s, char& e)
{
	if (s.top == s.base)
	{
		return ERROR;
	}
	else
	{
		s.top--;
		e = *s.top;
		return SUCCESS;
	}
}

Status StackEmpty(NumStack* s)
{
	if ((*s).base == (*s).top)
		return TRUE;
	else
		return FALSE;
}

Status StackEmpty(OperatorStack* s)
{
	if ((*s).base == (*s).top)
		return TRUE;
	else
		return FALSE;
}

char GetTop(OperatorStack* s)
{
	if (!StackEmpty(s))
	{
		char* temp = s->top;
		temp--;
		return *(temp);
	}
	else return '!';
}

double GetTop(NumStack* s)
{
	if (!StackEmpty(s))
	{
		double* temp = s->top;
		temp--;
		return *(temp);
	}
	else return -1;
}

void DisplayStack(OperatorStack* s)
{
	if (StackEmpty(s))return;
	for (int i = 0; i < s->top - s->base; i++)
	{
		printf("%c ", s->base[i]);
	}
	printf("  ");
}

void DisplayStack(NumStack* s)
{
	if (StackEmpty(s))return;
	for (int i = 0; i < s->top - s->base; i++)
	{
		printf("%f ", s->base[i]);
	}
	printf("  ");
}

Status isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '%' || c == '^' || c == '.' || c == '#')
		return TRUE;
	else
		return FALSE;
}

char ComparePriority(char a, char b)
{
	if (a == '+')
	{
		if (b == '*' || b == '/' || b == '(' || b == '^' || b == '%')
			return '<';
		else
			return '>';
	}
	else if (a == '-')
	{
		if (b == '*' || b == '/' || b == '(' || b == '^' || b == '%')
			return '<';
		else
			return '>';
	}

	else if (a == '*')
	{
		if (b == '(' || b == '^')
			return '<';
		else
			return '>';
	}
	else if (a == '/')
	{
		if (b == '(' || b == '^')
			return '<';
		else
			return '>';
	}
	else if (a == '%')
	{
		if (b == '(' || b == '^')
			return '<';
		else
			return '>';
	}
	else if (a == '^')
	{
		if (b == '(')
			return '<';
		else
			return '>';
	}
	else if (a == '(')
	{
		if (b == ')')
			return '=';
		else if (b == '#')
			return '!';
		else
			return '<';
	}
	else if (a == ')')
	{
		if (b == '(')
			return '!';
		else
			return '>';
	}
	else if (a == '#')
	{
		if (b == ')')
			return '!';
		if (b == '#')
			return '=';
		else
			return '<';
	}
}

double Calculate(double temp_1, double temp_2, char op)
{
	switch (op)
	{
	case '+':
		return temp_1 + temp_2;
	case '-':
		return 1.0 * temp_1 - temp_2;
	case '*':
		return temp_1 * temp_2;
	case '/':
		return 1.0 * temp_1 / temp_2;
	case '^':
		return 1.0 * pow(temp_1, temp_2);
	case '%':
		return static_cast<double>((int)temp_1 % (int)temp_2);
	}
}

Status DestroyStack(NumStack& s)
{
	if (s.base != NULL)
	{
		free(s.base);
		s.base = NULL;
		s.top = NULL;
		s.stack_size = 0;
		return SUCCESS;
	}
	else
		return ERROR;
}

Status DestroyStack(OperatorStack& s)
{
	if (s.base != NULL)
	{
		free(s.base);
		s.base = NULL;
		s.top = NULL;
		s.stack_size = 0;
		return SUCCESS;
	}
	else
		return ERROR;
}

#ifdef DEBUG_MODE_ON
Status StackDebug(OperatorStack operator_stack, NumStack num_stack)
{

	printf("DEBUG INFORMATION:\n");
	printf("Ŀǰ��OperatorStackջ��");
	DisplayStack(&operator_stack);
	printf("\nĿǰ��NumStackջ��");
	DisplayStack(&num_stack);
	printf("\n\n");
	return SUCCESS;
}
#endif

bool isValidInput(char c)
{
	if ((c >= '0' && c <= '9') || isOperator(c))
	{
		return true;
	}
	return false;
}

int main()
{
	//��������ջ�������ʼ��
	OperatorStack operator_stack;
	NumStack num_stack;
	NumStack temp_num_stack;
start:
	InitStack(operator_stack);
	InitStack(num_stack);
	InitStack(temp_num_stack);

	double sum = 0;
	double digit;
	int exponent = 0;

	//����ӷ���ջ(OperatorStack)�е����ķ����ַ�
	char operator_for_cal;
	//��ʱ���������ջ(NumStack)�е����������ַ�
	double left_num, right_num;

	cout << "\n������֧�ֵ������У�\'+\',  \'-\',  \'*\',  \'/\',  \'^\',  \'%\'" << endl;
	cout << "��������һ����׺���ʽ����ʹ��\'#\'�������������룡" << endl;
	Push(operator_stack, '#');
	char temp_char = getchar();
	time_t time_start = time(0);
	//����Ƿ�����
	if (!isValidInput(temp_char))
	{
		cout << endl << "INVALID CHARACTER has received! This Program will restart immediately!" << endl \
			<< "Please type in your expression with Numbers and \'+\',  \'-\',  \'*\',  \'/\',  \'^\',  \'%\',  \'#\' ONLY!" << endl;
		DestroyStack(num_stack);
		DestroyStack(temp_num_stack);
		DestroyStack(operator_stack);
		temp_char = ' ';
		rewind(stdin);
		goto start;
	}
	Status error_indicator = 0;
	while (temp_char != '#' || GetTop(&operator_stack) != '#')
	{
		while (!isOperator(temp_char))
		{
			Push(temp_num_stack, temp_char - '0');
			temp_char = getchar();

			if (!isValidInput(temp_char))
			{
				cout << endl << "INVALID CHARACTER has received! This Program will restart immediately!" << endl \
					<< "Please type in your expression with Numbers and \'+\',  \'-\',  \'*\',  \'/\',  \'^\',  \'%\',  \'#\' ONLY!" << endl;
				DestroyStack(num_stack);
				DestroyStack(temp_num_stack);
				DestroyStack(operator_stack);
				temp_char = ' ';
				rewind(stdin);
				goto start;
			}

			if (temp_char == '.')
			{
				temp_char = getchar();

				if (!isValidInput(temp_char))
				{
					cout << endl << "INVALID CHARACTER has received! This Program will restart immediately!" << endl \
						<< "Please type in your expression with Numbers and \'+\',  \'-\',  \'*\',  \'/\',  \'^\',  \'%\',  \'#\' ONLY!" << endl;
					DestroyStack(num_stack);
					DestroyStack(temp_num_stack);
					DestroyStack(operator_stack);
					temp_char = ' ';
					rewind(stdin);
					goto start;
				}

				int little_exp = -1;;
				while (!isOperator(temp_char))
				{
					sum += (temp_char - '0') * pow(10, little_exp);
					little_exp--;
					temp_char = getchar();
					if (!isValidInput(temp_char))
					{
						cout << endl << "INVALID CHARACTER has received! This Program will restart immediately!" << endl \
							<< "Please type in your expression with Numbers and \'+\',  \'-\',  \'*\',  \'/\',  \'^\',  \'%\',  \'#\' ONLY!" << endl;
						DestroyStack(num_stack);
						DestroyStack(temp_num_stack);
						DestroyStack(operator_stack);
						temp_char = ' ';
						rewind(stdin);
						goto start;
					}
				}
			}
		}
		while (StackEmpty(&temp_num_stack) == FALSE)
		{
			Pop(temp_num_stack, digit);
			sum = sum + digit * pow(10, exponent);
			exponent++;
		}
		exponent = 0;
		if (sum != 0)
		{
			Push(num_stack, (double)sum);
			sum = 0;
		}
#ifdef DEBUG_MODE_ON
		StackDebug(operator_stack, num_stack);//Debug
#endif
		if (isOperator(temp_char))
		{
			switch (ComparePriority(GetTop(&operator_stack), temp_char))
			{
			case '<':
				Push(operator_stack, temp_char);
				temp_char = getchar();
				if (!isValidInput(temp_char))
				{
					cout << endl << "INVALID CHARACTER has received! This Program will restart immediately!" << endl \
						<< "Please type in your expression with Numbers and \'+\',  \'-\',  \'*\',  \'/\',  \'^\',  \'%\',  \'#\' ONLY!" << endl;
					DestroyStack(num_stack);
					DestroyStack(temp_num_stack);
					DestroyStack(operator_stack);
					temp_char = ' ';
					rewind(stdin);
					goto start;
				}
#ifdef DEBUG_MODE_ON
				StackDebug(operator_stack, num_stack);//Debug
#endif
				break;
			case '>':
				Pop(operator_stack, operator_for_cal);
				Pop(num_stack, right_num);
				Pop(num_stack, left_num);
#ifdef DEBUG_MODE_ON
				StackDebug(operator_stack, num_stack);//Debug
#endif
				Push(num_stack, Calculate(left_num, right_num, operator_for_cal));
#ifdef DEBUG_MODE_ON
				cout << "The Calculate Function is called!" << endl << endl;
#endif
#ifdef DEBUG_MODE_ON
				StackDebug(operator_stack, num_stack);//Debug
#endif
				break;
			case '=':
				Pop(operator_stack, operator_for_cal);
				temp_char = getchar();
				if (!isValidInput(temp_char))
				{
					cout << endl << "INVALID CHARACTER has received! This Program will restart immediately!" << endl \
						<< "Please type in your expression with Numbers and \'+\',  \'-\',  \'*\',  \'/\',  \'^\',  \'%\',  \'#\' ONLY!"\
						<< endl;
					DestroyStack(num_stack);
					DestroyStack(temp_num_stack);
					DestroyStack(operator_stack);
					temp_char = ' ';
					rewind(stdin);
					goto start;
				}
#ifdef DEBUG_MODE_ON
				StackDebug(operator_stack, num_stack);//Debug
#endif
				break;
			case '!':
#ifdef DEBUG_MODE_ON
				StackDebug(operator_stack, num_stack);//Debug
#endif
				perror("Cannot Match The Priority of the two Operators");
				exit(OPERATOR_CANNOT_MATCH);
			}
		}
#ifdef DEBUG_MODE_ON
		cout << "temp_charΪ��" << temp_char << endl << endl;
#endif
	}
	time_t time_shutdown = time(0);
	cout << "���ʽ�����ս��Ϊ��" << GetTop(&num_stack) << endl << "������ʱ��" << time_shutdown - time_start << 's' << endl;

	cout << endl << endl;
	DestroyStack(num_stack);
	DestroyStack(temp_num_stack);
	DestroyStack(operator_stack);
	temp_char = ' ';
	rewind(stdin);
	goto start;

	return 0;
}