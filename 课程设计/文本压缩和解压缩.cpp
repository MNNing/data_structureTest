// 文本压缩和解压缩
#include<iostream>
#include<string.h>
using namespace std;
typedef char **HuffmanCode;    //动态分配数组存储哈夫曼编码表
//哈夫曼树结点结构体 
typedef struct 
{	int weight;                   //结点的权值
	char data;
	bool Input;
	int parent,lchild,rchild;       //结点的双亲、左孩子、右孩子的下标
}HTNode,*HuffmTree;    //动态分配数组存储哈夫曼树
//哈夫曼树类声明 
class HuffmanT
{
	public:
		HuffmanT(){}    //构造函数 
		~HuffmanT(){}   //析构函数 
		int  HuffmanTree(char *str);      //构造哈夫曼树 
		void Select(int n,int &s1,int &s2);   //查找权重较小的两个结点 
		void CreatHuffmanCode(int n);   //从叶子到根逆向求每个字符的赫夫曼编码
		void ShowHuffmanCode( int n);  //输出哈夫曼编码表 
		void EncodeHuffman( int n,char *str);    //字符串转二进制编码
		void DecodeHuffman(int n);       //二进制编码转字符串
	private:
		HuffmTree HT;
		HuffmanCode HC;
};
//构造哈夫曼树HT
int HuffmanT::HuffmanTree(char *str)
{
	int m,n=0;
	int s1,s2;
	int a[128]={0};
	for(int i=0;str[i];i++)
		a[str[i]]++;
	for(int j=0;j<128;j++)
	{
		if(a[j])
		{
			n++;
		}
	}
	cout<<"叶子结点个数:"<<n<<endl;  
	m=2*n-1;                 //m为哈夫曼树总结点数
	//0号单元未用，所以动态分配m+1个单元，HT[m]表示根结点
	HT=new HTNode[m+1];    
	for (int i=1; i<=m; ++i) //将1~m号单元中的双亲、左右孩子的下标都初始化为0
	{ 
	 	HT[i].parent=0;HT[i].lchild=0;HT[i].rchild=0;HT[i].Input=true;
	}
	int b=1;
	for(int j=0;j<128;j++)
	{
		if(a[j])
		{
			HT[b].data=char (j);
			HT[b].weight=a[j];
			b++;
		}
	}
	cout<<"字符       出现频率"<<endl;
	for (int i=1; i<=n; ++i)  //输入 前n个单元中叶子结点的权值
	{
		cout<<HT[i].data<<"       ";
	 	cout<<HT[i].weight;
	 	cout<<endl;
	}
	for (int i=n+1; i<=m; ++i)     //创建哈夫曼树
	{  //通过n-1次的选择、删除、合并来创建哈夫曼树
		Select( i-1, s1, s2);
		HT[s1]. parent =i;  HT[s2].parent=i; 
		HT[i].lchild=s1;  HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	return n;
}
//查找权重较小的两个结点 
void HuffmanT::Select(int n,int &s1,int &s2)
{
	int min,t;
	for(int k=0;k<2;k++)    //循环体执行两次，找出两个权重最小的叶子结点 
	{
		min=9999;
		for(int i=1;i<=n;i++)
		{
			if(HT[i].Input!=true)      //如果结点已经被访问过了，继续循环 
				continue;
			if(HT[i].weight<min)
			{
				min=HT[i].weight;
				t=i;
			}
		}
		HT[t].Input=false;
		if(k==0)
			s1=t;
		else 
			s2=t;
	}
}
//从叶子到根逆向求每个字符的赫夫曼编码，存储在编码表HC中
void HuffmanT::CreatHuffmanCode( int n)
{
	int c,f,start;
	char *cd;
	HC=new char *[n+1];         		//分配n个字符编码的头指针矢量
	cd=new char [n];			//分配临时存放编码的动态数组空间
	cd[n-1]='\0'; 	                               //编码结束符
	for(int i=1;i<=n; ++i)              //逐个字符求赫夫曼编码
	{	               
		start=n-1; c=i; f=HT[i].parent;       //start开始时指向最后； f指向结点c的双亲结点
		while(f!=0)
		{	                               //从叶子结点开始向上回溯，直到根结点
		    --start;                          			//回溯一次start向前指一个位置
		    if (HT[f].lchild==c)  cd[start]='0';	//结点c是f的左孩子，则生成代码0
		    else     cd[start]='1';               		//结点c是f的右孩子，则生成代码1
		    c=f; f=HT[f].parent;             		//继续向上回溯
		}                                  		//求出第i个字符的编码      
		HC[i]= new char [n-start];         	// 为第i 个字符编码分配空间
		strcpy(HC[i], &cd[start]);            //将求得的编码从临时空间cd复制到HC的当前行中
	}
	delete cd;                               	//释放临时空间
}
//输出哈夫曼编码表 
void HuffmanT::ShowHuffmanCode( int n)
{
	cout<<"赫夫曼编码表:"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<HT[i].data<<"   "<<HC[i]<<endl;
	}
}
//二进制编码转字符串 
void HuffmanT::DecodeHuffman(int n)
{
	int f=2*n-1;          //根结点下标 
	cout<<endl<<"请输入一串哈夫曼编码:"<<endl;
	char *str;
	str=new char;
	cin>>str;
	while(*str!='\0')
	{
		if(*str=='0')
		{
			f=HT[f].lchild;
			if(HT[f].lchild==0&&HT[f].rchild==0)
			{
				cout<<HT[f].data;
				f=2*n-1;
			}	
		}
		else if(*str=='1')
		{
			f=HT[f].rchild;
			if(HT[f].lchild==0&&HT[f].rchild==0)
			{
				cout<<HT[f].data;
				f=2*n-1;
			}	
		}
		str++;
	}
}
//字符串转二进制编码 
void HuffmanT::EncodeHuffman( int n,char *str)
{
	while(*str!='\0')
	{
		for(int i=1;i<=n;i++)
		{
			if(HT[i].data==*str)
				cout<<HC[i];
		}
		str++;
	}
}
//主函数 
int main()
{
	int n; 
	HuffmanT ht;
	char *str;
	str=new char;
	cout<<"请输入待编码的字符串:"<<endl;
	cin>>str;
	n=ht.HuffmanTree(str);
	ht.CreatHuffmanCode(n);
	ht.ShowHuffmanCode(n);
	ht.EncodeHuffman(n,str);
	ht.DecodeHuffman(n);
	return 0;
}


