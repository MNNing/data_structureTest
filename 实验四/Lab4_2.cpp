//最小生成树 
#include<iostream>
using namespace std;
const int MAXVER=101;  //生成树最大顶点数 
const long MAXEDG=10100;//生成树最大边数 
const int MAXSIZE=30;   //图最大顶点数 
const int maxWeight=999;  //没有通路的两点权值 
//生成树边结构体 
struct Edges{
	int u,v;
	int cost;
};
//图的最小生成树类定义 
class MinSpanTree
{
	public:
		MinSpanTree();//构造函数 
		~MinSpanTree();  //析构函数 
		bool insertVertex(const char &v);  // 插入顶点v
		bool insertEdge(int v1,int v2,int cost);  //插入边（v1，v2），权值为cost 
		void MakeGraph();  //构建图 
		void sort();   //排序，按照边的权重，从小到大 
		int find(int v);  //路径压缩 
		int union_set(int i);  //检查是否生成环 
		void Kruskal();   // 生成最小生成树 
		void ShowTree();   //输出最小生成树 
		int getWeight(int v1,int v2)  //取边（v1,v2)上的权值 
		{
			return v1!=-1&&v2!=-1?edge[v1][v2]:0;
		} 
	private:
		char *vertex;  //图的结点值 
		int **edge;   //图的边  
		int v_num,e_num,Edge_num;  //图的结点数，边数，最小生成树的边数 
		struct Edges Edge[MAXVER];  //最小生成树的边 
		int Parent[MAXVER];  //双亲结点 
		int Size[MAXVER];    //用于按秩压缩  
		int Flag[MAXVER];     
		int getVertexPos(char v)
		{
			for(int i=0;i<v_num;i++)
				if(vertex[i]==v)return i;
			return -1;
		}
};
//构造函数 
MinSpanTree::MinSpanTree()
{
	v_num=0;e_num=0;
	int i,j;
	Edge_num=0;
	vertex=new char[MAXSIZE];
	edge=new int*[MAXSIZE];
	for(int i=0;i<MAXSIZE;i++)
	{
		edge[i]=new int[MAXSIZE];
	}
	for(int i=0;i<MAXSIZE;i++)
		for(int j=0;j<MAXSIZE;j++)
			edge[i][j]=(i==j)?0:maxWeight;	
	for(int i = 0; i <=MAXVER; i++) {
         // 将parent初始化为自身
        Parent[i] = i;
         // 将size初始化为1，用于按秩压缩（如果不需要进行按秩压缩，不需要这个数组信息）
        Size[i] = 1;
    }
}
//虚构函数 
MinSpanTree::~MinSpanTree()
{
	delete []vertex;delete []edge;
}
// 插入顶点v
bool MinSpanTree::insertVertex(const char &v)
{
	if(v_num==MAXSIZE) return false;
	vertex[v_num++]=v;
	return true;
}
//插入边（v1，v2），权值为cost  
bool MinSpanTree::insertEdge(int v1,int v2,int cost)
{
	if(v1>-1&&v1<v_num&&v2>-1&&v2<v_num&&edge[v1][v2]==maxWeight)
	{
		edge[v1][v2]=edge[v2][v1]=cost;e_num++;
		Edge_num++;
		Edge[Edge_num].u=v1;Edge[Edge_num].v=v2;Edge[Edge_num].cost=cost;
		return true;
	}
	else
	{ 
		return false;
	}	
}
//构建图 
void MinSpanTree::MakeGraph()
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
//排序，按照边的权重，从小到大 
void MinSpanTree::sort()
{
	int i, j;
    int temp_u, temp_v, temp_cost;

    for(i = 1; i < Edge_num; i++) {
        for(j = 1; j <= Edge_num - i; j++) {
            if(Edge[j].cost > Edge[j+1].cost) {
                temp_u = Edge[j].u;
                temp_v = Edge[j].v;
                temp_cost = Edge[j].cost;
                Edge[j].u = Edge[j+1].u;
                Edge[j].v = Edge[j+1].v;
                Edge[j].cost = Edge[j+1].cost;
                Edge[j+1].u = temp_u;
                Edge[j+1].v = temp_v;
                Edge[j+1].cost = temp_cost;
            }
        }
    }
}
//返回双亲结点下标 
int MinSpanTree::find(int v)
{
	if(v != Parent[v]) {
        Parent[v] = find(Parent[v]); // 路径压缩
    }
    return Parent[v];
}
//检查是否生成环
int MinSpanTree::union_set(int i)
{
	int parent_u = find(Edge[i].u);
    int parent_v = find(Edge[i].v);

    // 节点u和v已经在同一颗树上了
    if(parent_u == parent_v) {
        return 0;
    }

    // 按秩压缩，将秩小一些的树加入到秩大一些的树
    if(Size[parent_u] > Size[parent_v]) {
        Parent[parent_v] = parent_u;
        Size[parent_u] += Size[parent_v];
    } else {
        Parent[parent_u] = parent_v;
        Size[parent_v] += Size[parent_u];
    }
    return 1;
} 
// Kruskal算法求最小生成树 
void MinSpanTree::Kruskal()
{
	int i;
    int counter;
    // 排序，按照边的权重，从小到大排序
    sort();
    counter = 0;
    // 按照边的权重，从小到大遍历所有的边
    // 直到编译完所有边，或者生成了最小生成树为止
    for(i = 1; i <= Edge_num&& counter < v_num-1; i++) {
        // 当新加入的边会形成环时，需要舍弃
        if(union_set(i) == 0) {
            continue;
        }
        // 将新加入的边的编号保存在Flag数组中，以便输入
        counter++;
        Flag[counter] = i;
    }
}
//输出最小生成树 
void MinSpanTree::ShowTree()
{
	int sum=0;
	for(int i=1;i<v_num;i++)
	{
		cout<<vertex[Edge[Flag[i]].u]<<"to"<<vertex[Edge[Flag[i]].v]<<endl;
		sum+=Edge[Flag[i]].cost;
	}
	cout<<"最短路径为:"<<sum<<endl;
}
//主函数 
int main()
{
	MinSpanTree mi;
	mi.MakeGraph();
	mi.Kruskal();
	mi.ShowTree();
	return 0;
}
