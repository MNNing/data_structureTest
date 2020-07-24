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
	BTNode *st[MAXSIZE],*p;  //St������Ϊ˳��ջ
	int top=-1,k,j=0;    // topΪջ��ָ��
	char ch;
	ch=str[j];
	while(ch!='\0')   //ѭ��ɨ��str�е�ÿ���ַ�
	{
		switch(ch)
		{
			case '(':   //���������ӽ�㣬��ջ
				top++;
				st[top]=p;
				k=1;
				break;
			case')':   //ջ����������������� 
				top--;
				break;
			case',':  //��ʼ�����Һ��ӽ��
				k=2;
				break;
			default:    //�������ֵ������һ����㣬��pָ����
				p=new BTNode;
				p->data=ch;   //��Ž��ֵ������ָ�붼����Ϊ��
				p->lchild=p->rchild=NULL;
				if(root==NULL)  //����δ���������
					root=p;   //p��ָ���Ϊ�������ĸ����
				else  //�ѽ��������������
				{
					switch(k)
					{
						case 1:st[top]->lchild=p;break;  //�½������Ϊջ����������
						case 2:st[top]->rchild=p;break;  //�½������Ϊջ�������Һ���
					}
				} 
		}
		j++;
		ch=str[j];  //����ɨ��str
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
		cout<<"�����ű�ʾ�����������:"<<endl;
		cin>>b;
		a.CreatBtTree(b);
		cout<<"��������������ݹ��㷨���Ϊ��"<<endl;
		a.InOrderBtTree1(a.GetRoot());
		cout<<endl<<"��������������ǵݹ��㷨���Ϊ��"<<endl;
		a.InOrderBtTree2(a.GetRoot());
		cout<<"�Ƿ������(y/n)"<<endl;
		cin>>c;
		system("cls");
	}while(c=='y'||c=='Y');
	return 0;
}

