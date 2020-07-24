//线索化二叉树
#include<iostream>
using namespace std;
const int MAXSIZE=100;
//线索二叉树结点 
typedef struct node
{
	char data;//结点数据域
	int ltag,rtag;//增加的线索标记
	struct node* lchild;//左孩子或线索指针
	struct node* rchild;//右孩子或线索指针
}TBTNode;//线索树结点类型定义
TBTNode *pre;		   		//全局变量
class InThrBiTree
{    
    public:
        InThrBiTree();    //构造函数 
        ~ InThrBiTree( );   //析构函数 
		void CreatThread();     //中序线索化二叉树
 		void  Thread(TBTNode *&p); //对二叉树进行中序线索化
   		void ThInOrder();   //中序遍历二叉线索树
		void CreatBtTree(char *str);  //创建二叉树 
    private:
        TBTNode *root,*head;   //root为根结点，head为头结点 
};
//构造函数 
InThrBiTree::InThrBiTree()
{
	root=new TBTNode;
	root=NULL;
}
//析构函数 
InThrBiTree::~ InThrBiTree()
{
	delete root;
}
//中序线索化二叉树
void InThrBiTree::CreatThread()     
{
    head=new TBTNode;        //创建头结点
    head->ltag=0;             //头结点有左孩子，若树非空，则其左孩子为树根
    head->rtag=1;               //头结点的右孩子指针为右线索
    head->rchild=root;          //头结点的右孩子指针指向根结点
    pre=new TBTNode;
    if (root==NULL)  head->lchild=head;   //若树为空，则左指针也指向自己
    else
    {
		head->lchild=root;      //头结点的左孩子指向根
		pre=head;            //pre是*p的前驱结点，供加线索用，pre初值指向头结点
		Thread(root);       //调用Thread()算法，对以b为根的二叉树进行中序线索化
		pre->rchild=head;       //Thread()算法结束后，pre为最右结点，pre的右线索指向头结点
		pre->rtag=1;
		head->rchild=pre;    	   //头结点的右线索指向pre
     }
} 
//对二叉树进行中序线索化
void  InThrBiTree::Thread(TBTNode *&p)    		
{   if (p!=NULL)	
    {  
	     Thread(p->lchild);           		//左子树线索化
	     if (p->lchild==NULL)          	//左孩子不存在，进行前驱结点线索化
	     {   p->lchild=pre; p->ltag=1;  }	//建立当前结点的前驱线索
	     else  p->ltag=0;                                 //p结点的左子树已线索化
	     if  (pre->rchild==NULL)	     	//对pre的后继结点线索化
	     {     pre->rchild=p;pre->rtag=1;}	//建立前驱结点的后继线索
	     else  pre->rtag=0;
	     pre=p;
	     Thread(p->rchild);  		//递归调用右子树线索化
    }
} 
//中序遍历二叉线索树，对每个数据元素直接输出
void InThrBiTree::ThInOrder()
{      //头结点的左链lchild指向根结点
       
      TBTNode *p=head->lchild;	 //p指向根结点
       while (p!=head)            //空树或遍历结束时，p==head
       {     
            while (p->ltag==0)   p=p->lchild;     //沿左孩子向下找开始结点
			cout<<p->data;		       //访问开始结点
			while (p->rtag==1 && p->rchild!=head)
			{   p=p->rchild;                  //沿右线索访问后继结点   
	    		cout<<p->data;
			}
			p=p->rchild;                 //转向p的右子树 
       }
} 
//构建二叉树 
void InThrBiTree::CreatBtTree(char *str)
{
	TBTNode *st[MAXSIZE],*p;  //St数组作为顺序栈
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
				p=new TBTNode;
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
//主函数 
int main()
{
	InThrBiTree ib;
	char *str;
	str=new char;
	cout<<"请输入二叉树括号表示串:"<<endl;
	cin>>str;
	ib.CreatBtTree(str);
	ib.CreatThread();
	ib.ThInOrder();
	return 0;
}
