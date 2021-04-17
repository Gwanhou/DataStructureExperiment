#include <iostream>
#include <malloc.h>
#include <cstdio>
#include<cassert>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 300
#define STACK_INCREMENT 10
#define QUEUE_MAXSIZE 100

//ERROR_EXIT_CODE
#define	UNKNOWN_ERROR 0x474544D8

//����DEBUG���
#define DEBUG_MODE_ON

typedef int Status;
typedef char DataType;

//ȫ�ֱ���
int node_amount = 0;
int degree_1_node_amount = 0;
int degree_2_node_amount = 0;
int leaf_node_amount = 0;
long long signed int max_elem;
long long signed int min_elem;

//�������ڵ�
typedef struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	DataType data;

	int pre_order_counted_times;
	bool in_order_isCounted;
	bool post_order_isCounted;
}*Node;

//������
typedef struct BinaryTree
{
	Node root;
	int node_amount;
}Tree;


//ѭ�����е�˳��洢�ṹ
typedef Node QElemType;

typedef struct {
	QElemType data[QUEUE_MAXSIZE];
	int front; //ͷָ��
	int rear;//βָ�룬���зǿ�ʱ��ָ���βԪ�ص���һ��λ��
}SqQueue;

//���ʶ���
Status queue_visit(QElemType item) {
	printf("%p", item);
	return SUCCESS;
}

//��ʼ���ն���
Status InitQueue(SqQueue* sQ) {
	sQ->front = 0;
	sQ->rear = 0;
	return SUCCESS;
}

//���������
Status ClearQueue(SqQueue* Q) {
	Q->front = Q->rear = 0;
	return SUCCESS;
}

//�ж϶����Ƿ�Ϊ��
Status QueueEmpty(SqQueue Q) {
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

//���ض����е�Ԫ�ظ���
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + QUEUE_MAXSIZE) % QUEUE_MAXSIZE;
}

//���ض�ͷԪ��
Status GetHead(SqQueue Q, QElemType* e) {
	if (Q.front == Q.rear)//�Ƿ�Ϊ�ն���
		return ERROR;
	*e = Q.data[Q.front];
	return SUCCESS;
}

//�ڶ�β����Ԫ��
Status EnterQueue(SqQueue* Q, QElemType e) {
	if ((Q->rear + 1) % QUEUE_MAXSIZE == Q->front)//��������
		return ERROR;

	Q->data[Q->rear] = e;//�����β
	Q->rear = (Q->rear + 1) % QUEUE_MAXSIZE;//β��ָ����ƣ�����������ת��ͷ��
	return SUCCESS;
}

//Ԫ�س���
Status DelQueue(SqQueue* Q, QElemType* e) {
	if (Q->front == Q->rear)//���п�
		return ERROR;
	*e = Q->data[Q->front];//���ض�ͷԪ��
	Q->front = (Q->front + 1) % QUEUE_MAXSIZE;//��ͷָ����ƣ��絽���ת��ͷ��
	return SUCCESS;
}

//��������Ԫ��
Status QueueTraverse(SqQueue Q) {
	int i = Q.front;
	while ((i + Q.front) != Q.rear) {
		queue_visit(Q.data[i]);
		i = (i + 1) % QUEUE_MAXSIZE;
	}
	printf("\n");
	return SUCCESS;
}


//����Ϊջģ��
typedef Node Elemtype;

typedef struct SqStack
{
	Elemtype* base;
	Elemtype* top;
	int stack_size;
}Stack;

