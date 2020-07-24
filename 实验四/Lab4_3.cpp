//У԰������ѯ
#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
const int MAXSIZE=30;
const int maxValue=9999;
//ͼ�ı߽ṹ�嶨��
typedef struct GraphEdge
{
	int dest;   //�ڽӶ����λ��
	int cost;   //�ߵ�Ȩֵ 
	GraphEdge *link;  // ��һ�������߽�� 
	GraphEdge(){}  //�޲ι��캯��
	GraphEdge(int num,int weight):dest(num),cost(weight),link(NULL){}
	bool operator !=(GraphEdge &R)const{
		return (dest!=R.dest)?true:false;
	}  //�������=���ع� 
}Edge;
//ͼ�Ľ��ṹ�嶨��
struct Vertex{
	int num;  //������� 
	string name;  //�������� 
	string intro;  //��������Ϣ 
	Edge *adj;    //��һ��������� 
};
//�ڽӱ���Ķ��� 
class GraphLink
{
	public:
		GraphLink();  //���캯�� 
		~GraphLink();  //�������� 
		string getValue(int i)  //�����±�Ϊi�Ľ���� 
		{
			return (i>=0&&i<numV)?NodeTable[i].name:0;
		}
		int getWeight(int v1,int v2);  //��ȡ�ߣ�v1,v2��Ȩֵ 
		bool insertVertex(string nam,string intr);//������v 
		bool insertEdge(int v1,int v2,int weight);//����ȨֵΪweight�ıߣ�v1,v2��
		int getFirstNeighbor(int v);//ȡ����v�ĵ�һ���ڽӶ���
		int getNextNeighbor(int v,int w);//ȡv���ڽӶ���w����һ�ڽӶ���
		void MakeGraph();  //����ͼ 
		void ShowIntro();  //������о������Ϣ 
		void ShowChOne();  //����û�ѡ��ľ���ļ����Ϣ 
		void ShortestPath(int v);  //�Ͻ���˹���㷨 
		int getVertexPos(string v){
			for(int i=0;i<numV;i++)
				if(NodeTable[i].name==v)return i;
			return -1;
		}  //��ȡ������Ϊv�Ľ���±� 
		void Floyd(int v1,int v2);  //���������㷨 
	private:
		Vertex *NodeTable;  //�ڽӱ����� 
		int numV,numE;   //����������� 
		bool *visit;    // ������������ 
		
};
//���캯�� 
GraphLink::GraphLink()
{
	numV=numE=0;
	NodeTable=new Vertex[MAXSIZE];
	visit=new bool[MAXSIZE];
	for(int i=0;i<MAXSIZE;i++)
	{
		NodeTable[i].adj=NULL;
		visit[i]=false; 
	}
}
//��������
GraphLink::~GraphLink()
{
	for(int i=0;i<numV;i++)
	{
		Edge *p=NodeTable[i].adj;
		while(p!=NULL)
		{
			NodeTable[i].adj=p->link;
			delete p;p=NodeTable[i].adj;
		}
	}
	delete []NodeTable;
}
//ȡ����v�ĵ�һ���ڽӶ��� 
int GraphLink::getFirstNeighbor(int v)
{
	if(v!=-1)
	{
		Edge *p=NodeTable[v].adj;
		if(p!=NULL) return p->dest;
	}
	return -1;
}
//ȡv���ڽӶ���w����һ�ڽӶ���
int GraphLink::getNextNeighbor(int v,int w)
{
	if(v!=-1)
	{
		Edge *p=NodeTable[v].adj;
		while(p!=NULL&&p->dest!=w)
			p=p->link;
		if(p!=NULL&&p->link!=NULL) return p->link->dest;
	}
	return -1;
}
//ȡ�ߣ�v1,v2)�ϵ�Ȩֵ 
int GraphLink::getWeight(int v1,int v2)
{
	if(v1!=-1&&v2!=-1)
	{
		if(v1==v2) return 0;
		Edge *p=NodeTable[v1].adj;
		while(p!=NULL&&p->dest!=v2)
			p=p->link;
		if(p!=NULL)return p->cost;
		else return maxValue;
	}
	return 0;
}
//���붥��nam 
bool GraphLink::insertVertex(string nam,string intr)
{
	if(numV==MAXSIZE) return false;
	NodeTable[numV].num=numV;
	NodeTable[numV].name=nam;
	NodeTable[numV].intro=intr;
	numV++;return true;
}
//����ߣ�v1��v2����ȨֵΪweight 
bool GraphLink::insertEdge(int v1,int v2,int weight)
{
	if(v1>=0&&v1<numV&&v2>=0&&v2<numV)
	{
		Edge *q,*p=NodeTable[v1].adj;
		while(p!=NULL&&p->dest!=v2)
			p=p->link;
		if(p!=NULL)return false;
		p=new Edge;q=new Edge;
		p->dest=v2;p->cost=weight;
		p->link=NodeTable[v1].adj;
		NodeTable[v1].adj=p;
		q->dest=v1;q->cost=weight;
		q->link=NodeTable[v2].adj;
		NodeTable[v2].adj=q;
		numE++;return true;
	}
}
//��ʼ��ͼ��Ϣ 
void GraphLink::MakeGraph()
{
	int n=11,i,j,k,weight;
	string name[11]={"���������","��һ��ѧ¥","һ������¥",
				"УҽԺ","ͼ���","�ϲ�","���¥",
				"������ѧ¥","��ѧ¥","���󽨹�����","���˳���"};
	string intro[11]={"��ζ���ò�֮����һ�����ͣ�����ʵ��","�Ͼɵ�������ζ,��һЩ�������ٵ�ѡ�޿�",
				"��֤����У������ÿһ�������ˣ�������С","ֻ�ܿ�С����ҩ�ѱ���",
				"ѧϰ����֮��","�ִ��ܽ��ܵ����ʺϳ���",
				"�����豸��ȫ������Գ�Ͽεĵط�","����ѧ¥����רҵ��������Ͽ�","ѧУ����¥���������ţ��칫�ĵط�",
				"���ʽ�������","08����˻���ë��ݣ��������ڿ�չ���ִ��ͻ"}; 
	for(i=0;i<n;i++)
	{
		insertVertex(name[i],intro[i]);
	}
	insertEdge(0,1,55);  //���쵽һ�� 
	insertEdge(0,2,99);  //���쵽һ��¥ 
	insertEdge(0,3,210); //���쵽УҽԺ 
	insertEdge(1,4,96);  // һ�̵�ͼ��� 
	insertEdge(1,7,346); //һ�̵����� 
	insertEdge(7,8,474);  //���̵���ѧ¥ 
	insertEdge(0,5,315);  //���쵽�ϲ� 
	insertEdge(3,5,288);  //УҽԺ���ϲ� 
	insertEdge(3,4,226);  //УҽԺ��ͼ��� 
	insertEdge(3,6,926);  //УҽԺ�����¥ 
	insertEdge(4,7,392);  //ͼ��ݵ����� 
	insertEdge(5,6,712);  //�ϲٵ����¥ 
	insertEdge(5,7,196);  //�ϲٵ����� 
	insertEdge(8,9,139);  //��ѧ¥������ 
	insertEdge(5,10,709); //�ϲٵ����˳��� 
	insertEdge(6,10,239);//���¥�����˳���
	insertEdge(8,10,529);//��ѧ¥�� ���˳���
}
//������о������Ϣ
void GraphLink::ShowIntro()
{
	cout<<"���"<<"\t"<<"��������"<<setw(19)<<"���"<<endl;
	for(int i=0;i<numV;i++)
	{
		cout<<setiosflags(ios::left)<<NodeTable[i].num<<"\t"<<setw(23)<<NodeTable[i].name<<setw(32)<<NodeTable[i].intro<<endl;
	} 
}
//����û�ѡ��ľ���ļ����Ϣ
void GraphLink::ShowChOne()
{
	cout<<"���"<<"\t"<<"��������"<<endl;
	for(int i=0;i<10;i++)
	{
		cout<<setiosflags(ios::left)<<NodeTable[i].num<<"\t"<<setw(23)<<NodeTable[i].name<<endl;
	} 
	int a;
	cout<<"��ѡ��"<<endl;
	cin>>a;
	if(a>=0&&a<10)
		cout<<NodeTable[a].intro<<endl;
	else
		cout<<"��������"<<endl;
}
//Dijkstra�����·�����㷨
void GraphLink::ShortestPath(int v)
{
	int n=numV; 
	bool *S=new bool[n];  //���·�����㼯 
	int i,j,k,w,min;
	int dist[n]; 
	//dist[i]�ǵ�ǰ�󵽵ĴӶ���v������i�����·������ 
	int path[n];
	//path[i]����󵽵����·�� 
	for(i=0;i<n;i++)
	{
		dist[i]=getWeight(v,i);   //�����ʼ�� 
		S[i]=false;     
		if(i!=v&&dist[i]<maxValue) path[i]=v;
		else path[i]=-1;
	}
	S[v]=true; dist[v]=0;   //����v���붥�㼯�� 
	for(i=0;i<n-1;i++)
	{
		min=maxValue; int u=v;   //ѡ����S�о������·���Ķ���u 
		for(j=0;j<n;j++)
			if(S[j]==false&&dist[j]<min)
			{
				u=j;min=dist[j];
			}
		S[u]=true;     //������u���뼯��S 
		for(k=0;k<n;k++){       //�޸� 
			w=getWeight(u,k);
			if(S[k]==false&&w<maxValue&&dist[u]+w<dist[k]){
				//����kδ����S�����ƹ�u��������·�� 
				dist[k]=dist[u]+w;
				path[k]=u;   //�޸ĵ�k�����·�� 
			}
		}
	}
	cout<<"�Ӷ���"<<getValue(v)<<"��������������·��Ϊ��"<<endl;
	int *d=new int [MAXSIZE];    //ջ���� 
	int top=-1;
	for(i=0;i<n;i++)
	{
		top=-1;
		if(i!=v)
		{
			j=i;
			while(j!=v)
			{
				top++;
				d[top]=j;
				j=path[j];
			}
			cout<<getValue(v);
			while(top!=-1){
				cout<<"->"<<getValue(d[top])<<"  ";
				top--;
			}
			cout<<"���·������Ϊ:"<<dist[i]<<"m"<<endl;
		}
	}
	delete []d;
}
//����ÿһ�Զ�������·�������·�����ȵ�Floyd�㷨 
void GraphLink::Floyd(int v1,int v2)
{
	int i,j,k,n=numV;
	int a[n][n];
	//a[i][j]�Ƕ���i��j֮������·������ 
	int path[n][n];
	//path[i][j]����Ӧ·���϶���j��ǰһ����Ķ���� 
	for(i=0;i<n;i++)       //����a��path��ʼ�� 
		for(j=0;j<n;j++){
			a[i][j]=getWeight(i,j);
			if(i!=j&&a[i][j]<maxValue) path[i][j]=i;
			else path[i][j]=0;
		}
	for(k=0;k<n;k++)                //���ÿһ��k������a(k)��path(k) 
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(a[i][k]+a[k][j]<a[i][j]){
					a[i][j]=a[i][k]+a[k][j];
					path[i][j]=path[k][j];           //����·�����ȣ��ƹ�k��j 
				}
	int *d=new int [MAXSIZE];     //ջ���� 
	int top=-1;
	j=path[v1][v2];     
	while(j!=v1)
	{
		top++;
		d[top]=j;
		j=path[v1][j];
	}
	cout<<getValue(v1);
	while(top!=-1){
			cout<<"->"<<getValue(d[top])<<"  ";
			top--;
		}
	cout<<"->"<<getValue(v2)<<"  ";
	cout<<"���·������Ϊ:"<<a[v1][v2]<<"m"<<endl;
	delete []d;
}
//������ 
int main()
{
	char ch='y';
	int a;
	string name;
	string sname,fname;
	GraphLink gr;
	gr.MakeGraph();
	do
	{
		cout<<"��ӭ����������ҵ��ѧ"<<endl;
		cout<<"1.���������Ҫ����"<<endl;
		cout<<"2.��Ҫ�������·��"<<endl;
		cout<<"3.ѡ������غ�Ŀ�ĵ�"<<endl;
		cout<<"4.ѡ������Ҫ�˽����Ҫ����"<<endl;
		cout<<"5.�˳�ϵͳ"<<endl;
		cout<<"��ѡ��";
		cin>>a;
		system("cls");
		switch(a)
		{
			case 1:
				gr.ShowIntro();
				break;
			case 2:
				cout<<"������һ����ʼ���������:"<<endl;
				cin>>name;
				if(gr.getVertexPos(name)!=-1)
				{
					gr.ShortestPath(gr.getVertexPos(name));
				} 
				else
					cout<<"Ŀ�꾰�㲻����!"<<endl;
				break;
			case 3:
				cout<<"�����������:"<<endl;
				cin>>sname;
				if(gr.getVertexPos(sname)==-1)
					cout<<"�����ز�����!"<<endl;
				else
				{
					cout<<"������Ŀ�ĵ�:"<<endl;
					cin>>fname;
					if(gr.getVertexPos(fname)!=-1)
					{
						if(gr.getVertexPos(sname)!=gr.getVertexPos(fname))
							gr.Floyd(gr.getVertexPos(sname),gr.getVertexPos(fname));
						else
							cout<<"Ŀ�ĵؼ�������!"<<endl;
					}
					else
						cout<<"Ŀ�ĵز�����:"<<endl;
				}
				break;
			case 4:
				gr.ShowChOne();
				break;
			case 5:
				cout<<"��ӭ�´�������(^_^)"<<endl;
				ch='n';
				break;
			default:
				cout<<"����Ƿ�!"<<endl;
				break;	
		}
		system("pause");
		system("cls");
	}while(ch=='y'||ch=='Y');
	return 0;
}
