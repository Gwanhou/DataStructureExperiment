#pragma warning (disable:4996)

#include <iostream>
#include <malloc.h>
#include <cstdio>
#include<cassert>
#include <string>
#include <algorithm>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 300
#define STACK_INCREMENT 10
#define QUEUE_MAXSIZE 100
#define OVERFLOW 3

//ERROR_EXIT_CODE
#define	INVALID_INPUT 0x474544D8

//����DEBUG���
#define DEBUG_MODE_ON

using namespace std;

typedef int Status;

int array_length;

//���������ڵ�
typedef struct HuffmanTreeNode
{
	char letter;
	int weight;
	string* huffman_code;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;
	bool isDeleted;
	int pre_order_counted_times;
}*TreeNode;

//��������
typedef struct HuffmanTree
{
	HuffmanTreeNode* root;
	int node_amount;
}Tree;

typedef TreeNode Elemtype;

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
	sp->left = nullptr;
	sp->right = nullptr;
	sp->pre_order_counted_times = 0;
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
		tn->left = nullptr;
		tn->right = nullptr;
		tn->pre_order_counted_times = 0;
		node_array[i + 1] = tn;
	}
	cout << endl << "**********��ȡ����**********" << endl;
	array_length = 27;
}

TreeNode GetMinWeight(TreeNode* node_array)
{
	int min_index = 10000;
	int min_weight = 10000;
	for (int i = 0; i < array_length; ++i)
	{
		if (node_array[i]->weight < min_weight && node_array[i]->isDeleted == false)
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
	for (int i = 0; i < array_length; ++i)
		if (node_array[i]->isDeleted == false)
			return false;
	return true;
}

void SaveNodeToArray(TreeNode new_node, TreeNode* node_array)
{
	node_array[array_length] = new_node;
	array_length++;
}

void CreateHuffmanTree(HuffmanTree& t, TreeNode* node_array)
{
	TreeNode parent_node = nullptr;
	while (true)
	{
		TreeNode node_1, node_2;
		node_1 = GetMinWeight(node_array);
		node_2 = GetMinWeight(node_array);
		parent_node = (TreeNode)malloc(sizeof(HuffmanTreeNode));
		if (parent_node == nullptr)
			exit(OVERFLOW);
		parent_node->isDeleted = false;
		parent_node->left = node_1;
		parent_node->right = node_2;
		parent_node->letter = '#';
		parent_node->weight = node_1->weight + node_2->weight;
		parent_node->pre_order_counted_times = 0;
		if (isEmpty(node_array))
			break;
		SaveNodeToArray(parent_node, node_array);
	}
	t.root = parent_node;
}

//���ʶ������ڵ㲢������������
void visit(TreeNode n, string s)
{
	if (n->letter == '#')
		return;

	std::cout << '\'' << n->letter << '\'' << "��ȨֵΪ��" << n->weight << ",Huffman����Ϊ��" << s << endl;
}

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
Status Push(Stack& s, TreeNode e)
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

//����Huffman����
void HuffmanCodeGenerator(HuffmanTree t, string* huffman_code_list)
{
	string s;
	s = "";
	TreeNode n = t.root;
	Stack node_stack;
	InitStack(node_stack);
	while (true)
	{
		if (n == t.root)
		{
			if (n->pre_order_counted_times == 0)
			{
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				s += '1';
			}
			if (n->pre_order_counted_times == 1)
			{
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				s += '0';
			}
			if (n->pre_order_counted_times == 2)
				break;
		}
		else
		{
			if (n->letter == '#')
			{
				if (n->pre_order_counted_times == 0)
				{
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->left;
					s += '1';
				}
				if (n->pre_order_counted_times == 1)
				{
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->right;
					s += '0';
				}
				if (n->pre_order_counted_times == 2)
				{
					Pop(node_stack, n);
					s = s.substr(0, s.length() - 1);
				}
			}
			else
			{
				std::cout << '\'' << n->letter << '\'' << "��ȨֵΪ��" << n->weight << ",Huffman����Ϊ��" << s << endl;
				//n->huffman_code = (string*)malloc(100);
				//*(n->huffman_code) = s;
				if (n->letter != ' ')
					huffman_code_list[n->letter - 'a' + 1] = s;
				if (n->letter == ' ')
					huffman_code_list[0] = s;
				Pop(node_stack, n);
				s = s.substr(0, s.length() - 1);
			}
		}
	}
}

string SearchHuffmanCode(char c, string* huffman_code_list)
{
	return huffman_code_list[c - 'a' + 1];
}

string HuffmanEncoder(string plaintext, string* huffman_code_list)
{
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
	string ciphertext = "";
	for (int i = 0; i < plaintext.length(); ++i)
	{
		if (plaintext.at(i) == ' ')
			ciphertext += huffman_code_list[0];
		else
			ciphertext += SearchHuffmanCode(plaintext.at(i), huffman_code_list);
	}
	return ciphertext;
}

string HuffmanDecoder(string ciphertext, string* huffman_code_list)
{
	string plaintext = "";
	int length = 1;
	int start_index = 0;
	bool isMatch = false;
	while (true)
	{
		string temp = ciphertext.substr(start_index, start_index + length - 1);
		for (int i = 0; i < 27; ++i)
		{
			if (temp==huffman_code_list[i])
			{
				isMatch = true;
				if (i == 0)
					plaintext += ' ';
				else
					plaintext += (char)(i + 'a' - 1);
			}
		}
		if (isMatch)
		{
			start_index += length;
			length = 1;
			isMatch = false;
		}
		else
			length++;
		if (start_index + length == ciphertext.length())
			return plaintext;
	}
}

int main()
{
	cout << "Sample Frequency of the alphabet:" << endl << "186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1" << endl << endl << endl;
	//����Huffman��
	TreeNode* node_array = new TreeNode[1000];
	GetAlphabetFreq(node_array);
	HuffmanTree test_tree;
	CreateHuffmanTree(test_tree, node_array);
	string* huffman_code_list = new string[30];

	//��ȡ27���ַ���Huffman����
	HuffmanCodeGenerator(test_tree, huffman_code_list);

	//��Ӧ�ؽ�Ӣ��ת��ΪHuffman���봦��������
	start:
	/*cout << "��ѡ�������߽��룺\n���� 1 ������תдΪHuffman Code\n���� 2 ��Huffman Codeת��Ϊ����" << endl;
	char choice;
	cin >> choice;
	
	switch (choice)
	{
	case '1':{
		char plaintext[1000];
		cout << "���������ģ�";
		gets_s(plaintext);
		string ciphertext = HuffmanEncoder(plaintext, huffman_code_list);
		cout << "�������£�" << endl;
		cout << ciphertext << endl;
			break;
		}
	case '2':{
		char ciphertext[1000];
		cout << "���������ģ�";
		gets_s(ciphertext);
		string plaintext = HuffmanDecoder(ciphertext, huffman_code_list);
		cout << "�������£�" << endl;
		cout << plaintext << endl;
		}
	}*/
	char ciphertext[1000];
	cout << "���������ģ�";
	gets_s(ciphertext);
	string plaintext = HuffmanDecoder(ciphertext, huffman_code_list);
	cout << "�������£�" << endl;
	cout << plaintext << endl;
	
	goto start;

	//test_only
	//cout << huffman_code_list[1];

	return 0;
}

//��������
//186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1