//��С������ 
#include<iostream>
using namespace std;
const int MAXVER=101;  //��������󶥵��� 
const long MAXEDG=10100;//������������ 
const int MAXSIZE=30;   //ͼ��󶥵��� 
const int maxWeight=999;  //û��ͨ·������Ȩֵ 
//�������߽ṹ�� 
struct Edges{
	int u,v;
	int cost;
};
//ͼ����С�������ඨ�� 
class MinSpanTree
{
	public:
		MinSpanTree();//���캯�� 
		~MinSpanTree();  //�������� 
		bool insertVertex(const char &v);  // ���붥��v
		bool insertEdge(int v1,int v2,int cost);  //����ߣ�v1��v2����ȨֵΪcost 
		void MakeGraph();  //����ͼ 
		void sort();   //���򣬰��ձߵ�Ȩ�أ���С���� 
		int find(int v);  //·��ѹ�� 
		int union_set(int i);  //����Ƿ����ɻ� 
		void Kruskal();   // ������С������ 
		void ShowTree();   //�����С������ 
		int getWeight(int v1,int v2)  //ȡ�ߣ�v1,v2)�ϵ�Ȩֵ 
		{
			return v1!=-1&&v2!=-1?edge[v1][v2]:0;
		} 
	private:
		char *vertex;  //ͼ�Ľ��ֵ 
		int **edge;   //ͼ�ı�  
		int v_num,e_num,Edge_num;  //ͼ�Ľ��������������С�������ı��� 
		struct Edges Edge[MAXVER];  //��С�������ı� 
		int Parent[MAXVER];  //˫�׽�� 
		int Size[MAXVER];    //���ڰ���ѹ��  
		int Flag[MAXVER];     
		int getVertexPos(char v)
		{
			for(int i=0;i<v_num;i++)
				if(vertex[i]==v)return i;
			return -1;
		}
};
//���캯�� 
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
         // ��parent��ʼ��Ϊ����
        Parent[i] = i;
         // ��size��ʼ��Ϊ1�����ڰ���ѹ�����������Ҫ���а���ѹ��������Ҫ���������Ϣ��
        Size[i] = 1;
    }
}
//�鹹���� 
MinSpanTree::~MinSpanTree()
{
	delete []vertex;delete []edge;
}
// ���붥��v
bool MinSpanTree::insertVertex(const char &v)
{
	if(v_num==MAXSIZE) return false;
	vertex[v_num++]=v;
	return true;
}
//����ߣ�v1��v2����ȨֵΪcost  
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
//����ͼ 
void MinSpanTree::MakeGraph()
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
//���򣬰��ձߵ�Ȩ�أ���С���� 
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
//����˫�׽���±� 
int MinSpanTree::find(int v)
{
	if(v != Parent[v]) {
        Parent[v] = find(Parent[v]); // ·��ѹ��
    }
    return Parent[v];
}
//����Ƿ����ɻ�
int MinSpanTree::union_set(int i)
{
	int parent_u = find(Edge[i].u);
    int parent_v = find(Edge[i].v);

    // �ڵ�u��v�Ѿ���ͬһ��������
    if(parent_u == parent_v) {
        return 0;
    }

    // ����ѹ��������СһЩ�������뵽�ȴ�һЩ����
    if(Size[parent_u] > Size[parent_v]) {
        Parent[parent_v] = parent_u;
        Size[parent_u] += Size[parent_v];
    } else {
        Parent[parent_u] = parent_v;
        Size[parent_v] += Size[parent_u];
    }
    return 1;
} 
// Kruskal�㷨����С������ 
void MinSpanTree::Kruskal()
{
	int i;
    int counter;
    // ���򣬰��ձߵ�Ȩ�أ���С��������
    sort();
    counter = 0;
    // ���ձߵ�Ȩ�أ���С����������еı�
    // ֱ�����������бߣ�������������С������Ϊֹ
    for(i = 1; i <= Edge_num&& counter < v_num-1; i++) {
        // ���¼���ı߻��γɻ�ʱ����Ҫ����
        if(union_set(i) == 0) {
            continue;
        }
        // ���¼���ıߵı�ű�����Flag�����У��Ա�����
        counter++;
        Flag[counter] = i;
    }
}
//�����С������ 
void MinSpanTree::ShowTree()
{
	int sum=0;
	for(int i=1;i<v_num;i++)
	{
		cout<<vertex[Edge[Flag[i]].u]<<"to"<<vertex[Edge[Flag[i]].v]<<endl;
		sum+=Edge[Flag[i]].cost;
	}
	cout<<"���·��Ϊ:"<<sum<<endl;
}
//������ 
int main()
{
	MinSpanTree mi;
	mi.MakeGraph();
	mi.Kruskal();
	mi.ShowTree();
	return 0;
}
