//实现基于有序顺序表的折半搜索
#include<iostream>
using namespace std;
const int MaxSize=20;
//顺序表数据结构体 
typedef struct DataNode
{
	int key;
}Node;
//折半搜索类的定义 
class SeqBinSearch
{
	public:
		SeqBinSearch();   //构造函数 
		~SeqBinSearch();      //析构函数 
		void MakeList();      //创建顺序表 
		int BinSearch(int k);   //折半查找 
	private:
		Node *data;      //顺序表数组 
		int low,high,mid;      //折半查找辅助变量 
}; 
//构造函数 
SeqBinSearch::SeqBinSearch()
{
	data=new Node[MaxSize];
}
//析构函数 
SeqBinSearch::~SeqBinSearch()
{
	delete data;
}
//构建顺序表 
void SeqBinSearch::MakeList()
{
	int n;
	cout<<"数据个数:"<<endl;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"第"<<i<<"个："<<endl;
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
	cout<<"顺序表:"<<endl; 
	for(int i=1;i<=n;i++)
		cout<<data[i].key<<" ";
	cout<<endl;
	low=1;high=n;
}
//折半查找 
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
	cout<<"请输入要搜索的整数:"<<endl;
	cin>>k;
	se.BinSearch(k);
	if(se.BinSearch(k)!=0)
		cout<<"查找成功，下标为 :"<<se.BinSearch(k);
	else cout<<"查询无果!"<<endl;
	return 0;
}
