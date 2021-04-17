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
	if (temp_char=='#')
		return NULL;
	n = (Node)malloc(sizeof(TreeNode));
	if (n == NULL)
		exit(OVERFLOW);
	n->data = temp_char;
	n->left = create();
	n->right = create();
	return n;
}

int main()
{
	Tree test_tree;
	std::cout << "Tips: ���²�������ķ�ʽ����Binary Tree��ʹ��\'#\'����÷�֧���ս�" << std::endl;
	test_tree.root = create();
	return 0;
}