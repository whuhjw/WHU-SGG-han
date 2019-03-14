
/*****************************************************************************************/
#include <stdafx.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>//输入/输出文件流类
using namespace std;
const int Maxr=100;//最多的读者
const int Maxb=100;//最多的图书
const int Maxbor=5;//每位读者最多借五本书
//读者类,实现对读者的信息的描述


class Reader       
{   
    private:
	int tag;  //删除标记 1:已删 0:未删
	int no;   //读者编号
	char name[10];  //读者姓名
	int borbook[Maxbor];//所借图书
    public:
		Reader() {}
    	char *getname() {return name;}      //获取姓名
		int gettag() {return tag;}         //获取删除标记
	    int getno() {return no;}           //获取读者编号
    	void setname(char na[])            //设置姓名
		{ 
		   strcpy(name,na);
		
		}
	void delreader(){  tag=1;  }//设置删除标记 1:已删 0:未删
	void addreader(int n,char *na)//增加读者
	{ 
		tag=0;
		no=n;
		strcpy(name,na);
		for(int i=0;i<Maxbor;i++)
			borbook[i]=0;
	}
	void borrowbook(int bookid)//借书操作
	{
		for(int i=0;i<Maxbor;i++)
		{ 
			if (borbook[i]==0)
			{
				borbook[i]=bookid;
				return;
				
			}
		}
		
	}
	int retbook(int bookid)//还书操作
	{ 
		for(int i=0;i<Maxbor;i++)
		{ 
			if(borbook[i]==bookid)
			{
			borbook[i]=0;
			return 1;
			
			}
		}
		return 0;
	}
	void disp()//读出读者信息
	{ 
		cout << setw(5) << no <<setw(10) << name<<"借书编号：[";
		for(int i=0;i<Maxbor;i++)
			if(borbook[i]!=0)
				cout << borbook[i] << "|";
		cout << "]"<<endl;
			
	}
};



//读者类库，实现建立读者的个人资料
 class RDatabase
{  
private:
   int top;       //读者记录指针
   Reader read[Maxr];//读者记录
public:
	RDatabase()   //构造函数，将reader.txt读到read[]中
	{
		Reader s;
		top=-1;
		fstream file("reader.txt",ios::in);//打开一个输入文件
		while (1)
		{
			file.read((char *)&s,sizeof(s));
			if (!file)break;
			top++;
			read[top]=s;
		}
		file.close();     //关闭 reader.txt
	}
    void clear()//删除所有读者信息
	{
		top=-1;
	}
	int addreader(int n,char *na)//添加读者时先查找是否存在
	{
		Reader *p=query(n);
		if (p==NULL)
		{
		  top++;
		  read[top].addreader(n,na);
		  return 1;
		}
		return 0;

	}
	Reader *query(int readerid)//按编号查找
	{
		for (int i=0;i<=top;i++)
			if (read[i].getno()==readerid && 
			read[i].gettag()==0)
			{
				return &read[i];
			}
			return NULL;
	}
	void disp()  //输出所有读者信息
	{
           for (int i=0;i<=top;i++)
			   read[i].disp();
	}
	void readerdata();//读者库维护
	~RDatabase()  //析构函数，将read[]写到reader.txt文件中
	{
		fstream file("reader.txt",ios::out);
        for (int i=0;i<=top;i++)
			if (read[i].gettag()==0)
				file.write((char *)&read[i],sizeof(read[i]));
			file.close();

	}
};
void RDatabase::readerdata()
{

    char choice;
	char rname[20];
	int readerid;
	Reader *r;
	while (choice!='0')
	{
        cout <<"\n\n\*************    读  者  维  护  ************** \n\n\n\t\t 1   新      增\n\n\t\t 2   更      改\n\n\t\t 3   删      除\n\n\t\t 4   查      找\n\n\t\t 5   显      示\n\n\t\t 6   全      删\n\n\t\t 0   退      出"<<endl;
		cin >> choice;
		switch (choice)
		{
            case '1':
				cout << "输入读者编号:";
				cin >> readerid;
				cout << "输入读者姓名:";
				cin >> rname;
				addreader (readerid,rname);
				cout<<"添加成功！"<<endl; 
				break;
            case '2':
				cout << "输入读者编号:";
				cin >> readerid;
				r=query(readerid);
				if (r==NULL)
				{
					cout << " 该读者不存在  "<<endl;
				    break;
				}
				cout << "输入新的姓名:";
				cin >> rname;
				r->setname(rname);
			 	break;
            case '3':
				   	cout << " 输入读者编号:";
                    cin >> readerid;
					r=query(readerid);
					if (r==NULL)
					{
					    cout <<" 该读者不存在" << endl;
					    break;
					}
					r->delreader();
					break;
			case '4':
				cout << "读入读者编号:";
				cin >> readerid;
				r=query(readerid);
				if (r==NULL)
				{
					cout <<"该读者不存在"<< endl;
					break;
				}
				cout<<"查找成功！详细信息如下："<<endl; 
				r->disp();
				break;
			case '5':
				disp();
				break;
			case '6':
				clear();
				break;
			default:cout<<"输入错误，请从新输入：";break;
		}
	}
}






