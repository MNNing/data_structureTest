//�赥����Ľ���ǰ��ؼ��ֵ�
//ֵ��С�������еģ���д���Դ˱���������򲢵��ԡ� 
#include<iostream>
using namespace std;
//�������㶨�� 
typedef struct LinkList{
	int data;
	struct LinkList *next;
}Link;
//������������Ķ��� 
class SearchLink
{
	public:
		SearchLink();  //���캯�� 
		~SearchLink();  //�������� 
		void InsertNode(int num);   //������ 
		void BinSearch(int r);    //���� 
		void showNode();   //��������� 
	private:
		Link *head;
};
//���캯�� 
SearchLink::SearchLink()
{
	head=new Link;
	head=NULL;
}
//�������� 
SearchLink::~SearchLink()
{
	delete head;
}
//������ 
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
//���� 
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
			cout<<"�ҵ��ˣ�λ��Ϊ:"<<i<<endl;
			break;
		}
		i++;
	}
	if(flag==0)
		cout<<"δ�ҵ�Ŀ������!"<<endl;		
}
//��������� 
void SearchLink::showNode()
{
	Link *p;
	cout<<"���������:"<<endl;
	for(p=head;p;p=p->next)
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}
//������ 
int main()
{
	SearchLink se;
	int a,n;
	cout<<"���ݸ���:"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"�������"<<i+1<<"������:"<<endl;
		cin>>a;
		se.InsertNode(a);
	}
	se.showNode();
	cout<<"�����������ѯ������:"<<endl;
	cin>>a;
	se.BinSearch(a);
	return 0;
}





