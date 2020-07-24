#include<iostream>
using namespace std;
const int MAX=100;
template <class T>
//顺序栈的类声明 
class Stack    
{
public:
	Stack();    //构造函数 
	~Stack();   //析构函数 
	void push(T x);   //入栈 
	T Pop();  //出栈 
	T GetTop();   //获取栈顶元素 
	bool EmptyStack();  //布尔函数  
private:
	T *data;
	int top;
};
template <class T>
//构造函数 
Stack<T>::Stack()
{
	data=new T[MAX];
	top=-1;
}
template <class T>
//析构函数 
Stack<T>::~Stack()
{
	delete data;
}
template <class T>
//入栈 
void Stack<T>::push(T x)
{
	top++;
	data[top]=x;
}
template <class T>
//出栈 
T Stack<T>::Pop()
{
	T x=data[top];
	top--;
	return x;
}
template <class T>
//获取栈顶元素 
T Stack<T>::GetTop()
{
	return data[top];
}
template <class T>
//布尔函数 
bool Stack<T>::EmptyStack()
{
	if(top==-1)
		return true;
	else
		return false;
}
//中缀算术表达式转化为后缀算术表达式 
int trans(char *exp,char postexp[]);
//后缀表达式的计算 
double compvalue(char postexp[]);
//主函数 
int main()
{
	int i=0;
	int count=0;//计数 
	char *exp,*postexp;
	exp=new char[MAX];
	postexp=new char[MAX];
	char n='y';
	do
	{
		cout<<"请输入算术表达式:"<<endl;
		cin>>exp; 
		count=trans(exp,postexp);
		cout<<"中缀表达式:"<<exp<<endl;
		cout<<"后缀表达式:";
		for(i=0;i<count;i++)
		{
			cout<<postexp[i];
		}
		cout<<endl<<"表达式的值:"<<compvalue(postexp)<<endl;
		cout<<"是否继续?请选择y/n:"<<endl;
		cin>>n;
	}while(n=='y'||n=='Y'); 
	return 0;
} 
int trans(char *exp,char postexp[])
{
	Stack<char> Optr;  //定义运算符栈指针 
	int i=0;   //i作为postexp的下标 
	char e;
	while(*exp!='\0')   //exp表达式未扫描完时循环 
	{
		switch(*exp)    
		{
		case '(':   //判定为左括号 
			Optr.push(*exp);
			exp++;   //继续扫描其他字符 
			break;
		case ')':     // 判定为右括号 
			e=Optr.Pop();
			while(e!='(')   
			{
				postexp[i++]=e;
				e=Optr.Pop();
			}
			exp++;
			break;
		case '+':    //判定为加号或减号 
		case '-':
			while(!Optr.EmptyStack())  //栈不为空循环 
			{
				e=Optr.GetTop();
				if(e!='(')
				{
					postexp[i++]=e;
					e=Optr.Pop();
				}
				else     //e是'('时退出循环 
					break;
			}
			Optr.push(*exp);   //将加或减进栈 
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
			while(*exp>='0'&&*exp<='9')  //判定为字符串 
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
					cout<<"除零错误!"<<endl;
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
