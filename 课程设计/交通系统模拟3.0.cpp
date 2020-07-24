//��ͨϵͳģ�� 
#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
using namespace std;
//�ļ�����,��D�̽��������ı��ļ� 
const char CityFile[] ="D:\\city.txt"; 
const char TrainFile[] ="D:\\train.txt"; 
const char FlightFile[] ="D:\\flight.txt"; 
const int  MAX_VERTEX_NUM=34;  //ͼ�ж�����Ŀ���ֵ
const int MaxSize=20;   
const int maxValue=9999;
typedef struct TrafficNodeData    //��ͨ������Ϣ 
{
	char name[MaxSize];      //���
	int StartTime;    //����ʱ��
	int StopTime;     //����ʱ��
	int Duration;    //ʱ��� 
	int EndCity;              //�ߵ���һ���㣬����һ�����б��
	int Cost;          //Ʊ��
	struct TrafficNodeData *link;  //��һ������ָ�� 
}TrafficNode;
typedef struct VNodeData          //·����Ϣ
{
	string cityname ;       //��������
	int TrainNum,FlightNum;    //�г�����������           
	TrafficNode *Tadj;      //�г��� 
	TrafficNode *Fadj;      //������ 
}VNode; 
//��ͨϵͳ��Ķ��� 
class TrafficGraph
{
	public:
		TrafficGraph();    //���캯�� 
		~TrafficGraph();   //�������� 
		int InitialInterface();   //��ʼ����¼���� 
		void ShowMenu(int n);    //����ѡ����� 
		bool ShowFpath(string name);//��ʾ������
		bool ShowTpath(string name);//��ʾ�г��� 
		bool DelFlight();//ɾ��������
		bool InsertFlight(int i,int j,int TFcost,int time1,int time2,char *TFname);//��Ӻ�����
		bool DelTrain();//ɾ������
		bool InsertTrain(int i,int j,int TFcost,int time1,int time2,char *TFname);//��ӻ���
		bool DelCity(string Name);//ɾ������
		void InsertCity(string Name);//��ӳ���
		int FindCity (string name);//���ҳ��в����س������
		//void InitData();  
		void FastestRoute();     //��ʱ���·�� 
		void CheapestRoute();    //��Ǯ����·�� 
		int getCost(int v,int u,int choose);    //������������֮���Ʊ�� 
		int getDuration(int v1,int v2,int choose);   //������ʻ��ʱ���� 
		int getTimes(int v1,int u,int k,int choose);   //���صȺ��ʱ�� 
		void getInfor(int v1,int v2,int choose);     //��ȡ�г��򺽰���Ϣ 
		int SaveSysInfo();     //����Ϣ�����ļ� 
		int InitSysData () ;   //���ļ���Ϣ��ʼ�� 
	private:
		VNode *AddList; //ϵͳ��Ϣ  
		int Cnum;      // ���и��� 
};
TrafficGraph::TrafficGraph()     //���캯�� 
{
	AddList=new VNode[MAX_VERTEX_NUM];
	Cnum=0;
	for(int i=0;i<MAX_VERTEX_NUM;i++)
	{
		AddList[i].Tadj=NULL;    //�г���ָ���ÿ� 
		AddList[i].Fadj=NULL;    //������ָ���ÿ�
	}	
} 
TrafficGraph::~TrafficGraph()      //�������� 
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
int TrafficGraph::InitialInterface()      //��ʼ������¼���� 
{
	string num1,num2;
	char a[10],c[10];
	char b[10];
	int flag;                   //ѭ����ֹ��� 
	char ab='n';                //�˳���ȷ���ַ� 
	ofstream out;               //�ļ�д�� 
	ifstream in;                //�ļ����� 
	cout<<"��----------------------------------��"<<endl;
	cout<<"��                                  ��"<<endl;
	cout<<"��  ��ӭʹ��ȫ����ͨ��ѯģ��ϵͳ1.0 ��"<<endl;
	cout<<"��                                  ��"<<endl;
	cout<<"��----------------------------------��"<<endl;
	string Magname="17080207";     //����Ա�˺ţ�Ψһ 
	char password[]="123456";      //����Ա���� 
	cout<<"** 1.�û�ע��   **"<<endl; 
	cout<<"** 2.�û���¼   **"<<endl;
	cout<<"** 3.����Ա��¼ **"<<endl;
	cout<<"** 4.�˳�ϵͳ   **"<<endl; 
	cout<<"��ѡ��";
	int x; 
	cin>>x;
	system("cls");
	switch(x)
	{
		case 1:
			cout<<"�������û���(������8λ)��"<<endl;
			cin>>num1;
			cout<<"����������(������10λ)��"<<endl;
			for(int j=0;j<10;j++)        //���밵�� 
			{
				a[j]=getch();
				cout<<"*";   //���ð��� 
				if(a[j]=='\r')//���س� 
				{
					a[j]='\0';//����������� 
					break;
				}
			}
			cout<<endl<<"���ٴ�����������룺"<<endl;
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
				cout<<endl<<"�����������벻һ�£����������룺"<<endl;
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
			out.open("username.txt",ios::app);     //�û��������ļ� 
			out<<num1<<endl;
			out.close();
			out.open("password.txt",ios::app);     //��Ӧ����������ļ� 
			out<<c<<endl;
			out.close();
			cout<<endl<<"ע����ϣ�ֱ�ӵ�¼!"<<endl;
			x=2;        //����2������û����ܱ� 
			system("pause");
			system("cls");
			break;
		case 2:
			char ch[100];
			int i,f;
			do
			{
				i=1;f=0; //i����ǵڼ����û���fΪ���ұ�ǣ��ҵ���Ϊ0 
				cout<<"�������û�����"<<endl;
				cin>>num2;
				in.open("username.txt");
				if(!in)
				{
					cout<<"û���û�ע��!"<<endl;
					exit(1);
				}
				do
				{
					in.getline(ch,100,'\n');    //���ļ��в��Ҹ��û��Ƿ�ע���� 
					if(ch==num2)
					{
						f=1;      //��ע���û���f=1 
						break;
					}
					i++;     //��¼�ǵڼ����û� 
				}while(ch!=num2&&!in.eof());   
				if(f==0)    //δע�� 
				{
					cout<<"���û�δע��!"<<endl;
					flag=1;  
					in.close();
				}
				else
				{
					cout<<"����������:"<<endl;
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
					for(int k=0;k<i;k++)    //�������Ƿ���ȷ 
					{
						in.getline(ch,100,'\n');
					}
					in.close();
					if(strcmp(ch,b)==0)
						flag=0;    //���ҳɹ���ѭ����־��0 
					else
					{
						cout<<endl<<"�û����������������"<<endl;
						flag=1;    //ʧ�ܣ�ѭ����־��1 
						system("pause");//��ͣ���� 
						system("cls");  //���� 
					}
				} 
				
			}while(flag==1);
			cout<<endl<<"��¼�ɹ�!"<<endl;
			system("pause");
			system("cls");
			break;
		case 3:
			do
			{
				cout<<"�������û�����"<<endl;
				cin>>num2;
				cout<<"����������:"<<endl;
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
					flag=0;       //���ҳɹ���ѭ����־��0 
				else
				{
					cout<<"�û����������������"<<endl;
					flag=1;
					system("pause");
					system("cls");
				}
			}while(flag==1);       //ʧ�ܣ�ѭ����־��1
			cout<<endl<<"��¼�ɹ�!"<<endl;
			system("pause");
			system("cls");
			break;
		case 4:
			cout<<"ȷ���˳���(y/n)"<<endl;
			cin>>ab;
			if(ab=='y'||ab=='Y')
				exit(1);    //�˳����� 
			else
			{
				system("cls");
				x=InitialInterface();//���������� 
			}
			break;
		default:
			cout<<"����Ƿ���������ѡ��"<<endl;
			system("pause") ;
			system("cls");
			x=InitialInterface();
			break;
	}
	return x;
}
//������ܱ� 
void TrafficGraph::ShowMenu(int n)
{
	switch(n)
	{
		case 2:         //�û���¼ 
			cout<<"** 1.��ѯ���·��     **"<<endl;
			cout<<"** 2.��ѯ������ʡ·�� **"<<endl;
			cout<<"** 3.�˳�             **"<<endl; 
			cout<<"���������ѡ��:"<<endl;
			break;
		case 3:        //����Ա��¼ 
			cout<<"** 1.��ӳ���   **"<<endl;
			cout<<"** 2.ɾ������   **"<<endl;
			cout<<"** 3.�����·   **"<<endl;
			cout<<"** 4.ɾ����·   **"<<endl;
			cout<<"** 5.��ʾ��·   **"<<endl;
			cout<<"** 6.�˳�       **"<<endl;
			cout<<"���������ѡ��:"<<endl;
			break;
		default:
			cout<<"û��!!"<<endl; 
			break;
	}
}
//��ӳ���
void TrafficGraph::InsertCity(string Name)
{
	if(Cnum<MAX_VERTEX_NUM)
	{
		AddList[Cnum].cityname=Name;
		AddList[Cnum].FlightNum=0;
		AddList[Cnum].TrainNum=0;
		Cnum++;
		cout<<"��ӳɹ�!"<<endl;
	} 
	else
		cout<<"��������!"<<endl;
} 
//���ҳ��в����س�����ţ�
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
//ɾ������
bool TrafficGraph::DelCity(string Name)
{
	int CityNo;          //������� 
	CityNo=FindCity(Name);
	if(Cnum==1||CityNo<0||CityNo>=MAX_VERTEX_NUM) return false;     //��ջ򶥵�ų�����Χ 
	TrafficNode *p,*s,*t;int i,k;
	while(AddList[CityNo].Tadj!=NULL)      //ɾ����CityNo�������������н�� 
	{
		p=AddList[CityNo].Tadj;k=p->EndCity;         //ȡ�ڽӶ���k 
		s=AddList[k].Tadj;t=NULL;              //�ҶԳƴ��ڵı߽�� 
		while(s!=NULL&&s->EndCity!=CityNo)
		{
			t=s;s=s->link;
		}
		if(s!=NULL)          //ɾ���Գƴ��ڵı߽�� 
		{
			if(t==NULL)AddList[k].Tadj=s->link;
			else t->link=s->link;
			delete s;
		}
		AddList[CityNo].Tadj=p->link;        //�������v�ı������� 
		delete p;AddList[CityNo].TrainNum--;   //������һ 
	}
	while(AddList[CityNo].Fadj!=NULL)           //������ͬ�� 
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
	Cnum--;      //��������һ 
	AddList[CityNo].cityname=AddList[Cnum].cityname;//�������ֱ�Ӳ��ñ������һ�����е���Ϣ����� 
	p=AddList[CityNo].Tadj=AddList[Cnum].Tadj;
	t=AddList[CityNo].Fadj=AddList[Cnum].Fadj;
	while(p!=NULL)//����е��г��߱�����ǿ�
	{
		s=AddList[p->EndCity].Tadj;
		while(s!=NULL)//δ�������ð�ε��յ�վ 
		{
			if(s->EndCity==Cnum)
			{//�������ð�ε��յ�վ 
				s->EndCity=CityNo;//���¸�վ�±�
				break;
			}
			else s=s->link;
		}
		p=p->link;                                                                //�޸� 
	}
	while(t!=NULL)//����еĺ����߱�����ǿ�
	{
		s=AddList[t->EndCity].Fadj;
		while(s!=NULL)//δ�������ð�ε��յ�վ
		{
			if(s->EndCity==Cnum)
			{//�������ð�ε��յ�վ
				s->EndCity=CityNo;//���¸�վ�±�
				break;
			}
			else s=s->link;
		}
		t=t->link;
	}
	return true;
} 
//��ӻ���
bool TrafficGraph::InsertTrain(int i,int j,int TFcost,int time1,int time2,char *TFname)
{
	if(i>=0&&i<Cnum&&j>=0&&j<Cnum)
	{
		TrafficNode *p=AddList[i].Tadj;      //i��Ӧ���г��� 
		while(p!=NULL&&p->EndCity!=j)        //Ѱ���ڽӶ���j 
			p=p->link;
		if(p!=NULL)return false;  //j�Ѵ��ڣ������� 
		p=new TrafficNode;        //���򣬴����½�� 
		p->EndCity=j;p->Cost=TFcost;         //����i���г��� 
		strcpy(p->name,TFname);
		p->StartTime=time1;//stHour*60+stMinute;
		p->StopTime=time2; //enHour*60+enMinute;
		p->Duration=time2-time1; 
		p->link=AddList[i].Tadj;//������·�����ܱ� 
		AddList[i].Tadj=p;
		AddList[i].TrainNum++;
		return true;
	}
	return false;
} 
//ɾ������
bool TrafficGraph::DelTrain() 
{
	string TSCname;
	char Tno[MaxSize];
	cout<<"������Ҫɾ������·��ʼ��վ:"<<endl;
	cin>>TSCname;
	int v1,v2=-1;
	v1=FindCity(TSCname);
	if(ShowTpath(TSCname))                   //�����TSCnameΪʼ��վ����· 
	{
		cout<<"����������ɾ���İ��:"<<endl;
		cin>>Tno;
		TrafficNode *p=AddList[v1].Tadj;
		while(p!=NULL)
		{
			if(strcmp(p->name,Tno)==0)           //���հ�����ҵ���Ӧ����· 
			{//�ҵ���Ӧ����·
				v2=p->EndCity;//��¼�յ�վ��·�±�
				break;
			}
			p=p->link;
		}
		if(v1!=-1&&v2!=-1)                
		{//��ʼվ���յ�վ����
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
//��Ӻ�����
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
//ɾ��������
bool TrafficGraph::DelFlight() 
{
	string FSCname;
	char Fno[MaxSize];
	cout<<"������Ҫɾ������·��ʼ��վ:"<<endl;
	cin>>FSCname;
	int v1,v2=-1;
	v1=FindCity(FSCname);
	if(ShowFpath(FSCname))
	{
		cout<<"����������ɾ���İ��:"<<endl;
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
//��ʾ�г��� 
bool TrafficGraph::ShowTpath(string name)
{
	int i;
	i=FindCity(name);    
	if(i!=-1)
	{
		if(AddList[i].Tadj!=NULL)
		{
			cout<<"��α��\t"<<"�յ�վ\t\t"<<"����ʱ��\t"<<"����ʱ��\t"<<"Ʊ��\t"<<endl; 
			for(TrafficNode *p=AddList[i].Tadj;p!=NULL;p=p->link)//ѭ��������α�� 
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
			cout<<"δ�����·!"<<endl;
			return false;
		}	
	} 
	else
	{
		cout<<"Ŀ�����δ¼��!"<<endl;
		return false;
	}		
}
//��ʾ������ 
bool TrafficGraph::ShowFpath(string name)
{
	int i;
	i=FindCity(name);
	if(i!=-1)
	{
		if(AddList[i].Fadj!=NULL)
		{
			cout<<"��α��\t"<<"�յ�վ\t\t"<<"����ʱ��\t"<<"����ʱ��\t"<<"Ʊ��\t"<<endl; 
			for(TrafficNode *p=AddList[i].Fadj;p!=NULL;p=p->link)//ѭ��������α�� 
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
			cout<<"δ�����·!"<<endl;
			return false;
		}	
	} 
	else
	{
		cout<<"Ŀ�����δ¼��!"<<endl;
		return false;
	}		
}
//��ȡ�������м�ķ��� 
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
// ��ȡ��·��Ϣ 
void TrafficGraph::getInfor (int v1,int v2,int choose)
{
	if(v1!=-1&&v2!=-1)
	{
		TrafficNode *p=new TrafficNode;
		switch(choose)
		{
			case 1:
				cout<<"�����𳵣�"<<endl; 
				p=AddList[v1].Tadj;
				break;
			case 2:
				cout<<"�����ɻ���"<<endl;
				p=AddList[v1].Fadj;
				break;
		}
		while(p!=NULL&&p->EndCity!=v2)
			p=p->link;
		if(p!=NULL)
		{
			cout<<"����ʱ��:"<<p->StartTime/60<<":";
			if(p->StartTime%60<10)
				cout<<"0";
			cout<<p->StartTime%60<<"\t";
			cout<<"����ʱ��:"<<p->StopTime/60<<":";
			if(p->StopTime%60<10)
				cout<<"0";
			cout<<p->StopTime%60<<"\t";
			cout<<"���:"<<p->name<<endl;
		}
	}
}
//���������·�� 
void TrafficGraph::CheapestRoute()
{
	int n=Cnum; 
	int choose;
	bool *S=new bool[n];  //���·�����㼯 
	int i,j,k,w,min;
	int dist[n]; 
	//dist[i]�ǵ�ǰ�󵽵ĴӶ���v������i�����·������ 
	int path[n];
	//path[i]����󵽵����·�� 
	string StartCity,EndCity;
	cout<<"��������ʼվ:"<<endl;
	cin>>StartCity;
	cout<<"�������յ�վ:"<<endl;
	cin>>EndCity;
	int v1=FindCity(StartCity) ;
	int v2=FindCity(EndCity);
	if(v1!=-1&&v2!=-1)
	{
		cout<<"��ѡ����з�ʽ:"<<endl;
		cout<<"**  1. �г�  **"<<endl;
		cout<<"**  2. ����  **"<<endl;
		cin>>choose; 
		if(choose==1||choose==2)
		{
			for(i=0;i<n;i++)
			{
				dist[i]=getCost(v1,i,choose);  //Ȩ�������ʼ��  
				S[i]=false;                    //���㼯�����ʼ��
				if(i!=v1&&dist[i]<maxValue) path[i]=v1;//���¸ö����±�
				else path[i]=-1;
			}
			S[v1]=true; dist[v1]=0;   //����v���붥�㼯�� 
			for(i=0;i<n-1;i++)        //С�ڳ�ʼ��վ�ĳ��и���
			{
				min=maxValue; int u=v1;   //ѡ����S�о������·���Ķ���u 
				for(j=0;j<n;j++)
					if(S[j]==false&&dist[j]<min)
					{//j����s����·������С����Сֵ
						u=j;min=dist[j];
					}
				S[u]=true;     //������u���뼯��S 
				for(k=0;k<n;k++){       //�޸� 
					w=getCost(u,k,choose);
					if(S[k]==false&&w<maxValue&&dist[u]+w<dist[k]){
						//����kδ����S�����ƹ�u��������·�� 
						dist[k]=dist[u]+w;
						path[k]=u;   //�޸ĵ�k�����·�� 
					}
				}
			}
			if(dist[v2]<maxValue)
			{
				cout<<"��"<<AddList[v1].cityname<<"��"<<AddList[v2].cityname<<"�ķ�����ʡ·��Ϊ��"<<endl;
				int *d=new int [MAX_VERTEX_NUM];    //ջ���� 
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
				cout<<"�ܷ���Ϊ:"<<dist[v2]<<"Ԫ"<<endl;
				delete []d;
			}
			else
				cout<<"δ�ҵ�������ʡ·����"<<endl;
		}
		else
			cout<<"ѡ��ʽ��������!"<<endl;
	}
	else
		cout<<"Ŀ�ĵػ�����ز�����!"<<endl;
}
//��ȡʱ��� 
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
//��ȡ�Ⱥ�ʱ�� 
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
//�������·�� 
void TrafficGraph::FastestRoute()
{
	int n=Cnum;
	int choose;
	bool *S=new bool[n];  //��ʡʱ·�����㼯
	int i,j,k,w,x,min;
	int dist[n]; 
	int path[n];
	string StartCity,EndCity;
	cout<<"��������ʼվ:"<<endl;
	cin>>StartCity;
	cout<<"�������յ�վ:"<<endl;
	cin>>EndCity;
	int v1=FindCity(StartCity);
	int v2=FindCity(EndCity);
	if(v1!=-1&&v2!=-1)
	{
		cout<<"��ѡ����з�ʽ:"<<endl;
		cout<<"**  1. �г�  **"<<endl;
		cout<<"**  2. ����  **"<<endl;
		cin>>choose; 
		if(choose==1||choose==2)
		{
			for(i=0;i<n;i++)
			{
				dist[i]=getDuration(v1,i,choose);   //�����ʼ�� 
				S[i]=false; 
				if(i!=v1&&dist[i]<maxValue) path[i]=v1;
				else path[i]=-1;
			}
			S[v1]=true; dist[v1]=0;   //����v���붥�㼯�� 
			for(i=0;i<n-1;i++)
			{
				min=maxValue; int u=v1;   //ѡ����S�о������·���ĵ㶥u 
				for(j=0;j<n;j++)
					if(S[j]==false&&dist[j]<min)
					{
						u=j;min=dist[j];
					}
				S[u]=true;     //������u���뼯��S 
				for(k=0;k<n;k++){       //�޸� 
					w=getDuration(u,k,choose);
					x=getTimes(path[u],u,k,choose);
					//if(w<maxValue)
						//cout<<"x="<<x<<endl;
					
					if(S[k]==false&&w<maxValue&&x>0&&dist[u]+w+x<dist[k]){
						//����kδ����S�����ƹ�u��������·�� 
						dist[k]=dist[u]+w+x;
						path[k]=u;   //�޸ĵ�k�����·�� 
					}
				}
			}
			if(dist[v2]<maxValue)
			{
				cout<<"��"<<AddList[v1].cityname<<"��"<<AddList[v2].cityname<<"�ĺ�ʱ���·��Ϊ��"<<endl;
				int *d=new int [MAX_VERTEX_NUM];    //ջ���� 
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
				cout<<"�ܺ�ʱΪ:"<<dist[v2]/60<<"Сʱ"<<dist[v2]%60<<"����"<<endl;
				delete []d;
			}
			else
				cout<<"δ�Һ�ʱ���·����"<<endl;
		}
		else
			cout<<"ѡ��ʽ��������!"<<endl;
	}
	else
		cout<<"Ŀ�ĵػ�����ز����ڣ�"<<endl;
}
/*void TrafficGraph::InitData()
{
	string name[31]={"����","�Ϻ�","���","ʯ��ׯ","̫ԭ","���ͺ���","����","����",
						"������","����","�Ͼ�","�Ϸ�","����","�ϲ�","����","̨��","֣��",
						"�人","��ɳ","����","����","����","����","����","����",
						"����","��³ľ��","�ɶ�","����","����","����"};
	 for(int i=0;i<31;i++)
	 {
	 	InsertCity(name[i]);
	 }
	 //InsertTrain();
	 //InsertFlight();
}*/
//����ͨϵͳ��Ϣд���ļ� 
int TrafficGraph::SaveSysInfo() 
{
    FILE *fp;
	int i,j,total; 
	TrafficNode *p;
    fp=fopen(CityFile,"w"); //�򿪳����ļ� 
    fprintf(fp,"%d\n",Cnum); //��ȡ�ļ��г��и��� 
    for (i=0;i<Cnum;i++) 
	{ //���ζ�ȡ�������� 
		const char *str=AddList[i].cityname.data();   //string����תchar 
        fprintf(fp,"%s\n",str); 
	} 
    fclose(fp);total=0; 
    fp=fopen(TrainFile,"w"); //���г��ļ�
    for (i=0;i<Cnum;i++) 
	{ 
        total+=AddList[i].TrainNum; 
	} 
    fprintf(fp,"%d\n",total); 
    for (i=0;i<Cnum;i++) 
	{ 
        for (p=AddList[i].Tadj;p!=NULL;p=p->link) 
		{ 
			
			const char*a=AddList[i].cityname.data();     //string����תchar 
			const char*b=AddList[p->EndCity].cityname.data();  //string����תchar 
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
//���ļ���Ϣ��ʼ��ϵͳ 
int TrafficGraph::InitSysData()
{ 
    FILE *fp;
    TrafficNode *p;
    char *a,*b,*c;
	a=new char;
	b=new char;
	c=new char;
	int i,j,k,hour1,minute1,num,cost,hour2,minute2; 
    fp=fopen(CityFile,"r"); //�򿪳����ļ� 
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
        fscanf(fp,"%s",p); //��ȡ������ 
		AddList[i].cityname=p;  
	} 
    fclose(fp); 
    fp=fopen(TrainFile,"r");//���г��ļ� 
    if (!fp) 
	{ 
        printf("\nError:Cannot Open Train File...\n"); 
        return -1; 
	} 
    fscanf(fp,"%d",&num); 
    for (i=0;i<num;i++) //�����ļ����г�����������ж�ȡ 
	{ 
		fscanf(fp,"%s",a);//��ȡ�г���� 
        fscanf(fp,"%s",b);//��ȡʼ��վ 
        fscanf(fp,"%s",c);//��ȡ�յ�վ 
		j=FindCity(b); //ʼ��վ�±� 
		k=FindCity(c);
		fscanf(fp,"%d:%d",&hour1,&minute1);
		fscanf(fp,"%d:%d",&hour2,&minute2);
		fscanf(fp,"%d",&cost); 
		InsertTrain(j,k,cost,hour1*60+minute1,hour2*60+minute2,a);
	} 
    fclose(fp); 
    fp=fopen(FlightFile,"r");//�򿪺����ļ�  
    if (!fp) 
	{ 
        printf("\nError:Cannot Open Flight File...\n"); 
        return -1; 
	} 
    fscanf(fp,"%d",&num); 
    for (i=0;i<num;i++) //�����ļ��к������������ж�ȡ 
	{   
        fscanf(fp,"%s",a); //��ȡ������
        fscanf(fp,"%s",b); //��ȡʼ��վ 
        fscanf(fp,"%s",c); //��ȡ�յ�վ
        j=FindCity(b); //ʼ��վ�±� 
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
						cout<<"����Ƿ�������"<<endl;
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
							cout<<"�������������"<<endl;
							cin>>name;
							tr.InsertCity(name);
							tr.SaveSysInfo();
							break;
						case 2:
							cout<<"������Ҫɾ���ĳ�����:"<<endl;
							cin>>name;
							bo=tr.DelCity(name);
							if(bo) cout<<"ɾ���ɹ�!"<<endl;
							else cout<<"ɾ��ʧ��!"<<endl;
							tr.SaveSysInfo();
							break;
						case 3:
							cout<<"1.�г�"<<endl;
							cout<<"2.����"<<endl;
							cin>>c;
							cout<<"��������ʼվ:"<<endl;
							cin>>StartCity;
							cout<<"�������յ�վ:"<<endl;
							cin>>EndCity;
							int i,j;
							i=tr.FindCity(StartCity);//ʼ��վ���б�� 
							j=tr.FindCity(EndCity);  //�յ�վ���б�� 
							if(i>=0&&j>=0)
							{
								cout<<"�����뻨��:"<<endl;
								cin>>TFcost;
								cout<<"����ʱ��(00:00,24Сʱ��):"<<endl;
								cin>>stHour>>ah>>stMinute;
								cout<<"����ʱ��(00:00,24Сʱ��):"<<endl;
								cin>>enHour>>ah>>enMinute;
								while(stHour*60+stMinute>=enHour*60+enMinute)
								{
									cout<<"ʱ�������쳣!����������:"<<endl;
									cout<<"����ʱ��(00:00,24Сʱ��):"<<endl;
									cin>>stHour>>ah>>stMinute;
									cout<<"����ʱ��(00:00,24Сʱ��):"<<endl;
									cin>>enHour>>ah>>enMinute;
								}
								cout<<"�������α��:"<<endl;
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
										cout<<"����Ƿ���"<<endl;
										break;
								 }
								 if(bo) cout<<"����ɹ�!"<<endl;
								 else cout<<"����ʧ��!"<<endl;
								 tr.SaveSysInfo(); 
							}
							else
							{
								cout<<"��ʼվ���յ�վ������!"<<endl;
							}
							break;
						case 4:
							cout<<"1.�г�"<<endl;
							cout<<"2.����"<<endl;
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
									cout<<"����Ƿ���"<<endl;
									break;
							 }
							 if(bo) cout<<"ɾ���ɹ�!"<<endl;
							 else cout<<"ɾ��ʧ��!"<<endl;
							 tr.SaveSysInfo(); 
							break;
						case 5:
							cout<<"������Ҫ������ʼ��վ:"<<endl;
							cin>>name;
							cout<<"1.�г�"<<endl;
							cout<<"2.����"<<endl;
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
									cout<<"����Ƿ���"<<endl;
									break;
							 } 
							break;
						case 6:
							ch='n';
							break;
						default:
							cout<<"����Ƿ�!"<<endl; 
							break;
					}
				}	
				else
				{
					cout<<"�������"<<endl;
					ch='n';
				}	
				system("pause"); 
				system("cls");
			}while(ch=='y'||ch=='Y');
		}
	}while(a!=4);
	return 0;
}





