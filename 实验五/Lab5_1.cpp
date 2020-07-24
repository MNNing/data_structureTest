//ʵ�ֻ�������˳�����۰�����
#include<iostream>
using namespace std;
const int MaxSize=20;
//˳������ݽṹ�� 
typedef struct DataNode
{
	int key;
}Node;
//�۰�������Ķ��� 
class SeqBinSearch
{
	public:
		SeqBinSearch();   //���캯�� 
		~SeqBinSearch();      //�������� 
		void MakeList();      //����˳��� 
		int BinSearch(int k);   //�۰���� 
	private:
		Node *data;      //˳������� 
		int low,high,mid;      //�۰���Ҹ������� 
}; 
//���캯�� 
SeqBinSearch::SeqBinSearch()
{
	data=new Node[MaxSize];
}
//�������� 
SeqBinSearch::~SeqBinSearch()
{
	delete data;
}
//����˳��� 
void SeqBinSearch::MakeList()
{
	int n;
	cout<<"���ݸ���:"<<endl;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"��"<<i<<"����"<<endl;
		cin>>data[i].key;
	}
	int term;
	for(int i=1;i<n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(data[j].key<data[i].key)
			{
				term=data[i].key;
				data[i].key=data[j].key;
				data[j].key=term;
			}
		}
	}
	cout<<"˳���:"<<endl; 
	for(int i=1;i<=n;i++)
		cout<<data[i].key<<" ";
	cout<<endl;
	low=1;high=n;
}
//�۰���� 
int SeqBinSearch::BinSearch(int k)
{
	while(low<=high)
	{
		mid=(low+high)/2;
		if(k<data[mid].key) high=mid-1;
		else if(k>data[mid].key) low=mid+1;
		else return mid;
	}
	return 0;
}
int main()
{
	int k;
	SeqBinSearch se;
	se.MakeList();
	cout<<"������Ҫ����������:"<<endl;
	cin>>k;
	se.BinSearch(k);
	if(se.BinSearch(k)!=0)
		cout<<"���ҳɹ����±�Ϊ :"<<se.BinSearch(k);
	else cout<<"��ѯ�޹�!"<<endl;
	return 0;
}
