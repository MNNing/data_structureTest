//建立二叉搜索树、实现其删除算法
#include<iostream>
using namespace std;
const int MaxSize=50;
//二叉树结点结构体 
typedef struct BiTreeNode{
	int data;
	BiTreeNode *Lchild,*Rchild;
}BiNode;
//二叉搜索树类的定义 
class BiSortTree
{
	public:
		BiSortTree();    //构造函数 
		~BiSortTree();    //析构函数 
		void InsertBST(BiNode *&root,BiNode *&s);    //插入结点 
		void MakeBST(int r[],int n);       //构建二叉树 
		void InOrderTraverse(BiNode *T);     //中序遍历二叉树 
		void DeleteBST(int k);           //删除结点 
		BiNode *SearchBST(BiNode *t,int k);          //查找结点 
		BiNode *GetRoot(){ return root;}      //返回根结点 
	private:
		BiNode *root;     //根结点 
};
//构造函数 
BiSortTree::BiSortTree()
{
	root=new BiNode;
	root=NULL;
} 
//析构函数 
BiSortTree::~BiSortTree()
{
	delete root;
} 
//插入结点 
void BiSortTree::InsertBST(BiNode *&root,BiNode *&s)
{
	if(root==NULL)        //根结点为空 
	{
		root=s;         //将s赋值给根结点root 
	}	
	else if(s->data<root->data)      //小于，插入左子树 
		InsertBST(root->Lchild,s);
	else
		InsertBST(root->Rchild,s);     //大于，插入右子树 
}
//构建二叉搜索树 
void BiSortTree::MakeBST(int r[],int n)
{
	for(int i=0;i<n;i++)
	{
		BiNode *s;
		s=new BiNode;
		s->data=r[i];
		s->Lchild=s->Rchild=NULL;
		InsertBST(root,s);
	}
	InOrderTraverse(root);        //中序遍历二叉树 
}
// 中序遍历二叉树 
void BiSortTree::InOrderTraverse(BiNode *T)
{
	if(T==NULL) return;
	else{
		
		InOrderTraverse(T->Lchild);
		cout<<T->data<<" ";
		InOrderTraverse(T->Rchild);
	}
}
//查找某个结点 
BiNode *BiSortTree::SearchBST(BiNode * t,int k)
{
	if(t==NULL)
		return NULL;
	else if( t->data==k)
		return  t;
	else if(k< t->data)
		return SearchBST( t->Lchild,k);
	else return SearchBST( t->Rchild,k);
}
//删除某个结点 
void BiSortTree::DeleteBST(int k)
{
	BiNode *b,*t,*p,*s,*par;
	int num;
	b=SearchBST(root,k);
	t=p=root;
	s=par=NULL;
	if(b)            //如果结点存在，接着删除 
	{
		while(p!=NULL)     //寻找结点的位置及结点的双亲结点 
		{
			if(b->data==p->data)
			{
				b=p;
				break;
			}
			else if(b->data<p->data)
			{
				t=p;p=p->Lchild;
			}
			else 
			{
				t=p;p=p->Rchild;
			}	
		} 
		if(t->Lchild==b)       //看b是双亲的左孩子还是右孩子 
			num=1;
		else if(t->Rchild==b)
			num=2;
		if(b->Lchild==NULL&&b->Rchild==NULL)  //若结点p是叶子，则直接删除结点p
		{
			if(num==1)
				t->Lchild=NULL;
			else if(num==2)
				t->Rchild=NULL;
		}
		else if(b->Lchild!=NULL&&b->Rchild==NULL)    //若结点p只有左子树，则只需重接p的左子树
		{
			if(num==1)
				t->Lchild=b->Lchild;
			else if(num==2)
				t->Rchild=b->Lchild;
		}
		else if(b->Lchild==NULL&&b->Rchild!=NULL)    //若结点p只有右子树，则只需重接p的右子树
		{
			if(num==1)
				t->Lchild=b->Rchild;
			else if(num==2)
				t->Rchild=b->Rchild;
		}
		else if(b->Lchild!=NULL&&b->Rchild!=NULL)   //若结点p的左右子树均不空 
		{
			//查找结点p的右子树上的最左下结点s及其双亲结点par
			s=b->Rchild;
			while(s!=NULL)
			{
				par=s;
				s=s->Lchild;
			}
			b->data=s->data;      //将结点s数据域替换到被删结点p的数据域
			if(b->Rchild->Lchild==NULL)    //若结点p的右孩子无左子树
				par->Rchild=s->Rchild;     //将s的右子树接到par的右子树上
			else
				par->Lchild=s->Rchild;     //否则，将s的右子树接到结点par的左子树上
			delete s;      //删除结点s
			
		}
		cout<<"删除成功!"<<endl; 
		InOrderTraverse(root);
	}
	else
		cout<<"要删除的结点不存在！"<<endl;
}
//主函数 
int main()
{
	int n;
	int r[MaxSize];
	BiSortTree bi;
	cout<<"请输入数据个数:"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"请输入第"<<i+1<<"个数:"<<endl;
		cin>>r[i];
	}
	bi.MakeBST(r,n);
	cout<<endl;
	cout<<"请输入想要搜索的数据:"<<endl;
	cin>>r[n];
	BiNode *p;
	p=bi.SearchBST(bi.GetRoot(),r[n]);
	if(p)
		cout<<"找到了!"<<endl;
	else
		cout<<"未找到!"<<endl; 
	cout<<"请输入要删除的结点数据:"<<endl;
	cin>>r[n];
	bi.DeleteBST(r[n]);
	return 0;
}

