// �ı�ѹ���ͽ�ѹ��
#include<iostream>
#include<string.h>
using namespace std;
typedef char **HuffmanCode;    //��̬��������洢�����������
//�����������ṹ�� 
typedef struct 
{	int weight;                   //����Ȩֵ
	char data;
	bool Input;
	int parent,lchild,rchild;       //����˫�ס����ӡ��Һ��ӵ��±�
}HTNode,*HuffmTree;    //��̬��������洢��������
//�������������� 
class HuffmanT
{
	public:
		HuffmanT(){}    //���캯�� 
		~HuffmanT(){}   //�������� 
		int  HuffmanTree(char *str);      //����������� 
		void Select(int n,int &s1,int &s2);   //����Ȩ�ؽ�С��������� 
		void CreatHuffmanCode(int n);   //��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
		void ShowHuffmanCode( int n);  //�������������� 
		void EncodeHuffman( int n,char *str);    //�ַ���ת�����Ʊ���
		void DecodeHuffman(int n);       //�����Ʊ���ת�ַ���
	private:
		HuffmTree HT;
		HuffmanCode HC;
};
//�����������HT
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
	cout<<"Ҷ�ӽ�����:"<<n<<endl;  
	m=2*n-1;                 //mΪ���������ܽ����
	//0�ŵ�Ԫδ�ã����Զ�̬����m+1����Ԫ��HT[m]��ʾ�����
	HT=new HTNode[m+1];    
	for (int i=1; i<=m; ++i) //��1~m�ŵ�Ԫ�е�˫�ס����Һ��ӵ��±궼��ʼ��Ϊ0
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
	cout<<"�ַ�       ����Ƶ��"<<endl;
	for (int i=1; i<=n; ++i)  //���� ǰn����Ԫ��Ҷ�ӽ���Ȩֵ
	{
		cout<<HT[i].data<<"       ";
	 	cout<<HT[i].weight;
	 	cout<<endl;
	}
	for (int i=n+1; i<=m; ++i)     //������������
	{  //ͨ��n-1�ε�ѡ��ɾ�����ϲ���������������
		Select( i-1, s1, s2);
		HT[s1]. parent =i;  HT[s2].parent=i; 
		HT[i].lchild=s1;  HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	return n;
}
//����Ȩ�ؽ�С��������� 
void HuffmanT::Select(int n,int &s1,int &s2)
{
	int min,t;
	for(int k=0;k<2;k++)    //ѭ����ִ�����Σ��ҳ�����Ȩ����С��Ҷ�ӽ�� 
	{
		min=9999;
		for(int i=1;i<=n;i++)
		{
			if(HT[i].Input!=true)      //�������Ѿ������ʹ��ˣ�����ѭ�� 
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
//��Ҷ�ӵ���������ÿ���ַ��ĺշ������룬�洢�ڱ����HC��
void HuffmanT::CreatHuffmanCode( int n)
{
	int c,f,start;
	char *cd;
	HC=new char *[n+1];         		//����n���ַ������ͷָ��ʸ��
	cd=new char [n];			//������ʱ��ű���Ķ�̬����ռ�
	cd[n-1]='\0'; 	                               //���������
	for(int i=1;i<=n; ++i)              //����ַ���շ�������
	{	               
		start=n-1; c=i; f=HT[i].parent;       //start��ʼʱָ����� fָ����c��˫�׽��
		while(f!=0)
		{	                               //��Ҷ�ӽ�㿪ʼ���ϻ��ݣ�ֱ�������
		    --start;                          			//����һ��start��ǰָһ��λ��
		    if (HT[f].lchild==c)  cd[start]='0';	//���c��f�����ӣ������ɴ���0
		    else     cd[start]='1';               		//���c��f���Һ��ӣ������ɴ���1
		    c=f; f=HT[f].parent;             		//�������ϻ���
		}                                  		//�����i���ַ��ı���      
		HC[i]= new char [n-start];         	// Ϊ��i ���ַ��������ռ�
		strcpy(HC[i], &cd[start]);            //����õı������ʱ�ռ�cd���Ƶ�HC�ĵ�ǰ����
	}
	delete cd;                               	//�ͷ���ʱ�ռ�
}
//�������������� 
void HuffmanT::ShowHuffmanCode( int n)
{
	cout<<"�շ��������:"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<HT[i].data<<"   "<<HC[i]<<endl;
	}
}
//�����Ʊ���ת�ַ��� 
void HuffmanT::DecodeHuffman(int n)
{
	int f=2*n-1;          //������±� 
	cout<<endl<<"������һ������������:"<<endl;
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
//�ַ���ת�����Ʊ��� 
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
//������ 
int main()
{
	int n; 
	HuffmanT ht;
	char *str;
	str=new char;
	cout<<"�������������ַ���:"<<endl;
	cin>>str;
	n=ht.HuffmanTree(str);
	ht.CreatHuffmanCode(n);
	ht.ShowHuffmanCode(n);
	ht.EncodeHuffman(n,str);
	ht.DecodeHuffman(n);
	return 0;
}


