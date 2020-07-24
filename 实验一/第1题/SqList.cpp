#include<iostream> 
#include<stdio.h>
using namespace std;
const int MaxSize=100;
class SeqList
{
	public:
		SeqList();          //构造函数 
		SeqList(int a[],int n);
		void Get(int i);    //按位查找 
		void Locate(int x);  //按值查找 
		void Insert(int i,int x);//插入 
		void Delet(int i);//删除 
		void show();  //输出所有元素 
	private:
		int data[MaxSize];
		int length;
};
//函数功能：不带参数的构造函数 
SeqList::SeqList()
{
	length=0;
}
//函数功能：带参数的构造函数 
SeqList::SeqList(int a[],int n)
{
	if (n>MaxSize)           //判断是否上溢           
	    cout<<"参数非法"<<endl;
	else
	{
		for (int i=0; i<n; i++)  
        data[i]=a[i];             //依次赋值 
        length=n; 
	} 
}
// 函数功能：按位查找 
void SeqList::Get(int i) 
{
	while(i<0||i>length)
	{
		cout<<"位置异常，请重新输入！！！"<<endl;
		cin>>i; 
	}
	cout<<"目标元素:"<< data[i-1]<<endl;
	    
}
//函数功能：按值查找
void SeqList::Locate(int x)    
{
	int f=0;
	for(int i=0;i<length;i++)
	{
		if(x==data[i])
		{
			f=1;        //是否找到目标元素的标志 
			cout<<"您要找的数据在第"<< i+1<<"位"<<endl;
		}
		
	}
	if(f==0)
		cout<<"未找到目标元素"<<endl;
}
//函数功能：在某个位置插入某个值 
void SeqList::Insert(int i,int x)
{
	if(length>=MaxSize)
	{
		cout<<"上溢";
		exit(1); 
	}
	while(i<1||i>length+1)
	{
		cout<<"位置异常,请重新输入！！"<<endl;
		cin>>i;
		
	}
	for(int j=length;j>i-1;j--)
	{
		data[j]=data[j-1];    //数组元素后移 
	}
	data[i-1]=x;        //插入 
	length+=1;
}
//函数功能：删除指定数据 
void SeqList::Delet(int i)
{
	if(length<=0)
	{
		cout<<"表空"<<endl;
		exit(1); 
	}
	while(i<1||i>length)
	{
		cout<<"位置异常,请重新输入！！"<<endl;
		cin>>i;
		
	}
	int a=data[i-1];
	for(int j=i-1;j<length-1;j++)
	{
		data[j]=data[j+1];          //数组元素前移 
	}
	length--;
	cout<<"要删除的数据为"<<a<<endl;
}
//函数功能：展示所有数据 
void SeqList::show()
{
	if(length>0)
	{
		cout<<endl;
		for(int i=0;i<length;i++)
	    cout<<data[i]<<" ";
	    cout<<endl;
	}
	else
	   cout<<"空表"<<endl; 
	
}
//主函数 
int main(void)
{
	int list[10];
	int x;
	int a,b,c,d,e;
	cout<<"创建一个整型数组："<<endl; 
	cout<<"请输入任意十个整型数："<<endl;
	for(int i=0;i<10;i++)
	{
		cin>>x;
		list[i]=x;
	}
	SeqList L(list,10);
	L.show();
	cout<<"您想要将元素插入到第几位"<<endl;
	cin>>a;
	cout<<"您想要插入什么元素"<<endl;
	cin>>b;
	L.Insert(a,b);               //插入 
	L.show();
	cout<<"您想要删除第几位元素"<<endl;
	cin>>e;
	L.Delet(e);                    //删除 
	L.show();
	cout<<"您想要搜索第几位元素"<<endl;
	cin>>c;
	L.Get(c);                       //按位查找 
	cout<<"您想要搜索哪个元素的位置"<<endl;
	cin>>d;
	L.Locate(d);                  //按值查找
	return 0;
}