//图书类，实现对图书的描述，图书的编号，书名，借出，还入等
class Book
{
private:
    int tag;//删除标记 1:已删 0:未删
	int no;//图书编号
	char name[20];//书名
	int onshelf;//是否再架 1:再架 2:已借
public:
	Book(){}
	char *getname() { return name; }//获取姓名
	int getno(){ return no; }//获取图书编号
	int gettag(){ return tag; }//获取删除标记
	void setname(char na[])//设置书名
	{
		strcpy(name,na);
	}
	void delbook(){ tag=1;}//删除图书
	void addbook(int n,char *na)//增加图书
	{
		tag=0;
		no=n;
		strcpy(name,na);
		onshelf=1;
	}
	int borrowbook()//借书操作
	{
		if (onshelf==1)
		{
			onshelf=0;
			return 1;
		}
		return 0;
	}
	void retbook()//还书操作
	{
		onshelf=1;
	}
	void disp()//输出图书
	{
		cout << setw(6) << no << setw(18) << name << setw(10)
			<<(onshelf==1? "可借":"已借") <<endl;
	}
};






//图书库类，实现对图书的维护，查找，删除等
class BDatabase
{
private:
    int top;         //图书记录指针
	Book book[Maxb]; //图书记录
public:
	BDatabase()//构造函数，将book.txt读到book[]中
	{ 
			Book b;
			top=-1;
			fstream file("book.txt",ios::in);
			while (1)
			{
				file.read((char *)&b,sizeof(b));
				if (!file) break;
				top++;
				book[top]=b;
			}
			file.close();
	}
    void clear()//全删
	{
		top=-1;
	}
    int addbook(int n,char *na)//增加图书
	{
		Book *p=query(n);
		if (NULL==p)
		{
			top++;
			book[top].addbook(n,na);
			return 1;
		}
		return 0;
	}
	Book *query(int bookid)//查找图书
	{
		for (int i=0;i<=top;i++)
			if (book[i].getno()==bookid &&book[i].gettag()==0)
			{	
				return &book[i];
			}
			return NULL;
	}
	void bookdata();//图书库维护
	void disp()
	{
	  for (int i=0;i<=top;i++)
		  if (book[i].gettag()==0)
			  book[i].disp();
	}
	~BDatabase()//析构函数，将book[]写到book.txt文件中
	{
		fstream file("book.txt",ios::out);
        for (int i=0;i<=top;i++)
			if (book[i].gettag()==0)
				file.write((char *)&book[i],sizeof(book[i]));
			file.close();
	}
};
void BDatabase::bookdata()
{
    char choice;
	char bname[40];
	int bookid;
	Book *b;
	while (choice!='0')
	{
		cout <<"\n\n\n\*************    图  书  维  护  ************** "<<endl<<endl;
		cout<<"\t\t1   新     增\n \t\t2   更     改\n\t\t3   删     除\n\t\t4   查     找\n\t\t5   显     示\n\t\t6   全     删\n\t\t0   退     出"<<endl;
        cout<<"请选择操作：";
		cin >> choice;
		switch (choice)
		{
            case '1':
				cout << "输入图书编号:"<<endl;
				cin >> bookid;
                cout << "输入图书书名:"<<endl;
				cin >> bname;
				addbook(bookid,bname);
				cout<<"添加成功！";
				break;
            case '2':
				cout << "输入图书编号:"<<endl;
				cin >> bookid;
				b=query(bookid);
				if (b==NULL)
				{
					cout << " 该图书不存在  "<<endl;
				    break;
				}
				cout << "输入新的书名:"<<endl;
				cin >> bname;
				b->setname(bname);
			 	break;
            case '3':
				   	cout <<"请输入要删除的图书编号:"<<endl;
                    cin >> bookid;
					b=query(bookid);
					if (b==NULL)
					{
					    cout <<" 该图书不存在" << endl;
					    break;
					}
					b->delbook();
					break;
			case '4':
				cout << "请输入要查找的图书编号:"<<endl;
				cin >> bookid;
				b=query(bookid);
				if (b==NULL)
				{
					cout <<"  该图书不存在"<< endl;
					break;
				}
				cout<<"查找成功！详细信息如下：" <<endl;
				b->disp();
				break;
			case '5':
				disp();
				break;
			case '6':
				clear();
				break;
			default:cout<<"输入错误，请从新输入:";
		}
	}
}



