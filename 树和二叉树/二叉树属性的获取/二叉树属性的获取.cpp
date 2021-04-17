#include <iostream>
#include <cstdio>
#include <malloc.h>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define INIT_NODE_SIZE 10

//ERROR_EXIT_CODE
#define	UNKNOWN_ERROR 0x474544D8

//����DEBUG���
#define DEBUG_MODE_ON

typedef int Status;
typedef char elemType;

int node_amount = 0;

//�������ڵ�
typedef struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	elemType data;
}*Node;

//������
typedef struct BinaryTree
{
	Node root;
	int node_amount;
}Tree;

Node create()
{
	std::cout << "create() is called!" << std::endl;
	Node n;
	char temp_char;
	temp_char = getchar();
	if (temp_char == '#')
		return NULL;
	n = (Node)malloc(sizeof(TreeNode));
	if (n == NULL)
		exit(OVERFLOW);
	n->data = temp_char;
	n->left = create();
	n->right = create();
	return n;
}

void visit(Node n)
{
	std::cout << n->data;
}

Status pre_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	visit(n);
	pre_order_traverse(n->left);
	pre_order_traverse(n->right);
	return SUCCESS;
}

Status in_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	in_order_traverse(n->left);
	visit(n);
	in_order_traverse(n->right);
	return SUCCESS;
}

Status post_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	post_order_traverse(n->left);
	post_order_traverse(n->right);
	visit(n);
	return SUCCESS;
}

void count_record()
{
	node_amount++;
}

int get_node_amount(Node n)
{
	if (n == NULL)
		return NULL;
	count_record();
	get_node_amount(n->left);
	get_node_amount(n->right);
	return SUCCESS;
}


int main()
{
	Tree test_tree;
	std::cout << "Tips: ���²�������ķ�ʽ����Binary Tree��ʹ��\'#\'����÷�֧���ս�" << std::endl;
	test_tree.root = create();
	std::cout << "��������Ľ����" << std::endl;
	pre_order_traverse(test_tree.root);
	std::cout << std::endl;
	std::cout << "��������Ľ����" << std::endl;
	in_order_traverse(test_tree.root);
	std::cout << std::endl;
	std::cout << "��������Ľ����" << std::endl;
	post_order_traverse(test_tree.root);
	std::cout << std::endl;

	get_node_amount(test_tree.root);
	std::cout << "�������Ľڵ�����Ϊ��" << node_amount << std::endl;
	
	return 0;
}