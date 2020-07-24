//����������������ʵ����ɾ���㷨
#include<iostream>
using namespace std;
const int MaxSize=50;
//���������ṹ�� 
typedef struct BiTreeNode{
	int data;
	BiTreeNode *Lchild,*Rchild;
}BiNode;
//������������Ķ��� 
class BiSortTree
{
	public:
		BiSortTree();    //���캯�� 
		~BiSortTree();    //�������� 
		void InsertBST(BiNode *&root,BiNode *&s);    //������ 
		void MakeBST(int r[],int n);       //���������� 
		void InOrderTraverse(BiNode *T);     //������������� 
		void DeleteBST(int k);           //ɾ����� 
		BiNode *SearchBST(BiNode *t,int k);          //���ҽ�� 
		BiNode *GetRoot(){ return root;}      //���ظ���� 
	private:
		BiNode *root;     //����� 
};
//���캯�� 
BiSortTree::BiSortTree()
{
	root=new BiNode;
	root=NULL;
} 
//�������� 
BiSortTree::~BiSortTree()
{
	delete root;
} 
//������ 
void BiSortTree::InsertBST(BiNode *&root,BiNode *&s)
{
	if(root==NULL)        //�����Ϊ�� 
	{
		root=s;         //��s��ֵ�������root 
	}	
	else if(s->data<root->data)      //С�ڣ����������� 
		InsertBST(root->Lchild,s);
	else
		InsertBST(root->Rchild,s);     //���ڣ����������� 
}
//�������������� 
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
	InOrderTraverse(root);        //������������� 
}
// ������������� 
void BiSortTree::InOrderTraverse(BiNode *T)
{
	if(T==NULL) return;
	else{
		
		InOrderTraverse(T->Lchild);
		cout<<T->data<<" ";
		InOrderTraverse(T->Rchild);
	}
}
//����ĳ����� 
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
//ɾ��ĳ����� 
void BiSortTree::DeleteBST(int k)
{
	BiNode *b,*t,*p,*s,*par;
	int num;
	b=SearchBST(root,k);
	t=p=root;
	s=par=NULL;
	if(b)            //��������ڣ�����ɾ�� 
	{
		while(p!=NULL)     //Ѱ�ҽ���λ�ü�����˫�׽�� 
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
		if(t->Lchild==b)       //��b��˫�׵����ӻ����Һ��� 
			num=1;
		else if(t->Rchild==b)
			num=2;
		if(b->Lchild==NULL&&b->Rchild==NULL)  //�����p��Ҷ�ӣ���ֱ��ɾ�����p
		{
			if(num==1)
				t->Lchild=NULL;
			else if(num==2)
				t->Rchild=NULL;
		}
		else if(b->Lchild!=NULL&&b->Rchild==NULL)    //�����pֻ������������ֻ���ؽ�p��������
		{
			if(num==1)
				t->Lchild=b->Lchild;
			else if(num==2)
				t->Rchild=b->Lchild;
		}
		else if(b->Lchild==NULL&&b->Rchild!=NULL)    //�����pֻ������������ֻ���ؽ�p��������
		{
			if(num==1)
				t->Lchild=b->Rchild;
			else if(num==2)
				t->Rchild=b->Rchild;
		}
		else if(b->Lchild!=NULL&&b->Rchild!=NULL)   //�����p���������������� 
		{
			//���ҽ��p���������ϵ������½��s����˫�׽��par
			s=b->Rchild;
			while(s!=NULL)
			{
				par=s;
				s=s->Lchild;
			}
			b->data=s->data;      //�����s�������滻����ɾ���p��������
			if(b->Rchild->Lchild==NULL)    //�����p���Һ�����������
				par->Rchild=s->Rchild;     //��s���������ӵ�par����������
			else
				par->Lchild=s->Rchild;     //���򣬽�s���������ӵ����par����������
			delete s;      //ɾ�����s
			
		}
		cout<<"ɾ���ɹ�!"<<endl; 
		InOrderTraverse(root);
	}
	else
		cout<<"Ҫɾ���Ľ�㲻���ڣ�"<<endl;
}
//������ 
int main()
{
	int n;
	int r[MaxSize];
	BiSortTree bi;
	cout<<"���������ݸ���:"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"�������"<<i+1<<"����:"<<endl;
		cin>>r[i];
	}
	bi.MakeBST(r,n);
	cout<<endl;
	cout<<"��������Ҫ����������:"<<endl;
	cin>>r[n];
	BiNode *p;
	p=bi.SearchBST(bi.GetRoot(),r[n]);
	if(p)
		cout<<"�ҵ���!"<<endl;
	else
		cout<<"δ�ҵ�!"<<endl; 
	cout<<"������Ҫɾ���Ľ������:"<<endl;
	cin>>r[n];
	bi.DeleteBST(r[n]);
	return 0;
}

