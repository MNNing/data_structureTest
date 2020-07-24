//循环链表表示队列
#include<iostream>
using namespace std;
//链队数据结点类型
typedef struct Node
{
	int data;   //结点数据域
	struct Node *next; //指向下一结点
}DataNode;
//链队列类的声明
class LinkQueue
{
	public:
		LinkQueue();  //构造函数   
		~LinkQueue();   //析构函数 
		void EnQueue(int x);  //入队 
		int DeQueue();   //出队 
		void DestoryQueue(LinkQueue &lq);  //销毁队列 
		void ShowQueue();  //输出所有队列元素 
		bool Empty();  //布尔函数 
	private:
		DataNode *rear;	  //尾结点 
};
//构造函数 
LinkQueue::LinkQueue()
{
	rear=new DataNode;
	rear->next=rear;
}
//析构函数 
LinkQueue::~LinkQueue()
{
	delete rear;
}
//入队函数 
void LinkQueue::EnQueue(int x)
{ 
	DataNode *s;
	s=new DataNode;
	s->data=x;
	s->next=rear->next; 
	rear->next=s;
	rear=s;
}
//出队函数 
int LinkQueue::DeQueue()
{
	DataNode *s;
	s=new DataNode;
	if(rear->next->next==rear)    //队列中只剩一个元素的情况 
	{
		s=rear->next->next;
		rear->next->next=s->next;
		rear=rear->next;    //rear指向头结点 
	}
	else
	{
		s=rear->next->next;
		rear->next->next=s->next;
	}
	int x=s->data;
	delete s;
	return x;
}
//销毁队列 
void LinkQueue::DestoryQueue(LinkQueue &lq)
{
	int x;
	while(rear->next!=rear)
		x=lq.DeQueue();
	delete rear;
	cout<<"队列已被销毁!"<<endl;
}
//布尔函数判空 
bool LinkQueue::Empty()
{
	if(rear->next==rear)
		return true;
	else
		return false;
}
//输出所有队列元素 
void LinkQueue::ShowQueue()
{
	if(rear->next!=rear)
	{
		
		DataNode *p=rear->next->next;
		cout<<"队列中所有元素:";
		while(p!=rear->next)
		{
			cout<<p->data<<" ";
			p=p->next;
		}
		cout<<endl;
	}
	else
		cout<<"队列为空!"<<endl;
	
}
//主函数 
int main(void)
{
	LinkQueue lq;
	int x;
	int flag=1;
	do
	{
		cout<<"*----------*"<<endl;//输出功能表 
		cout<<"*1.元素入队*"<<endl;
		cout<<"*2.元素出队*"<<endl;
		cout<<"*3.销毁队列*"<<endl;
		cout<<"*4.输出队列*"<<endl; 
		cout<<"*5.退出程序*"<<endl;
		cout<<"*----------*"<<endl; 
		cout<<"请选择:(1~5)"<<endl; 
		int y;
		cin>>y;
		switch(y)
		{
			case 1:
				cout<<"请输入数据元素:"<<endl;
				cin>>x;
				lq.EnQueue(x);
				break;
			case 2:
				if(!lq.Empty())
					cout<<"出队元素为:"<<lq.DeQueue()<<endl;
				else
					cout<<"队列为空!"<<endl;
				break;
			case 3:
				if(!lq.Empty())
					lq.DestoryQueue(lq);
				else
					cout<<"队列为空!"<<endl;
				break;
			case 4:
				lq.ShowQueue();
				break;
			case 5:
				cout<<"程序结束!"<<endl; 
				flag=0;
				break;
			default:
				cout<<"输入非法!!"<<endl;		
		}
		system("pause");
		system("cls"); 
	}while(flag==1);
	return 0;
}
