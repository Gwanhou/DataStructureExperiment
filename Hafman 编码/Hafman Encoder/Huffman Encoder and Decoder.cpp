#pragma warning (disable:4996)

#include <iostream>
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

//ERROR_EXIT_CODE
#define INVALID_INPUT 0x474544D8

//����DEBUG���
//#define DEBUG_MODE_ON

using namespace std;

//ȫ�ֱ���
int array_length;

typedef int Status;

//���������ڵ�
typedef struct HuffmanTreeNode {
	char letter;
	int weight;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;
	bool isDeleted;
	int pre_order_counted_times;
} *TreeNode;

//��������
struct HuffmanTree {
	HuffmanTreeNode* root;
};

typedef TreeNode ElemType;

typedef struct SqStack {
	ElemType* base;
	ElemType* top;
	int stack_size;
} Stack;

//��ʼ��һ��ջ
Status InitStack(Stack& s) {
	s.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (s.base == nullptr) {
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
Status Push(Stack& s, TreeNode e) {
	if ((s.top - s.base) >= s.stack_size) {//����Ƿ�ջ����
		//����׷�ӿռ䣬��СΪSTACK_INCREMENT
		s.base = (ElemType*)realloc(s.base, s.stack_size + STACK_INCREMENT);
		//���ʱ�Ƿ�ɹ����䵽���ڴ�ռ�
		if (s.base == nullptr) {
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
Status Pop(Stack& s, ElemType& e) {
	if (s.top == s.base) {
		return ERROR;
	}
	else {
		s.top--;
		e = *s.top;
		return SUCCESS;
	}
}

//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(Stack s) {
	if (s.base == s.top)
		return TRUE;
	else
		return FALSE;
}

//����ĸƵ�ȱ����������ڵ㣬�����������ڵ�ĵ�ַ����������
void GetAlphabetFreq(TreeNode* node_array) {
	cout << "**********��ȡ��ĸƵ�ȱ�**********" << endl;

	auto sp = (TreeNode)malloc(sizeof(HuffmanTreeNode));
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

	for (int i = 0; i < 26; ++i) {
		auto tn = (TreeNode)malloc(sizeof(HuffmanTreeNode));
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

TreeNode GetMinWeight(TreeNode* node_array) {
	int min_index = 10000;
	int min_weight = 10000;
	for (int i = 0; i < array_length; ++i) {
		if (node_array[i]->weight < min_weight && !node_array[i]->isDeleted) {
			min_weight = node_array[i]->weight;
			min_index = i;
		}
	}
	node_array[min_index]->isDeleted = true;
	return node_array[min_index];
}

bool isEmpty(TreeNode* node_array) {
	for (int i = 0; i < array_length; ++i)
		if (!node_array[i]->isDeleted)
			return false;
	return true;
}

void SaveNodeToArray(TreeNode new_node, TreeNode* node_array) {
	node_array[array_length] = new_node;
	array_length++;
}

void CreateHuffmanTree(HuffmanTree& t, TreeNode* node_array) {
	TreeNode parent_node;
	while (true) {
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

//����Huffman����
void HuffmanCodeGenerator(HuffmanTree t, string* huffman_code_list) {
	string s;
	s = "";
	TreeNode n = t.root;
	Stack node_stack;
	InitStack(node_stack);
	while (true) {
		if (n == t.root) {
			if (n->pre_order_counted_times == 0) {
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				s += '1';
			}
			if (n->pre_order_counted_times == 1) {
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				s += '0';
			}
			if (n->pre_order_counted_times == 2)
				break;
		}
		else {
			if (n->letter == '#') {
				if (n->pre_order_counted_times == 0) {
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->left;
					s += '1';
				}
				if (n->pre_order_counted_times == 1) {
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->right;
					s += '0';
				}
				if (n->pre_order_counted_times == 2) {
					Pop(node_stack, n);
					s = s.substr(0, s.length() - 1);
				}
			}
			else {
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

string SearchHuffmanCode(char c, string* huffman_code_list) {
	return huffman_code_list[c - 'a' + 1];
}

string HuffmanEncoder(string plaintext, string* huffman_code_list) {
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
	string ciphertext;
	for (char i : plaintext) {
		if (i == ' ')
			ciphertext += huffman_code_list[0];
		else
			ciphertext += SearchHuffmanCode(i, huffman_code_list);
	}
	return ciphertext;
}

string HuffmanDecoder(const string& ciphertext, string* huffman_code_list) {
	string plaintext;
	int length = 1; //10010000100001100011111101000011100011011110
	int start_index = 0;
	bool isMatch = false;
	while (true) {
		if (start_index + length > ciphertext.length())
			return plaintext;
		string temp = ciphertext.substr(start_index, length);
		for (int i = 0; i < 27; ++i) {
			if (temp == huffman_code_list[i]) {
				isMatch = true;
				if (i == 0)
					plaintext += ' ';
				else
					plaintext += (char)(i + 'a' - 1);
			}
		}
		if (isMatch) {
			start_index += length;
			length = 1;
			isMatch = false;
		}
		else {
			if (start_index + length >= ciphertext.length()) {
				cout << "δ֪������ֹ�˽����������У�" << endl;
				exit(INVALID_INPUT);
			}
			length++;
		}
	}
}

string GetBinCode(const string& s)
{
	string bin_code;
	cout << "**********ԭ�ĵĶ����Ʊ���**********" << endl;
	for (char i : s)
	{
		char temp[100];
		itoa(i, temp, 2);
		cout << i << '\t' << temp << endl;
		bin_code += temp;
	}
	return bin_code;
}

int main() {
	cout << "Tips:Here is the Sample Frequency of the alphabet:" << endl
		<< "186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1" << endl << endl << endl;
	//����Huffman��
	auto* node_array = new TreeNode[1000];
	GetAlphabetFreq(node_array);
	HuffmanTree test_tree{};
	CreateHuffmanTree(test_tree, node_array);
	auto* huffman_code_list = new string[30];

	//��ȡ27���ַ���Huffman����
	HuffmanCodeGenerator(test_tree, huffman_code_list);

	//��Ӧ�ؽ�Ӣ��ת��ΪHuffman���봦��������
start:
	cout << "**********��ѡ�������߽���**********\n  #���� 1 ������תдΪHuffman Code#\n  #���� 2 ��Huffman Codeת��Ϊ����#" << endl;
	char choice;
	fflush(stdin);
	cin >> choice;

	switch (choice) {
	case '1': {
		char plaintext[1000] = { 0 };
		cout << endl << endl << "**************������ԭ��**************" << endl;
		cin.ignore();
		gets_s(plaintext);
		string ciphertext = HuffmanEncoder(plaintext, huffman_code_list);
		cout << "Huffman Code���£�" << endl;
		cout << ciphertext << endl;
		cout << "***************תд����***************" << endl << endl;
		string bin_text = GetBinCode(plaintext);
		cout << "***********ԭ�ĵĶ����Ʊ���***********" << endl;
		cout << bin_text << endl;
		double compression_ratio = (1.0 - (double)ciphertext.length() / (double)bin_text.length()) * 100;
		cout << endl << "ѹ���� ---> " << compression_ratio << '%' << endl;
		break;
	}
	case '2': {
		char ciphertext[1000] = { 0 };
		cout << endl << endl << "**********������Huffman Code**********" << endl;
		cin.ignore();
		gets_s(ciphertext);
		string plaintext = HuffmanDecoder(ciphertext, huffman_code_list);
		cout << "�������£�" << endl;
		cout << plaintext << endl;
		cout << "***************תд����***************" << endl << endl << endl;
		string bin_text = GetBinCode(plaintext);
		cout << "***********ԭ�ĵĶ����Ʊ���***********" << endl;
		cout << bin_text << endl;
		string ciphertext_copy = ciphertext;
		double compression_ratio = ((double)bin_text.length() / (double)ciphertext_copy.length() - 1.0) * 100;
		cout << endl << "��������� ---> " << compression_ratio << '%' << endl;
		break;
	}
	default:
		exit(INVALID_INPUT);
	}
	cout << "*************�������н���*************" << endl << endl << endl << endl << endl;
	goto start;
}

//��������
//#186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1

//#Huffman---10010000100001100011111101000011100011011110
//#Plaintext---i love you