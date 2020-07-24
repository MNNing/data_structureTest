//图的深度优先遍历和广度优先遍历 
#include<iostream>
using namespace std;
const int MAXSIZE=30;
const int QueueSize=100; 
//队列类的声明 
class CirQueue
{ 
  public:
    CirQueue();  //构造函数 
    void EnQueue(int x);   //入队 
    int DeQueue();       //出队       
    bool Empty();      //布尔判空 
  private:
    int *data;    //队列元素 
    int front, rear;  //队头，队尾指针 
};
//构造函数 
CirQueue::CirQueue()
{
	data=new int[QueueSize];
	front=rear=-1;  //初始条件 
}
//入队 
void CirQueue::EnQueue(int x)
{
	rear++;
	data[rear]=x;
}
//出队 
int CirQueue::DeQueue()
{
	front++;
	return data[front];
}
//布尔判空 
bool CirQueue::Empty()
{
	if(front==rear)
		return true;
	else
		return false;
}
//图的边结构体定义 
typedef struct GraphEdge
{
	int dest;   //邻接顶点的位置 
	int cost;   //边的权值 
	GraphEdge *link;   // 下一条关联边结点 
	GraphEdge(){}  //无参构造函数 
	GraphEdge(int num,int weight):dest(num),cost(weight),link(NULL){}  //含参构造函数 
	bool operator !=(GraphEdge &R)const{
		return (dest!=R.dest)?true:false;
	}  //运算符！=的重构 
}Edge;
//图的结点结构体定义 
struct Vertex{
	char data;  //顶点的信息 
	Edge *adj;  //第一条关联结点 
};
//邻接表类的定义 
class GraphLink
{
	public:
		GraphLink();  //构造函数 
		~GraphLink();  //析构函数 
		int getWeight(int v1,int v2);  //获取边（v1,v2）权值 
		bool insertVertex(const char& v);//插入结点v 
		bool insertEdge(int v1,int v2,int weight);  //插入权值为weight的边（v1,v2） 
		int getFirstNeighbor(int v);  //取顶点v的第一个邻接顶点
		int getNextNeighbor(int v,int w);//取v的邻接顶点w的下一邻接顶点
		void DFSTraverse(int v);// 深度优先遍历
		void BFSTraverse(int v);//广度优先遍历
		void MakeGraph();//构建图 
	private:
		Vertex *NodeTable;  //邻接表数组 
		int numV,numE;  //顶点数，边数 
		bool *visit;   // 辅助布尔数组 
		int getVertexPos(const char v){
			for(int i=0;i<numV;i++)
				if(NodeTable[i].data==v)return i;
			return -1;
		}    //返回结点v的位置下标 
};
//构造函数 
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
//析构函数 
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
//取顶点v的第一个邻接顶点 
int GraphLink::getFirstNeighbor(int v)
{
	if(v!=-1)
	{
		Edge *p=NodeTable[v].adj;
		if(p!=NULL) return p->dest;
	}
	return -1;
}
//取v的邻接顶点w的下一邻接顶点
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
//取边（v1,v2)上的权值
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
//插入顶点v
bool GraphLink::insertVertex(const char&v)
{
	if(numV==MAXSIZE) return false;
	NodeTable[numV].data=v;
	numV++;return true;
}
//插入边（v1，v2），权值为weight 
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
//深度优先遍历 
void GraphLink::DFSTraverse(int v)
{
	int w;
	visit[v]=true;
	cout<<NodeTable[v].data;
	for(w=getFirstNeighbor(v);w>=0;w=getNextNeighbor(v,w))
		if(!visit[w]) DFSTraverse(w);
}
//广度优先遍历 
void GraphLink::BFSTraverse(int v)
{
	CirQueue cq;  //队列类对象 
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
//构建图 
void GraphLink::MakeGraph()
{
	int n,m,i,j,k,weight;
	char e1,e2;
	cout<<"请输入顶点数目："<<endl;
	cin>>n;
	cout<<"请输入弧数："<<endl;
	cin>>m;
	cout<<"请输入"<<n<<"个顶点"<<endl;
	for(i=0;i<n;i++)
	{
		cout<<"输入顶点"<<i<<":";
		cin>>e1;insertVertex(e1);
	}
	i=0;
	cout<<"输入"<<m<<"条弧"<<endl; 
	while(i<m)
	{
		cout<<"输入弧"<<i<<":";
		cin>>e1>>e2>>weight;
		j=getVertexPos(e1);k=getVertexPos(e2);
		if(j==-1||k==-1)
			cout<<"边两端点信息有误，重新输入!"<<endl;
		else
		{
			insertEdge(j,k,weight);
			i++;
		}
	}
}
//主函数 
int main()
{
	GraphLink gr;  //邻接表类对象 
	gr.MakeGraph();  //构建邻接表 
	cout<<"深度优先遍历:"<<endl;
	gr.DFSTraverse(0);
	cout<<endl<<"广度优先遍历:"<<endl;
	gr.BFSTraverse(0);
	return 0;
}
