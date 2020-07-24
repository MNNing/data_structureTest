//������1����ջ 
#include<iostream>
using namespace std;
typedef struct LNode   //��ջ���ݽ������ 
{
    int data;             //������
    struct LNode *next;       //ָ����
}LinkStNode;
//��ջ������� 
class LinkStack
{    
   public:
        LinkStack( );   //���캯�� 
        ~LinkStack( );   //��������         
        void Push(int x);  //��ջ 
        int Pop( );     //��ջ 
        int GetTop( );   //��ȡջ��Ԫ�� 
        void ShowStack();  //�������ջ��Ԫ�� 
        bool Empty();    //�����п� 
   private:
        LinkStNode *top;   //ջ��ָ�� 
};
//���캯�� 
LinkStack::LinkStack()
{
	top=new LinkStNode;
	top=NULL;
}
//�������� 
LinkStack::~LinkStack()
{
	delete top;
}
//��ջ 
void LinkStack::Push(int x)
{
	LinkStNode *s;
	s=new LinkStNode;
	s->data=x;
	s->next=top;
	top=s;
}
//��ջ 
int LinkStack::Pop()
{
	int x=top->data; 
	LinkStNode *p=top; 
	top=top->next;   
	delete p;
	return x;
	
}
//��ȡջ��Ԫ�� 
int LinkStack::GetTop()
{
	return top->data;
}
//���������п� 
bool LinkStack::Empty()
{
	if(top==NULL)
		return true;
	else
		return false;
}
//�������ջ��Ԫ�� 
void LinkStack::ShowStack()
{
	LinkStNode *p=top;
	while(p->next!=NULL)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<p->data<<endl;
}
//������ 
int main(void)
{
	LinkStack st;
	int f=0; 
	int x,y=1;
	do
	{
		cout<<"-----------"<<endl;
		cout<<"1.  ��ջ   "<<endl;
		cout<<"2.  ��ջ   "<<endl; 
		cout<<"3.  ȡջ�� "<<endl; 
		cout<<"4.  ���ջ "<<endl;
		cout<<"5.  ����   "<<endl;
		cout<<"-----------"<<endl; 
		cout<<"��ѡ����:"<<endl;
		cin>>f;
		switch(f)
		{
			case 1:
				cout<<"��������ջԪ��:";
				cin>>x;
				st.Push(x);
				break;
			case 2:
				if(!st.Empty())
			    	cout<<"��ջԪ��:"<<st.Pop()<<endl;
			    else
			    	cout<<"ջ��!!"<<endl;
				break;
			case 3:
				if(!st.Empty())
			    	cout<<"ջ��Ԫ��:"<<st.GetTop()<<endl;
			    else
			    	cout<<"ջ��!!"<<endl;
				break;
			case 4:
				if(!st.Empty())
					st.ShowStack();
				else
			    	cout<<"ջ��!!"<<endl;
				break;
			case 5:
				cout<<"���������"<<endl;
			    y=0;
			    break;
			default:
				y=0;
				cout<<"�����쳣!!"<<endl;
		}
		system("pause");
		system("cls");  
	}while(y==1);
	return 0;
}
   

