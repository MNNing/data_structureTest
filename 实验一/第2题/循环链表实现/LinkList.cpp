//ѭ������ʵ�� 
#include<iostream>
using namespace std;
typedef struct Node    //���� 
{
	int data;
	Node *next;
}LNode;
class JpCircle       //�� 
{
	public:
		JpCircle();              //���캯�� 
		JpCircle(int a[],int n);
		void insert(int n);      //������������ 
		LNode *Locate(int s);       //����ָ���һ�������� ��ָ�� 
		LNode *getLink();           //����ͷָ�� 
		int LastOne();     //�������һ������ 
	private:
		LNode *first;          //ͷָ�� 
};
//�������ܣ��޲ι��캯��
JpCircle::JpCircle()
{
	first=new LNode;
	first->next=first;   //ѭ������ 
}
//�������ܣ����в����Ĺ��캯�� 
JpCircle::JpCircle(int a[],int n)
{
	first=new LNode;
	first->next=first;
	LNode *p=first;    //������� 
	for(int i=0;i<n;i++)
	{
		LNode *s;   //�½���� 
		s=new LNode;  //�����ڴ� 
		s->data=a[i];  //��ֵ 
		s->next=p->next;   //���� 
		p->next=s;    //ǰ�巨 
		p=s;      //�������ָ��ǰ��� 
	}
}
//�������ܣ����������б�
void JpCircle::insert(int n)
{
	LNode *p=first;
	for(int i=1;i<=n;i++)
	{
		LNode *s;
		s=new LNode;   //�½���� 
		s->data=i;     //��ֵ 
		s->next=p->next;
		p->next=s;
		p=s;
	}
} 
//�������ܣ��ҵ�ָ���һλ�����ߵ�ָ�벢����
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
//�������ܣ�����ͷָ�� 
LNode *JpCircle::getLink()
{
	return first;
}
//�������ܣ��������һ���˵�λ��
int JpCircle::LastOne()
{
	return first->next->data;
} 
//Լɪ��������ʾ 
void JpPlaying(JpCircle &jp,int n,int m,int s);
//������ 
int main(void)
{
	int n,s,m;
	do
	{
		JpCircle Link;
		cout<<"�����������:"<<endl;
		cin>>n;	
		while(n<0)
		{
			cout<<"������������������!"<<endl;
			cin>>n;
		}
		if(n==0)
		{
			cout<<"�������н���������"<<endl; 
			break;
		}
		cout<<"�����뱨�����ڣ�"<<endl;
		cin>>m;
		while(m<=0||m>n)
		{
			cout<<"������������������!"<<endl;
			cin>>m;
		}
		cout<<"������ӵڼ�������ʼ������"<<endl;
		cin>>s;
		while(s<=0||s>n)
		{
			cout<<"������������������!"<<endl;
			cin>>s;
		}
		Link.insert(n);
		JpPlaying(Link,n,m,s);
		cout<<"���һ���˱����"<<Link.LastOne()<<endl; 
	}while(n!=0);
	return 0;
}
//�������ܣ�Josephus�����ģ�� 
void JpPlaying(JpCircle &jp,int n,int m,int s)
{
	LNode *p,*pre=NULL;
	p=jp.Locate(s);            
	pre=jp.getLink(); 
	int i,j;
	if(m==1)                //ѭ������Ϊһ������������� 
	{
		pre=jp.Locate(s-1);
		for(i=1;i<n;i++)
		{
			cout<<"���е�����:"<<p->data<<endl;
			pre->next=p->next;
			delete p;
			p=pre->next;
			if(p==jp.getLink())         //�ж�p�Ƿ�Ϊͷָ�� 
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
			cout<<"���е�����:"<<p->data<<endl;
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
