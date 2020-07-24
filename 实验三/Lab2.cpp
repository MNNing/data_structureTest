#include<iostream>
#include<stdlib.h>

using namespace std;

const int MAXSIZE=20;
  
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
		int SumNodes(BTNode *b);     
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
 
int BtTree::SumNodes(BTNode *b)
{
    if (b==NULL) 
		return 0;
    else
    	return SumNodes(b->lchild)+SumNodes(b->rchild)+1;
}

int main()
{
	int b=0;
	char d;
	do
	{
		BtTree a;
		char *c;
		c=new char;
		cout<<"�����ű�ʾ�������������"<<endl;
		cin>>c;
		a.CreatBtTree(c);
		b=a.SumNodes(a.GetRoot());
		cout<<"�����ĿΪ :"<<b<<endl;
		cout<<"�Ƿ������(y/n)"<<endl;
		cin>>d;
		system("cls");
	}while(d=='y'||d=='Y');
	return 0;
}
