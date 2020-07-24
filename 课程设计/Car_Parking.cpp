// ˫��ͣ�������� 
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//������Ϣ���
typedef struct InforCar
{
	string data;  //���ƺ�
	int time;  //ͣ��ʱ��
	double fee;  //����
}ICar;
//ģ��ͣ����������
class Car_P
{
	public:
		Car_P();        //���캯��
		~Car_P();       //��������
		void ParkCar(Car_P &pCar,int &n);  //ͣ������
		void ChargeOut(Car_P &pCar,int &n);  //�շѹ���
		void FirstPark();   //ͣ������ʼ��
		void ShowAll();     //���ͣ������ȫ����������Ϣ
		int SearchFor(int &a,int &b);   //��ѯ�Ƿ��пճ�λ
		void AddTime();   //ͣ��ʱ���ۼ�
		void OutFile();     //�ļ�д��
		void InFile(int n);   //�ļ�����
	private:
		ICar **space;   //��λ
		double sum;
};
//���캯��
Car_P::Car_P()
{
	space=new ICar*[2];
	for(int i=0;i<2;i++)
	{
		space[i]=new ICar[6];
		for(int j=0;j<6;j++)
		{
			space[i][j].data="0";   //���ƺų�ʼ��Ϊ��
			space[i][j].time=0;     //ͣ��ʱ���ʼ��Ϊ��
		}
	}
	sum=0;
}
//��������
Car_P::~Car_P()
{
	for(int i=0;i<2;i++)
		delete []space[i];
	delete []space;
}
//ͣ������ʼ��
void Car_P::FirstPark()
{
	ofstream out;   //���������
	out.open("car.dat",ios::trunc);   //���ļ�
	int t=20;
	string a[4]={"001","002","003","004"};  //��ʼ��������������ƺ�
	for(int i=0;i<4;i++)
	{
		space[0][i].data=a[i];
		space[0][i].time=t;
		out<<"��"<<1<<"�㡢��"<<i+1<<"�����ĳ��ƺ�:"<<space[0][i].data<<" "<<"ͣ��ʱ��:"<<space[0][i].time<<"����"<<endl;   //������д�뵽����ļ���
		t=t-5;
	}
	out.close();
}
//�鿴ͣ�����������
void Car_P::ShowAll()
{
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data!="0")  //�����ƺŲ�Ϊ��
			{
				cout<<"��"<<i+1<<"�㡢��"<<j+1<<"�����ĳ��ƺ�:"<<space[i][j].data<<"  ";
				cout<<"ͣ��ʱ��:"<<space[i][j].time<<"����"<<endl<<endl;
			}
			else
				cout<<"��"<<i+1<<"�㡢��"<<j+1<<"����λΪ��"<<endl<<endl;
		}
	}
}
//����ͣ��ʱ��
void Car_P::AddTime()
{
	for(int i=0;i<2;i++)
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data!="0")
			{
				space[i][j].time+=5;
			}
		}
}
//��ѯ�ճ�λ
int Car_P::SearchFor(int &a,int &b)
{
	int flag=0;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data=="0")    //��ͷ��ʼ�ҵ��ĵ�һ���ճ�λ
			{
				a=i;
				b=j;
				flag=1;
				return 1;
			}
		}
	}
	if(flag==0)
		return 0;
}
//ͣ������
void Car_P::ParkCar(Car_P &pCar,int &n)
{
	string id;
	int a,b,c;
	int flag=0;
	cout<<"�����복�ƺ�"<<endl;
	cin>>id;
	while(id=="0")
	{
		cout<<"����Ƿ�������������!"<<endl;
		cin>>id;
	}
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data==id)
			{
				flag=1;
			}
		}
	}
	if(flag==0)
	{
		c=pCar.SearchFor(a,b);  //��ѯ�ճ�λ
		if(c==0)
			cout<<"û�ж��೵λ��!"<<endl;
		else
		{
			pCar.AddTime();  //ʱ���ۼ�
			cout<<"�뽫��ͣ����"<<a+1<<"�㣬��"<<b+1<<"�ų�λ"<<endl;
			space[a][b].data=id;
			space[a][b].time=5;
			n++;
			pCar.OutFile();  //д���ļ�
		}
	}
	else
		cout<<"�ó��Ѿ���ͣ��������!"<<endl;
}
//ȡ���շѹ���
void Car_P::ChargeOut(Car_P &pCar,int &n)
{
	int flag=0;
	string s;
	cout<<"�����복�ƺ�:"<<endl;
	cin>>s;
	for(int i=0;i<2;i++)
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data==s)
			{
				space[i][j].fee=space[i][j].time*0.2;
				space[i][j].data="0";
				space[i][j].time=0;
				flag=1;
				n--;
				pCar.OutFile();
				cout<<"ͣ���շ�:"<<space[i][j].fee<<"Ԫ"<<endl;
				sum+=space[i][j].fee;
				cout<<"�Ƿ������ǰͣ����������:y/n"<<endl;
				char ch='n';
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					cout<<"ͣ����������:"<<sum<<"Ԫ"<<endl;
				}
				break;
			}
		}
		if(flag==0)
			cout<<"δ�ҵ�Ŀ�공����"<<endl;
}
//�ļ�д��
void Car_P::OutFile()
{
	ofstream out;   //���������
	out.open("car.dat",ios::trunc);  //���ļ�
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data!="0")
			{
				out<<"��"<<i+1<<"�㡢��"<<j+1<<"�����ĳ��ƺ�:"<<space[i][j].data<<"ͣ��ʱ��:"<<space[i][j].time<<"����"<<endl;  //������д�뵽����ļ���
			}
		}
	}
	out.close();   //�ر��ļ�
}
//�ļ����
void Car_P::InFile(int n)
{
	ifstream in("car.dat"); //���������󣬲����ļ�
	char ch[100];
	for(int i=0;i<n;i++)
	{
		in.getline(ch, 100, '\n'); //�������ȡһ������
		cout<<ch<<endl<<endl;
	}
	in.close(); //�ر��ļ�
}
//������
int main()
{
	Car_P pCar;
	int x,n=4;
	int flag=1;
	pCar.FirstPark();    //��ʼ��
	do
	{
		cout << "*******************************************" << endl;
		cout << "******      ͣ �� �� �� �� ϵ ͳ     ******" << endl;
		cout << "******       1.����ͣ���Ǽ�          ******" << endl;
		cout << "******       2.�����뿪�Ǽ�          ******" << endl;
		cout << "******       3.��λ��Ϣ�鿴          ******" << endl;
		cout << "******       4.�鿴�ļ���Ϣ          ******" << endl;
		cout << "******       5.��ȫ�˳�ϵͳ          ******" << endl;
		cout << "����������ѡ��";
		cin>>x;
		switch(x)
		{
		case 1:
			pCar.ParkCar(pCar,n);    //ͣ������
			break;
		case 2:
			pCar.ChargeOut(pCar,n);   //�շѹ���
			break;
		case 3:
			pCar.ShowAll();   //���ͣ���������г�����Ϣ
			break;
		case 4:
			pCar.InFile(n);   //�ļ�����
			break;
		case 5:
			cout<<"�������н���!"<<endl;
			flag=0;
			break;
		default:
			cout<<"����Ƿ���"<<endl;
		}
		system("pause");
		system("cls");
	}while(flag==1);
	return 0;
}
