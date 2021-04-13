#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <process.h>

using namespace std;

#define SUCCESS 1
#define ERROR 0
#define INIT_SIZE 10
#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0

//int�ɸ�Ϊ������������
typedef int ElemType;
typedef int Status;

typedef struct
{
	int length;
	size_t listSize;
	int* elemAddress;
}SeqList;

//��ʼ��˳�����Ա�
Status InitList(SeqList& l)
{
	l.elemAddress = (ElemType*)malloc(INIT_SIZE);//Ϊ���Ա�L�����ڴ�ռ�
	if (!l.elemAddress)
	{
		exit(OVERFLOW);//����޷����뵽�ڴ�ռ䣬�������"OVERFLOW 3"
	}
	l.length = 0;
	l.listSize = INIT_SIZE;
	return SUCCESS;
}

//�ݻ�һ��˳�����Ա�
Status DestroyList(SeqList& l)
{
	free(l.elemAddress);
	l.elemAddress = NULL;
	l.length = 0;
	l.listSize = 0;
	return SUCCESS;
}

//���һ��˳�����Ա�
Status ClearList(SeqList& l)
{
	l.length = 0;
	return SUCCESS;
}

//�ж�˳�����Ա��Ƿ�Ϊ��
Status ListEmpty(SeqList& l)
{
	if (l.length == 0)
		return TRUE;
	else
		return FALSE;
}

//��ȡ˳�����Ա��е�i��Ԫ�����ݵ�ֵ
Status GetElem(SeqList l, int i, ElemType& e)
{
	e = l.elemAddress[i];
	return SUCCESS;
}

//��˳�����Ա���Ѱ�Ҵ�������compare()������λ��
int LocateElem(SeqList l, ElemType e, Status compare(ElemType, ElemType))
{
	int i = 0;
	for (i = 0; i <= l.length; ++i)
	{
		if (compare(l.elemAddress[i], e))
		{
			break;
		}
	}
	if (i < l.length)
		return i;
	else
		return ERROR;
}

//��ȡ˳�����Ա���Ԫ�ص�ǰһ��Ԫ��
Status PriorElem(SeqList l, ElemType curElem, ElemType& preElem)
{
	if (l.elemAddress[0] != preElem)
	{
		int i = 1;
		while (i < l.length && l.elemAddress[i] != curElem)
		{
			i++;
		}
		preElem = l.elemAddress[i - 1];
		return SUCCESS;
	}
	return ERROR;
}

//��ȡ˳�����Ա���Ԫ�ص���һ��Ԫ��
Status NextElem(SeqList l, ElemType curElem, ElemType& nextElem)
{
	if (l.elemAddress[l.length - 1] != curElem)
	{
		int i = 0;
		while (i < l.length && l.elemAddress[i] != curElem)
		{
			i++;
		}
		nextElem = l.elemAddress[i + 1];
		return SUCCESS;
	}
	else
		return ERROR;
}

//��˳�����Ա�ĵ�index��λ�ò�����Ԫ��
Status ListInsert(SeqList& l, int index, ElemType& e)
{
	for (int i = l.length - 1; i >= index; --i)
	{
		l.elemAddress[i + 1] = l.elemAddress[i];
	}
	l.elemAddress[index] = e;
	l.length++;
	return SUCCESS;
}

//ɾ��˳�����Ա��еĵ�index��Ԫ��
Status ListDelete(SeqList& l, int index, ElemType& e)
{
	e = l.elemAddress[index];
	for (int i = index; i < l.length; ++i)
	{
		l.elemAddress[i] = l.elemAddress[i + 1];
	}
	l.length--;
	return SUCCESS;
}

//�鲢La,Lb��Lc
Status ListMerge(SeqList la, SeqList lb, SeqList& lc)
{
	ElemType* a_tail = la.elemAddress + la.length - 1;
	ElemType* b_tail = lb.elemAddress + la.length - 1;

	ElemType* pa = la.elemAddress;
	ElemType* pb = lb.elemAddress;

	ElemType* pc = (ElemType*)malloc(la.length + lb.length);

	while (pa <= a_tail && pb <= b_tail)
	{
		if (*pa <= *pb)
		{
			*pc = *pa;
			pc++;
			pa++;
		}
		else
		{
			*pc = *pb;
			pc++;
			pb++;
		}
	}
	while (pa <= a_tail)
	{
		*pc = *pa;
		pc++;
		pa++;
	}
	while (pb <= b_tail)
	{
		*pc = *pb;
		pc++;
		pb++;
	}
}