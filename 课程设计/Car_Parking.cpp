// 双层停车场管理 
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//车辆信息结点
typedef struct InforCar
{
	string data;  //车牌号
	int time;  //停车时间
	double fee;  //费用
}ICar;
//模拟停车场类声明
class Car_P
{
	public:
		Car_P();        //构造函数
		~Car_P();       //析构函数
		void ParkCar(Car_P &pCar,int &n);  //停车操作
		void ChargeOut(Car_P &pCar,int &n);  //收费管理
		void FirstPark();   //停车场初始化
		void ShowAll();     //输出停车场中全部车辆的信息
		int SearchFor(int &a,int &b);   //查询是否有空车位
		void AddTime();   //停车时间累加
		void OutFile();     //文件写入
		void InFile(int n);   //文件读出
	private:
		ICar **space;   //车位
		double sum;
};
//构造函数
Car_P::Car_P()
{
	space=new ICar*[2];
	for(int i=0;i<2;i++)
	{
		space[i]=new ICar[6];
		for(int j=0;j<6;j++)
		{
			space[i][j].data="0";   //车牌号初始化为零
			space[i][j].time=0;     //停车时间初始化为零
		}
	}
	sum=0;
}
//析构函数
Car_P::~Car_P()
{
	for(int i=0;i<2;i++)
		delete []space[i];
	delete []space;
}
//停车场初始化
void Car_P::FirstPark()
{
	ofstream out;   //输出流对象
	out.open("car.dat",ios::trunc);   //打开文件
	int t=20;
	string a[4]={"001","002","003","004"};  //初始情况的四辆车车牌号
	for(int i=0;i<4;i++)
	{
		space[0][i].data=a[i];
		space[0][i].time=t;
		out<<"第"<<1<<"层、第"<<i+1<<"辆车的车牌号:"<<space[0][i].data<<" "<<"停车时间:"<<space[0][i].time<<"分钟"<<endl;   //将数据写入到输出文件中
		t=t-5;
	}
	out.close();
}
//查看停车场车辆情况
void Car_P::ShowAll()
{
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data!="0")  //若车牌号不为零
			{
				cout<<"第"<<i+1<<"层、第"<<j+1<<"辆车的车牌号:"<<space[i][j].data<<"  ";
				cout<<"停车时间:"<<space[i][j].time<<"分钟"<<endl<<endl;
			}
			else
				cout<<"第"<<i+1<<"层、第"<<j+1<<"个车位为空"<<endl<<endl;
		}
	}
}
//增加停车时间
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
//查询空车位
int Car_P::SearchFor(int &a,int &b)
{
	int flag=0;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data=="0")    //从头开始找到的第一个空车位
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
//停车操作
void Car_P::ParkCar(Car_P &pCar,int &n)
{
	string id;
	int a,b,c;
	int flag=0;
	cout<<"请输入车牌号"<<endl;
	cin>>id;
	while(id=="0")
	{
		cout<<"输入非法，请重新输入!"<<endl;
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
		c=pCar.SearchFor(a,b);  //查询空车位
		if(c==0)
			cout<<"没有多余车位了!"<<endl;
		else
		{
			pCar.AddTime();  //时间累加
			cout<<"请将车停到第"<<a+1<<"层，第"<<b+1<<"号车位"<<endl;
			space[a][b].data=id;
			space[a][b].time=5;
			n++;
			pCar.OutFile();  //写入文件
		}
	}
	else
		cout<<"该车已经在停车场中了!"<<endl;
}
//取车收费管理
void Car_P::ChargeOut(Car_P &pCar,int &n)
{
	int flag=0;
	string s;
	cout<<"请输入车牌号:"<<endl;
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
				cout<<"停车收费:"<<space[i][j].fee<<"元"<<endl;
				sum+=space[i][j].fee;
				cout<<"是否输出当前停车场总收入:y/n"<<endl;
				char ch='n';
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					cout<<"停车场总收入:"<<sum<<"元"<<endl;
				}
				break;
			}
		}
		if(flag==0)
			cout<<"未找到目标车辆！"<<endl;
}
//文件写入
void Car_P::OutFile()
{
	ofstream out;   //输出流对象
	out.open("car.dat",ios::trunc);  //打开文件
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(space[i][j].data!="0")
			{
				out<<"第"<<i+1<<"层、第"<<j+1<<"辆车的车牌号:"<<space[i][j].data<<"停车时间:"<<space[i][j].time<<"分钟"<<endl;  //将数据写入到输出文件中
			}
		}
	}
	out.close();   //关闭文件
}
//文件输出
void Car_P::InFile(int n)
{
	ifstream in("car.dat"); //输入流对象，并打开文件
	char ch[100];
	for(int i=0;i<n;i++)
	{
		in.getline(ch, 100, '\n'); //从外设读取一行数据
		cout<<ch<<endl<<endl;
	}
	in.close(); //关闭文件
}
//主函数
int main()
{
	Car_P pCar;
	int x,n=4;
	int flag=1;
	pCar.FirstPark();    //初始化
	do
	{
		cout << "*******************************************" << endl;
		cout << "******      停 车 场 管 理 系 统     ******" << endl;
		cout << "******       1.汽车停车登记          ******" << endl;
		cout << "******       2.汽车离开登记          ******" << endl;
		cout << "******       3.车位信息查看          ******" << endl;
		cout << "******       4.查看文件信息          ******" << endl;
		cout << "******       5.安全退出系统          ******" << endl;
		cout << "请输入您的选择：";
		cin>>x;
		switch(x)
		{
		case 1:
			pCar.ParkCar(pCar,n);    //停车操作
			break;
		case 2:
			pCar.ChargeOut(pCar,n);   //收费管理
			break;
		case 3:
			pCar.ShowAll();   //输出停车场中所有车辆信息
			break;
		case 4:
			pCar.InFile(n);   //文件读出
			break;
		case 5:
			cout<<"程序运行结束!"<<endl;
			flag=0;
			break;
		default:
			cout<<"输入非法！"<<endl;
		}
		system("pause");
		system("cls");
	}while(flag==1);
	return 0;
}
