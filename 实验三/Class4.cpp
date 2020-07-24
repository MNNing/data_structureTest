//������������
#include<iostream>
using namespace std;
const int MAXSIZE=100;
//������������� 
typedef struct node
{
	char data;//���������
	int ltag,rtag;//���ӵ��������
	struct node* lchild;//���ӻ�����ָ��
	struct node* rchild;//�Һ��ӻ�����ָ��
}TBTNode;//������������Ͷ���
TBTNode *pre;		   		//ȫ�ֱ���
class InThrBiTree
{    
    public:
        InThrBiTree();    //���캯�� 
        ~ InThrBiTree( );   //�������� 
		void CreatThread();     //����������������
 		void  Thread(TBTNode *&p); //�Զ�������������������
   		void ThInOrder();   //�����������������
		void CreatBtTree(char *str);  //���������� 
    private:
        TBTNode *root,*head;   //rootΪ����㣬headΪͷ��� 
};
//���캯�� 
InThrBiTree::InThrBiTree()
{
	root=new TBTNode;
	root=NULL;
}
//�������� 
InThrBiTree::~ InThrBiTree()
{
	delete root;
}
//����������������
void InThrBiTree::CreatThread()     
{
    head=new TBTNode;        //����ͷ���
    head->ltag=0;             //ͷ��������ӣ������ǿգ���������Ϊ����
    head->rtag=1;               //ͷ�����Һ���ָ��Ϊ������
    head->rchild=root;          //ͷ�����Һ���ָ��ָ������
    pre=new TBTNode;
    if (root==NULL)  head->lchild=head;   //����Ϊ�գ�����ָ��Ҳָ���Լ�
    else
    {
		head->lchild=root;      //ͷ��������ָ���
		pre=head;            //pre��*p��ǰ����㣬���������ã�pre��ֵָ��ͷ���
		Thread(root);       //����Thread()�㷨������bΪ���Ķ�������������������
		pre->rchild=head;       //Thread()�㷨������preΪ���ҽ�㣬pre��������ָ��ͷ���
		pre->rtag=1;
		head->rchild=pre;    	   //ͷ����������ָ��pre
     }
} 
//�Զ�������������������
void  InThrBiTree::Thread(TBTNode *&p)    		
{   if (p!=NULL)	
    {  
	     Thread(p->lchild);           		//������������
	     if (p->lchild==NULL)          	//���Ӳ����ڣ�����ǰ�����������
	     {   p->lchild=pre; p->ltag=1;  }	//������ǰ����ǰ������
	     else  p->ltag=0;                                 //p������������������
	     if  (pre->rchild==NULL)	     	//��pre�ĺ�̽��������
	     {     pre->rchild=p;pre->rtag=1;}	//����ǰ�����ĺ������
	     else  pre->rtag=0;
	     pre=p;
	     Thread(p->rchild);  		//�ݹ����������������
    }
} 
//���������������������ÿ������Ԫ��ֱ�����
void InThrBiTree::ThInOrder()
{      //ͷ��������lchildָ������
       
      TBTNode *p=head->lchild;	 //pָ������
       while (p!=head)            //�������������ʱ��p==head
       {     
            while (p->ltag==0)   p=p->lchild;     //�����������ҿ�ʼ���
			cout<<p->data;		       //���ʿ�ʼ���
			while (p->rtag==1 && p->rchild!=head)
			{   p=p->rchild;                  //�����������ʺ�̽��   
	    		cout<<p->data;
			}
			p=p->rchild;                 //ת��p�������� 
       }
} 
//���������� 
void InThrBiTree::CreatBtTree(char *str)
{
	TBTNode *st[MAXSIZE],*p;  //St������Ϊ˳��ջ
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
				p=new TBTNode;
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
//������ 
int main()
{
	InThrBiTree ib;
	char *str;
	str=new char;
	cout<<"��������������ű�ʾ��:"<<endl;
	cin>>str;
	ib.CreatBtTree(str);
	ib.CreatThread();
	ib.ThInOrder();
	return 0;
}
