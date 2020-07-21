#include<iostream>
    #define N 10
    #include<cstring>
    using namespace std;
    int a[N];
    int t=1;
    int n;//n为给出的一串数中的最大数	
    int m;//m为给出的位数 	
    //常用的非递归迭代过程
	
    void  Iter_backtrack(){
    	//第一步，先把每个数组都初始化为0 
		
    	memset(a,0,sizeof(a));
    	//第二步，非递归迭代过程
    	t=1;
    	while(t!=0){//1.先想到回溯的条件，当回溯到第0位结束 
    		//2.再想什么时候回溯，什么时候继续前进 
    		if(a[t]<n){//这种情况下不回溯 
    			a[t]=a[t]+1;
    			if(a[t]<=n){
    				if(t==m){
    					for(int i=1;i<=m;i++)
    						cout<<a[i]<<" ";
    					cout<<endl; 
    				}else	t++;
    			} 
    		}else{//这种情况下回溯 
    			a[t]=0;//这个与上面那个回溯规律是一样的 
    			t--; 
    		} 
    	} 
    }
    int main(){
		printf("一串数中的最大数为：");
		scanf("%d",&n);
		printf("位数为：");
		scanf("%d",&m);
    	Iter_backtrack();
    	return 0;
}