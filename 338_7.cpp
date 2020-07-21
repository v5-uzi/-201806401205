#include <iostream>
using namespace std;
//�ӿռ��нڵ�����
#include "beibao.h"
double c=30; 
const int n=3;
double *w;
double *p;
double cw;
double cp;
int    *bestX;
MaxHeap * heap;
//�Ͻ纯��bound����������Ӧ��ֵ���Ͻ�
 double bound(int i){
	double cleft=c-cw;
	double b=cp;
	while(i<=n&&w[i]<=cleft){
		cleft=cleft-w[i];
		b=b+p[i];
		i++;
	}
	//װ��ʣ������װ������
	if(i<=n)
		b=b+p[i]/w[i]*cleft;
	return b;
}
//addLiveNode��һ���µĻ�����뵽�Ӽ��������ȶ�����
 void addLiveNode(double up,double pp,double ww,int lev,BBnode* par,bool ch){
	//��һ���µĻ�����뵽�Ӽ�����������
	BBnode *b=new BBnode(par,ch);
	HeapNode  node =HeapNode(b,up,pp,ww,lev);
	heap->put(node);
}
 double MaxKnapsack(){
	//���ȶ���ʽ��֧�޽編����������ֵ��bestx�������Ž�
	BBnode * enode=new BBnode();
	int i=1;
	double bestp=0;//��ǰ����ֵ
	double up=bound(1);//��ǰ�Ͻ�
	while(i!=n+1){//��Ҷ�ӽ��
		//��鵱ǰ��չ����������ӽ��
		double wt=cw+w[i];
		if(wt<=c){
			if(cp+p[i]>bestp)
				bestp=cp+p[i];
			addLiveNode(up,cp+p[i],cw+w[i],i+1,enode,true);
		}
		up=bound(i+1);
		if(up>=bestp)
			addLiveNode(up,cp,cw,i+1,enode,false);
		HeapNode node =heap->removeMax();
		enode=node.liveNode;
		cw=node.weight;
		cp=node.profit;
		up=node.upperProfit;
		i=node.level;
	}
	for(int j=n;j>0;j--){
 
		bestX[j]=(enode->leftChild)?1:0;
		enode=enode->parent;
	}
	return cp;
}
 double knapsack(double *pp,double *ww,double cc,int *xx){
	//�������ֵ��bestX�������Ž�
	c=cc;
	//n=sizeof(pp)/sizeof(double);
	//�����Ե�λ������ֵ�������Ʒ����
	Element *q=new Element[n];
	double ws=0.0;
	double ps=0.0;
	for(int i=0;i<n;i++){
		q[i]=Element(i+1,pp[i+1]/ww[i+1]);
		ps=ps+pp[i+1];
		ws=ws+ww[i+1];
	}
	if(ws<=c){
		return  ps;
	}           
	p=new double[n+1];
	w=new double[n+1];
	for(i=0;i<n;i++){
		p[i+1]=pp[q[i].id];
		w[i+1]=ww[q[i].id];
	}
	cw=0.0;
	cp=0.0;
	bestX = new int[n+1];
	heap = new MaxHeap(n);
	double bestp = MaxKnapsack();
	for(int j=0;j<n;j++)
		xx[q[j].id]=bestX[j+1];
 
	return  bestp;
 
}
void main(){
	
	w=new double[4];
	w[1]=15;w[2]=16;w[3]=15;
	p=new double[4];
	p[1]=25;p[2]=45;p[3]=25;
	int *x = new int[4];
	double m = knapsack(p,w,c,x);
	cout<<"*****��֧�޽編*****"<<endl;
	cout<<"*****��Ʒ������n="<<n<<endl;
	cout<<"*****����������c="<<c<<endl;
	cout<<"*****��Ʒ�������飺w= {"<<w[3]<<" "<<w[1]<<" "<<w[2]<<"}"<<endl;
	cout<<"*****��Ʒ��ֵ���飺v= {"<<p[3]<<" "<<p[1]<<" "<<p[2]<<"}"<<endl;
	cout<<"*****����ֵ��="<<m<<endl;
	cout<<"*****ѡ�е���Ʒ��:";
	for(int i=1;i<=3;i++)
		cout<<x[i]<<" ";
	cout<<endl;
}
