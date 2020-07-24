//校园导游咨询
#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
const int MAXSIZE=30;
const int maxValue=9999;
//图的边结构体定义
typedef struct GraphEdge
{
	int dest;   //邻接顶点的位置
	int cost;   //边的权值 
	GraphEdge *link;  // 下一条关联边结点 
	GraphEdge(){}  //无参构造函数
	GraphEdge(int num,int weight):dest(num),cost(weight),link(NULL){}
	bool operator !=(GraphEdge &R)const{
		return (dest!=R.dest)?true:false;
	}  //运算符！=的重构 
}Edge;
//图的结点结构体定义
struct Vertex{
	int num;  //结点的序号 
	string name;  //景点名称 
	string intro;  //景点简介信息 
	Edge *adj;    //第一条关联结点 
};
//邻接表类的定义 
class GraphLink
{
	public:
		GraphLink();  //构造函数 
		~GraphLink();  //析构函数 
		string getValue(int i)  //返回下标为i的结点名 
		{
			return (i>=0&&i<numV)?NodeTable[i].name:0;
		}
		int getWeight(int v1,int v2);  //获取边（v1,v2）权值 
		bool insertVertex(string nam,string intr);//插入结点v 
		bool insertEdge(int v1,int v2,int weight);//插入权值为weight的边（v1,v2）
		int getFirstNeighbor(int v);//取顶点v的第一个邻接顶点
		int getNextNeighbor(int v,int w);//取v的邻接顶点w的下一邻接顶点
		void MakeGraph();  //构建图 
		void ShowIntro();  //输出所有景点的信息 
		void ShowChOne();  //输出用户选择的景点的简介信息 
		void ShortestPath(int v);  //迪杰特斯拉算法 
		int getVertexPos(string v){
			for(int i=0;i<numV;i++)
				if(NodeTable[i].name==v)return i;
			return -1;
		}  //获取景点名为v的结点下标 
		void Floyd(int v1,int v2);  //佛洛依德算法 
	private:
		Vertex *NodeTable;  //邻接表数组 
		int numV,numE;   //结点数，边数 
		bool *visit;    // 辅助布尔数组 
		
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
		if(v1==v2) return 0;
		Edge *p=NodeTable[v1].adj;
		while(p!=NULL&&p->dest!=v2)
			p=p->link;
		if(p!=NULL)return p->cost;
		else return maxValue;
	}
	return 0;
}
//插入顶点nam 
bool GraphLink::insertVertex(string nam,string intr)
{
	if(numV==MAXSIZE) return false;
	NodeTable[numV].num=numV;
	NodeTable[numV].name=nam;
	NodeTable[numV].intro=intr;
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
//初始化图信息 
void GraphLink::MakeGraph()
{
	int n=11,i,j,k,weight;
	string name[11]={"新天天餐厅","第一教学楼","一号宿舍楼",
				"校医院","图书馆","南操","软件楼",
				"第三教学楼","科学楼","工大建国饭店","奥运场馆"};
	string intro[11]={"美味的用餐之所，一日三餐，便宜实惠","老旧但很有韵味,上一些人数较少的选修课",
				"见证过建校以来的每一代工大人，宿舍略小","只能看小病，药费便宜",
				"学习交流之处","现代塑胶跑道，适合晨练",
				"电子设备齐全，程序猿上课的地方","主教学楼，各专业都在这儿上课","学校的主楼，正对南门，办公的地方",
				"国际交流中心","08年奥运会羽毛球馆，现在用于开展各种大型活动"}; 
	for(i=0;i<n;i++)
	{
		insertVertex(name[i],intro[i]);
	}
	insertEdge(0,1,55);  //天天到一教 
	insertEdge(0,2,99);  //天天到一号楼 
	insertEdge(0,3,210); //天天到校医院 
	insertEdge(1,4,96);  // 一教到图书馆 
	insertEdge(1,7,346); //一教到三教 
	insertEdge(7,8,474);  //三教到科学楼 
	insertEdge(0,5,315);  //天天到南操 
	insertEdge(3,5,288);  //校医院到南操 
	insertEdge(3,4,226);  //校医院到图书馆 
	insertEdge(3,6,926);  //校医院到软件楼 
	insertEdge(4,7,392);  //图书馆到三教 
	insertEdge(5,6,712);  //南操到软件楼 
	insertEdge(5,7,196);  //南操到三教 
	insertEdge(8,9,139);  //科学楼到建国 
	insertEdge(5,10,709); //南操到奥运场馆 
	insertEdge(6,10,239);//软件楼到奥运场馆
	insertEdge(8,10,529);//科学楼到 奥运场馆
}
//输出所有景点的信息
void GraphLink::ShowIntro()
{
	cout<<"编号"<<"\t"<<"景点名称"<<setw(19)<<"简介"<<endl;
	for(int i=0;i<numV;i++)
	{
		cout<<setiosflags(ios::left)<<NodeTable[i].num<<"\t"<<setw(23)<<NodeTable[i].name<<setw(32)<<NodeTable[i].intro<<endl;
	} 
}
//输出用户选择的景点的简介信息
void GraphLink::ShowChOne()
{
	cout<<"编号"<<"\t"<<"景点名称"<<endl;
	for(int i=0;i<10;i++)
	{
		cout<<setiosflags(ios::left)<<NodeTable[i].num<<"\t"<<setw(23)<<NodeTable[i].name<<endl;
	} 
	int a;
	cout<<"请选择："<<endl;
	cin>>a;
	if(a>=0&&a<10)
		cout<<NodeTable[a].intro<<endl;
	else
		cout<<"输入有误！"<<endl;
}
//Dijkstra求最短路径的算法
void GraphLink::ShortestPath(int v)
{
	int n=numV; 
	bool *S=new bool[n];  //最短路径顶点集 
	int i,j,k,w,min;
	int dist[n]; 
	//dist[i]是当前求到的从顶点v到顶点i的最短路径长度 
	int path[n];
	//path[i]存放求到的最短路径 
	for(i=0;i<n;i++)
	{
		dist[i]=getWeight(v,i);   //数组初始化 
		S[i]=false;     
		if(i!=v&&dist[i]<maxValue) path[i]=v;
		else path[i]=-1;
	}
	S[v]=true; dist[v]=0;   //顶点v加入顶点集合 
	for(i=0;i<n-1;i++)
	{
		min=maxValue; int u=v;   //选不在S中具有最短路径的顶点u 
		for(j=0;j<n;j++)
			if(S[j]==false&&dist[j]<min)
			{
				u=j;min=dist[j];
			}
		S[u]=true;     //将顶点u加入集合S 
		for(k=0;k<n;k++){       //修改 
			w=getWeight(u,k);
			if(S[k]==false&&w<maxValue&&dist[u]+w<dist[k]){
				//顶点k未加入S，且绕过u可以缩短路径 
				dist[k]=dist[u]+w;
				path[k]=u;   //修改到k的最短路径 
			}
		}
	}
	cout<<"从顶点"<<getValue(v)<<"到其他顶点的最短路径为："<<endl;
	int *d=new int [MAXSIZE];    //栈数组 
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
			cout<<"最短路径长度为:"<<dist[i]<<"m"<<endl;
		}
	}
	delete []d;
}
//计算每一对顶点间最短路径及最短路径长度的Floyd算法 
void GraphLink::Floyd(int v1,int v2)
{
	int i,j,k,n=numV;
	int a[n][n];
	//a[i][j]是顶点i和j之间的最短路径长度 
	int path[n][n];
	//path[i][j]是相应路径上顶点j的前一顶点的顶点号 
	for(i=0;i<n;i++)       //矩阵a与path初始化 
		for(j=0;j<n;j++){
			a[i][j]=getWeight(i,j);
			if(i!=j&&a[i][j]<maxValue) path[i][j]=i;
			else path[i][j]=0;
		}
	for(k=0;k<n;k++)                //针对每一个k，产生a(k)及path(k) 
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(a[i][k]+a[k][j]<a[i][j]){
					a[i][j]=a[i][k]+a[k][j];
					path[i][j]=path[k][j];           //缩短路径长度，绕过k到j 
				}
	int *d=new int [MAXSIZE];     //栈数组 
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
	cout<<"最短路径长度为:"<<a[v1][v2]<<"m"<<endl;
	delete []d;
}
//主函数 
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
		cout<<"欢迎来到北京工业大学"<<endl;
		cout<<"1.北工大的主要景点"<<endl;
		cout<<"2.主要景点浏览路线"<<endl;
		cout<<"3.选择出发地和目的地"<<endl;
		cout<<"4.选择你想要了解的主要景点"<<endl;
		cout<<"5.退出系统"<<endl;
		cout<<"请选择：";
		cin>>a;
		system("cls");
		switch(a)
		{
			case 1:
				gr.ShowIntro();
				break;
			case 2:
				cout<<"请输入一个起始景点的名称:"<<endl;
				cin>>name;
				if(gr.getVertexPos(name)!=-1)
				{
					gr.ShortestPath(gr.getVertexPos(name));
				} 
				else
					cout<<"目标景点不存在!"<<endl;
				break;
			case 3:
				cout<<"请输入出发地:"<<endl;
				cin>>sname;
				if(gr.getVertexPos(sname)==-1)
					cout<<"出发地不存在!"<<endl;
				else
				{
					cout<<"请输入目的地:"<<endl;
					cin>>fname;
					if(gr.getVertexPos(fname)!=-1)
					{
						if(gr.getVertexPos(sname)!=gr.getVertexPos(fname))
							gr.Floyd(gr.getVertexPos(sname),gr.getVertexPos(fname));
						else
							cout<<"目的地即出发地!"<<endl;
					}
					else
						cout<<"目的地不存在:"<<endl;
				}
				break;
			case 4:
				gr.ShowChOne();
				break;
			case 5:
				cout<<"欢迎下次再来！(^_^)"<<endl;
				ch='n';
				break;
			default:
				cout<<"输入非法!"<<endl;
				break;	
		}
		system("pause");
		system("cls");
	}while(ch=='y'||ch=='Y');
	return 0;
}
