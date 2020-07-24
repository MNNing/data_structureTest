//��ǿ�� 
#include<iostream>
using namespace std;
const int MAX_SIZE=20;
class SeqStack
{
	public:
		SeqStack();    //���캯�� 
		~SeqStack();   //�������� 
		void Push(char x);  //��ջ���� 
		char Pop();       //��ջ���� 
	private:
		char *data;
		int top;
	
};
//�������ܣ����캯�� 
SeqStack::SeqStack()
{
	data=new char[MAX_SIZE];
	top=-1;
} 
//�������ܣ��������� 
SeqStack::~SeqStack()
{
	delete []data;
}
//�������ܣ���ջ���� 
void SeqStack::Push(char x)
{
	if(top>=MAX_SIZE-1)
	{
		cout<<"���磡"<<endl;
		exit(1);
	}
	else
	{
		top++;
		data[top]=x;
	}
}
//�������ܣ���ջ���� 
char SeqStack::Pop()
{
	if(top==-1)
	{
		cout<<"��գ�"<<endl;
		exit(1);
	}
	else
	{
		char s=data[top];
		top--;
		return s;
	}
}
//������ 
int main(void)
{
	SeqStack st;
	char *str;
    str=new char[MAX_SIZE];
	int flag=0;  //��־
	cout<<"��������жϵ��ַ���:"<<endl;
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
		cout<<"�ַ����Գ�!!"<<endl;
	else
		cout<<"�ַ������Գ�!!"<<endl; 
	return 0;
}
