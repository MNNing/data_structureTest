//ѭ�������ʾ����
#include<iostream>
using namespace std;
//�������ݽ������
typedef struct Node
{
	int data;   //���������
	struct Node *next; //ָ����һ���
}DataNode;
//�������������
class LinkQueue
{
	public:
		LinkQueue();  //���캯��   
		~LinkQueue();   //�������� 
		void EnQueue(int x);  //��� 
		int DeQueue();   //���� 
		void DestoryQueue(LinkQueue &lq);  //���ٶ��� 
		void ShowQueue();  //������ж���Ԫ�� 
		bool Empty();  //�������� 
	private:
		DataNode *rear;	  //β��� 
};
//���캯�� 
LinkQueue::LinkQueue()
{
	rear=new DataNode;
	rear->next=rear;
}
//�������� 
LinkQueue::~LinkQueue()
{
	delete rear;
}
//��Ӻ��� 
void LinkQueue::EnQueue(int x)
{ 
	DataNode *s;
	s=new DataNode;
	s->data=x;
	s->next=rear->next; 
	rear->next=s;
	rear=s;
}
//���Ӻ��� 
int LinkQueue::DeQueue()
{
	DataNode *s;
	s=new DataNode;
	if(rear->next->next==rear)    //������ֻʣһ��Ԫ�ص���� 
	{
		s=rear->next->next;
		rear->next->next=s->next;
		rear=rear->next;    //rearָ��ͷ��� 
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
//���ٶ��� 
void LinkQueue::DestoryQueue(LinkQueue &lq)
{
	int x;
	while(rear->next!=rear)
		x=lq.DeQueue();
	delete rear;
	cout<<"�����ѱ�����!"<<endl;
}
//���������п� 
bool LinkQueue::Empty()
{
	if(rear->next==rear)
		return true;
	else
		return false;
}
//������ж���Ԫ�� 
void LinkQueue::ShowQueue()
{
	if(rear->next!=rear)
	{
		
		DataNode *p=rear->next->next;
		cout<<"����������Ԫ��:";
		while(p!=rear->next)
		{
			cout<<p->data<<" ";
			p=p->next;
		}
		cout<<endl;
	}
	else
		cout<<"����Ϊ��!"<<endl;
	
}
//������ 
int main(void)
{
	LinkQueue lq;
	int x;
	int flag=1;
	do
	{
		cout<<"*----------*"<<endl;//������ܱ� 
		cout<<"*1.Ԫ�����*"<<endl;
		cout<<"*2.Ԫ�س���*"<<endl;
		cout<<"*3.���ٶ���*"<<endl;
		cout<<"*4.�������*"<<endl; 
		cout<<"*5.�˳�����*"<<endl;
		cout<<"*----------*"<<endl; 
		cout<<"��ѡ��:(1~5)"<<endl; 
		int y;
		cin>>y;
		switch(y)
		{
			case 1:
				cout<<"����������Ԫ��:"<<endl;
				cin>>x;
				lq.EnQueue(x);
				break;
			case 2:
				if(!lq.Empty())
					cout<<"����Ԫ��Ϊ:"<<lq.DeQueue()<<endl;
				else
					cout<<"����Ϊ��!"<<endl;
				break;
			case 3:
				if(!lq.Empty())
					lq.DestoryQueue(lq);
				else
					cout<<"����Ϊ��!"<<endl;
				break;
			case 4:
				lq.ShowQueue();
				break;
			case 5:
				cout<<"�������!"<<endl; 
				flag=0;
				break;
			default:
				cout<<"����Ƿ�!!"<<endl;		
		}
		system("pause");
		system("cls"); 
	}while(flag==1);
	return 0;
}