//��ʼ��һ��ջ
Status InitStack(Stack& s)
{
	s.base = (Elemtype*)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
	if (s.base == nullptr)
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
Status Push(Stack& s, Elemtype e)
{
	if ((s.top - s.base) >= s.stack_size) {//����Ƿ�ջ����
		//����׷�ӿռ䣬��СΪSTACK_INCREMENT
		s.base = (Elemtype*)realloc(s.base, s.stack_size + STACK_INCREMENT);
		//���ʱ�Ƿ�ɹ����䵽���ڴ�ռ�
		if (s.base == nullptr)
		{
			perror("Unable to allocate to memory space");
			exit(OVERFLOW);
		}
		//����ջ��λ�ú�ջ��С(stack_size)��¼
		s.top = s.base + s.stack_size;
		s.stack_size = s.stack_size + STACK_INCREMENT;
	}
	//*s.top++ = e;
	*s.top = e;
	s.top++;
	return SUCCESS;
}

//��ջ
Status Pop(Stack& s, Elemtype& e)
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

//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(Stack s)
{
	if (s.base == s.top)
		return TRUE;
	else
		return FALSE;
}

//�����������ڵ�
Node create()
{
	//std::cout << "create() is called!" << std::endl;
	Node n;
	DataType temp_var;
	temp_var = getchar();
	if (temp_var == '#')
		return nullptr;
	n = (Node)malloc(sizeof(TreeNode));
	if (n == nullptr)
		exit(OVERFLOW);
	n->data = temp_var;
	n->pre_order_counted_times = 0;
	n->in_order_isCounted = false;
	n->post_order_isCounted = false;
	n->left = create();
	n->right = create();
	return n;
}

//���ʶ������ڵ㲢������������
void visit(Node n)
{
	std::cout << n->data;
}

//����ݹ����
Status pre_order_traverse(Node n)
{
	if (n == nullptr)
		return NULL;
	visit(n);
	pre_order_traverse(n->left);
	pre_order_traverse(n->right);
	return SUCCESS;
}

//����ݹ����
Status in_order_traverse(Node n)
{
	if (n == nullptr)
		return NULL;
	in_order_traverse(n->left);
	visit(n);
	in_order_traverse(n->right);
	return SUCCESS;
}

//����ݹ����
Status post_order_traverse(Node n)
{
	if (n == nullptr)
		return NULL;
	post_order_traverse(n->left);
	post_order_traverse(n->right);
	visit(n);
	return SUCCESS;
}

SqQueue q;
Node root_node;

//��������
Status queue_traverse(Node n)
{
	if (n == root_node && n->left == nullptr && n->right == nullptr)
	{
		visit(n);
		return SUCCESS;
	}
	visit(n);
	if (n->left != nullptr)
		EnterQueue(&q, n->left);
	if (n->right != nullptr)
		EnterQueue(&q, n->right);
	if (QueueEmpty(q) && n != root_node)
		return SUCCESS;
	DelQueue(&q, &n);
	queue_traverse(n);
}

void count_record()
{
	node_amount++;
}

int recursion_get_node_amount(Node n)//�ݹ�����
{
	if (n == nullptr)
		return NULL;
	count_record();
	recursion_get_node_amount(n->left);
	recursion_get_node_amount(n->right);
	return SUCCESS;
}

//�ǵݹ����������ͳ�ƽڵ�����
void pre_get_node_info(Tree t)
{
	Node n = t.root;
	Stack node_stack;
	InitStack(node_stack);
	while (true)
	{
		if (n == t.root)
		{

			if (t.root->left != nullptr && t.root->right != nullptr)
			{
				if (t.root->pre_order_counted_times == 0)
				{
					max_elem = static_cast<int>(t.root->data);//�ڸ��ڵ��ʼ�����ֵ����Сֵ��׼
					min_elem = static_cast<int>(t.root->data);
					degree_2_node_amount++;
					visit(n);
					node_amount++;
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->left;
					continue;
				}
				if (t.root->pre_order_counted_times == 1)
				{
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->right;
					continue;
				}
				if (t.root->pre_order_counted_times == 2)
				{
					break;
				}
			}
			if (t.root->left != nullptr && t.root->right == nullptr)
			{
				if (t.root->pre_order_counted_times == 0)
				{
					max_elem = static_cast<int>(t.root->data);//�ڸ��ڵ��ʼ�����ֵ����Сֵ��׼
					min_elem = static_cast<int>(t.root->data);
					degree_1_node_amount++;
					visit(n);
					node_amount++;
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->left;
					continue;
				}
				if (t.root->pre_order_counted_times == 1)
				{
					break;
				}
			}
			if (t.root->left == nullptr && t.root->right != nullptr)
			{
				if (t.root->pre_order_counted_times == 0)
				{
					max_elem = static_cast<int>(t.root->data);//�ڸ��ڵ��ʼ�����ֵ����Сֵ��׼
					min_elem = static_cast<int>(t.root->data);
					degree_1_node_amount++;
					visit(n);
					node_amount++;
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->right;
					continue;
				}
				if (t.root->pre_order_counted_times == 1)
				{
					break;
				}
			}
			if (t.root->left == nullptr && t.root->right == nullptr)
			{
				max_elem = static_cast<int>(t.root->data);//���/��Сֵ��Ϊ���ڵ㱾��
				min_elem = static_cast<int>(t.root->data);
				leaf_node_amount++;
				visit(n);
				node_amount = 1;
				break;
			}
		}

		if (n->left != nullptr && n->right != nullptr && n != t.root)
		{
			if (n->pre_order_counted_times == 0)
			{
				if (static_cast<int>(n->data) > max_elem)
					max_elem = n->data;
				if (static_cast<int>(n->data) < min_elem)
					min_elem = n->data;
				degree_2_node_amount++;
				visit(n);
				node_amount++;
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				continue;
			}
			if (n->pre_order_counted_times == 1)
			{
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				continue;
			}
			if (n->pre_order_counted_times == 2)
			{
				Pop(node_stack, n);
			}
		}
		if (n->left != nullptr && n->right == nullptr)
		{
			if (n->pre_order_counted_times == 0)
			{
				if (static_cast<int>(n->data) > max_elem)
					max_elem = n->data;
				if (static_cast<int>(n->data) < min_elem)
					min_elem = n->data;
				degree_1_node_amount++;
				visit(n);
				node_amount++;
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				continue;
			}
			if (n->pre_order_counted_times == 1)
			{
				Pop(node_stack, n);
				continue;
			}
		}
		if (n->left == nullptr && n->right != nullptr)
		{
			if (n->pre_order_counted_times == 0)
			{
				if (static_cast<int>(n->data) > max_elem)
					max_elem = n->data;
				if (static_cast<int>(n->data) < min_elem)
					min_elem = n->data;
				degree_1_node_amount++;
				visit(n);
				node_amount++;
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				continue;
			}
			if (n->pre_order_counted_times == 1)
			{
				Pop(node_stack, n);
				continue;
			}
		}
		if (n->left == nullptr && n->right == nullptr)
		{
			if (static_cast<int>(n->data) > max_elem)
				max_elem = n->data;
			if (static_cast<int>(n->data) < min_elem)
				min_elem = n->data;
			leaf_node_amount++;
			visit(n);
			node_amount++;
			Pop(node_stack, n);
		}
	}
}

//�ǵݹ��������
void in_order_stack_traverse(Tree t)
{
	Stack s;
	InitStack(s);
	Node n = t.root;
	if (n->left == nullptr && n->right == nullptr)
	{
		visit(n);
		return;
	}
	while (true)
	{
		if (n->left != nullptr && !n->left->in_order_isCounted)
		{
			Push(s, n);
			n = n->left;
			continue;
		}
		else
		{
			if (!n->in_order_isCounted)
			{
				visit(n);
				n->in_order_isCounted = true;
			}
			if (n->right != nullptr && !n->right->in_order_isCounted)
			{
				Push(s, n);
				n = n->right;
				continue;
			}
			Pop(s, n);
		}
		if (StackEmpty(s))
		{
			if (n->left != nullptr && n->right != nullptr && n->left->in_order_isCounted &&
				n->right->in_order_isCounted)
				return;
			if (n->left != nullptr && n->right == nullptr && n->left->in_order_isCounted && n->in_order_isCounted == true)
				return;
			if (n->left == nullptr && n->right != nullptr && n->right->in_order_isCounted && n->in_order_isCounted == true)
				return;
		}
	}
}

//�ǵݹ鷽ʽ�������
void post_order_stack_traverse(Tree t)
{
	Node n;
	n = t.root;
	Stack s;
	InitStack(s);
	if (n->left == nullptr && n->right == nullptr)
	{
		visit(n);
		return;
	}
	while (true)
	{
		if (n->left != nullptr && !n->left->post_order_isCounted)
		{
			Push(s, n);
			n = n->left;
			continue;
		}
		else
		{
			if (n->right != nullptr && !n->right->post_order_isCounted)
			{
				Push(s, n);
				n = n->right;
				continue;
			}
			else
			{
				if (!n->post_order_isCounted)
				{
					visit(n);
					n->post_order_isCounted = true;
				}
				Pop(s, n);
			}
		}
		if (StackEmpty(s))
		{
			if (n->left != nullptr && n->right != nullptr && n->left->post_order_isCounted &&
				n->right->post_order_isCounted && n->post_order_isCounted)
				return;
			if (n->left != nullptr && n->right == nullptr && n->left->post_order_isCounted && n->post_order_isCounted)
				return;
			if (n->left == nullptr && n->right != nullptr && n->right->post_order_isCounted && n->post_order_isCounted)
				return;
		}
	}
}

//��������:
//Input:
//+**/A##B##C##D##E##
//InOrder
//A/B*C*D+E
//PostOrder
//AB/C*D*E+

int main()
{
	//��ʼ��һ���������򴴽���
	Tree test_tree;
	std::cout << "Tips: ���²�������ķ�ʽ����Binary Tree��ʹ��\'#\'����÷�֧���ս�" << std::endl;
	test_tree.root = create();


	//�ݹ鷽������
	std::cout << "�ݹ鷽������������Ľ����" << std::endl;
	pre_order_traverse(test_tree.root);
	std::cout << std::endl;

	std::cout << "�ݹ鷽������������Ľ����" << std::endl;
	in_order_traverse(test_tree.root);
	std::cout << std::endl;

	std::cout << "�ݹ鷽���ĺ�������Ľ����" << std::endl;
	post_order_traverse(test_tree.root);
	std::cout << std::endl << std::endl;

	//�ǵݹ鷽������
	std::cout << "�ǵݹ鷽������������Ľ����" << std::endl;
	pre_get_node_info(test_tree);
	std::cout << std::endl;

	std::cout << "�ǵݹ鷽������������Ľ����" << std::endl;
	in_order_stack_traverse(test_tree);
	std::cout << std::endl;

	std::cout << "�ǵݹ鷽���ĺ�������Ľ����" << std::endl;
	post_order_stack_traverse(test_tree);
	std::cout << std::endl << std::endl;


	//���а���α���
	InitQueue(&q);
	root_node = test_tree.root;
	std::cout << "ʹ�ö��а���α����Ľ����" << std::endl;
	queue_traverse(test_tree.root);
	std::cout << std::endl << std::endl;


	//����ڵ�ͳ����Ϣ
	std::cout << "���õݹ鷽�����ҵ��Ķ������Ľڵ�����Ϊ��" << node_amount << std::endl;
	std::cout << "�ǵݹ鷽�����ҵ��Ķ������Ľڵ�����Ϊ��" << node_amount << std::endl;
	std::cout << "�ǵݹ鷽�����ҵ��Ķ�������Ϊ2�Ľڵ�����Ϊ��" << degree_2_node_amount << std::endl;
	std::cout << "�ǵݹ鷽�����ҵ��Ķ�������Ϊ1�Ľڵ�����Ϊ��" << degree_1_node_amount << std::endl;
	std::cout << "�ǵݹ鷽�����ҵ��Ķ�����Ҷ�ӽڵ�����Ϊ��" << leaf_node_amount << std::endl;
	std::cout << "����������ֵ��С��Ԫ����ֵΪ��" << static_cast<int> (min_elem) << '\t' << \
		"ת��Ϊԭʼ���ͼ���" << static_cast<DataType>(min_elem) << std::endl;
	std::cout << "����������ֵ����Ԫ����ֵΪ��" << static_cast<int> (max_elem) << '\t' << \
		"ת��Ϊԭʼ���ͼ���" << static_cast<DataType>(max_elem) << std::endl;

	return 0;
}