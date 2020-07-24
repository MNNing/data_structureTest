//交通系统模拟 
#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
using namespace std;
//文件操作,在D盘建立三个文本文件 
const char CityFile[] ="D:\\city.txt"; 
const char TrainFile[] ="D:\\train.txt"; 
const char FlightFile[] ="D:\\flight.txt"; 
const int  MAX_VERTEX_NUM=34;  //图中顶点数目最大值
const int MaxSize=20;   
const int maxValue=9999;
typedef struct TrafficNodeData    //交通工具信息 
{
	char name[MaxSize];      //班次
	int StartTime;    //出发时间
	int StopTime;     //到达时间
	int Duration;    //时间段 
	int EndCity;              //边的另一顶点，即下一个城市编号
	int Cost;          //票价
	struct TrafficNodeData *link;  //下一条边链指针 
}TrafficNode;
typedef struct VNodeData          //路线信息
{
	string cityname ;       //城市名称
	int TrainNum,FlightNum;    //列车、航班数量           
	TrafficNode *Tadj;      //列车线 
	TrafficNode *Fadj;      //航班线 
}VNode; 
//交通系统类的定义 
class TrafficGraph
{
	public:
		TrafficGraph();    //构造函数 
		~TrafficGraph();   //析构函数 
		int InitialInterface();   //开始及登录界面 
		void ShowMenu(int n);    //功能选择界面 
		bool ShowFpath(string name);//显示航班线
		bool ShowTpath(string name);//显示列车线 
		bool DelFlight();//删除航班线
		bool InsertFlight(int i,int j,int TFcost,int time1,int time2,char *TFname);//添加航班线
		bool DelTrain();//删除火车线
		bool InsertTrain(int i,int j,int TFcost,int time1,int time2,char *TFname);//添加火车线
		bool DelCity(string Name);//删除城市
		void InsertCity(string Name);//添加城市
		int FindCity (string name);//查找城市并返回城市序号
		//void InitData();  
		void FastestRoute();     //耗时最短路径 
		void CheapestRoute();    //花钱最少路径 
		int getCost(int v,int u,int choose);    //返回两个城市之间的票价 
		int getDuration(int v1,int v2,int choose);   //返回行驶的时间间隔 
		int getTimes(int v1,int u,int k,int choose);   //返回等候的时间 
		void getInfor(int v1,int v2,int choose);     //获取列车或航班信息 
		int SaveSysInfo();     //将信息存入文件 
		int InitSysData () ;   //用文件信息初始化 
	private:
		VNode *AddList; //系统信息  
		int Cnum;      // 城市个数 
};
TrafficGraph::TrafficGraph()     //构造函数 
{
	AddList=new VNode[MAX_VERTEX_NUM];
	Cnum=0;
	for(int i=0;i<MAX_VERTEX_NUM;i++)
	{
		AddList[i].Tadj=NULL;    //列车线指针置空 
		AddList[i].Fadj=NULL;    //航班线指针置空
	}	
} 
TrafficGraph::~TrafficGraph()      //析构函数 
{
	for(int i=0;i<Cnum;i++)
	{
		TrafficNode *p=AddList[i].Tadj;
		while(p!=NULL)
		{
			AddList[i].Tadj=p->link;
			delete p;p=AddList[i].Tadj;
		}
		TrafficNode *q=AddList[i].Fadj;
		while(q!=NULL)
		{
			AddList[i].Fadj=q->link;
			delete q;q=AddList[i].Fadj;
		}
	}
	delete []AddList;
}
int TrafficGraph::InitialInterface()      //初始化及登录界面 
{
	string num1,num2;
	char a[10],c[10];
	char b[10];
	int flag;                   //循环终止标记 
	char ab='n';                //退出、确认字符 
	ofstream out;               //文件写入 
	ifstream in;                //文件读出 
	cout<<"┌----------------------------------┐"<<endl;
	cout<<"│                                  │"<<endl;
	cout<<"│  欢迎使用全国交通咨询模拟系统1.0 │"<<endl;
	cout<<"│                                  │"<<endl;
	cout<<"└----------------------------------┘"<<endl;
	string Magname="17080207";     //管理员账号，唯一 
	char password[]="123456";      //管理员密码 
	cout<<"** 1.用户注册   **"<<endl; 
	cout<<"** 2.用户登录   **"<<endl;
	cout<<"** 3.管理员登录 **"<<endl;
	cout<<"** 4.退出系统   **"<<endl; 
	cout<<"请选择：";
	int x; 
	cin>>x;
	system("cls");
	switch(x)
	{
		case 1:
			cout<<"请输入用户名(不超过8位)："<<endl;
			cin>>num1;
			cout<<"请设置密码(不超过10位)："<<endl;
			for(int j=0;j<10;j++)        //密码暗码 
			{
				a[j]=getch();
				cout<<"*";   //设置暗码 
				if(a[j]=='\r')//按回车 
				{
					a[j]='\0';//密码输入结束 
					break;
				}
			}
			cout<<endl<<"请再次输入你的密码："<<endl;
			for(int j=0;j<10;j++)
			{
				c[j]=getch();
				cout<<"*";
				if(c[j]=='\r')
				{
					c[j]='\0';
					break;
				}
			}
			while(strcmp(a,c)!=0) 
			{
				cout<<endl<<"两次密码输入不一致，请重新输入："<<endl;
				for(int j=0;j<10;j++)
				{
					c[j]=getch();
					cout<<"*";
					if(c[j]=='\r')
					{
						c[j]='\0';
						break;
					}
				}
			}
			out.open("username.txt",ios::app);     //用户名存入文件 
			out<<num1<<endl;
			out.close();
			out.open("password.txt",ios::app);     //对应的密码存入文件 
			out<<c<<endl;
			out.close();
			cout<<endl<<"注册完毕，直接登录!"<<endl;
			x=2;        //返回2，输出用户功能表 
			system("pause");
			system("cls");
			break;
		case 2:
			char ch[100];
			int i,f;
			do
			{
				i=1;f=0; //i标记是第几个用户，f为查找标记，找到记为0 
				cout<<"请输入用户名："<<endl;
				cin>>num2;
				in.open("username.txt");
				if(!in)
				{
					cout<<"没有用户注册!"<<endl;
					exit(1);
				}
				do
				{
					in.getline(ch,100,'\n');    //在文件中查找该用户是否注册了 
					if(ch==num2)
					{
						f=1;      //是注册用户，f=1 
						break;
					}
					i++;     //记录是第几个用户 
				}while(ch!=num2&&!in.eof());   
				if(f==0)    //未注册 
				{
					cout<<"该用户未注册!"<<endl;
					flag=1;  
					in.close();
				}
				else
				{
					cout<<"请输入密码:"<<endl;
					for(int j=0;j<10;j++)
					{
						b[j]=getch();
						cout<<"*";
						if(b[j]=='\r')
						{
							b[j]='\0';
							break;
						}
					}
					in.close();
					in.open("password.txt");
					for(int k=0;k<i;k++)    //看密码是否正确 
					{
						in.getline(ch,100,'\n');
					}
					in.close();
					if(strcmp(ch,b)==0)
						flag=0;    //查找成功，循环标志置0 
					else
					{
						cout<<endl<<"用户名或密码输入错误！"<<endl;
						flag=1;    //失败，循环标志置1 
						system("pause");//暂停界面 
						system("cls");  //清屏 
					}
				} 
				
			}while(flag==1);
			cout<<endl<<"登录成功!"<<endl;
			system("pause");
			system("cls");
			break;
		case 3:
			do
			{
				cout<<"请输入用户名："<<endl;
				cin>>num2;
				cout<<"请输入密码:"<<endl;
				for(int j=0;j<10;j++)
				{
					b[j]=getch();
					cout<<"*";
					if(b[j]=='\r')
					{
						b[j]='\0';
						break;
					}
				}
				cout<<endl;
				if(num2==Magname&&strcmp(password,b)==0)
					flag=0;       //查找成功，循环标志置0 
				else
				{
					cout<<"用户名或密码输入错误！"<<endl;
					flag=1;
					system("pause");
					system("cls");
				}
			}while(flag==1);       //失败，循环标志置1
			cout<<endl<<"登录成功!"<<endl;
			system("pause");
			system("cls");
			break;
		case 4:
			cout<<"确认退出？(y/n)"<<endl;
			cin>>ab;
			if(ab=='y'||ab=='Y')
				exit(1);    //退出程序 
			else
			{
				system("cls");
				x=InitialInterface();//返回主界面 
			}
			break;
		default:
			cout<<"输入非法！请重新选择："<<endl;
			system("pause") ;
			system("cls");
			x=InitialInterface();
			break;
	}
	return x;
}
//输出功能表 
void TrafficGraph::ShowMenu(int n)
{
	switch(n)
	{
		case 2:         //用户登录 
			cout<<"** 1.查询最快路线     **"<<endl;
			cout<<"** 2.查询费用最省路线 **"<<endl;
			cout<<"** 3.退出             **"<<endl; 
			cout<<"请输入你的选择:"<<endl;
			break;
		case 3:        //管理员登录 
			cout<<"** 1.添加城市   **"<<endl;
			cout<<"** 2.删除城市   **"<<endl;
			cout<<"** 3.添加线路   **"<<endl;
			cout<<"** 4.删除线路   **"<<endl;
			cout<<"** 5.显示线路   **"<<endl;
			cout<<"** 6.退出       **"<<endl;
			cout<<"请输入你的选择:"<<endl;
			break;
		default:
			cout<<"没有!!"<<endl; 
			break;
	}
}
//添加城市
void TrafficGraph::InsertCity(string Name)
{
	if(Cnum<MAX_VERTEX_NUM)
	{
		AddList[Cnum].cityname=Name;
		AddList[Cnum].FlightNum=0;
		AddList[Cnum].TrainNum=0;
		Cnum++;
		cout<<"添加成功!"<<endl;
	} 
	else
		cout<<"城市已满!"<<endl;
} 
//查找城市并返回城市序号：
int TrafficGraph::FindCity (string name) 
{ 
    for (int i=0;i<Cnum;i++) 
	{ 
         if (name==AddList[i].cityname) 
		 { 
             return i; 
		 } 	 
	} 
    return -1; 
} 
//删除城市
bool TrafficGraph::DelCity(string Name)
{
	int CityNo;          //城市序号 
	CityNo=FindCity(Name);
	if(Cnum==1||CityNo<0||CityNo>=MAX_VERTEX_NUM) return false;     //表空或顶点号超出范围 
	TrafficNode *p,*s,*t;int i,k;
	while(AddList[CityNo].Tadj!=NULL)      //删除第CityNo个边链表中所有结点 
	{
		p=AddList[CityNo].Tadj;k=p->EndCity;         //取邻接顶点k 
		s=AddList[k].Tadj;t=NULL;              //找对称存在的边结点 
		while(s!=NULL&&s->EndCity!=CityNo)
		{
			t=s;s=s->link;
		}
		if(s!=NULL)          //删除对称存在的边结点 
		{
			if(t==NULL)AddList[k].Tadj=s->link;
			else t->link=s->link;
			delete s;
		}
		AddList[CityNo].Tadj=p->link;        //清除顶点v的边链表结点 
		delete p;AddList[CityNo].TrainNum--;   //边数减一 
	}
	while(AddList[CityNo].Fadj!=NULL)           //航班线同上 
	{
		p=AddList[CityNo].Fadj;k=p->EndCity;
		s=AddList[k].Fadj;t=NULL;
		while(s!=NULL&&s->EndCity!=CityNo)
		{
			t=s;s=s->link;
		}
		if(s!=NULL)
		{
			if(t==NULL)AddList[k].Fadj=s->link;
			else t->link=s->link;
			delete s;
		}
		AddList[CityNo].Fadj=p->link;
		delete p;AddList[CityNo].FlightNum--;
	}
	Cnum--;      //城市数减一 
	AddList[CityNo].cityname=AddList[Cnum].cityname;//填补，这里直接采用表中最后一个城市的信息进行填补 
	p=AddList[CityNo].Tadj=AddList[Cnum].Tadj;
	t=AddList[CityNo].Fadj=AddList[Cnum].Fadj;
	while(p!=NULL)//填补城市的列车线边链表非空
	{
		s=AddList[p->EndCity].Tadj;
		while(s!=NULL)//未遍历到该班次的终点站 
		{
			if(s->EndCity==Cnum)
			{//遍历到该班次的终点站 
				s->EndCity=CityNo;//记下该站下标
				break;
			}
			else s=s->link;
		}
		p=p->link;                                                                //修改 
	}
	while(t!=NULL)//填补城市的航班线边链表非空
	{
		s=AddList[t->EndCity].Fadj;
		while(s!=NULL)//未遍历到该班次的终点站
		{
			if(s->EndCity==Cnum)
			{//遍历到该班次的终点站
				s->EndCity=CityNo;//记下该站下标
				break;
			}
			else s=s->link;
		}
		t=t->link;
	}
	return true;
} 
//添加火车线
bool TrafficGraph::InsertTrain(int i,int j,int TFcost,int time1,int time2,char *TFname)
{
	if(i>=0&&i<Cnum&&j>=0&&j<Cnum)
	{
		TrafficNode *p=AddList[i].Tadj;      //i对应的列车线 
		while(p!=NULL&&p->EndCity!=j)        //寻找邻接顶点j 
			p=p->link;
		if(p!=NULL)return false;  //j已存在，不插入 
		p=new TrafficNode;        //否则，创建新结点 
		p->EndCity=j;p->Cost=TFcost;         //链入i的列车线 
		strcpy(p->name,TFname);
		p->StartTime=time1;//stHour*60+stMinute;
		p->StopTime=time2; //enHour*60+enMinute;
		p->Duration=time2-time1; 
		p->link=AddList[i].Tadj;//将该线路链入总表 
		AddList[i].Tadj=p;
		AddList[i].TrainNum++;
		return true;
	}
	return false;
} 
//删除火车线
bool TrafficGraph::DelTrain() 
{
	string TSCname;
	char Tno[MaxSize];
	cout<<"请输入要删除的线路的始发站:"<<endl;
	cin>>TSCname;
	int v1,v2=-1;
	v1=FindCity(TSCname);
	if(ShowTpath(TSCname))                   //输出以TSCname为始发站的线路 
	{
		cout<<"请输入你想删除的班次:"<<endl;
		cin>>Tno;
		TrafficNode *p=AddList[v1].Tadj;
		while(p!=NULL)
		{
			if(strcmp(p->name,Tno)==0)           //按照班次名找到对应的线路 
			{//找到对应的线路
				v2=p->EndCity;//记录终点站线路下标
				break;
			}
			p=p->link;
		}
		if(v1!=-1&&v2!=-1)                
		{//起始站和终点站存在
			TrafficNode *p=AddList[v1].Tadj,*q=NULL,*s=p;
			while(p!=NULL&&p->EndCity!=v2)
			{
				q=p; p=p->link;
			}
			if(p!=NULL)
			{
				if(p==s) AddList[v1].Tadj=p->link;
				else q->link=p->link;
				delete p;
			}
			AddList[v1].TrainNum--;
			return true;
		}
		return false;
	}
	return false;
}
//添加航班线
bool TrafficGraph::InsertFlight(int i,int j,int TFcost,int time1,int time2,char *TFname)
{
	if(i>=0&&i<Cnum&&j>=0&&j<Cnum)
	{
		TrafficNode *p=AddList[i].Fadj;
		while(p!=NULL&&p->EndCity!=j)
			p=p->link;
		if(p!=NULL)return false;
		p=new TrafficNode;
		p->EndCity=j;p->Cost=TFcost;
		strcpy(p->name,TFname);
		p->StartTime=time1;//stHour*60+stMinute;
		p->StopTime=time2;//enHour*60+enMinute;
		p->Duration=time2-time1;
		p->link=AddList[i].Fadj;
		AddList[i].Fadj=p;
		AddList[i].FlightNum++;
		return true;
	}
	return false;
} 
//删除航班线
bool TrafficGraph::DelFlight() 
{
	string FSCname;
	char Fno[MaxSize];
	cout<<"请输入要删除的线路的始发站:"<<endl;
	cin>>FSCname;
	int v1,v2=-1;
	v1=FindCity(FSCname);
	if(ShowFpath(FSCname))
	{
		cout<<"请输入你想删除的班次:"<<endl;
		cin>>Fno;
		TrafficNode *p=AddList[v1].Fadj;
		while(p!=NULL)
		{
			if(strcmp(p->name,Fno)==0)
			{
				v2=p->EndCity;
				break;
			}
			p=p->link;
		}
		if(v1!=-1&&v2!=-1)
		{
			TrafficNode *p=AddList[v1].Fadj,*q=NULL,*s=p;
			while(p!=NULL&&p->EndCity!=v2)
			{
				q=p; p=p->link;
			}
			if(p!=NULL)
			{
				if(p==s) AddList[v1].Fadj=p->link;
				else q->link=p->link;
				delete p;
			}
			AddList[v2].FlightNum--;
			return true;
		}
		return false;
	}
	return false;
}
//显示列车线 
bool TrafficGraph::ShowTpath(string name)
{
	int i;
	i=FindCity(name);    
	if(i!=-1)
	{
		if(AddList[i].Tadj!=NULL)
		{
			cout<<"班次编号\t"<<"终点站\t\t"<<"出发时间\t"<<"到达时间\t"<<"票价\t"<<endl; 
			for(TrafficNode *p=AddList[i].Tadj;p!=NULL;p=p->link)//循环搜索班次编号 
			{
				cout<<p->name<<"\t\t";              
				cout<<AddList[p->EndCity].cityname<<"\t\t";
				cout<<p->StartTime/60<<":";
				if(p->StartTime%60<10)
				{
					cout<<"0";
				}
				cout<<p->StartTime%60<<"\t\t";
				cout<<p->StopTime/60<<":";
				if(p->StopTime%60<10)
				{
					cout<<"0";
				}
				cout<<p->StopTime%60<<"\t\t";
				cout<<p->Cost<<"\t\t";
				cout<<endl;
			}
			return true;
		}
		else
		{
			cout<<"未添加线路!"<<endl;
			return false;
		}	
	} 
	else
	{
		cout<<"目标城市未录入!"<<endl;
		return false;
	}		
}
//显示航班线 
bool TrafficGraph::ShowFpath(string name)
{
	int i;
	i=FindCity(name);
	if(i!=-1)
	{
		if(AddList[i].Fadj!=NULL)
		{
			cout<<"班次编号\t"<<"终点站\t\t"<<"出发时间\t"<<"到达时间\t"<<"票价\t"<<endl; 
			for(TrafficNode *p=AddList[i].Fadj;p!=NULL;p=p->link)//循环搜索班次编号 
			{
				cout<<p->name<<"\t\t";
				cout<<AddList[p->EndCity].cityname<<"\t\t";
				cout<<p->StartTime/60<<":";
				if(p->StartTime%60<10)
				{
					cout<<"0";
				}
				cout<<p->StartTime%60<<"\t\t";
				cout<<p->StopTime/60<<":";
				if(p->StopTime%60<10)
				{
					cout<<"0";
				}
				cout<<p->StopTime%60<<"\t\t";
				cout<<p->Cost<<"\t\t";
				cout<<endl;
			}
			return true;
		}
		else
		{
			cout<<"未添加线路!"<<endl;
			return false;
		}	
	} 
	else
	{
		cout<<"目标城市未录入!"<<endl;
		return false;
	}		
}
//获取两个城市间的费用 
int TrafficGraph::getCost(int v,int u,int choose)
{
	if(v!=-1&&u!=-1)
	{
		if(v==u) return 0;
		TrafficNode *p=new TrafficNode; 
		switch(choose)
		{
			case 1:
				p=AddList[v].Tadj;
				break;
			case 2:
				p=AddList[v].Fadj;
				break;
		}
		while(p!=NULL&&p->EndCity!=u)
			p=p->link;
		if(p!=NULL)return p->Cost;
		else return maxValue;
	}
	return 0;
}
// 获取线路信息 
void TrafficGraph::getInfor (int v1,int v2,int choose)
{
	if(v1!=-1&&v2!=-1)
	{
		TrafficNode *p=new TrafficNode;
		switch(choose)
		{
			case 1:
				cout<<"乘坐火车："<<endl; 
				p=AddList[v1].Tadj;
				break;
			case 2:
				cout<<"乘坐飞机："<<endl;
				p=AddList[v1].Fadj;
				break;
		}
		while(p!=NULL&&p->EndCity!=v2)
			p=p->link;
		if(p!=NULL)
		{
			cout<<"出发时刻:"<<p->StartTime/60<<":";
			if(p->StartTime%60<10)
				cout<<"0";
			cout<<p->StartTime%60<<"\t";
			cout<<"到达时刻:"<<p->StopTime/60<<":";
			if(p->StopTime%60<10)
				cout<<"0";
			cout<<p->StopTime%60<<"\t";
			cout<<"班次:"<<p->name<<endl;
		}
	}
}
//查找最便宜路线 
void TrafficGraph::CheapestRoute()
{
	int n=Cnum; 
	int choose;
	bool *S=new bool[n];  //最短路径顶点集 
	int i,j,k,w,min;
	int dist[n]; 
	//dist[i]是当前求到的从顶点v到顶点i的最短路径长度 
	int path[n];
	//path[i]存放求到的最短路径 
	string StartCity,EndCity;
	cout<<"请输入起始站:"<<endl;
	cin>>StartCity;
	cout<<"请输入终点站:"<<endl;
	cin>>EndCity;
	int v1=FindCity(StartCity) ;
	int v2=FindCity(EndCity);
	if(v1!=-1&&v2!=-1)
	{
		cout<<"请选择出行方式:"<<endl;
		cout<<"**  1. 列车  **"<<endl;
		cout<<"**  2. 航班  **"<<endl;
		cin>>choose; 
		if(choose==1||choose==2)
		{
			for(i=0;i<n;i++)
			{
				dist[i]=getCost(v1,i,choose);  //权重数组初始化  
				S[i]=false;                    //顶点集数组初始化
				if(i!=v1&&dist[i]<maxValue) path[i]=v1;//记下该顶点下标
				else path[i]=-1;
			}
			S[v1]=true; dist[v1]=0;   //顶点v加入顶点集合 
			for(i=0;i<n-1;i++)        //小于除始发站的城市个数
			{
				min=maxValue; int u=v1;   //选不在S中具有最短路径的顶点u 
				for(j=0;j<n;j++)
					if(S[j]==false&&dist[j]<min)
					{//j不在s中且路径长度小于最小值
						u=j;min=dist[j];
					}
				S[u]=true;     //将顶点u加入集合S 
				for(k=0;k<n;k++){       //修改 
					w=getCost(u,k,choose);
					if(S[k]==false&&w<maxValue&&dist[u]+w<dist[k]){
						//顶点k未加入S，且绕过u可以缩短路径 
						dist[k]=dist[u]+w;
						path[k]=u;   //修改到k的最短路径 
					}
				}
			}
			if(dist[v2]<maxValue)
			{
				cout<<"从"<<AddList[v1].cityname<<"到"<<AddList[v2].cityname<<"的费用最省路径为："<<endl;
				int *d=new int [MAX_VERTEX_NUM];    //栈数组 
				int top=-1;
				j=v2;
				while(j!=v1)
				{
					top++;
					d[top]=j;
					j=path[j];
				}
				cout<<AddList[v1].cityname;
				d[top+1]=v1;
				while(top!=-1){
					cout<<"->"<<AddList[d[top]].cityname<<"  ";
					getInfor(d[top+1],d[top],choose);
					top--;
					if(top!=-1)
					{
						cout<<AddList[d[top+1]].cityname;
					}
				}
				cout<<"总费用为:"<<dist[v2]<<"元"<<endl;
				delete []d;
			}
			else
				cout<<"未找到费用最省路径！"<<endl;
		}
		else
			cout<<"选择方式输入有误!"<<endl;
	}
	else
		cout<<"目的地或出发地不存在!"<<endl;
}
//获取时间段 
int TrafficGraph::getDuration(int v1,int v2,int choose)
{
	if(v1!=-1&&v2!=-1)
	{
		if(v1==v2) return 0;
		TrafficNode *p=new TrafficNode; 
		switch(choose)
		{
			case 1:
				p=AddList[v1].Tadj;
				break;
			case 2:
				p=AddList[v1].Fadj;
				break;
		}
		while(p!=NULL&&p->EndCity!=v2)
			p=p->link;
		if(p!=NULL)return p->Duration;
		else return maxValue;
	}
	return 0;
}
//获取等候时间 
int TrafficGraph::getTimes(int v1,int u,int k,int choose)
{
	if(v1!=-1&&u!=-1&&k!=-1)
	{
		TrafficNode *p=new TrafficNode,*q=new TrafficNode; 
		switch(choose)
		{
			case 1:
				p=AddList[v1].Tadj;
				q=AddList[u].Tadj;
				break;
			case 2:
				p=AddList[v1].Fadj;
				q=AddList[u].Fadj;
				break;
		}
		while(p!=NULL&&p->EndCity!=u)
		{
			p=p->link;
		}
		while(q!=NULL&&q->EndCity!=k)
		{
			q=q->link;
		}	
		if(p!=NULL&&q!=NULL) 
		{
			return (q->StartTime-p->StopTime);
		}
		else 
			return maxValue;
	}
	return 0;
}
//查找最快路径 
void TrafficGraph::FastestRoute()
{
	int n=Cnum;
	int choose;
	bool *S=new bool[n];  //最省时路径顶点集
	int i,j,k,w,x,min;
	int dist[n]; 
	int path[n];
	string StartCity,EndCity;
	cout<<"请输入起始站:"<<endl;
	cin>>StartCity;
	cout<<"请输入终点站:"<<endl;
	cin>>EndCity;
	int v1=FindCity(StartCity);
	int v2=FindCity(EndCity);
	if(v1!=-1&&v2!=-1)
	{
		cout<<"请选择出行方式:"<<endl;
		cout<<"**  1. 列车  **"<<endl;
		cout<<"**  2. 航班  **"<<endl;
		cin>>choose; 
		if(choose==1||choose==2)
		{
			for(i=0;i<n;i++)
			{
				dist[i]=getDuration(v1,i,choose);   //数组初始化 
				S[i]=false; 
				if(i!=v1&&dist[i]<maxValue) path[i]=v1;
				else path[i]=-1;
			}
			S[v1]=true; dist[v1]=0;   //顶点v加入顶点集合 
			for(i=0;i<n-1;i++)
			{
				min=maxValue; int u=v1;   //选不在S中具有最短路径的点顶u 
				for(j=0;j<n;j++)
					if(S[j]==false&&dist[j]<min)
					{
						u=j;min=dist[j];
					}
				S[u]=true;     //将顶点u加入集合S 
				for(k=0;k<n;k++){       //修改 
					w=getDuration(u,k,choose);
					x=getTimes(path[u],u,k,choose);
					//if(w<maxValue)
						//cout<<"x="<<x<<endl;
					
					if(S[k]==false&&w<maxValue&&x>0&&dist[u]+w+x<dist[k]){
						//顶点k未加入S，且绕过u可以缩短路径 
						dist[k]=dist[u]+w+x;
						path[k]=u;   //修改到k的最短路径 
					}
				}
			}
			if(dist[v2]<maxValue)
			{
				cout<<"从"<<AddList[v1].cityname<<"到"<<AddList[v2].cityname<<"的耗时最短路径为："<<endl;
				int *d=new int [MAX_VERTEX_NUM];    //栈数组 
				int top=-1;
				j=v2;
				while(j!=v1)
				{
					top++;
					d[top]=j;
					j=path[j];
				}
				d[top+1]=v1;
				cout<<AddList[v1].cityname;
				while(top!=-1){
					cout<<"->"<<AddList[d[top]].cityname<<"  ";
					getInfor(d[top+1],d[top],choose);
					top--;
					if(top!=-1)
					{
						cout<<AddList[d[top+1]].cityname;
					}
				}
				cout<<"总耗时为:"<<dist[v2]/60<<"小时"<<dist[v2]%60<<"分钟"<<endl;
				delete []d;
			}
			else
				cout<<"未找耗时最短路径！"<<endl;
		}
		else
			cout<<"选择方式输入有误!"<<endl;
	}
	else
		cout<<"目的地或出发地不存在！"<<endl;
}
/*void TrafficGraph::InitData()
{
	string name[31]={"北京","上海","天津","石家庄","太原","呼和浩特","沈阳","长春",
						"哈尔滨","济南","南京","合肥","杭州","南昌","福州","台北","郑州",
						"武汉","长沙","广州","海口","南宁","西安","银川","兰州",
						"西宁","乌鲁木齐","成都","贵阳","昆明","拉萨"};
	 for(int i=0;i<31;i++)
	 {
	 	InsertCity(name[i]);
	 }
	 //InsertTrain();
	 //InsertFlight();
}*/
//将交通系统信息写入文件 
int TrafficGraph::SaveSysInfo() 
{
    FILE *fp;
	int i,j,total; 
	TrafficNode *p;
    fp=fopen(CityFile,"w"); //打开城市文件 
    fprintf(fp,"%d\n",Cnum); //读取文件中城市个数 
    for (i=0;i<Cnum;i++) 
	{ //依次读取各城市名 
		const char *str=AddList[i].cityname.data();   //string类型转char 
        fprintf(fp,"%s\n",str); 
	} 
    fclose(fp);total=0; 
    fp=fopen(TrainFile,"w"); //打开列车文件
    for (i=0;i<Cnum;i++) 
	{ 
        total+=AddList[i].TrainNum; 
	} 
    fprintf(fp,"%d\n",total); 
    for (i=0;i<Cnum;i++) 
	{ 
        for (p=AddList[i].Tadj;p!=NULL;p=p->link) 
		{ 
			
			const char*a=AddList[i].cityname.data();     //string类型转char 
			const char*b=AddList[p->EndCity].cityname.data();  //string类型转char 
            fprintf(fp,"%s %s %s ", AddList[i].Tadj->name, a, b); 
            fprintf(fp,"%2d:%2d %2d:%2d %d\n", p->StartTime/60, 
            p->StartTime%60, p->StopTime/60, p->StopTime%60, p->Cost); 
		} 
	} 
    fclose(fp);total=0; 
    fp=fopen(FlightFile,"w"); 
    for (i=0;i<Cnum;i++) 
	{ 
        total+=AddList[i].FlightNum; 
	} 
    fprintf(fp,"%d\n",total); 
    for (i=0;i<Cnum;i++) 
	{ 
        for (p=AddList[i].Fadj;p!=NULL;p=p->link) 
		{ 
		  	const char*a=AddList[i].cityname.data();
			const char*b=AddList[p->EndCity].cityname.data();
            fprintf(fp,"%s %s %s ", AddList[i].Fadj->name, a, b); 
            fprintf(fp,"%2d:%2d %2d:%2d %d\n", p->StartTime/60, 
            p->StartTime%60, p->StopTime/60, p->StopTime%60, p->Cost); 
		} 
	} 
    fclose(fp);
	return 1; 
}
//用文件信息初始化系统 
int TrafficGraph::InitSysData()
{ 
    FILE *fp;
    TrafficNode *p;
    char *a,*b,*c;
	a=new char;
	b=new char;
	c=new char;
	int i,j,k,hour1,minute1,num,cost,hour2,minute2; 
    fp=fopen(CityFile,"r"); //打开城市文件 
    if (!fp) 
	{ 
        printf("\nError:Cannot Open City File...\n"); 
        return -1; 
	} 
    fscanf(fp,"%d",&Cnum); 
    for (i=0;i<Cnum;i++) 
	{ 
		char *p;
		p=new char;
        fscanf(fp,"%s",p); //读取城市名 
		AddList[i].cityname=p;  
	} 
    fclose(fp); 
    fp=fopen(TrainFile,"r");//打开列车文件 
    if (!fp) 
	{ 
        printf("\nError:Cannot Open Train File...\n"); 
        return -1; 
	} 
    fscanf(fp,"%d",&num); 
    for (i=0;i<num;i++) //根据文件中列车班次总数进行读取 
	{ 
		fscanf(fp,"%s",a);//读取列车班次 
        fscanf(fp,"%s",b);//读取始发站 
        fscanf(fp,"%s",c);//读取终点站 
		j=FindCity(b); //始发站下标 
		k=FindCity(c);
		fscanf(fp,"%d:%d",&hour1,&minute1);
		fscanf(fp,"%d:%d",&hour2,&minute2);
		fscanf(fp,"%d",&cost); 
		InsertTrain(j,k,cost,hour1*60+minute1,hour2*60+minute2,a);
	} 
    fclose(fp); 
    fp=fopen(FlightFile,"r");//打开航班文件  
    if (!fp) 
	{ 
        printf("\nError:Cannot Open Flight File...\n"); 
        return -1; 
	} 
    fscanf(fp,"%d",&num); 
    for (i=0;i<num;i++) //根据文件中航班班次总数进行读取 
	{   
        fscanf(fp,"%s",a); //读取航班班次
        fscanf(fp,"%s",b); //读取始发站 
        fscanf(fp,"%s",c); //读取终点站
        j=FindCity(b); //始发站下标 
        k=FindCity(c);
		fscanf(fp,"%d:%d",&hour1,&minute1);
		fscanf(fp,"%d:%d",&hour2,&minute2);
		fscanf(fp,"%d",&cost); 
		InsertFlight(j,k,cost,hour1*60+minute1,hour2*60+minute2,a);
	} 
    fclose(fp);
	return 1; 
} 
int main()
{
	int a,b,c;
	char ch='y';
	string name;
	string StartCity,EndCity;
	int TFcost;
	int stHour,stMinute;
	int enHour,enMinute;
	char ah;
	char TFname[MaxSize];
	bool bo; 
	TrafficGraph tr;
	//tr.InitSysData();
	do
	{
		a=tr.InitialInterface();
		if(a==2)
		{
			do
			{
				tr.ShowMenu(2);
				cin>>b;
				switch(b)
				{
					case 1:
						tr.FastestRoute();
						break;
					case 2:
						tr.CheapestRoute();
						break;
					case 3:
						ch='n';
						break;
					default:
						cout<<"输入非法！！！"<<endl;
				}
				system("pause");
				system("cls");
			}while(ch=='y');
		}
		else if(a==3)
		{
			do{
				tr.ShowMenu(3);
				cin>>b;
				if(b>=0&&b<=9)
				{
					switch(b)
					{
						case 1:
							cout<<"请输入城市名："<<endl;
							cin>>name;
							tr.InsertCity(name);
							tr.SaveSysInfo();
							break;
						case 2:
							cout<<"请输入要删除的城市名:"<<endl;
							cin>>name;
							bo=tr.DelCity(name);
							if(bo) cout<<"删除成功!"<<endl;
							else cout<<"删除失败!"<<endl;
							tr.SaveSysInfo();
							break;
						case 3:
							cout<<"1.列车"<<endl;
							cout<<"2.航班"<<endl;
							cin>>c;
							cout<<"请输入起始站:"<<endl;
							cin>>StartCity;
							cout<<"请输入终点站:"<<endl;
							cin>>EndCity;
							int i,j;
							i=tr.FindCity(StartCity);//始发站城市编号 
							j=tr.FindCity(EndCity);  //终点站城市编号 
							if(i>=0&&j>=0)
							{
								cout<<"请输入花费:"<<endl;
								cin>>TFcost;
								cout<<"出发时刻(00:00,24小时制):"<<endl;
								cin>>stHour>>ah>>stMinute;
								cout<<"到达时刻(00:00,24小时制):"<<endl;
								cin>>enHour>>ah>>enMinute;
								while(stHour*60+stMinute>=enHour*60+enMinute)
								{
									cout<<"时间输入异常!请重新输入:"<<endl;
									cout<<"出发时刻(00:00,24小时制):"<<endl;
									cin>>stHour>>ah>>stMinute;
									cout<<"到达时刻(00:00,24小时制):"<<endl;
									cin>>enHour>>ah>>enMinute;
								}
								cout<<"请输入班次编号:"<<endl;
								cin>>TFname;
								switch(c)
								{
									case 1:
										bo=tr.InsertTrain(i,j,TFcost,stHour*60+stMinute,enHour*60+enMinute,TFname);
										break;
									case 2:
										bo=tr.InsertFlight(i,j,TFcost,stHour*60+stMinute,enHour*60+enMinute,TFname);
										break;
									default:
										cout<<"输入非法！"<<endl;
										break;
								 }
								 if(bo) cout<<"插入成功!"<<endl;
								 else cout<<"插入失败!"<<endl;
								 tr.SaveSysInfo(); 
							}
							else
							{
								cout<<"起始站或终点站不存在!"<<endl;
							}
							break;
						case 4:
							cout<<"1.列车"<<endl;
							cout<<"2.航班"<<endl;
							cin>>c;
							switch(c)
							{
								case 1:
									bo=tr.DelTrain();
									break;
								case 2:
									bo=tr.DelFlight();
									break;
								default:
									cout<<"输入非法！"<<endl;
									break;
							 }
							 if(bo) cout<<"删除成功!"<<endl;
							 else cout<<"删除失败!"<<endl;
							 tr.SaveSysInfo(); 
							break;
						case 5:
							cout<<"请输入要搜索的始发站:"<<endl;
							cin>>name;
							cout<<"1.列车"<<endl;
							cout<<"2.航班"<<endl;
							cin>>c;
							switch(c)
							{
								case 1:
									tr.ShowTpath(name);
									break;
								case 2:
									tr.ShowFpath(name);
									break;
								default:
									cout<<"输入非法！"<<endl;
									break;
							 } 
							break;
						case 6:
							ch='n';
							break;
						default:
							cout<<"输入非法!"<<endl; 
							break;
					}
				}	
				else
				{
					cout<<"输入错误！"<<endl;
					ch='n';
				}	
				system("pause"); 
				system("cls");
			}while(ch=='y'||ch=='Y');
		}
	}while(a!=4);
	return 0;
}





