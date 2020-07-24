//基本题1：链栈 
#include<iostream>
using namespace std;
typedef struct LNode   //链栈数据结点类型 
{
    int data;             //数据域
    struct LNode *next;       //指针域
}LinkStNode;
//链栈类的声明 
class LinkStack
{    
   public:
        LinkStack( );   //构造函数 
        ~LinkStack( );   //析构函数         
        void Push(int x);  //入栈 
        int Pop( );     //出栈 
        int GetTop( );   //获取栈顶元素 
        void ShowStack();  //输出所有栈中元素 
        bool Empty();    //布尔判空 
   private:
        LinkStNode *top;   //栈顶指针 
};
//构造函数 
LinkStack::LinkStack()
{
	top=new LinkStNode;
	top=NULL;
}
//析构函数 
LinkStack::~LinkStack()
{
	delete top;
}
//入栈 
void LinkStack::Push(int x)
{
	LinkStNode *s;
	s=new LinkStNode;
	s->data=x;
	s->next=top;
	top=s;
}
//出栈 
int LinkStack::Pop()
{
	int x=top->data; 
	LinkStNode *p=top; 
	top=top->next;   
	delete p;
	return x;
	
}
//获取栈顶元素 
int LinkStack::GetTop()
{
	return top->data;
}
//布尔函数判空 
bool LinkStack::Empty()
{
	if(top==NULL)
		return true;
	else
		return false;
}
//输出所有栈中元素 
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
//主函数 
int main(void)
{
	LinkStack st;
	int f=0; 
	int x,y=1;
	do
	{
		cout<<"-----------"<<endl;
		cout<<"1.  入栈   "<<endl;
		cout<<"2.  出栈   "<<endl; 
		cout<<"3.  取栈顶 "<<endl; 
		cout<<"4.  输出栈 "<<endl;
		cout<<"5.  结束   "<<endl;
		cout<<"-----------"<<endl; 
		cout<<"请选择功能:"<<endl;
		cin>>f;
		switch(f)
		{
			case 1:
				cout<<"请输入入栈元素:";
				cin>>x;
				st.Push(x);
				break;
			case 2:
				if(!st.Empty())
			    	cout<<"出栈元素:"<<st.Pop()<<endl;
			    else
			    	cout<<"栈空!!"<<endl;
				break;
			case 3:
				if(!st.Empty())
			    	cout<<"栈顶元素:"<<st.GetTop()<<endl;
			    else
			    	cout<<"栈空!!"<<endl;
				break;
			case 4:
				if(!st.Empty())
					st.ShowStack();
				else
			    	cout<<"栈空!!"<<endl;
				break;
			case 5:
				cout<<"程序结束！"<<endl;
			    y=0;
			    break;
			default:
				y=0;
				cout<<"输入异常!!"<<endl;
		}
		system("pause");
		system("cls");  
	}while(y==1);
	return 0;
}
   

