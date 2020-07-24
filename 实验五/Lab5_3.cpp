//散列法存储数据
#include<iostream>
using namespace std;
const int MaxSize=12000;
//散列表数据结构体 
typedef struct{
	int data;   //数据项 
	bool visit;   //辅助布尔变量 
}Node;
//主函数 
int main()
{
	Node H[MaxSize];         //散列表 
	int a,pos;      //输入变量和位置变量 
	for(int i=0;i<MaxSize;i++)
		H[i].visit=false;           //初始化 
	cout<<"请输入12000个小于12000的数:"<<endl;
	for(int i=0;i<MaxSize;i++)
	{
		cin>>a;
		pos=a/2;             //散列函数 
		while(H[pos].visit)     //发生冲突时，寻找下一个散列地址 
		{
			pos++;
			pos=pos%MaxSize;
		}
		H[pos].data=a;        //将数据存入散列表 
		H[pos].visit=true;
	}
	cout<<"哈希表如下："<<endl;         //输出哈希表 
	for(int i=0;i<=MaxSize;i++)
		cout<<H[i].data<<" ";
	return 0; 
}
