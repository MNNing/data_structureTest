//ͼ��������ȱ����͹�����ȱ��� 
#include<iostream>
using namespace std;
const int MAXSIZE=30;
const int QueueSize=100; 
//����������� 
class CirQueue
{ 
  public:
    CirQueue();  //���캯�� 
    void EnQueue(int x);   //��� 
    int DeQueue();       //����       
    bool Empty();      //�����п� 
  private:
    int *data;    //����Ԫ�� 
    int front, rear;  //��ͷ����βָ�� 
};
//���캯�� 
CirQueue::CirQueue()
{
	data=new int[QueueSize];
	front=rear=-1;  //��ʼ���� 
}
//��� 
void CirQueue::EnQueue(int x)
{
	rear++;
	data[rear]=x;
}
//���� 
int CirQueue::DeQueue()
{
	front++;
	return data[front];
}
//�����п� 
bool CirQueue::Empty()
{
	if(front==rear)
		return true;
	else
		return false;
}
//ͼ�ı߽ṹ�嶨�� 
typedef struct GraphEdge
{
	int dest;   //�ڽӶ����λ�� 
	int cost;   //�ߵ�Ȩֵ 
	GraphEdge *link;   // ��һ�������߽�� 
	GraphEdge(){}  //�޲ι��캯�� 
	GraphEdge(int num,int weight):dest(num),cost(weight),link(NULL){}  //���ι��캯�� 
	bool operator !=(GraphEdge &R)const{
		return (dest!=R.dest)?true:false;
	}  //�������=���ع� 
}Edge;
//ͼ�Ľ��ṹ�嶨�� 
struct Vertex{
	char data;  //�������Ϣ 
	Edge *adj;  //��һ��������� 
};
//�ڽӱ���Ķ��� 
class GraphLink
{
	public:
		GraphLink();  //���캯�� 
		~GraphLink();  //�������� 
		int getWeight(int v1,int v2);  //��ȡ�ߣ�v1,v2��Ȩֵ 
		bool insertVertex(const char& v);//������v 
		bool insertEdge(int v1,int v2,int weight);  //����ȨֵΪweight�ıߣ�v1,v2�� 
		int getFirstNeighbor(int v);  //ȡ����v�ĵ�һ���ڽӶ���
		int getNextNeighbor(int v,int w);//ȡv���ڽӶ���w����һ�ڽӶ���
		void DFSTraverse(int v);// ������ȱ���
		void BFSTraverse(int v);//������ȱ���
		void MakeGraph();//����ͼ 
	private:
		Vertex *NodeTable;  //�ڽӱ����� 
		int numV,numE;  //������������ 
		bool *visit;   // ������������ 
		int getVertexPos(const char v){
			for(int i=0;i<numV;i++)
				if(NodeTable[i].data==v)return i;
			return -1;
		}    //���ؽ��v��λ���±� 
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
		Edge *p=NodeTable[v1].adj;
		while(p!=NULL&&p->dest!=v2)
			p=p->link;
		if(p!=NULL)return p->cost;
	}
	return 0;
}
//���붥��v
bool GraphLink::insertVertex(const char&v)
{
	if(numV==MAXSIZE) return false;
	NodeTable[numV].data=v;
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
//������ȱ��� 
void GraphLink::DFSTraverse(int v)
{
	int w;
	visit[v]=true;
	cout<<NodeTable[v].data;
	for(w=getFirstNeighbor(v);w>=0;w=getNextNeighbor(v,w))
		if(!visit[w]) DFSTraverse(w);
}
//������ȱ��� 
void GraphLink::BFSTraverse(int v)
{
	CirQueue cq;  //��������� 
	int u,w;
	for(int i=0;i<numV;i++)
	{
		visit[i]=false;
	}
	visit[v]=true;
	cq.EnQueue(v);
	cout<<NodeTable[v].data;
	while(!cq.Empty())
	{
		u=cq.DeQueue();
		for(w=getFirstNeighbor(u);w>=0;w=getNextNeighbor(u,w))
		{
			if(!visit[w])
			{
				visit[w]=true;
				cq.EnQueue(w);
				cout<<NodeTable[w].data;
			}
		}
	}
}
//����ͼ 
void GraphLink::MakeGraph()
{
	int n,m,i,j,k,weight;
	char e1,e2;
	cout<<"�����붥����Ŀ��"<<endl;
	cin>>n;
	cout<<"�����뻡����"<<endl;
	cin>>m;
	cout<<"������"<<n<<"������"<<endl;
	for(i=0;i<n;i++)
	{
		cout<<"���붥��"<<i<<":";
		cin>>e1;insertVertex(e1);
	}
	i=0;
	cout<<"����"<<m<<"����"<<endl; 
	while(i<m)
	{
		cout<<"���뻡"<<i<<":";
		cin>>e1>>e2>>weight;
		j=getVertexPos(e1);k=getVertexPos(e2);
		if(j==-1||k==-1)
			cout<<"�����˵���Ϣ������������!"<<endl;
		else
		{
			insertEdge(j,k,weight);
			i++;
		}
	}
}
//������ 
int main()
{
	GraphLink gr;  //�ڽӱ������ 
	gr.MakeGraph();  //�����ڽӱ� 
	cout<<"������ȱ���:"<<endl;
	gr.DFSTraverse(0);
	cout<<endl<<"������ȱ���:"<<endl;
	gr.BFSTraverse(0);
	return 0;
}
