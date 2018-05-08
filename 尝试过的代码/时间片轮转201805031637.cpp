//错1 flag变量在执行函数中又定义了一次，以至于添加的时候修改flag无用
#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct PNode {
	struct PNode *next;
	char name[10];
	int All_Time;
	int Runed_Time;
	char state;
}*Proc;
int ProcNum;
int flag;
void InitPCB(Proc &H,Proc &t)
{
	cout << "请输入进程数量:";
	cin >> ProcNum;
	int Num = ProcNum;
	H = (Proc)malloc(sizeof(PNode));
	H->next = NULL;
	Proc p = H;
	cout << "请按格式输入进程信息:\n";
	while (Num--)
	{
		p = p->next = (Proc)malloc(sizeof(PNode));
		cout << "进程名 所需花费总时间 已经运行时间" << endl;
		cin >> p->name >> p->All_Time >> p->Runed_Time;
		p->state = 'R';
		p->next = NULL;
	}
	t = p;//记录尾部结点 
	p->next = H->next;
}
void DispInfo(Proc H)
{
	Proc p = H->next;
	do {
		if (p->state != 'E')
		{
			cout << "进程名:" << p->name << "\t总运行时间:" << p->All_Time << "\t已运行时间:" << p->Runed_Time << "\t状态:" << p->state << endl;
			p = p->next;
		}
		else p = p->next;
	} while (p != H->next);
}
void insert_InitPCB(Proc &H,Proc &t)
{
	int insertNum;
	cout << "请输入添加进程数量:";
	cin >>insertNum;
	int Num = insertNum;	
	Proc q = t;
	cout << "请按格式输入进程信息:\n";
	while (Num--)
	{


		q = q->next = (Proc)malloc(sizeof(PNode));
		cout << "进程名 所需花费总时间 已经运行时间" << endl;
		cin >> q->name >> q->All_Time >> q->Runed_Time;
		q->state = 'R';
		q->next = NULL;
	}
	q->next = H->next;
	t = q;
	flag+=insertNum; 
}



void SJP_Simulator(Proc &H,Proc &t) {
	cout << endl << "开始:\n";
	flag = ProcNum;
	int round = 0;
	Proc p = H->next;
	while (p->All_Time > p->Runed_Time)
	{
		round++;
		cout << endl << "第" << round << "轮" << p->name << "进程运行中" << endl;
		p->Runed_Time++;
		DispInfo(H);
		if (p->All_Time == p->Runed_Time)
		{
			p->state = 'E';
			flag--;
			cout << p->name << "进程结束,删除该进程!\n";
		}	
		cout<<"如果需要增加进程请输入i,否则输入c"<<endl; 
		char m;
		cin >> m;
		if (m == 'i')
		{
			insert_InitPCB(H,t);
		}
		p = p->next;
		while (flag &&(p->state=='E'))
			p = p->next;
	}
	cout << endl << "完成线上所有任务!\n";
}

int main()
{
	Proc H;
	Proc t;
	InitPCB(H,t);
	DispInfo(H);
	SJP_Simulator(H,t);
}


