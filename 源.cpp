#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
struct wordnum
{
	char word;//�����ַ�
	double weight;//Ȩֵ
};
typedef struct Haffmantree
{
	wordnum a;
	int lchild, rchild, parent;
}*Haffman,Haff;
void Select(Haffman& T, int n, int& s1, int& s2)//�ҵ�Ȩֵ��С������ֵ���±꣬����s1��ȨֵС��s2��Ȩֵ
{
	int min = 0;
	for (int i = 1; i <= n; i++) 
	{
		if (T[i].parent == 0) 
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++) 
	{
		if (T[i].parent == 0 && T[i].a.weight < T[min].a.weight)
			min = i;
	}
	s1 = min;//�ҵ���һ����Сֵ��������s1
	for (int i = 1; i <= n; i++)
	{
		if (T[i].parent == 0&&i!=s1)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (T[i].parent == 0 && T[i].a.weight < T[min].a.weight&&i!=s1)
			min = i;
	}
	s2 = min;  //�ҵ��ڶ�����Сֵ��������s2
}
void creatHafuman(Haffman& T,wordnum L[],int n)
{
	int m = 2 * n - 1;//������n����Ҫ�󹹽������������򹹽������Ĺ��������Ľ������Ϊ2n-1
	T = (Haffman)calloc(m + 1, sizeof(Haff));
	for (int i = 1; i <= n; i++)//���ڵ㸳��ĸ�����Ӧ��Ȩֵ
	{
		T[i].a.weight = L[i].weight;
		T[i].a.word = L[i].word;
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(T, i - 1, s1, s2);   //ÿ��ѭ��ѡ��Ȩֵ��С��s1��s2,�������ǵĸ����
		T[i].a.weight = T[s1].a.weight + T[s2].a.weight;   //�´����Ľڵ�i ��Ȩ����s1��s2��Ȩ��֮��
		T[i].lchild = s1;   //�´����Ľڵ�i ��������s1
		T[i].rchild = s2;   //�´����Ľڵ�i ���Һ�����s2
		T[s1].parent = i;   //s1�ĸ������´����Ľڵ�i
		T[s2].parent = i;   //s2�ĸ������´����Ľڵ�i
	}
}
void HuffmanCoding(Haffman& T, char**& HuffCode, int n)
{
	HuffCode = (char**)malloc(sizeof(char*) * (n + 1));   //����char�Ͷ���ָ�룬�����ɰ������char*��ַ�����飬��n+1���ռ䣬��Ϊ�±�Ϊ0�Ŀռ䲻��
	char* tempcode = (char*)malloc(sizeof(char) * n);
	tempcode[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		int doing = i;   //doingΪ���ڱ�������ݽڵ�
		int parent = T[doing].parent;   //�ҵ��ýڵ�ĸ����
		while (parent) {   //ֱ�������Ϊ0(NULL)���������Ϊ�����ʱֹͣ
			if (T[parent].lchild == doing)   //����ý�����丸�������ӣ������Ϊ0������Ϊ1
				tempcode[--start] = '0';
			else
				tempcode[--start] = '1';
			doing = parent;   //�������Ͻ��б���
			parent = T[parent].parent;
		}
		HuffCode[i] = (char*)malloc(sizeof(char) * (n - start));   //�������ڴ洢������ڴ�ռ�
		strcpy(HuffCode[i], &tempcode[start]);   //�����뿽�����ַ�ָ�������е���Ӧλ��
	}
	free(tempcode); //�ͷŸ����ռ�
}
int main()
{
	FILE* fp;
	int i = 0;
	fp = fopen("test.txt", "r");
	if (fp == NULL)
	{
		fp = fopen("test.txt", "w");
		cout << "�ļ������ɹ�";
		return 0;
	}
	fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
	int max = ftell(fp);//����ļ���ǰָ��λ�ã���Ϊ�ļ�����
	rewind(fp);//���ļ�ָ���ƶ�����ͷ��׼����ȡ
	char* a = new char[max];
	fread(a, 1, max, fp);//��ȡ�ļ�
	wordnum L[27];
	for (int i = 1; i <= 26; i++)
	{
		L[i].weight = 0;
		L[i].word = 'a' + i - 1;
	}
	int  n = 26;
	for (int i = 0; i<max; i++)
	{
		for (int j = 1; j <= 26; j++)
		{
			if (a[i] == L[j].word||a[i]+32==L[j].word)
			{
				L[j].weight++;
			}
		}
	}
	for (int j = 1; j <= n; j++)
	{
		if (L[j].weight == 0)
		{
			for (int i = j; i < n; i++)
			{
				L[i].word = L[i + 1].word;
				L[i].weight = L[i + 1].weight;
			}
			n--;
			j--;
		}
	}
	for (int i = 1; i <= n; i++)//��Ȩֵ
	{
		L[i].weight = L[i].weight / max;
	}
	Haffman T;
	creatHafuman(T, L, n);
	char** HuffCode;
	HuffmanCoding(T, HuffCode, n);
	for (int i = 1; i <= n; i++)
		printf("  %c �Ĺ����������ǣ�%s��Ȩֵ�ǣ�%lf\n", T[i].a.word, HuffCode[i],T[i].a.weight);
	//cout << max;
	fclose(fp);



}
