#include<iostream> 
#include<stdio.h>
using namespace std;
const int MaxSize=100;
class SeqList
{
	public:
		SeqList();          //���캯�� 
		SeqList(int a[],int n);
		void Get(int i);    //��λ���� 
		void Locate(int x);  //��ֵ���� 
		void Insert(int i,int x);//���� 
		void Delet(int i);//ɾ�� 
		void show();  //�������Ԫ�� 
	private:
		int data[MaxSize];
		int length;
};
//�������ܣ����������Ĺ��캯�� 
SeqList::SeqList()
{
	length=0;
}
//�������ܣ��������Ĺ��캯�� 
SeqList::SeqList(int a[],int n)
{
	if (n>MaxSize)           //�ж��Ƿ�����           
	    cout<<"�����Ƿ�"<<endl;
	else
	{
		for (int i=0; i<n; i++)  
        data[i]=a[i];             //���θ�ֵ 
        length=n; 
	} 
}
// �������ܣ���λ���� 
void SeqList::Get(int i) 
{
	while(i<0||i>length)
	{
		cout<<"λ���쳣�����������룡����"<<endl;
		cin>>i; 
	}
	cout<<"Ŀ��Ԫ��:"<< data[i-1]<<endl;
	    
}
//�������ܣ���ֵ����
void SeqList::Locate(int x)    
{
	int f=0;
	for(int i=0;i<length;i++)
	{
		if(x==data[i])
		{
			f=1;        //�Ƿ��ҵ�Ŀ��Ԫ�صı�־ 
			cout<<"��Ҫ�ҵ������ڵ�"<< i+1<<"λ"<<endl;
		}
		
	}
	if(f==0)
		cout<<"δ�ҵ�Ŀ��Ԫ��"<<endl;
}
//�������ܣ���ĳ��λ�ò���ĳ��ֵ 
void SeqList::Insert(int i,int x)
{
	if(length>=MaxSize)
	{
		cout<<"����";
		exit(1); 
	}
	while(i<1||i>length+1)
	{
		cout<<"λ���쳣,���������룡��"<<endl;
		cin>>i;
		
	}
	for(int j=length;j>i-1;j--)
	{
		data[j]=data[j-1];    //����Ԫ�غ��� 
	}
	data[i-1]=x;        //���� 
	length+=1;
}
//�������ܣ�ɾ��ָ������ 
void SeqList::Delet(int i)
{
	if(length<=0)
	{
		cout<<"���"<<endl;
		exit(1); 
	}
	while(i<1||i>length)
	{
		cout<<"λ���쳣,���������룡��"<<endl;
		cin>>i;
		
	}
	int a=data[i-1];
	for(int j=i-1;j<length-1;j++)
	{
		data[j]=data[j+1];          //����Ԫ��ǰ�� 
	}
	length--;
	cout<<"Ҫɾ��������Ϊ"<<a<<endl;
}
//�������ܣ�չʾ�������� 
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
	   cout<<"�ձ�"<<endl; 
	
}
//������ 
int main(void)
{
	int list[10];
	int x;
	int a,b,c,d,e;
	cout<<"����һ���������飺"<<endl; 
	cout<<"����������ʮ����������"<<endl;
	for(int i=0;i<10;i++)
	{
		cin>>x;
		list[i]=x;
	}
	SeqList L(list,10);
	L.show();
	cout<<"����Ҫ��Ԫ�ز��뵽�ڼ�λ"<<endl;
	cin>>a;
	cout<<"����Ҫ����ʲôԪ��"<<endl;
	cin>>b;
	L.Insert(a,b);               //���� 
	L.show();
	cout<<"����Ҫɾ���ڼ�λԪ��"<<endl;
	cin>>e;
	L.Delet(e);                    //ɾ�� 
	L.show();
	cout<<"����Ҫ�����ڼ�λԪ��"<<endl;
	cin>>c;
	L.Get(c);                       //��λ���� 
	cout<<"����Ҫ�����ĸ�Ԫ�ص�λ��"<<endl;
	cin>>d;
	L.Locate(d);                  //��ֵ����
	return 0;
}
