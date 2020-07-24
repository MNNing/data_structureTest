//������ʵ��
#include<iostream>
using namespace std;
const int MaxSize=100;
class JpCircle
{
	public:
		JpCircle();               //�޲������캯�� 
		JpCircle(int a[],int n);  //���ι��캯�� 
		int GetPeople(int x);     //��ȡĳһ�±��Ӧ������Ԫ�� 
		void insert(int n);       //�������ݱ� 
		int LastOne();            //�������һ���˵����� 
		void Delete(int x);       //ɾ����Ȧ��Ա 
	private:
		int list[MaxSize];         
		int length; 
};
//�������ܣ��޲ι��캯��
JpCircle::JpCircle()
{
	length=0;
}
//�������ܣ����в����Ĺ��캯�� 
JpCircle::JpCircle(int a[],int n)
{
	for(int i=0;i<n;i++)
	{
		list[i]=a[i];
	}
	length=n;
}
//�������ܣ����������б�
void JpCircle::insert(int n)
{
	for(int i=0;i<n;i++)
	{
		list[i]=i+1;	
	}
	length=n;
} 
//�������ܣ��������һ���˵�λ��
int JpCircle::LastOne()
{
	return list[0];
} 
//�������ܣ�ɾ������Ԫ��
void JpCircle::Delete(int x)
{
	for(int d=x;d<length-1;d++)
	{
		list[d]=list[d+1];
	}
	length--;
} 
//�������ܣ����Ԫ����Ϣ
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
		cout<<"�����������:"<<endl;
		cin>>n;	
		while(n<0)
		{
			cout<<"Error,Please input again!"<<endl;
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
			cout<<"Error,Please input again!"<<endl;
			cin>>m;
		}
		cout<<"������ӵڼ�������ʼ������"<<endl;
		cin>>s;
		while(s<=0||s>n)
		{
			cout<<"Error,Please input again!"<<endl;
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
	int x=s-1;               //��ʼλ�� 
	int p=n;                 //������ 
	int i,j;
	if(m==1)
	{
		for(i=1;i<n;i++)
		{
			cout<<"  ���е�����:"<<jp.GetPeople(x)<<endl;
			jp.Delete(x);
			p=p-1;
			if( x>p-1)  //�ж��Ƿ�����β�� 
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
				if( x>=p-1&&j+1<m)  //�ж��Ƿ�����β�� 
				{
					x=-1;
				}
			}
			cout<<"���е�����:"<<jp.GetPeople(x)<<endl;
			jp.Delete(x);
			p=p-1;	
		}
	} 
} 
