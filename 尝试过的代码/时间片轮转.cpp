#include<iostream>
#include<cstdlib>
using namespace std; 
typedef struct PNode{  
	struct PNode *next; //指针 
	char name[10]; 
	int All_Time; 
	int Runed_Time; 
    char state;
	int end_flag; 
}*Proc; 

int ProcNum,insert_num; //进程数量 
void InitPCB(Proc &H)//创建进程 
{ 
	cout<<"请输入进程数量:";
	cin>>ProcNum;
	int Num=ProcNum; 
    H=(Proc)malloc(sizeof(PNode)); 
	H->next=NULL;
    Proc p=H;  
    cout<<"请按格式输入进程信息:\n"; 
    while(Num--) 
	{   
		p=p->next=(Proc)malloc(sizeof(PNode)); 
		cout<<"进程名 所需花费总时间 已经运行时间 是否为最后一个输入的进程(0/1)"<<endl;
		cin>>p->name>>p->All_Time>>p->Runed_Time>>p->end_flag;
		p->state='R';
		p->next=NULL;
	}
    p->next=H->next;
}

//循环单链表的遍历  
void insert_InitPCB(Proc &H)  
{  
    Proc pHead = H->next;   //pHead指向头结点  
    Proc p = pHead->next;   //p指向首节点，第一个有效节点  
  
    while(p != pHead)  //循环链表的终止条件:（p != 头指针）  
    {  
       // printf("%d ", p->data);  
        p = p->next;  
    } 
	cout<<"请输入进程数量:";
	cin>>insert_num;
	int Num=insert_num; 
	ProcNum+=insert_num; 
 //   H=(Proc)malloc(sizeof(PNode)); 
//	H->next=NULL;
  //  Proc p=H;  
    cout<<"请按格式输入进程信息:\n"; 
    while(Num--) 
	{   
		p=p->next=(Proc)malloc(sizeof(PNode)); 
		cout<<"进程名 所需花费总时间 已经运行时间 是否为最后一个输入的进程(0/1)"<<endl;
		cin>>p->name>>p->All_Time>>p->Runed_Time>>p->end_flag;
		p->state='R';
		p->next=NULL;
	}
    p->next=H->next;
  
}  
//void insert_InitPCB(Proc &H)//增加进程 
//{  
//	cout<<"请输入增加进程数量:";
//	cin>>insert_num;
//	ProcNum+=insert_num;
//	int Num=insert_num;//ProcNum; 
//    //H=(Proc)malloc(sizeof(PNode)); 
////	H->next=NULL;W
//    Proc p=(Proc)malloc(sizeof(PNode)); 
//    cout<<"请按格式输入进程信息:\n"; 
//    while(Num--) 
//	{ 
//		p=p->next=(Proc)malloc(sizeof(PNode)); 
//		cout<<"进程名 所需花费总时间 已经运行时间"<<endl;
//		cin>>p->name>>p->All_Time>>p->Runed_Time;
//		p->state='R';
//		p->next=NULL;
//	}
//    p->next=H->next;
//}
void DispInfo(Proc H)//进程运行输出内容 
{
	Proc p=H->next; 
	do{ 
		if(p->state!='E')
		{
			cout<<"进程名:"<<p->name<<"\t总运行时间:"<<p->All_Time<<"\t已运行时间:"<<p->Runed_Time<<"\t状态:"<<p->state<<endl;
			p=p->next;
		}
        else p=p->next; 
	}
	while (p!=H->next);  
}
void SJP_Simulator(Proc &H)
{//进程运行 
	cout<<endl<<"开始:\n";
	int flag=ProcNum;
    int round=0; 
	Proc p=H->next; 
    while(p->All_Time > p->Runed_Time)
	{
		round++;
        cout<<endl<<"第"<<round<<"轮"<<p->name<<"进程运行中"<<endl;
        p->Runed_Time++;
		DispInfo(H); 
	//	system("pause");
		
		if(p->All_Time == p->Runed_Time)
		{
			p->state='E';
			flag--;
			cout<<p->name<<"进程结束,删除该进程!\n";
		}
		
		
		cout<<"如果需要增加进程请输入i"<<endl; 
		char c=getchar();
		if(c=='i')
		insert_InitPCB(H); 
		p=p->next;
        while(flag && p->All_Time == p->Runed_Time)
			p=p->next;
	}
    cout<<endl<<"完成线上所有任务!\n";
}
void Insert() //随时增加进程 
{
	int insert_num;
	cout<<("请输入增加的进程数目");
	cin>>insert_num;
	ProcNum+=insert_num;
	
}

 
int main( )
{
	Proc H; 
    InitPCB(H);
    DispInfo(H);
	SJP_Simulator(H);
		system("pause");
//		cout<<"如果需要增加进程请输入i"<<endl; 
//		char c=getchar();
//		if(c=='i')
//		insert_InitPCB(H); 
	return 0; 
}

