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

//�ڵ�����
typedef struct LinkListNode
{
	ElemType data;
	struct LinkListNode* next;
}*Link, * Position;

//��������
typedef struct SinglyLinkList
{
	Link head, tail;
	int elemAmount;
}LinkList;

Status MakeNode(Link* p, ElemType e)
{
	*p = (Link)malloc(sizeof(LinkListNode));
	if (p == NULL)
	{
		perror("ERROR");
		return NULL;
	}
	else
	{
		(*p)->data = e;
		return SUCCESS;
	}
}

void FreeNode(Link p, LinkList l)
{
	Link search = l.head;
	while (search != NULL && search->next != p)
	{
		search = search->next;
	}
	if (search->next = p)
	{
		search->next = p->next;
	}
	free(p);
}

//��ʼ������
Status InitList(LinkList& l)
{
	Link p;
	p = (Link)malloc(sizeof(Link));
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

//�ݻ�һ������
Status DestroyList(LinkList& l)
{
	Link p = l.head;
	Link tmp;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
	l.head = NULL;
	l.tail = NULL;
	l.elemAmount = NULL;
	return SUCCESS;
}

//�������
Status ClearList(LinkList& l)
{
	l.elemAmount = 0;
	return SUCCESS;
}

//��һ���ڵ���뵽ͷ�ڵ�ǰ
Status InsFirst(Link headNode, Link insertNode)
{
	insertNode->next = headNode;
	return SUCCESS;
}

//ɾ��ͷ�ڵ�
Status DelFirst(Link headNode, Link& q)
{
	q = headNode->next;
	free(headNode);
	return SUCCESS;
}
 
//�������β������һ���ڵ�
Status Append(LinkList& l, Link s)
{
	l.tail->next = s;
	return SUCCESS;
}

//ɾ���ڵ�
Status Remove(LinkList& l, Link& q)
{
	q = l.tail;
	Link p = l.head;
	while (p->next != l.tail)
	{
		p = p->next;
	}
	l.tail = p;
	return SUCCESS;
}

//��p�ڵ�֮ǰ����һ���ڵ�
Status InsBefore(LinkList& l, Link& p, Link s)
{
	Link tmp = l.head;
	while (tmp->next != p)
	{
		tmp = tmp->next;
	}
	tmp->next = s;
	s->next = p;
	p = s;
	return SUCCESS;
}

//��p�ڵ�֮�����һ���ڵ�
Status InsAfter(LinkList& l, Link& p, Link s)
{
	Link tmp = p->next;
	p->next = s;
	s->next = tmp;
	p = s;
	return SUCCESS;
}

//Ϊ�ڵ�p�е�������ֵ
Status SetCurElem(Link& p, ElemType e)
{
	p->data = e;
	return SUCCESS;
}

//��ȡp�ڵ��д洢������ֵ
ElemType GetCurElem(Link p)
{
	return p->data;
}

//�ж������Ƿ�Ϊ��
Status ListEmpty(LinkList l)
{
	if (!l.head)
	{
		perror("The LinkList is not exist!");
		return ERROR;
	}
	if (l.head->next == NULL)
		return TRUE;
	else
		return FALSE;
}

//��ȡ�����Ԫ�ظ���
int ListLength(LinkList l)
{
	if (!l.head)
	{
		perror("The LinkList is not exist!");
		return ERROR;
	}
	return l.elemAmount;
}

//��ȡͷָ��
Position GetHead(LinkList l)
{
	return l.head;
}

//��ȡβָ��
Position GetLast(LinkList l)
{
	return l.tail;
}

//��ȡp�ڵ��ǰ��
Position PriorPos(LinkList l, Link p)
{
	if (p = l.head)
		return ERROR;
	else
	{
		Link tmp = l.head;
		while (tmp->next != p)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
}

//��ȡp�ڵ�ĺ��
Position NextPos(LinkList l, Link p)
{
	if (p = l.tail)
		return ERROR;
	else
	{
		return p->next;
	}
}

//����ָ�������е�index���ڵ��ָ��
Status LocatePos(LinkList l, int index, Link& p)
{
	if (!(index >= '0' && index <= '9') || index > l.elemAmount)
	{
		perror("Invalid index figure");
		return ERROR;
	}
	Link tmp = l.head;
	for (int i = 1; i < index; ++i)
	{
		tmp = tmp->next;
	}
	p = tmp;
	return SUCCESS;
}

//������L��Ѱ�Ҵ�������compare()�����Ľڵ�λ�ã�������ָ��ýڵ��ָ��
Position LocateElem(LinkList l, ElemType e, Status(*compare)(ElemType, ElemType))
{
	Link p = l.head;
	while (p != NULL && !(compare(((*p).data), e)))
	{
		p = p->next;
	}
	return p;
}

//��������
Status ListTraverse(LinkList l, Status (*visit)(LinkList l)) 
{
	Link p=l.head;
	while (p!=NULL)
	{
		if (visit(l))
			p = p->next;
		else
			return ERROR;
	}
	return SUCCESS;
}