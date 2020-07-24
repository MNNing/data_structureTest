//用数组实现
#include<iostream>
using namespace std;
const int MaxSize=100;
class JpCircle
{
	public:
		JpCircle();               //无参数构造函数 
		JpCircle(int a[],int n);  //含参构造函数 
		int GetPeople(int x);     //获取某一下标对应的数据元素 
		void insert(int n);       //构造数据表 
		int LastOne();            //返回最后一个人的数据 
		void Delete(int x);       //删除出圈成员 
	private:
		int list[MaxSize];         
		int length; 
};
//函数功能：无参构造函数
JpCircle::JpCircle()
{
	length=0;
}
//函数功能：带有参数的构造函数 
JpCircle::JpCircle(int a[],int n)
{
	for(int i=0;i<n;i++)
	{
		list[i]=a[i];
	}
	length=n;
}
//函数功能：构造数据列表
void JpCircle::insert(int n)
{
	for(int i=0;i<n;i++)
	{
		list[i]=i+1;	
	}
	length=n;
} 
//函数功能：返回最后一个人的位置
int JpCircle::LastOne()
{
	return list[0];
} 
//函数功能：删除数组元素
void JpCircle::Delete(int x)
{
	for(int d=x;d<length-1;d++)
	{
		list[d]=list[d+1];
	}
	length--;
} 
//函数功能：获得元素信息
int JpCircle::GetPeople(int x)
{
	return list[x];
} 
void JpPlaying(JpCircle &jp,int n,int m,int s);
int main(void)
{
	int n,s,m;
	do
	{
		JpCircle Link;
		cout<<"请输入结点个数:"<<endl;
		cin>>n;	
		while(n<0)
		{
			cout<<"Error,Please input again!"<<endl;
			cin>>n;
		}
		if(n==0)
		{
			cout<<"程序运行结束！！！"<<endl; 
			break;
		}
		cout<<"请输入报数周期："<<endl;
		cin>>m;
		while(m<=0||m>n)
		{
			cout<<"Error,Please input again!"<<endl;
			cin>>m;
		}
		cout<<"请输入从第几个数开始报数："<<endl;
		cin>>s;
		while(s<=0||s>n)
		{
			cout<<"Error,Please input again!"<<endl;
			cin>>s;
		}
		Link.insert(n);
		JpPlaying(Link,n,m,s);
		cout<<"最后一个人编号是"<<Link.LastOne()<<endl; 
	}while(n!=0);
	return 0;
}
//函数功能：Josephus问题的模拟 
void JpPlaying(JpCircle &jp,int n,int m,int s)
{
	int x=s-1;               //初始位置 
	int p=n;                 //总人数 
	int i,j;
	if(m==1)
	{
		for(i=1;i<n;i++)
		{
			cout<<"  出列的人是:"<<jp.GetPeople(x)<<endl;
			jp.Delete(x);
			p=p-1;
			if( x>p-1)  //判断是否到数组尾部 
			{
				x=0;
			}	
		}
	}
	else
	{
		for( i=1;i<n;i++)
		{
			for( j=1;j<m;j++)
			{
				x=x+1;
				if( x>=p-1&&j+1<m)  //判断是否到数组尾部 
				{
					x=-1;
				}
			}
			cout<<"出列的人是:"<<jp.GetPeople(x)<<endl;
			jp.Delete(x);
			p=p-1;	
		}
	} 
} 
