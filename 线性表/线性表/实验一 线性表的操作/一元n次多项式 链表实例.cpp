#include <iostream>
#include <string>
#include <cstdio>
#include <malloc.h>

using namespace std;

#define SUCCESS 1
#define ERROR 0
#define INIT_SIZE 100
#define MAX_SIZE 200
#define TRUE 1
#define FALSE 0
#define INVALID_INPUT 666

//Status��Ϊ��������ֵ�����ͣ����غ���������״̬
typedef int Status;

//�ڵ�����
typedef struct LinkListNode
{
	//data
	int exp;
	float coe;

	//index
	struct LinkListNode* next;
}*Link, * Position;

//��������
typedef struct SinglyLinkList
{
	Link head, tail;
	int elemAmount;
}LinkList;

int ElemAmount_1 = 0;
int ElemAmount_2 = 0;
int ElemAmount_3 = 0;

//��ʼ��һ���������а�����ͷָ�룬βָ���Ԫ�ظ�������
Status InitList(LinkList& l)
{
	Link p;
	p = (Link)malloc(20);
	if (p != NULL)
	{
		p->next = NULL;
		l.head = p;
		l.tail = p;
		l.elemAmount = 0;
		return SUCCESS;
	}
	else
		perror("Cannot Initial LinkList");
}

//�ж�һ���ַ����Ƿ�Ϊ���ִ������ز���ֵ
bool IsNumber(const char* str)
{

	double aa;
	int nn = sscanf_s(str, "%lf", &aa);
	return nn != 0;
}

//��ȡ����ʽ��ϵ����ָ��
Status GetPoly(int length, LinkList l) {
	Link last = l.head;
	Link cur;
	cur = (Link)malloc(20);
	last->next = cur;

	for (size_t i = 0; i < length; i++)
	{
		if (cur == NULL)
		{
			perror("ERROR");
			return NULL;
		}
		else
		{
			char check[100];
			printf("�������%d���ָ����", i + 1);
			cin >> check;
			if (!IsNumber(check)) {
				perror("Invalid Input");
				exit(INVALID_INPUT);
			}
			else
				cur->exp = atoi(check);
			printf("�������%d���ϵ����", i + 1);
			cin >> check;
			if (!IsNumber(check)) {
				perror("Invalid Input");
				exit(INVALID_INPUT);
			}
			else
				cur->coe = atoi(check);
		}
		last = cur;
		cur = (Link)malloc(20);
		last->next = cur;
	}
	l.tail = last;
	free(cur);
	return SUCCESS;
}

//�������ʽ
Status PrintPoly(int length, LinkList l) {
	Link node = l.head->next;
	for (size_t i = 0; i < length - 1; i++)
	{
		if (node->coe == 0)
			continue;
		else {
			if (node->coe == 1)
				printf(" X^%d +", node->exp);
			else
				printf(" (%.2f)*X^%d +", node->coe, node->exp);
		}
		node = node->next;
	}

	if (node->coe != 0)
	{
		if (node->coe == 1)
			printf(" X^%d", node->exp);
		else
			printf(" (%.2f)*X^%d", node->coe, node->exp);
	}
	return SUCCESS;
}

//������ʽ���ս���������������
Status SortPoly(int& length, LinkList& l) {
	bool isChanged = true;
	bool isEqual = true;
	int equalCase = 0;
	Link node = l.head;

	//�����������е���
	while (isChanged)
	{
		isChanged = false;

		node = l.head->next;
		Link last = l.head;

		for (size_t i = 0; i < length; i++)
		{
			if (node->exp < node->next->exp) {
				Link temp;
				temp = node->next;
				node->next = temp->next;
				last->next = temp;
				temp->next = node;
				isChanged = true;
				last = last->next;
			}
			else {
				last = node;
				node = node->next;
			}
		}

	}

	//���´�������ںϲ������ͷ�һ��ָ��ֵ��ͬ�Ľڵ�
	node = l.head->next;
	for (size_t i = 0; i < length - 1; i++)
	{

		if (node->exp == node->next->exp) {
			node->coe = node->next->coe + node->coe;
			LinkListNode* tmp = node->next;
			node->next = tmp->next;
			equalCase++;
			free(tmp);
		}
		else
			node = node->next;
	}
	length -= equalCase;
	return SUCCESS;
}

//����������ʽ�ϲ������ս���˳������
Status MergePoly(LinkList poly_1, LinkList poly_2, LinkList& poly_3) {
	InitList(poly_3);
	poly_3.head->next = poly_1.head->next;
	LinkListNode* p = poly_3.head->next;

	for (size_t i = 0; i < ElemAmount_1 - 1; i++)
	{
		p = p->next;
	}
	p->next = poly_2.head->next;
	ElemAmount_3 = ElemAmount_1 + ElemAmount_2;
	SortPoly(ElemAmount_3, poly_3);
	return SUCCESS;
}

int main() {
start:
	char* check = new char[50];//���ڻ������������
	cout << "�����������1������ʽ" << endl;
	cout << "��1������ʽ�������ǣ�";
	cin >> check;
	if (!IsNumber(check)) {//����Ƿ�Ϊ�Ƿ�����
		perror("Invalid Input");
		exit(INVALID_INPUT);
	}
	else
		ElemAmount_1 = atoi(check);
	LinkList poly_1;
	InitList(poly_1);
	GetPoly(ElemAmount_1, poly_1);
	cout << "\n������ĵ�1������ʽΪ��\n";
	PrintPoly(ElemAmount_1, poly_1);
	SortPoly(ElemAmount_1, poly_1);
	cout << endl << "��������֮��Ϊ��" << endl;
	PrintPoly(ElemAmount_1, poly_1);

	cout << "\n\n\n�����������2������ʽ" << endl;
	cout << "��2������ʽ�������ǣ�";
	cin >> check;
	if (!IsNumber(check)) {
		perror("Invalid Input");
		exit(INVALID_INPUT);
	}
	else
		ElemAmount_2 = atoi(check);
	delete check;
	LinkList poly_2;
	InitList(poly_2);
	GetPoly(ElemAmount_2, poly_2);
	cout << "\n������ĵ�2������ʽΪ��\n";
	PrintPoly(ElemAmount_2, poly_2);
	SortPoly(ElemAmount_2, poly_2);
	cout << endl << "��������֮��Ϊ��" << endl;
	PrintPoly(ElemAmount_2, poly_2);

	LinkList poly_3;
	MergePoly(poly_1, poly_2, poly_3);

	printf("\n\n����ʽ1�Ͷ���ʽ2�ϲ�����������֮��Ϊ��\n");
	PrintPoly(ElemAmount_3, poly_3);
	goto start;
	return 0;
	
}
