#include <iostream>
#include <cstdio>
#include <malloc.h>

#define SUCCESS 1
#define ERROR 0
#define INIT_SIZE 100
#define MAX_SIZE 200

using namespace std;

typedef int Status;

struct Poly {
	int exp;
	float coe;
}poly_1[INIT_SIZE], poly_2[INIT_SIZE], poly_3[MAX_SIZE];

int ElemAmount_3 = 0;

//��ȡ����ʽ��ϵ����ָ��
Status GetPoly(int length, Poly* poly) {
	for (size_t i = 0; i < length; i++)
	{
		printf("�������%d���ָ����", i + 1);
		scanf_s("%d", &poly[i].exp);

		printf("�������%d���ϵ����", i + 1);
		scanf_s("%f", &poly[i].coe);
	}
	return SUCCESS;
}

//�������ʽ
Status PrintPoly(int length, Poly* poly) {
	for (size_t i = 0; i < length - 1; i++)
	{
		if (poly[i].coe == 0)
			continue;
		else {
			if (poly[i].coe == 1)
				printf(" X^%d +", poly[i].exp);
			else
				printf(" (%.2f)*X^%d +", poly[i].coe, poly[i].exp);
		}
	}
	if (poly[length - 1].coe != 0)
	{
		if (poly[length - 1].coe == 1)
			printf(" X^%d", poly[length - 1].exp);
		else
			printf(" (%.2f)*X^%d", poly[length - 1].coe, poly[length - 1].exp);
	}
	return SUCCESS;
}

//��������
Status SortPoly(int& length, Poly* poly) {
	int equalCase = 0;
	for (size_t i = 0; i < length - 1; i++)
	{
		for (size_t j = i + 1; j < length; j++)
		{
			if (poly[i].exp == poly[j].exp && poly[i].exp != -1)
			{
				poly[i].coe += poly[j].coe;
				poly[j].exp = -1;
				poly[j].coe = 0;
				equalCase++;
			}
			if (poly[i].exp < poly[j].exp) {
				int exp_temp;
				exp_temp = poly[j].exp;
				poly[j].exp = poly[i].exp;
				poly[i].exp = exp_temp;
				float coe_temp;
				coe_temp = poly[j].coe;
				poly[j].coe = poly[i].coe;
				poly[i].coe = coe_temp;
			}
		}
	}
	length -= equalCase;
	return SUCCESS;
}

//����������ʽ�ϲ������ս���˳������
Status MergePoly(int ElemAmount_1, int ElemAmount_2, Poly* poly_1, Poly* poly_2, Poly* poly_3) {
	int i = 0, j = 0, k = 0;
	while (i < ElemAmount_1 && j < ElemAmount_2)
	{
		if (poly_1[i].exp == poly_2[j].exp) {
			poly_3[k].coe = poly_1[i].coe + poly_2[j].coe;
			poly_3[k].exp = poly_1[i].exp;
			i++;
			j++;
			k++;
		}
		if (poly_1[i].exp > poly_2[j].exp) {
			poly_3[k].exp = poly_1[i].exp;
			poly_3[k].coe = poly_1[i].coe;
			i++;
			k++;
		}
		if (poly_1[i].exp < poly_2[j].exp)
		{
			poly_3[k].exp = poly_2[j].exp;
			poly_3[k].coe = poly_2[j].coe;
			j++;
			k++;
		}
	}
	if (i == ElemAmount_1) {
		for (; j < ElemAmount_2; j++)
		{
			poly_3[k + 1].coe = poly_2[j].coe;
			poly_3[k + 1].exp = poly_2[j].exp;
			k++;
		}
	}
	else {
		for (; i < ElemAmount_1; i++)
		{
			poly_3[k + 1].coe = poly_1[i].coe;
			poly_3[k + 1].exp = poly_1[i].exp;
			k++;
		}
	}
	ElemAmount_3 = k;
	return SUCCESS;
}

int main() {
	int ElemAmount_1 = 0;
	cout << "�����������1������ʽ" << endl;
	cout << "��һ������ʽ�������ǣ�";
	cin >> ElemAmount_1;
	GetPoly(ElemAmount_1, poly_1);
	cout << "\n������ĵ�1������ʽΪ��\n";
	PrintPoly(ElemAmount_1, poly_1);
	SortPoly(ElemAmount_1, poly_1);
	cout << endl << "��������֮��Ϊ��" << endl;
	PrintPoly(ElemAmount_1, poly_1);

	cout << endl << endl;

	int ElemAmount_2 = 0;
	cout << "�����������2������ʽ" << endl;
	cout << "��2������ʽ�������ǣ�";
	cin >> ElemAmount_2;
	GetPoly(ElemAmount_2, poly_2);
	cout << "\n������ĵ�2������ʽΪ��\n";
	PrintPoly(ElemAmount_2, poly_2);
	SortPoly(ElemAmount_2, poly_2);
	cout << endl << "��������֮��Ϊ��" << endl;
	PrintPoly(ElemAmount_2, poly_2);

	MergePoly(ElemAmount_1, ElemAmount_2, poly_1, poly_2, poly_3);

	printf("\n\n����ʽ1�Ͷ���ʽ2�ϲ�֮��Ϊ��\n");
	PrintPoly(ElemAmount_3, poly_3);

	return 0;
}