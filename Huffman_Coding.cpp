#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
struct wordnum
{
	char word;//单个字符
	double weight;//权值
};
typedef struct Haffmantree
{
	wordnum a;
	int lchild, rchild, parent;
}*Haffman,Haff;
void Select(Haffman& T, int n, int& s1, int& s2)//找到权值最小的两个值的下标，其中s1的权值小于s2的权值
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
	s1 = min;//找到第一个最小值，并赋给s1
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
	s2 = min;  //找到第二个最小值，并赋给s2
}
void creatHafuman(Haffman& T,wordnum L[],int n)
{
	int m = 2 * n - 1;//若给定n个数要求构建哈夫曼树，则构建出来的哈夫曼树的结点总数为2n-1
	T = (Haffman)calloc(m + 1, sizeof(Haff));
	for (int i = 1; i <= n; i++)//给节点赋字母及其对应的权值
	{
		T[i].a.weight = L[i].weight;
		T[i].a.word = L[i].word;
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(T, i - 1, s1, s2);   //每次循环选择权值最小的s1和s2,生成它们的父结点
		T[i].a.weight = T[s1].a.weight + T[s2].a.weight;   //新创建的节点i 的权重是s1和s2的权重之和
		T[i].lchild = s1;   //新创建的节点i 的左孩子是s1
		T[i].rchild = s2;   //新创建的节点i 的右孩子是s2
		T[s1].parent = i;   //s1的父亲是新创建的节点i
		T[s2].parent = i;   //s2的父亲是新创建的节点i
	}
}
void HuffmanCoding(Haffman& T, char**& HuffCode, int n)
{
	HuffCode = (char**)malloc(sizeof(char*) * (n + 1));   //运用char型二级指针，可理解成包含多个char*地址的数组，开n+1个空间，因为下标为0的空间不用
	char* tempcode = (char*)malloc(sizeof(char) * n);
	tempcode[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		int doing = i;   //doing为正在编码的数据节点
		int parent = T[doing].parent;   //找到该节点的父结点
		while (parent) {   //直到父结点为0(NULL)，即父结点为根结点时停止
			if (T[parent].lchild == doing)   //如果该结点是其父结点的左孩子，则编码为0，否则为1
				tempcode[--start] = '0';
			else
				tempcode[--start] = '1';
			doing = parent;   //继续往上进行编码
			parent = T[parent].parent;
		}
		HuffCode[i] = (char*)malloc(sizeof(char) * (n - start));   //开辟用于存储编码的内存空间
		strcpy(HuffCode[i], &tempcode[start]);   //将编码拷贝到字符指针数组中的相应位置
	}
	free(tempcode); //释放辅助空间
}
int main()
{
	FILE* fp;
	int i = 0;
	fp = fopen("test.txt", "r");
	if (fp == NULL)
	{
		fp = fopen("test.txt", "w");
		cout << "文件建立成功";
		return 0;
	}
	fseek(fp, 0, SEEK_END);//文件指针移动到末尾
	int max = ftell(fp);//获得文件当前指针位置，即为文件长度
	rewind(fp);//将文件指针移动到开头，准备读取
	char* a = new char[max];
	fread(a, 1, max, fp);//读取文件
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
	for (int i = 1; i <= n; i++)//求权值
	{
		L[i].weight = L[i].weight / max;
	}
	Haffman T;
	creatHafuman(T, L, n);
	char** HuffCode;
	HuffmanCoding(T, HuffCode, n);
	for (int i = 1; i <= n; i++)
		printf("  %c 的哈夫曼编码是：%s；权值是：%lf\n", T[i].a.word, HuffCode[i],T[i].a.weight);
	//cout << max;
	fclose(fp);



}
