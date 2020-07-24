//������1:˳��ջ 
#include<iostream>
using namespace std;
const int MAX_SIZE=100;
template <class T>
//˳��ջ������� 
class SeqStack
{
	public:
		SeqStack();   //���캯�� 
		~SeqStack();  //�������� 
		void Push(T x); //��ջ 
		T Pop();      //��ջ 
		T GetTop();    //ȡջ��Ԫ�� 
		void ShowStack(); //���ջ������Ԫ�� 
		bool Empty();    //�пղ������� 
	private:
		T *data;    //����Ԫ�� 
		int top;    //ջ��ָ�� 
};
//���캯�� 
template<class T>
SeqStack<T>::SeqStack()
{
	data=new T[MAX_SIZE];
	top=-1;
}
//�������� 
template<class T>
SeqStack<T>::~SeqStack()
{
	delete []data;
}
//�������ܣ���ջ���� 
template<class T>
void SeqStack<T>::Push(T x)
{
	if(top==MAX_SIZE-1)     //�ж��Ƿ����� 
	{
		cout<<"�����"<<endl;
		exit(1);
	}
	else
	{
		top++;
		data[top]=x;
		cout<<"��"<<top+1<<"λԪ����ջ�ɹ�"<<endl; 
	}
}
//�������ܣ���ջ���� 
template<class T>
T SeqStack<T>::Pop()
{
		T x=data[top];
		top--;
		return x;
}
//�������ܣ�ȡջ��Ԫ�� 
template<class T>
T SeqStack<T>::GetTop()
{
	return data[top];
}
//��������:�п� 
template<class T>
bool SeqStack<T>::Empty()
{
	if(top==-1)
		return true;
	else
		return false;
}
//�������ܣ����ջ��Ԫ�� 
template<class T>
void SeqStack<T>::ShowStack()
{
	cout<<"ջ������Ԫ�����:"<<endl;
	for(int p=top;p!=-1;p--)
	{
		cout<<data[p]<<" ";
	}
	cout<<endl;
} 
//������ 
int main(void)
{
	SeqStack<int> st;  //��������� 
	int f=0; 
	int x;
	int y=1;       //ѭ����ֹ�� 
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
					cout<<"ջ��!"<<endl;
				break;
			case 3:
				if(!st.Empty())
					cout<<"ջ��Ԫ��:"<<st.GetTop()<<endl;
				else
					cout<<"ջ��!"<<endl;
				break;
			case 4:
				if(!st.Empty())
					st.ShowStack();
				else
					cout<<"ջ��!"<<endl;
				break;
			case 5:
				cout<<"���������"<<endl;
			    y=0;
			    break;
			default:
				cout<<"�����쳣!!"<<endl;
		}
		system("pause");
		system("cls");  
	}while(y==1);
	return 0;
}
