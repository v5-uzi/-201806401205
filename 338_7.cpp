#include <iostream>
using namespace std;
//子空间中节点类型
#include "beibao.h"
double c=30; 
const int n=3;
double *w;
double *p;
double cw;
double cp;
int    *bestX;
MaxHeap * heap;
//上界函数bound计算结点所相应价值的上界
 double bound(int i){
	double cleft=c-cw;
	double b=cp;
	while(i<=n&&w[i]<=cleft){
		cleft=cleft-w[i];
		b=b+p[i];
		i++;
	}
	//装填剩余容量装满背包
	if(i<=n)
		b=b+p[i]/w[i]*cleft;
	return b;
}
//addLiveNode将一个新的活结点插入到子集树和优先队列中
 void addLiveNode(double up,double pp,double ww,int lev,BBnode* par,bool ch){
	//将一个新的活结点插入到子集树和最大堆中
	BBnode *b=new BBnode(par,ch);
	HeapNode  node =HeapNode(b,up,pp,ww,lev);
	heap->put(node);
}
 double MaxKnapsack(){
	//优先队列式分支限界法，返回最大价值，bestx返回最优解
	BBnode * enode=new BBnode();
	int i=1;
	double bestp=0;//当前最优值
	double up=bound(1);//当前上界
	while(i!=n+1){//非叶子结点
		//检查当前扩展结点的左儿子子结点
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
	//返回最大值，bestX返回最优解
	c=cc;
	//n=sizeof(pp)/sizeof(double);
	//定义以单位重量价值排序的物品数组
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
	cout<<"*****分支限界法*****"<<endl;
	cout<<"*****物品个数：n="<<n<<endl;
	cout<<"*****背包容量：c="<<c<<endl;
	cout<<"*****物品重量数组：w= {"<<w[3]<<" "<<w[1]<<" "<<w[2]<<"}"<<endl;
	cout<<"*****物品价值数组：v= {"<<p[3]<<" "<<p[1]<<" "<<p[2]<<"}"<<endl;
	cout<<"*****最优值：="<<m<<endl;
	cout<<"*****选中的物品是:";
	for(int i=1;i<=3;i++)
		cout<<x[i]<<" ";
	cout<<endl;
}
