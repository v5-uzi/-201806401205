#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
using namespace std;
 
typedef struct node{
	char ch;                          //�洢�ýڵ��ʾ���ַ���ֻ��Ҷ�ӽڵ��õĵ�
	int val;                          //��¼�ýڵ��Ȩֵ
	struct node *self,*left,*right;   //����ָ�룬�ֱ����ڼ�¼�Լ��ĵ�ַ�����ӵĵ�ַ���Һ��ӵĵ�ַ
	friend bool operator <(const node &a,const node &b) //��������أ��������ȶ��еıȽϽṹ
	{
		return a.val>b.val;           //������ȨֵС�����ȳ�����
	}
}node;
 
priority_queue<node> p;                //�������ȶ���
char res[30];                          //���ڼ�¼����������
void dfs(node *root,int level)         //��ӡ�ַ��Ͷ�Ӧ�Ĺ���������
{
	if(root->left==root->right)        //Ҷ�ӽڵ�����ӵ�ַһ�������Һ��ӵ�ַ����һ����ΪNULL;Ҷ�ӽڵ��¼���ַ�
	{
		if(level==0)                   //��AAAAA������ֻ��һ�ַ������
		{
			res[0]='0';
			level++;
		}
		res[level]='\0';               //�ַ�������'\0'����
		printf("%c=>%s\n",root->ch,res);
	}
	else
	{
		res[level]='0';                //���֧Ϊ0
		dfs(root->left,level+1);
		res[level]='1';                //�ҷ�֧Ϊ1
		dfs(root->right,level+1);
	}
}
void huffman(int *hash)                //������������
{
	node *root,fir,sec;
	for(int i=0;i<26;i++)              //����ֻ�ܴ���ȫΪ��дӢ���ַ�����Ϣ�����ʹ�ϣҲֻ��26��
	{
		if(!hash[i])                   //��Ӧ��ĸ��text��δ����
			continue;
		root=(node *)malloc(sizeof(node));          //���ٽڵ�
		root->self=root;                            //��¼�Լ��ĵ�ַ�����㸸�ڵ������Լ�
		root->left=root->right=NULL;                //�ýڵ���Ҷ�ӽڵ㣬���Һ��ӵ�ַ��ΪNULL
		root->ch='A'+i;                             //��¼�ýڵ��ʾ���ַ�
		root->val=hash[i];                          //��¼���ַ���Ȩֵ
		p.push(*root);                              //���ýڵ�ѹ�����ȶ���
	}
    //����ѭ��ģ�⽨�����̣�ÿ��ȡ��������С�Ľڵ�ϲ�������ѹ�����
    //��������ʣ��ڵ�����Ϊ1ʱ�����������������
	while(p.size()>1)
	{
		fir=p.top();p.pop();      //ȡ����С�Ľڵ�
		sec=p.top();p.pop();      //ȡ����С�Ľڵ�
		root=(node *)malloc(sizeof(node));          //�����½ڵ㣬������Ϊfir��sec�ĸ��ڵ�
		root->self=root;                            //��¼�Լ��ĵ�ַ������ýڵ�ĸ��ڵ�����
		root->left=fir.self;      //��¼���ӽڵ��ַ
		root->right=sec.self;     //��¼�Һ��ӽڵ��ַ
		root->val=fir.val+sec.val;//�ýڵ�ȨֵΪ������Ȩֵ֮��
		p.push(*root);            //���½ڵ�ѹ�����
	}
	fir=p.top();p.pop();          //�������������ĸ��ڵ�
	dfs(fir.self,0);              //���Ҷ�ӽڵ��¼���ַ��Ͷ�Ӧ�Ĺ���������
}
int main()
{
	char text[100];
	int hash[30];
	memset(hash,0,sizeof(hash)); //��ϣ�����ʼ��ȫΪ0
	printf("��������Ҫ����Ĵ�д�ַ�:\n");
	scanf("%s",text);             //������Ϣ��text
	for(int i=0;text[i]!='\0';i++)//ͨ����ϣ��ÿ���ַ��ĳ��ִ���
	{
		hash[text[i]-'A']++;      //����������е�ȫΪӢ�Ĵ�д��ĸ
	}
	huffman(hash);
	return 0;
}
