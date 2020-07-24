//循环链表实现 
#include<iostream>
using namespace std;
typedef struct Node    //链表 
{
	int data;
	Node *next;
}LNode;
class JpCircle       //类 
{
	public:
		JpCircle();              //构造函数 
		JpCircle(int a[],int n);
		void insert(int n);      //构造数据链表 
		LNode *Locate(int s);       //返回指向第一个报数者 的指针 
		LNode *getLink();           //返回头指针 
		int LastOne();     //返回最后一个数据 
	private:
		LNode *first;          //头指针 
};
//函数功能：无参构造函数
JpCircle::JpCircle()
{
	first=new LNode;
	first->next=first;   //循环链表 
}
//函数功能：带有参数的构造函数 
JpCircle::JpCircle(int a[],int n)
{
	first=new LNode;
	first->next=first;
	LNode *p=first;    //工作结点 
	for(int i=0;i<n;i++)
	{
		LNode *s;   //新建结点 
		s=new LNode;  //分配内存 
		s->data=a[i];  //赋值 
		s->next=p->next;   //插入 
		p->next=s;    //前插法 
		p=s;      //工作结点指向当前结点 
	}
}
//函数功能：构造数据列表
void JpCircle::insert(int n)
{
	LNode *p=first;
	for(int i=1;i<=n;i++)
	{
		LNode *s;
		s=new LNode;   //新建结点 
		s->data=i;     //赋值 
		s->next=p->next;
		p->next=s;
		p=s;
	}
} 
//函数功能：找到指向第一位报数者的指针并返回
LNode *JpCircle::Locate(int s)
{
	LNode *p=first->next;
	if(s==0)
	{
		return first;
	}
	else
	{
		for(int i=1;i<s;i++)
		p=p->next; 
		return p;
	}
} 
//函数功能：返回头指针 
LNode *JpCircle::getLink()
{
	return first;
}
//函数功能：返回最后一个人的位置
int JpCircle::LastOne()
{
	return first->next->data;
} 
//约瑟夫问题演示 
void JpPlaying(JpCircle &jp,int n,int m,int s);
//主函数 
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
			cout<<"发生错误，请重新输入!"<<endl;
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
			cout<<"发生错误，请重新输入!"<<endl;
			cin>>m;
		}
		cout<<"请输入从第几个数开始报数："<<endl;
		cin>>s;
		while(s<=0||s>n)
		{
			cout<<"发生错误，请重新输入!"<<endl;
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
	LNode *p,*pre=NULL;
	p=jp.Locate(s);            
	pre=jp.getLink(); 
	int i,j;
	if(m==1)                //循环周期为一的情况单独讨论 
	{
		pre=jp.Locate(s-1);
		for(i=1;i<n;i++)
		{
			cout<<"出列的人是:"<<p->data<<endl;
			pre->next=p->next;
			delete p;
			p=pre->next;
			if(p==jp.getLink())         //判断p是否为头指针 
			{
				pre=p;
				p=p->next;
			}
		}
	}
	else
	{
		for( i=1;i<n;i++)
		{
			for( j=1;j<m;j++)
			{
				pre=p;
				p=p->next;
				if(p==jp.getLink())
				{
					pre=p;
					p=p->next;
				}
			}
			cout<<"出列的人是:"<<p->data<<endl;
			pre->next=p->next;
			delete p;
			p=pre->next;
			if(p==jp.getLink())
			{
				pre=p;
				p=p->next;
			} 
		}
	}
} 