//main() 函数的实现，程序的主界面的引导

int main()
{    
	char choice;
	int bookid,readerid;
	RDatabase ReaderDB;
	Reader *r;
	BDatabase BookDB;
	Book *b;
	while(choice!='0')
	{       
			cout <<endl<<endl<<"*************    图  书  管  理  系  统  **************\n\n\n";

		    
			cout <<"\t\t\t1    借       书\n\n\t\t\t2    还       书 \n\n\t\t\t3    图 书 管 理\n\n\t\t\t4    读 者 管 理\n\n\t\t\t0    离       开"<<endl;
			cout <<endl<<endl<<"*******************************************************\n\n\n";
            cout<<"请选择需要进行的操作序号：";
            cin >> choice;
			switch (choice)
			{
			case '1':
				cout <<"  借书\n请输入读者编号:"<<endl;
				cin >>readerid;
				cout <<"请输入图书编号："<<endl;
				cin >>bookid;
				r=ReaderDB.query(readerid);//按编号查找
				if (NULL==r)
				{
					cout <<"  不存在该读者，不能借书"<< endl;
					break;
				}
				b=BookDB.query(bookid);
				if (b==NULL)
				{
					cout <<"  不存在该图书，不能借书"<< endl;
					break;
				}
				if (b->borrowbook()==0)
				{
					cout << "  该图书已借出，不能借书"<< endl;
					break;
				}
				r->borrowbook(b->getno());
				cout<<"借书成功！"<<endl;
				break;
			case '2':
				cout<<"还书\n请输入读者编号:";
				cin >>readerid;
				cout << "请输入图书编号:";
				cin >>bookid;
				r=ReaderDB.query(readerid);
				if (r==NULL)
				{
					cout <<" 不存在该读者，不能还书" << endl;
					break;
				}
				b=BookDB.query(bookid);
				if (b==NULL)
				{
					cout <<"  不存在该图书，不能还书" <<endl;
					break;
				}
				b->retbook();
				r->retbook(b->getno());
				cout<<"还书成功！"<<endl;				
				break;
			case '3':
					BookDB.bookdata();
					break;
			case '4':
				    ReaderDB.readerdata();
				    break;
			default:cout<<"输入错误，请从新输入：";

			}
	}
}
