#include<iostream>
    #define N 10
    #include<cstring>
    using namespace std;
    int a[N];
    int t=1;
    int n;//nΪ������һ�����е������	
    int m;//mΪ������λ�� 	
    //���õķǵݹ��������
	
    void  Iter_backtrack(){
    	//��һ�����Ȱ�ÿ�����鶼��ʼ��Ϊ0 
		
    	memset(a,0,sizeof(a));
    	//�ڶ������ǵݹ��������
    	t=1;
    	while(t!=0){//1.���뵽���ݵ������������ݵ���0λ���� 
    		//2.����ʲôʱ����ݣ�ʲôʱ�����ǰ�� 
    		if(a[t]<n){//��������²����� 
    			a[t]=a[t]+1;
    			if(a[t]<=n){
    				if(t==m){
    					for(int i=1;i<=m;i++)
    						cout<<a[i]<<" ";
    					cout<<endl; 
    				}else	t++;
    			} 
    		}else{//��������»��� 
    			a[t]=0;//����������Ǹ����ݹ�����һ���� 
    			t--; 
    		} 
    	} 
    }
    int main(){
		printf("һ�����е������Ϊ��");
		scanf("%d",&n);
		printf("λ��Ϊ��");
		scanf("%d",&m);
    	Iter_backtrack();
    	return 0;
}