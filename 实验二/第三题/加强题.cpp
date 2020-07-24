//加强题 
#include<iostream>
using namespace std;
const int MAX_SIZE=20;
class SeqStack
{
	public:
		SeqStack();    //构造函数 
		~SeqStack();   //析构函数 
		void Push(char x);  //入栈操作 
		char Pop();       //出栈操作 
	private:
		char *data;
		int top;
	
};
//函数功能：构造函数 
SeqStack::SeqStack()
{
	data=new char[MAX_SIZE];
	top=-1;
} 
//函数功能：析构函数 
SeqStack::~SeqStack()
{
	delete []data;
}
//函数功能：入栈操作 
void SeqStack::Push(char x)
{
	if(top>=MAX_SIZE-1)
	{
		cout<<"上溢！"<<endl;
		exit(1);
	}
	else
	{
		top++;
		data[top]=x;
	}
}
//函数功能：出栈操作 
char SeqStack::Pop()
{
	if(top==-1)
	{
		cout<<"表空！"<<endl;
		exit(1);
	}
	else
	{
		char s=data[top];
		top--;
		return s;
	}
}
//主函数 
int main(void)
{
	SeqStack st;
	char *str;
    str=new char[MAX_SIZE];
	int flag=0;  //标志
	cout<<"请输入待判断的字符串:"<<endl;
    cin>>str;
	char *p=str;
	while(*str!='\0')
	{
		st.Push(*str);
		str++;
	}
	while(*p!='\0')
	{
		if(*p!=st.Pop())
			flag=1;
		p++;
	}
	if(flag==0)
		cout<<"字符串对称!!"<<endl;
	else
		cout<<"字符串不对称!!"<<endl; 
	return 0;
}
