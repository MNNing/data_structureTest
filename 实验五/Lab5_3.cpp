//ɢ�з��洢����
#include<iostream>
using namespace std;
const int MaxSize=12000;
//ɢ�б����ݽṹ�� 
typedef struct{
	int data;   //������ 
	bool visit;   //������������ 
}Node;
//������ 
int main()
{
	Node H[MaxSize];         //ɢ�б� 
	int a,pos;      //���������λ�ñ��� 
	for(int i=0;i<MaxSize;i++)
		H[i].visit=false;           //��ʼ�� 
	cout<<"������12000��С��12000����:"<<endl;
	for(int i=0;i<MaxSize;i++)
	{
		cin>>a;
		pos=a/2;             //ɢ�к��� 
		while(H[pos].visit)     //������ͻʱ��Ѱ����һ��ɢ�е�ַ 
		{
			pos++;
			pos=pos%MaxSize;
		}
		H[pos].data=a;        //�����ݴ���ɢ�б� 
		H[pos].visit=true;
	}
	cout<<"��ϣ�����£�"<<endl;         //�����ϣ�� 
	for(int i=0;i<=MaxSize;i++)
		cout<<H[i].data<<" ";
	return 0; 
}
