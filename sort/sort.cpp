#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

const int maxsize = 10;
void menu()//模拟菜单选项
{
	cout << "---------------------------------------------------------" << endl;
	cout << "|       1____________产生待排序数据                     |" << endl;
	cout << "|       2____________简单选择排序                       |" << endl;
	cout << "|       3____________直接插入排序                       |" << endl;
	cout << "|       4____________快速排序                           |" << endl;
	cout << "|       5____________输出排序顺序表                     |" << endl;
	cout << "|       0____________退出系统                           |" << endl;
	cout << "---------------------------------------------------------" << endl;
}


template <class K>    //K为待排序关键字的类型
class Element  //待排序元素
{
private:
	K key;  //待排序关键字
// others……//其它成员
public:
	Element() {}
	Element(K k) { key = k; }
	Element<K>& operator=(Element<K>& x) //赋值运算符重载
	{
		key = x.key;
		return *this;
	}
	int getkey() { return key; }
	void setkey(K k) { key = k; }
	bool operator==(Element<K>& x) { return key == x.key; } //关系运算符重载
	bool operator<=(Element<K>& x) { return key <= x.key; }//关系运算符重载
	bool operator>=(Element<K>& x) { return key >= x.key; } //关系运算符重载
	friend ostream& operator<<(ostream& outs, Element<K>& x)
	{
		outs << x.key;
		return outs;
	}
	friend istream& operator>>(istream& ins, Element<K>& x)
	{
		ins >> x.key;
		return ins;
	}
};



template <class K>
class dataList  //简化的排序顺序表类，
{
private:
	Element<K>* Vector;   //存储排序元素的向量,0号单元不存储数据
	int maxSize;    //向量空间容量
	int currentSize;   //当前表长
public:
	dataList(int maxSz = maxsize) :maxSize(maxSz), currentSize(0)//构造函数
	{
		Vector = new Element<K>[maxSize];
	}
	int Length() { return currentSize; }//返回表长
	void Swap(Element<K>& x, Element<K>& y)//交换
	{
		Element<K>temp = x;
		x = y;
		y = temp;
	}
	Element<K>& operator[](const int& i) { return Vector[i]; }//下标运算重载
	void setNullList() { currentSize = 0; }
	void insert(K e)
	{//显示异常信息
		if (currentSize >= maxSize) throw "上溢";
		currentSize++;
		Element<K>* vernier;
		vernier = Vector + currentSize;
		vernier->setkey(e);
	}
};




template <class K>
void restore(dataList<K>& dest, dataList<K>& source)//数据备份
{
	dest.setNullList();//将表置空
	for (int i = 1; i <= source.Length(); i++)
		dest.insert(source[i].getkey());
}

// （1）	直接插入排序
template <class K>
void InsertSort(dataList<K>& L, int n)//对顺序表L[1~n]直接插入排序
{
	//按排序码 Key 非递减顺序对表进行排序
	Element<K>* temp;  int i, j;
	for (i = 2; i <= L.Length(); i++) {
		temp = &L[i];
		K a = temp->getkey();
		for (j = i; j > 1; j--)  //从后向前顺序比较 
			if (a <= L[j - 1].getkey())
				L[j].setkey(L[j - 1].getkey());
			else break;
		L[j].setkey(a);
	}

}

// （2）	简单选择排序
template <class K>
void SimpleSelectSort(dataList<K>& L, int n)// 对顺序表L[1~n]进行简单选择排序
{
	for (int i = 1; i <= L.Length(); i++) {
		int k = i;      //选择具有最小排序码的对象
		for (int j = i + 1; j <= L.Length(); j++)
			if (L[j] <= L[k])
				k = j;    //当前具最小排序码的对象
		if (k != i)    //对换到第 i 个位置
			L.Swap(L[i], L[k]);
	}
}
// 快速排序

template <class K>
int partation(dataList<K>& L, int start, int last)//对L[start~last]进行快速排序的一次划分
{
	int pivotpos = start;                        //基准位置
	Element<K>* pivot = &L[start];
	for (int i = start + 1; i <= last; i++)
		if (L[i].getkey() < pivot->getkey())
		{
			pivotpos++;
			if (pivotpos != i)
				L.Swap(L[pivotpos], L[i]);
		}   //小于基准对象的交换到区间的左侧去
	L.Swap(L[start], L[pivotpos]);
	return pivotpos;
}
template <class K>
void QuickSort(dataList<K>& L, int start, int last)//对L[start~last]进行快速排序
{//在序列 leftright 中递归地进行快速排序
	if (start < last) {
		int pivotpos = partation(L, start, last);    //划分
			//对左序列同样处理
		QuickSort(L, start, pivotpos - 1);
		//对右序列同样处理
		QuickSort(L, pivotpos + 1, last);
	}
}
template <class K>
void QuickSort(dataList<K>& L)//快速排序
{
	QuickSort(L, 1, L.Length());   //对L[1~n]进行快速排序
}





template <class K>
void print(dataList<K>& L)
{
	for (int i = 1; i < maxsize + 1; i++)
		cout << L[i] << " ";

}


int main()
{
	srand(time(NULL));
	dataList<int>L(maxsize + 1);
	dataList<int>backupList(maxsize + 1);
	menu();
	while (1)
	{
		int select;
		cout << "请输入您的选择：";
		; cin >> select;
		switch (select)
		{
		case 1:
		{	//产生待排序数据
			L.setNullList();//将原表置空
			backupList.setNullList();//将备份表置空
			for (int i = 1; i <= maxsize; i++)//产生待排序顺序表的元素
			{
				Element<int> elem(rand() % 100);
				L.insert(elem.getkey());  //在表尾插入;
			}
			cout << "创建后数据："; print(L);
			restore(backupList, L);   //数据备份
			break;
		}
		case 2:
			restore(L, backupList);   //数据恢复
			cout << "排序前数据："; print(L); cout << endl;
			SimpleSelectSort(L, 10);//简单选择排序
			cout << "排序后数据："; print(L);
			break;
		case 3:
			restore(L, backupList);  //数据恢复
			cout << "排序前数据："; print(L); cout << endl;
			InsertSort(L, 10);//直接插入排序
			cout << "排序后数据："; print(L);
			break;
		case 4:
			restore(L, backupList);  //数据恢复
			cout << "排序前数据："; print(L); cout << endl;
			QuickSort(L);//快速排序
			cout << "排序后数据："; print(L);
			break;
		case 5:
			cout << "待排顺序表："; print(L);//输出排序表
			break;
		case 0:
			system("pause");
			return 1;
		default:
			cout << endl << "您输入的选项有误，请重新输入：";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
