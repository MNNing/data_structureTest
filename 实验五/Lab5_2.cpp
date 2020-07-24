//设单链表的结点是按关键字的
//值从小到大排列的，试写出对此表的搜索程序并调试。 
#include<iostream>
using namespace std;
//单链表结点定义 
typedef struct LinkList{
	int data;
	struct LinkList *next;
}Link;
//单链表搜索类的定义 
class SearchLink
{
	public:
		SearchLink();  //构造函数 
		~SearchLink();  //析构函数 
		void InsertNode(int num);   //插入结点 
		void BinSearch(int r);    //查找 
		void showNode();   //输出单链表 
	private:
		Link *head;
};
//构造函数 
SearchLink::SearchLink()
{
	head=new Link;
	head=NULL;
}
//析构函数 
SearchLink::~SearchLink()
{
	delete head;
}
//插入结点 
void SearchLink::InsertNode(int num)
{
	Link *s,*p,*q;
	p=new Link;
	p->data=num;
	p->next=NULL;
	if(head==NULL)
	{
		head=p;
		return;
	}
	if(head->data>p->data)
	{
		p->next=head;
		head=p;
		return;
	}
	for(q=head,s=head->next;s;q=s,s=s->next)
	{
		if(s->data>p->data)
		{
			p->next=s;
			q->next=p;
			return;
		}
	}
	q->next=p;
	return;
}
//搜索 
void SearchLink::BinSearch(int r)
{
	Link *p;
	int flag=0;
	int i=1;
	for(p=head;p!=NULL;p=p->next)
	{
		if(p->data==r)
		{
			flag=1;
			cout<<"找到了，位置为:"<<i<<endl;
			break;
		}
		i++;
	}
	if(flag==0)
		cout<<"未找到目标数据!"<<endl;		
}
//输出单链表 
void SearchLink::showNode()
{
	Link *p;
	cout<<"单链表输出:"<<endl;
	for(p=head;p;p=p->next)
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}
//主函数 
int main()
{
	SearchLink se;
	int a,n;
	cout<<"数据个数:"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"请输入第"<<i+1<<"个数据:"<<endl;
		cin>>a;
		se.InsertNode(a);
	}
	se.showNode();
	cout<<"请输入您想查询的数据:"<<endl;
	cin>>a;
	se.BinSearch(a);
	return 0;
}





