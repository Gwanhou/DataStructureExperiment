#include <iostream>
#include <malloc.h>
#include <cstdio>
#include<cassert>
#include <string>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 300
#define STACK_INCREMENT 10
#define QUEUE_MAXSIZE 100

//ERROR_EXIT_CODE
#define	INVALID_INPUT 0x474544D8

//����DEBUG���
#define DEBUG_MODE_ON

using namespace std;

typedef int Status;


//���������ڵ�
typedef struct HuffmanTreeNode
{
	char letter;
	int weight;
	string huffman_code;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;
	bool isDeleted;
}*TreeNode;

//��������
typedef struct HuffmanTree
{
	HuffmanTreeNode* root;
	int node_amount;
}Tree;

//����ĸƵ�ȱ����������ڵ㣬�����������ڵ�ĵ�ַ����������
void GetAlphabetFreq(TreeNode* node_array)
{
	cout << "**********��ȡ��ĸƵ�ȱ�**********" << endl;

	TreeNode sp = (TreeNode)malloc(sizeof(HuffmanTreeNode));
	if (sp == nullptr)
		exit(OVERFLOW);
	sp->letter = ' ';
	cout << "������\' �ո� \'��Ȩֵ��";
	cin >> sp->weight;
	sp->isDeleted = false;
	node_array[0] = sp;

	for (int i = 0; i < 26; ++i)
	{
		TreeNode tn = (TreeNode)malloc(sizeof(HuffmanTreeNode));
		if (tn == nullptr)
			exit(OVERFLOW);
		tn->letter = (char)('a' + i);
		cout << "������\' " << tn->letter << " \'��Ȩֵ��";
		cin >> tn->weight;
		tn->isDeleted = false;
		node_array[i + 1] = tn;
	}
	cout << endl << "**********��ȡ����**********" << endl;
}

TreeNode GetMinWeight(TreeNode* node_array)
{
	int min_index = 0;
	int min_weight = node_array[0]->weight;
	for (int i = 1; i <= 26; ++i)
	{
		if (node_array[i]->weight<min_weight&&node_array[i]->isDeleted==false)
		{
			min_weight = node_array[i]->weight;
			min_index = i;
		}
	}
	node_array[min_index]->isDeleted = true;
	return node_array[min_index];
}

bool isEmpty(TreeNode* node_array)
{
	for (int i = 0; i < 27; ++i)
		if (node_array[i]->isDeleted == false)
			return false;
	return true;
}

void CreateHuffmanTree(HuffmanTree &t,TreeNode* node_array)
{
	while (!isEmpty(node_array))
	{
		TreeNode node_1, node_2;
		node_1 = GetMinWeight(node_array);
		node_2 = GetMinWeight(node_array);
		TreeNode par
	}
	
}

int main()
{
	TreeNode* node_array=new TreeNode[30];
	GetAlphabetFreq(node_array);
	HuffmanTree test_tree;
	CreateHuffmanTree(test_tree, node_array);
}