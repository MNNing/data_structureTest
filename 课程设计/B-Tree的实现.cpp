//B-Tree的实现
#include<iostream>
using namespace std; 
static const int M=3;                  //B树的最小度数
static const int KEY_MAX=2*M-1;        //节点包含关键字的最大个数
static const int KEY_MIN=M-1;          //非根节点包含关键字的最小个数
static const int CHILD_MAX=KEY_MAX+1;  //孩子节点的最大个数
static const int CHILD_MIN=KEY_MIN+1;  //孩子节点的最小个数
typedef struct Node
{
	bool isLeaf;             //是否是叶子节点
	int keyNum;              //节点包含的关键字数量
	int keyValue[KEY_MAX];     //关键字的值数组
	Node *pChild[CHILD_MAX]; //子树指针数组
	Node(bool b=true, int n=0):isLeaf(b), keyNum(n){}
}Node;
class BTree
{
	public:
		BTree();         //构造函数 
		~BTree();         //析构函数 
		bool insert(const int &key);    //向B数中插入新结点key
		bool deletekey(const int &key);   //从B中删除结点key
		void display();//打印树的关键字
		bool contain(const int &key);   //检查该key是否存在于B树中                 
		void clear();    //清空B树 
		void recursive_delete(Node *pNode);   //删除树
		void deleteNode(Node *&pNode);//删除节点
		bool search(Node *pNode, const int &key);//查找关键字
		void splitChild(Node *pParent, int nChildIndex, Node *pChild);//分裂子节点
		void insertNonFull(Node *pNode, const int &key);//在非满节点中插入关键字
		void displayBtree(Node *pNode);	 //打印树 
		void mergeChild(Node *pParent, int index);//合并两个子节点
	    void recursive_delete(Node *pNode, const int &key);//递归的删除关键字
		int getbefore(Node *pNode);//找到前驱关键字
		int getafter(Node *pNode);//找到后继关键字
		Node *GetRoot(){ return Root;
		}
	private:
		Node * Root;  //B树的根节点
};
BTree::BTree()           //构造函数 
{
	Root=new Node;
	Root = NULL;  //创建一棵空的B树
}
BTree::~BTree()            //析构函数 
{
	clear();
}
bool BTree::insert(const int &key)    //向B数中插入新结点key
{
	//整型参数key:关键字的值 
	if (contain(key))  //检查该关键字是否已经存在
	{
		return false;
	}
	else
	{
		if (Root==NULL)//检查是否为空树
		{
			Root=new Node();
		}
		if (Root->keyNum==KEY_MAX) //检查根节点是否已满
		{
			Node *pNode = new Node();  //创建新的根节点
			pNode->isLeaf = false;
			pNode->pChild[0] = Root;
			splitChild(pNode, 0, Root);      //分裂子节点 
			Root = pNode;  //更新根节点指针
		}
		insertNonFull(Root, key);        //插入关键字 
		return true;
	}
}
bool BTree::deletekey(const int &key)    //从B中删除结点key
{
	//整型参数key:关键字的值 
	if (!search(Root, key))  //不存在
	{
		return false;
	}
	if (Root->keyNum==1)//特殊情况处理
	{
		if (Root->isLeaf)
		{
			clear();       //清空树表 
			return true;
		}
		else
		{
			Node *pChild1 = Root->pChild[0];
			Node *pChild2 = Root->pChild[1];
			if (pChild1->keyNum==KEY_MIN&&pChild2->keyNum==KEY_MIN)
			{
				mergeChild(Root, 0);   //合并两个子节点 
				deleteNode(Root);     //删除结点 
				Root = pChild1;     //更新根结点指针 
			}
		}
	}
	recursive_delete(Root, key);    //递归的删除关键字 
	return true;
}
void BTree::display() //打印树的关键字
{
	if(Root!=NULL)
		displayBtree(Root);
	else
		cout<<"空树，没有数据!"<<endl;
	
}
bool BTree::contain(const int &key)   //检查该key是否存在于B树中
{
	//整型参数key:关键字的值
	return search(Root, key);
}
void BTree::clear()                      //清空B树
{
	recursive_delete(Root);    //删除树 
	Root = NULL;
}
void BTree::recursive_delete(Node *pNode)    //删除树
{
	//Node类型的参数pNode：树结点指针 
	if (pNode!=NULL)
	{
		if (!pNode->isLeaf)
		{
			for(int i=0; i<=pNode->keyNum; ++i)
				recursive_delete(pNode->pChild[i]);
		}
		deleteNode(pNode);
	}
}
void BTree::deleteNode(Node *&pNode)   //删除节点
{
	//Node类型的参数pNode：树结点指针
	if (pNode!=NULL)
	{
		delete pNode;
		pNode = NULL;
	}
}
bool BTree::search(Node *pNode, const int &key)  //查找关键字
{
	//Node类型的参数pNode：树结点指针；整型参数key:关键字的值 
	if (pNode==NULL)  //检测节点指针是否为空 
	{
		return false;
	}
	else
	{
		int i;
		for (i=0; i<pNode->keyNum && key>*(pNode->keyValue+i); ++i)//找到使key<=pNode->keyValue[i]成立的最小下标i
		{
		}
		if (i<pNode->keyNum && key==pNode->keyValue[i])
		{
			return true;
		}
		else
		{
			if (pNode->isLeaf)   //检查该节点是否为叶子节点
			{
				return false;
			}
			else
			{
				return search(pNode->pChild[i], key);
			}
		}
	}
}
void BTree::splitChild(Node *pParent, int nChildIndex, Node *pChild)  //分裂子节点
{
	// Node类型的参数pParent:父节点；pChild：孩子结点；整型参数nChildIndex：孩子下标 
	//将pChild分裂成pRightNode和pChild两个节点
	Node *pRightNode = new Node();//分裂后的右节点
	pRightNode->isLeaf = pChild->isLeaf;
	pRightNode->keyNum = KEY_MIN;
	int i;
	for (i=0; i<KEY_MIN; ++i)//拷贝关键字的值
	{
		pRightNode->keyValue[i] = pChild->keyValue[i+CHILD_MIN];
	}
	if (!pChild->isLeaf)  //如果不是叶子节点，拷贝孩子节点指针
	{
		for (i=0; i<CHILD_MIN; ++i)
		{
			pRightNode->pChild[i] = pChild->pChild[i+CHILD_MIN];
		}
	}
	
	pChild->keyNum = KEY_MIN;  //更新左子树的关键字个数

	for (i=pParent->keyNum; i>nChildIndex; --i)//将父节点中的nChildIndex后的所有关键字的值和子树指针向后移一位
	{
		pParent->pChild[i+1] = pParent->pChild[i];
		pParent->keyValue[i] = pParent->keyValue[i-1];
	}
	++pParent->keyNum;  //更新父节点的关键字个数
	pParent->pChild[nChildIndex+1] = pRightNode;  //存储右子树指针
	pParent->keyValue[nChildIndex] = pChild->keyValue[KEY_MIN];//把节点的中间值提到父节点
}

