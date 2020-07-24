//基本题1:顺序栈 
#include<iostream>
using namespace std;
const int MAX_SIZE=100;
template <class T>
//顺序栈类的声明 
class SeqStack
{
	public:
		SeqStack();   //构造函数 
		~SeqStack();  //析构函数 
		void Push(T x); //入栈 
		T Pop();      //出栈 
		T GetTop();    //取栈顶元素 
		void ShowStack(); //输出栈中所有元素 
		bool Empty();    //判空布尔函数 
	private:
		T *data;    //数据元素 
		int top;    //栈顶指针 
};
//构造函数 
template<class T>
SeqStack<T>::SeqStack()
{
	data=new T[MAX_SIZE];
	top=-1;
}
//析构函数 
template<class T>
SeqStack<T>::~SeqStack()
{
	delete []data;
}
//函数功能：入栈操作 
template<class T>
void SeqStack<T>::Push(T x)
{
	if(top==MAX_SIZE-1)     //判断是否上溢 
	{
		cout<<"溢出！"<<endl;
		exit(1);
	}
	else
	{
		top++;
		data[top]=x;
		cout<<"第"<<top+1<<"位元素入栈成功"<<endl; 
	}
}
//函数功能：出栈操作 
template<class T>
T SeqStack<T>::Pop()
{
		T x=data[top];
		top--;
		return x;
}
//函数功能：取栈顶元素 
template<class T>
T SeqStack<T>::GetTop()
{
	return data[top];
}
//函数功能:判空 
template<class T>
bool SeqStack<T>::Empty()
{
	if(top==-1)
		return true;
	else
		return false;
}
//函数功能：输出栈中元素 
template<class T>
void SeqStack<T>::ShowStack()
{
	cout<<"栈中所有元素输出:"<<endl;
	for(int p=top;p!=-1;p--)
	{
		cout<<data[p]<<" ";
	}
	cout<<endl;
} 
//主函数 
int main(void)
{
	SeqStack<int> st;  //定义类对象 
	int f=0; 
	int x;
	int y=1;       //循环终止符 
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
					cout<<"栈空!"<<endl;
				break;
			case 3:
				if(!st.Empty())
					cout<<"栈顶元素:"<<st.GetTop()<<endl;
				else
					cout<<"栈空!"<<endl;
				break;
			case 4:
				if(!st.Empty())
					st.ShowStack();
				else
					cout<<"栈空!"<<endl;
				break;
			case 5:
				cout<<"程序结束！"<<endl;
			    y=0;
			    break;
			default:
				cout<<"输入异常!!"<<endl;
		}
		system("pause");
		system("cls");  
	}while(y==1);
	return 0;
}
