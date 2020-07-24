#include<iostream>
using namespace std;
const int MAX=100;
template <class T>
//˳��ջ�������� 
class Stack    
{
public:
	Stack();    //���캯�� 
	~Stack();   //�������� 
	void push(T x);   //��ջ 
	T Pop();  //��ջ 
	T GetTop();   //��ȡջ��Ԫ�� 
	bool EmptyStack();  //��������  
private:
	T *data;
	int top;
};
template <class T>
//���캯�� 
Stack<T>::Stack()
{
	data=new T[MAX];
	top=-1;
}
template <class T>
//�������� 
Stack<T>::~Stack()
{
	delete data;
}
template <class T>
//��ջ 
void Stack<T>::push(T x)
{
	top++;
	data[top]=x;
}
template <class T>
//��ջ 
T Stack<T>::Pop()
{
	T x=data[top];
	top--;
	return x;
}
template <class T>
//��ȡջ��Ԫ�� 
T Stack<T>::GetTop()
{
	return data[top];
}
template <class T>
//�������� 
bool Stack<T>::EmptyStack()
{
	if(top==-1)
		return true;
	else
		return false;
}
//��׺�������ʽת��Ϊ��׺�������ʽ 
int trans(char *exp,char postexp[]);
//��׺���ʽ�ļ��� 
double compvalue(char postexp[]);
//������ 
int main()
{
	int i=0;
	int count=0;//���� 
	char *exp,*postexp;
	exp=new char[MAX];
	postexp=new char[MAX];
	char n='y';
	do
	{
		cout<<"�������������ʽ:"<<endl;
		cin>>exp; 
		count=trans(exp,postexp);
		cout<<"��׺���ʽ:"<<exp<<endl;
		cout<<"��׺���ʽ:";
		for(i=0;i<count;i++)
		{
			cout<<postexp[i];
		}
		cout<<endl<<"���ʽ��ֵ:"<<compvalue(postexp)<<endl;
		cout<<"�Ƿ����?��ѡ��y/n:"<<endl;
		cin>>n;
	}while(n=='y'||n=='Y'); 
	return 0;
} 
int trans(char *exp,char postexp[])
{
	Stack<char> Optr;  //���������ջָ�� 
	int i=0;   //i��Ϊpostexp���±� 
	char e;
	while(*exp!='\0')   //exp���ʽδɨ����ʱѭ�� 
	{
		switch(*exp)    
		{
		case '(':   //�ж�Ϊ������ 
			Optr.push(*exp);
			exp++;   //����ɨ�������ַ� 
			break;
		case ')':     // �ж�Ϊ������ 
			e=Optr.Pop();
			while(e!='(')   
			{
				postexp[i++]=e;
				e=Optr.Pop();
			}
			exp++;
			break;
		case '+':    //�ж�Ϊ�ӺŻ���� 
		case '-':
			while(!Optr.EmptyStack())  //ջ��Ϊ��ѭ�� 
			{
				e=Optr.GetTop();
				if(e!='(')
				{
					postexp[i++]=e;
					e=Optr.Pop();
				}
				else     //e��'('ʱ�˳�ѭ�� 
					break;
			}
			Optr.push(*exp);   //���ӻ����ջ 
			exp++;
			break;
		case '*':
		case '/':
			while(!Optr.EmptyStack())
			{
				e=Optr.GetTop();
				if(e=='*'||e=='/')
				{
					postexp[i++]=e;
					e=Optr.Pop();
				}
				else
					break;
			}
			Optr.push(*exp);
			exp++;
			break;
		default:
			while(*exp>='0'&&*exp<='9')  //�ж�Ϊ�ַ��� 
			{
				postexp[i++]=*exp;
				exp++;
			}
			postexp[i++]='#';
		}	
    }
    while(!Optr.EmptyStack())
	{
		e=Optr.Pop();
		postexp[i++]=e;
	}
	postexp[i]='\0';
	return i;
}
double compvalue(char postexp[])
{
	double a,b,c,d,e;
	Stack<double> opnd;
	while(*postexp!='\0')
	{
		switch(*postexp)
		{
			case '+':
				a=opnd.Pop();
				b=opnd.Pop();
				c=b+a;
				opnd.push(c);
				break;
			case '-':
				a=opnd.Pop();
				b=opnd.Pop();
				c=b-a;
				opnd.push(c);
				break;
			case '*':
				a=opnd.Pop();
				b=opnd.Pop();
				c=b*a;
				opnd.push(c);
				break;
			case '/':
				a=opnd.Pop();
				b=opnd.Pop();
				if(a!=0)
				{
					c=b/a;
					opnd.push(c);
					break; 
				}
				else
				{
					cout<<"�������!"<<endl;
					exit(1);
				}
				break;
			default:
				d=0;
				while(*postexp>='0'&&*postexp<='9')
				{
					d=10*d+*postexp-'0';
					postexp++;
				}
				opnd.push(d);
				break;
		}
		postexp++;
	}
	e=opnd.GetTop();
	return e;
}
