//B-Tree��ʵ��
#include<iostream>
using namespace std; 
static const int M=3;                  //B������С����
static const int KEY_MAX=2*M-1;        //�ڵ�����ؼ��ֵ�������
static const int KEY_MIN=M-1;          //�Ǹ��ڵ�����ؼ��ֵ���С����
static const int CHILD_MAX=KEY_MAX+1;  //���ӽڵ��������
static const int CHILD_MIN=KEY_MIN+1;  //���ӽڵ����С����
typedef struct Node
{
	bool isLeaf;             //�Ƿ���Ҷ�ӽڵ�
	int keyNum;              //�ڵ�����Ĺؼ�������
	int keyValue[KEY_MAX];     //�ؼ��ֵ�ֵ����
	Node *pChild[CHILD_MAX]; //����ָ������
	Node(bool b=true, int n=0):isLeaf(b), keyNum(n){}
}Node;
class BTree
{
	public:
		BTree();         //���캯�� 
		~BTree();         //�������� 
		bool insert(const int &key);    //��B���в����½��key
		bool deletekey(const int &key);   //��B��ɾ�����key
		void display();//��ӡ���Ĺؼ���
		bool contain(const int &key);   //����key�Ƿ������B����                 
		void clear();    //���B�� 
		void recursive_delete(Node *pNode);   //ɾ����
		void deleteNode(Node *&pNode);//ɾ���ڵ�
		bool search(Node *pNode, const int &key);//���ҹؼ���
		void splitChild(Node *pParent, int nChildIndex, Node *pChild);//�����ӽڵ�
		void insertNonFull(Node *pNode, const int &key);//�ڷ����ڵ��в���ؼ���
		void displayBtree(Node *pNode);	 //��ӡ�� 
		void mergeChild(Node *pParent, int index);//�ϲ������ӽڵ�
	    void recursive_delete(Node *pNode, const int &key);//�ݹ��ɾ���ؼ���
		int getbefore(Node *pNode);//�ҵ�ǰ���ؼ���
		int getafter(Node *pNode);//�ҵ���̹ؼ���
		Node *GetRoot(){ return Root;
		}
	private:
		Node * Root;  //B���ĸ��ڵ�
};
BTree::BTree()           //���캯�� 
{
	Root=new Node;
	Root = NULL;  //����һ�ÿյ�B��
}
BTree::~BTree()            //�������� 
{
	clear();
}
bool BTree::insert(const int &key)    //��B���в����½��key
{
	//���Ͳ���key:�ؼ��ֵ�ֵ 
	if (contain(key))  //���ùؼ����Ƿ��Ѿ�����
	{
		return false;
	}
	else
	{
		if (Root==NULL)//����Ƿ�Ϊ����
		{
			Root=new Node();
		}
		if (Root->keyNum==KEY_MAX) //�����ڵ��Ƿ�����
		{
			Node *pNode = new Node();  //�����µĸ��ڵ�
			pNode->isLeaf = false;
			pNode->pChild[0] = Root;
			splitChild(pNode, 0, Root);      //�����ӽڵ� 
			Root = pNode;  //���¸��ڵ�ָ��
		}
		insertNonFull(Root, key);        //����ؼ��� 
		return true;
	}
}
bool BTree::deletekey(const int &key)    //��B��ɾ�����key
{
	//���Ͳ���key:�ؼ��ֵ�ֵ 
	if (!search(Root, key))  //������
	{
		return false;
	}
	if (Root->keyNum==1)//�����������
	{
		if (Root->isLeaf)
		{
			clear();       //������� 
			return true;
		}
		else
		{
			Node *pChild1 = Root->pChild[0];
			Node *pChild2 = Root->pChild[1];
			if (pChild1->keyNum==KEY_MIN&&pChild2->keyNum==KEY_MIN)
			{
				mergeChild(Root, 0);   //�ϲ������ӽڵ� 
				deleteNode(Root);     //ɾ����� 
				Root = pChild1;     //���¸����ָ�� 
			}
		}
	}
	recursive_delete(Root, key);    //�ݹ��ɾ���ؼ��� 
	return true;
}
void BTree::display() //��ӡ���Ĺؼ���
{
	if(Root!=NULL)
		displayBtree(Root);
	else
		cout<<"������û������!"<<endl;
	
}
bool BTree::contain(const int &key)   //����key�Ƿ������B����
{
	//���Ͳ���key:�ؼ��ֵ�ֵ
	return search(Root, key);
}
void BTree::clear()                      //���B��
{
	recursive_delete(Root);    //ɾ���� 
	Root = NULL;
}
void BTree::recursive_delete(Node *pNode)    //ɾ����
{
	//Node���͵Ĳ���pNode�������ָ�� 
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
void BTree::deleteNode(Node *&pNode)   //ɾ���ڵ�
{
	//Node���͵Ĳ���pNode�������ָ��
	if (pNode!=NULL)
	{
		delete pNode;
		pNode = NULL;
	}
}
bool BTree::search(Node *pNode, const int &key)  //���ҹؼ���
{
	//Node���͵Ĳ���pNode�������ָ�룻���Ͳ���key:�ؼ��ֵ�ֵ 
	if (pNode==NULL)  //���ڵ�ָ���Ƿ�Ϊ�� 
	{
		return false;
	}
	else
	{
		int i;
		for (i=0; i<pNode->keyNum && key>*(pNode->keyValue+i); ++i)//�ҵ�ʹkey<=pNode->keyValue[i]��������С�±�i
		{
		}
		if (i<pNode->keyNum && key==pNode->keyValue[i])
		{
			return true;
		}
		else
		{
			if (pNode->isLeaf)   //���ýڵ��Ƿ�ΪҶ�ӽڵ�
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
void BTree::splitChild(Node *pParent, int nChildIndex, Node *pChild)  //�����ӽڵ�
{
	// Node���͵Ĳ���pParent:���ڵ㣻pChild�����ӽ�㣻���Ͳ���nChildIndex�������±� 
	//��pChild���ѳ�pRightNode��pChild�����ڵ�
	Node *pRightNode = new Node();//���Ѻ���ҽڵ�
	pRightNode->isLeaf = pChild->isLeaf;
	pRightNode->keyNum = KEY_MIN;
	int i;
	for (i=0; i<KEY_MIN; ++i)//�����ؼ��ֵ�ֵ
	{
		pRightNode->keyValue[i] = pChild->keyValue[i+CHILD_MIN];
	}
	if (!pChild->isLeaf)  //�������Ҷ�ӽڵ㣬�������ӽڵ�ָ��
	{
		for (i=0; i<CHILD_MIN; ++i)
		{
			pRightNode->pChild[i] = pChild->pChild[i+CHILD_MIN];
		}
	}
	
	pChild->keyNum = KEY_MIN;  //�����������Ĺؼ��ָ���

	for (i=pParent->keyNum; i>nChildIndex; --i)//�����ڵ��е�nChildIndex������йؼ��ֵ�ֵ������ָ�������һλ
	{
		pParent->pChild[i+1] = pParent->pChild[i];
		pParent->keyValue[i] = pParent->keyValue[i-1];
	}
	++pParent->keyNum;  //���¸��ڵ�Ĺؼ��ָ���
	pParent->pChild[nChildIndex+1] = pRightNode;  //�洢������ָ��
	pParent->keyValue[nChildIndex] = pChild->keyValue[KEY_MIN];//�ѽڵ���м�ֵ�ᵽ���ڵ�
}

//�ڷ����ڵ��в���ؼ���
void BTree::insertNonFull(Node *pNode, const int &key)
{
	// Node���͵Ĳ���pNode�������ָ�룻���Ͳ���key:�ؼ��ֵ�ֵ 
	int i = pNode->keyNum;  //��ȡ�ڵ��ڹؼ��ָ���
	if (pNode->isLeaf)      //pNode��Ҷ�ӽڵ�
	{
		while (i>0&&key<pNode->keyValue[i-1])   //�Ӻ���ǰ�����ҹؼ��ֵĲ���λ��
		{
			pNode->keyValue[i] = pNode->keyValue[i-1];  //�����λ
			--i;
		}
		pNode->keyValue[i] = key;  //����ؼ��ֵ�ֵ
		++pNode->keyNum; //���½ڵ�ؼ��ֵĸ���
	}
	else//pNode���ڽڵ�
	{
		while(i>0&&key<pNode->keyValue[i-1])   //�Ӻ���ǰ�����ҹؼ��ֵĲ��������
			--i;
		Node *pChild = pNode->pChild[i];  //Ŀ���������ָ�� 
		if (pChild->keyNum==KEY_MAX)  //�����ڵ�����
		{
			splitChild(pNode, i, pChild);//���������ڵ�
			if(key>pNode->keyValue[i])   //ȷ��Ŀ������
				pChild = pNode->pChild[i+1];
		}
		insertNonFull(pChild, key);  //����ؼ��ֵ�Ŀ�������ڵ�
	}
}
//��ӡ��
void BTree::displayBtree(Node *pNode)
{
	//Node���͵Ĳ���pNode�������ָ��
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
//�ϲ������ӽڵ�
void BTree::mergeChild(Node *pParent, int index)
{
	//Node���͵Ĳ���pParent�������ָ�룻���Ͳ���index:�ؼ���key���±� 
	Node *pChild1 = pParent->pChild[index];     //�ڵ�pNode��ǰ��key���ӽڵ�
	Node *pChild2 = pParent->pChild[index+1];    //�ڵ�pNode�к���key���ӽڵ�
	//��pChild2���ݺϲ���pChild1
	pChild1->keyNum = KEY_MAX;
	pChild1->keyValue[KEY_MIN] = pParent->keyValue[index];//�����ڵ�index��ֵ����
	int i;
	for (i=0; i<KEY_MIN; ++i)     //�� pChild2��ӵ�pChild1�� 
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

	//���ڵ�ɾ��index��key��index�����ǰ��һλ
	--pParent->keyNum;
	for(i=index; i<pParent->keyNum; ++i)
	{
		pParent->keyValue[i] = pParent->keyValue[i+1];
		pParent->pChild[i+1] = pParent->pChild[i+2];
	}
	deleteNode(pChild2);  //ɾ��pChild2
}
//�ݹ��ɾ���ؼ���
void BTree::recursive_delete(Node *pNode, const int &key)
{
	//Node���͵Ĳ���pNode�������ָ�룻���Ͳ���key:�ؼ��ֵ�ֵ  
	int i=0;
	while(i<pNode->keyNum&&key>pNode->keyValue[i])
		++i;
	if (i<pNode->keyNum&&key==pNode->keyValue[i])//�ؼ���key�ڽڵ�pNode��
	{
		if (pNode->isLeaf)//pNode�Ǹ�Ҷ�ڵ�
		{
			//��pNode��ɾ��key 
			--pNode->keyNum;
			for (; i<pNode->keyNum; ++i)
			{
				pNode->keyValue[i] = pNode->keyValue[i+1];
			}
			return;
		}
		else//pNode�Ǹ��ڽڵ�
		{
			Node *pChildPrev = pNode->pChild[i];//�ڵ�pNode��ǰ��key���ӽڵ�
			Node *pChildNext = pNode->pChild[i+1];//�ڵ�pNode�к���key���ӽڵ�
			if (pChildPrev->keyNum>=CHILD_MIN)//�ڵ�pChildPrev�����ٰ���CHILD_MIN���ؼ���
			{
				int prevKey = getbefore(pChildPrev); //��ȡkey��ǰ���ؼ���
			    recursive_delete(pChildPrev, prevKey);
				pNode->keyValue[i] = prevKey;     //�滻��key��ǰ���ؼ���
				return;
			}
			else if (pChildNext->keyNum>=CHILD_MIN)//�ڵ�pChildNext�����ٰ���CHILD_MIN���ؼ���
			{
				int nextKey = getafter(pChildNext); //��ȡkey�ĺ�̹ؼ���
				recursive_delete(pChildNext, nextKey);
				pNode->keyValue[i] = nextKey;     //�滻��key�ĺ�̹ؼ���
				return;
			}
			else//�ڵ�pChildPrev��pChildNext�ж�ֻ����CHILD_MIN-1���ؼ���
			{
				mergeChild(pNode, i);
				recursive_delete(pChildPrev, key);
			}
		}
	}
	else//�ؼ���key���ڽڵ�pNode��
	{
		Node *pChildNode = pNode->pChild[i];//����key���������ڵ�
		if (pChildNode->keyNum==KEY_MIN)//ֻ��t-1���ؼ���
		{
			Node *pLeft = i>0 ? pNode->pChild[i-1] : NULL;  //���ֵܽڵ�
			Node *pRight = i<pNode->keyNum ? pNode->pChild[i+1] : NULL;//���ֵܽڵ�
			int j;
			if (pLeft&&pLeft->keyNum>=CHILD_MIN)//���ֵܽڵ�������CHILD_MIN���ؼ���
			{
				//���ڵ���i-1�Ĺؼ���������pChildNode��
				for (j=pChildNode->keyNum; j>0; --j)  
				{
					pChildNode->keyValue[j] = pChildNode->keyValue[j-1];
				}
				pChildNode->keyValue[0] = pNode->keyValue[i-1];
				
				if (!pLeft->isLeaf)  
				{
					for (j=pChildNode->keyNum+1; j>0; --j) //pLeft�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��
					{
						pChildNode->pChild[j] = pChildNode->pChild[j-1];
					}
					pChildNode->pChild[0] = pLeft->pChild[pLeft->keyNum];
				}
				++pChildNode->keyNum;
				pNode->keyValue[i] = pLeft->keyValue[pLeft->keyNum-1];//pLeft�ڵ��е����ؼ���������pNode��
				--pLeft->keyNum;
			}
			else if (pRight&&pRight->keyNum>=CHILD_MIN)//���ֵܽڵ�������CHILD_MIN���ؼ���
			{
				//���ڵ���i�Ĺؼ���������pChildNode��
				pChildNode->keyValue[pChildNode->keyNum] = pNode->keyValue[i];
				++pChildNode->keyNum;
				pNode->keyValue[i] = pRight->keyValue[0];//pRight�ڵ��е���С�ؼ���������pNode��
				--pRight->keyNum;
				for (j=0; j<pRight->keyNum; ++j)
				{
					pRight->keyValue[j] = pRight->keyValue[j+1];
				}
				if (!pRight->isLeaf)  
				{
					pChildNode->pChild[pChildNode->keyNum] = pRight->pChild[0];//pRight�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��
				    for (j=0; j<=pRight->keyNum; ++j)
				    {
						pRight->pChild[j] = pRight->pChild[j+1];
				    }
				}
			}
			//�����ֵܽڵ㶼ֻ����CHILD_MIN-1���ڵ�
			else if (pLeft)//�����ֵܺϲ�
			{
				mergeChild(pNode, i-1);
				pChildNode = pLeft;
			}
			else if (pRight)//�����ֵܺϲ�
			{
				mergeChild(pNode, i);
				pChildNode = pRight;
			}
		}
		recursive_delete(pChildNode, key);
	}
}
int BTree::getbefore(Node *pNode)//�ҵ�ǰ���ؼ���
{
	//Node���͵Ĳ���pNode�������ָ��
	while (!pNode->isLeaf)
	{
		pNode = pNode->pChild[pNode->keyNum];
	}
	return pNode->keyValue[pNode->keyNum-1];
}
int BTree::getafter(Node *pNode)//�ҵ���̹ؼ���
{
	//Node���͵Ĳ���pNode�������ָ��
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
		cout<<"**  B_Tree��ʵ�ּ�����   **"<<endl;
		cout<<"**     1.��������        **"<<endl;
		cout<<"**     2.ɾ������        **"<<endl;
		cout<<"**     3.��������        **"<<endl;
		cout<<"**     4.���B_Tree      **"<<endl;
		cout<<"**     5.�˳�ϵͳ        **"<<endl;
		cout<<"��ѡ��:"<<endl;
		cin>>n;
		visit=false;
		switch(n)
		{
			case 1:
				cout<<"���������������:"<<endl;
				cin>>key;
				visit=cb.insert(key);
				if(visit)
					cout<<"����ɹ�!"<<endl;
				else
					cout<<"����ʧ��!"<<endl;
				break;
			case 2:
				cout<<"��������Ҫɾ��������:"<<endl;
				cin>>key;
				visit=cb.deletekey(key);
				if(visit)
					cout<<"ɾ���ɹ�!"<<endl;
				else
					cout<<"ɾ��ʧ��!"<<endl;
				break;
			case 3:
				cout<<"����������ҵ�����:"<<endl;
				cin>>key;
				visit=cb.search(cb.GetRoot(),key);
				if(visit)
					cout<<"���ҳɹ�!"<<endl;
				else
					cout<<"����ʧ��!"<<endl;
				break;
			case 4:
				cb.display();
				break;
			case 5:
				cout<<"�������н���!"<<endl;
				ch='n';
				break;
			default:
				cout<<"�������!!"<<endl;
				break;
		} 
		system("pause");
		system("cls");	
	}while(ch=='y'||ch=='Y');
	return 0;
}