//在非满节点中插入关键字
void BTree::insertNonFull(Node *pNode, const int &key)
{
	// Node类型的参数pNode：树结点指针；整型参数key:关键字的值 
	int i = pNode->keyNum;  //获取节点内关键字个数
	if (pNode->isLeaf)      //pNode是叶子节点
	{
		while (i>0&&key<pNode->keyValue[i-1])   //从后往前，查找关键字的插入位置
		{
			pNode->keyValue[i] = pNode->keyValue[i-1];  //向后移位
			--i;
		}
		pNode->keyValue[i] = key;  //插入关键字的值
		++pNode->keyNum; //更新节点关键字的个数
	}
	else//pNode是内节点
	{
		while(i>0&&key<pNode->keyValue[i-1])   //从后往前，查找关键字的插入的子树
			--i;
		Node *pChild = pNode->pChild[i];  //目标子树结点指针 
		if (pChild->keyNum==KEY_MAX)  //子树节点已满
		{
			splitChild(pNode, i, pChild);//分裂子树节点
			if(key>pNode->keyValue[i])   //确定目标子树
				pChild = pNode->pChild[i+1];
		}
		insertNonFull(pChild, key);  //插入关键字到目标子树节点
	}
}
//打印树
void BTree::displayBtree(Node *pNode)
{
	//Node类型的参数pNode：树结点指针
	if (pNode!=NULL)
	{
		int i;
		for (i=0; i<pNode->keyNum; ++i)
		{
			if (!pNode->isLeaf)
			{
				displayBtree(pNode->pChild[i]);
			}
			cout<<pNode->keyValue[i]<<" ";
		}
	}
}
//合并两个子节点
void BTree::mergeChild(Node *pParent, int index)
{
	//Node类型的参数pParent：树结点指针；整型参数index:关键字key的下标 
	Node *pChild1 = pParent->pChild[index];     //节点pNode中前于key的子节点
	Node *pChild2 = pParent->pChild[index+1];    //节点pNode中后于key的子节点
	//将pChild2数据合并到pChild1
	pChild1->keyNum = KEY_MAX;
	pChild1->keyValue[KEY_MIN] = pParent->keyValue[index];//将父节点index的值下移
	int i;
	for (i=0; i<KEY_MIN; ++i)     //将 pChild2添加到pChild1中 
	{
		pChild1->keyValue[i+KEY_MIN+1] = pChild2->keyValue[i];
	}
	if (!pChild1->isLeaf)
	{
		for (i=0; i<CHILD_MIN; ++i)
		{
			pChild1->pChild[i+CHILD_MIN] = pChild2->pChild[i];
		}
	}

	//父节点删除index的key，index后的往前移一位
	--pParent->keyNum;
	for(i=index; i<pParent->keyNum; ++i)
	{
		pParent->keyValue[i] = pParent->keyValue[i+1];
		pParent->pChild[i+1] = pParent->pChild[i+2];
	}
	deleteNode(pChild2);  //删除pChild2
}
//递归的删除关键字
void BTree::recursive_delete(Node *pNode, const int &key)
{
	//Node类型的参数pNode：树结点指针；整型参数key:关键字的值  
	int i=0;
	while(i<pNode->keyNum&&key>pNode->keyValue[i])
		++i;
	if (i<pNode->keyNum&&key==pNode->keyValue[i])//关键字key在节点pNode中
	{
		if (pNode->isLeaf)//pNode是个叶节点
		{
			//从pNode中删除key 
			--pNode->keyNum;
			for (; i<pNode->keyNum; ++i)
			{
				pNode->keyValue[i] = pNode->keyValue[i+1];
			}
			return;
		}
		else//pNode是个内节点
		{
			Node *pChildPrev = pNode->pChild[i];//节点pNode中前于key的子节点
			Node *pChildNext = pNode->pChild[i+1];//节点pNode中后于key的子节点
			if (pChildPrev->keyNum>=CHILD_MIN)//节点pChildPrev中至少包含CHILD_MIN个关键字
			{
				int prevKey = getbefore(pChildPrev); //获取key的前驱关键字
			    recursive_delete(pChildPrev, prevKey);
				pNode->keyValue[i] = prevKey;     //替换成key的前驱关键字
				return;
			}
			else if (pChildNext->keyNum>=CHILD_MIN)//节点pChildNext中至少包含CHILD_MIN个关键字
			{
				int nextKey = getafter(pChildNext); //获取key的后继关键字
				recursive_delete(pChildNext, nextKey);
				pNode->keyValue[i] = nextKey;     //替换成key的后继关键字
				return;
			}
			else//节点pChildPrev和pChildNext中都只包含CHILD_MIN-1个关键字
			{
				mergeChild(pNode, i);
				recursive_delete(pChildPrev, key);
			}
		}
	}
	else//关键字key不在节点pNode中
	{
		Node *pChildNode = pNode->pChild[i];//包含key的子树根节点
		if (pChildNode->keyNum==KEY_MIN)//只有t-1个关键字
		{
			Node *pLeft = i>0 ? pNode->pChild[i-1] : NULL;  //左兄弟节点
			Node *pRight = i<pNode->keyNum ? pNode->pChild[i+1] : NULL;//右兄弟节点
			int j;
			if (pLeft&&pLeft->keyNum>=CHILD_MIN)//左兄弟节点至少有CHILD_MIN个关键字
			{
				//父节点中i-1的关键字下移至pChildNode中
				for (j=pChildNode->keyNum; j>0; --j)  
				{
					pChildNode->keyValue[j] = pChildNode->keyValue[j-1];
				}
				pChildNode->keyValue[0] = pNode->keyValue[i-1];
				
				if (!pLeft->isLeaf)  
				{
					for (j=pChildNode->keyNum+1; j>0; --j) //pLeft节点中合适的子女指针移植到pChildNode中
					{
						pChildNode->pChild[j] = pChildNode->pChild[j-1];
					}
					pChildNode->pChild[0] = pLeft->pChild[pLeft->keyNum];
				}
				++pChildNode->keyNum;
				pNode->keyValue[i] = pLeft->keyValue[pLeft->keyNum-1];//pLeft节点中的最大关键字上升到pNode中
				--pLeft->keyNum;
			}
			else if (pRight&&pRight->keyNum>=CHILD_MIN)//右兄弟节点至少有CHILD_MIN个关键字
			{
				//父节点中i的关键字下移至pChildNode中
				pChildNode->keyValue[pChildNode->keyNum] = pNode->keyValue[i];
				++pChildNode->keyNum;
				pNode->keyValue[i] = pRight->keyValue[0];//pRight节点中的最小关键字上升到pNode中
				--pRight->keyNum;
				for (j=0; j<pRight->keyNum; ++j)
				{
					pRight->keyValue[j] = pRight->keyValue[j+1];
				}
				if (!pRight->isLeaf)  
				{
					pChildNode->pChild[pChildNode->keyNum] = pRight->pChild[0];//pRight节点中合适的子女指针移植到pChildNode中
				    for (j=0; j<=pRight->keyNum; ++j)
				    {
						pRight->pChild[j] = pRight->pChild[j+1];
				    }
				}
			}
			//左右兄弟节点都只包含CHILD_MIN-1个节点
			else if (pLeft)//与左兄弟合并
			{
				mergeChild(pNode, i-1);
				pChildNode = pLeft;
			}
			else if (pRight)//与右兄弟合并
			{
				mergeChild(pNode, i);
				pChildNode = pRight;
			}
		}
		recursive_delete(pChildNode, key);
	}
}
int BTree::getbefore(Node *pNode)//找到前驱关键字
{
	//Node类型的参数pNode：树结点指针
	while (!pNode->isLeaf)
	{
		pNode = pNode->pChild[pNode->keyNum];
	}
	return pNode->keyValue[pNode->keyNum-1];
}
int BTree::getafter(Node *pNode)//找到后继关键字
{
	//Node类型的参数pNode：树结点指针
	while (!pNode->isLeaf)
	{
		pNode = pNode->pChild[0];
	}
	return pNode->keyValue[0];
}
int main()
{
	BTree cb;
	int n,key; 
	bool visit; 
	char ch='y';
	do{
		cout<<"**  B_Tree的实现及分析   **"<<endl;
		cout<<"**     1.插入数据        **"<<endl;
		cout<<"**     2.删除数据        **"<<endl;
		cout<<"**     3.查找数据        **"<<endl;
		cout<<"**     4.输出B_Tree      **"<<endl;
		cout<<"**     5.退出系统        **"<<endl;
		cout<<"请选择:"<<endl;
		cin>>n;
		visit=false;
		switch(n)
		{
			case 1:
				cout<<"请输入待插入数据:"<<endl;
				cin>>key;
				visit=cb.insert(key);
				if(visit)
					cout<<"插入成功!"<<endl;
				else
					cout<<"插入失败!"<<endl;
				break;
			case 2:
				cout<<"请输入想要删除的数据:"<<endl;
				cin>>key;
				visit=cb.deletekey(key);
				if(visit)
					cout<<"删除成功!"<<endl;
				else
					cout<<"删除失败!"<<endl;
				break;
			case 3:
				cout<<"请输入待查找的数据:"<<endl;
				cin>>key;
				visit=cb.search(cb.GetRoot(),key);
				if(visit)
					cout<<"查找成功!"<<endl;
				else
					cout<<"查找失败!"<<endl;
				break;
			case 4:
				cb.display();
				break;
			case 5:
				cout<<"程序运行结束!"<<endl;
				ch='n';
				break;
			default:
				cout<<"输入错误!!"<<endl;
				break;
		} 
		system("pause");
		system("cls");	
	}while(ch=='y'||ch=='Y');
	return 0;
}
