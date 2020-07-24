#include<iostream>
#include<stdlib.h>

using namespace std;

const int MAXSIZE=100; 

typedef struct BTNode{
	char data;   
	struct BTNode *lchild,*rchild;   
}BTNode;
 
class BtTree
{
	public:
		BtTree();    
		~BtTree();    
		BTNode *GetRoot();  
		void CreatBtTree(char *str);   
		void InOrderBtTree1(BTNode *r);   
		void InOrderBtTree2(BTNode *r);  
	private:
		BTNode *root;   
};
 
BtTree::BtTree()
{
	root=new BTNode;
	root=NULL;   
}
 
BtTree::~BtTree()
{
	delete root;
}
 
BTNode *BtTree::GetRoot()
{
	return root;
}
 
void BtTree::CreatBtTree(char *str)
{
	BTNode *st[MAXSIZE],*p;  //St数组作为顺序栈
	int top=-1,k,j=0;    // top为栈顶指针
	char ch;
	ch=str[j];
	while(ch!='\0')   //循环扫描str中的每个字符
	{
		switch(ch)
		{
			case '(':   //可能有左孩子结点，进栈
				top++;
				st[top]=p;
				k=1;
				break;
			case')':   //栈顶结点的子树处理完毕 
				top--;
				break;
			case',':  //开始处理右孩子结点
				k=2;
				break;
			default:    //遇到结点值，创建一个结点，由p指向它
				p=new BTNode;
				p->data=ch;   //存放结点值，左右指针都设置为空
				p->lchild=p->rchild=NULL;
				if(root==NULL)  //若尚未建立根结点
					root=p;   //p所指结点为二叉树的根结点
				else  //已建立二叉树根结点
				{
					switch(k)
					{
						case 1:st[top]->lchild=p;break;  //新建结点作为栈顶结点的左孩子
						case 2:st[top]->rchild=p;break;  //新建结点作为栈顶结点的右孩子
					}
				} 
		}
		j++;
		ch=str[j];  //继续扫描str
	}
}
 
void BtTree::InOrderBtTree1(BTNode *r)
{
	if(r==NULL)     
		return;
	else
	{
		InOrderBtTree1(r->lchild);  
		cout<<r->data;    
		InOrderBtTree1(r->rchild);   
	}
}
 
void BtTree::InOrderBtTree2(BTNode *r)
{
	BTNode *st[MAXSIZE],*p;   
	int top=-1;   
	p=r;
	while(top!=-1||p!=NULL)
	{
		while(p!=NULL) 
		{
			top++;
			st[top]=p; 
			p=p->lchild; 
		}
		if(top!=-1)  
		{
			p=st[top];
			top--;    
			cout<<p->data;
			p=p->rchild;    
		}
	}
	cout<<endl;
}
 
int main()
{
	BtTree a;
	char *b;
	b=new char;
	char c='n';
	do
	{
		cout<<"用括号表示法输入二叉树:"<<endl;
		cin>>b;
		a.CreatBtTree(b);
		cout<<"中序遍历二叉树递归算法结果为："<<endl;
		a.InOrderBtTree1(a.GetRoot());
		cout<<endl<<"中序遍历二叉树非递归算法结果为："<<endl;
		a.InOrderBtTree2(a.GetRoot());
		cout<<"是否继续：(y/n)"<<endl;
		cin>>c;
		system("cls");
	}while(c=='y'||c=='Y');
	return 0;
}

