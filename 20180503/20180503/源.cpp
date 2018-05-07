//错1 flag变量在执行函数中又定义了一次，以至于添加的时候修改flag无用
#include<iostream>
#include<cstdlib>
#define maxnum 50//最大进程数目 
using namespace std;
typedef struct PCB {
	struct PCB *next;
	char name[10];
	int All_Time;
	int Runed_Time;
	int pri;
	char state;
}*Proc;


/****
全局变量定义
***** */
int ProcNum;
int flag, num, t;
struct PCB pcblist[maxnum];



void InitPCB(Proc &H, Proc &t)
{
	cout << "请输入进程数量:";
	cin >> ProcNum;
	int Num = ProcNum;
	H = (Proc)malloc(sizeof(PCB));
	H->next = NULL;
	Proc p = H;
	cout << "请按格式输入进程信息:\n";
	while (Num--)
	{
		p = p->next = (Proc)malloc(sizeof(PCB));
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
		if (p->state != 'F')
		{
			cout << "进程名:" << p->name << "\t总运行时间:" << p->All_Time << "\t已运行时间:" << p->Runed_Time << "\t状态:" << p->state << endl;
			p = p->next;
		}
		else p = p->next;
	} while (p != H->next);
}
void insert_InitPCB(Proc &H, Proc &t)
{
	int insertNum;
	cout << "请输入添加进程数量:";
	cin >> insertNum;
	int Num = insertNum;
	Proc q = t;
	cout << "请按格式输入进程信息:\n";
	while (Num--)
	{


		q = q->next = (Proc)malloc(sizeof(PCB));
		cout << "进程名 所需花费总时间 已经运行时间" << endl;
		cin >> q->name >> q->All_Time >> q->Runed_Time;
		q->state = 'R';
		q->next = NULL;
	}
	q->next = H->next;
	t = q;
	flag += insertNum;
}



void SJP_Simulator(Proc &H, Proc &t) {
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
			p->state = 'F';
			flag--;
			cout << p->name << "进程结束,删除该进程!\n";
		}
		cout << "如果需要增加进程请输入i,否则输入c" << endl;
		char m;
		cin >> m;
		if (m == 'i')
		{
			insert_InitPCB(H, t);
		}
		p = p->next;
		while (flag && (p->state == 'F'))
			p = p->next;
	}
	cout << endl << "完成线上所有任务!\n";
}

/************************************************************
*************************************************************
*************************************************************
优先权调度算法
****************************************************************
*****************************************************************
*****************************************************************/
void init()
{
	int i;
	for (i = 0; i<num; i++)
	{
		cout << "进程" << i + 1 << ":" << "进程名 优先权 运行时间 " << endl;
		cin >> pcblist[i].name >> pcblist[i].pri >> pcblist[i].All_Time;
		pcblist[i].state = 'R';
		getchar();
	}
}

int max_pri_process()
{
	int max = -100;
	int i;
	int key; //key表示当前优先权最高的进程的num 
	for (i = 0; i<num; i++)
	{
		if (pcblist[i].state == 'n')
			return -1;
		else
			if (max<pcblist[i].pri&&pcblist[i].state == 'R')
			{
				max = pcblist[i].pri;
				key = i;
			}
	}
	if (pcblist[key].state == 'F')
		return -1;
	else
		return key;//优先权最高的进程的num 
}

void show()
{
	int i;
	cout << endl << "进程名 优先权 运行时间" << endl;
	cout << "-------------------------------------------------" << endl;
	for (i = 0; i<num; i++)
	{
		//cout<<pcblist[i].ID<<pcblist[i].pri<<pcblist[i].All_Time<<endl;
		printf("%s%6d%8d\n", &pcblist[i].name, pcblist[i].pri, pcblist[i].All_Time);
	}
	cout << "开始!" << endl;
}
int insert()
{
	cout << "请增加的进程数目" << endl;
	int insert_num;
	cin >> insert_num;
	int count = num + insert_num;

	for (int i = num; i<count; i++)
	{
		cout << "进程" << i + 1 << ":" << "进程名 优先权 运行时间 " << endl;
		cin >> pcblist[i].name >> pcblist[i].pri >> pcblist[i].All_Time;
		pcblist[i].state = 'R';
		getchar();
	}
	for (int j = num; j<count; j++)
	{
		t += pcblist[j].All_Time;
	}
	num = count;

	return 0;
}

void run()//进程运行函数 
{
	int i, j;

	for (j = 0; j<num; j++)
	{
		t += pcblist[j].All_Time;
	}
	cout << endl << "初态为" << endl;
	show();
	//	getchar(); 
	for (j = 0; j<t; j++)
	{
		while (max_pri_process() != -1)//置当前优先权最高的进程state为n 
		{
			pcblist[max_pri_process()].state = 'n';
		}
		for (i = 0; i<num; i++)
		{
			if (pcblist[i].state == 'n') //
			{
				pcblist[i].pri -= 1;
				pcblist[i].All_Time--;
				{
					if (pcblist[i].All_Time == 0)
						pcblist[i].state = 'F';
					else
					{
						pcblist[i].state = 'R';
						num--;
					}
				}
				show();
				getchar();
				cout << "如果需要增加进程请输入i,否则输入c" << endl;
				char m;
				cin >> m;
				if (m == 'i')
					insert();

			}
		}
	}
}
void run2()//进程运行函数 
{
	int i, j;

	for (j = 0; j<num; j++)
	{
		t += pcblist[j].All_Time;
	}
	cout << endl << "初态为" << endl;
	show();
	getchar();
	for (j = 0; j<t; j++)
	{
		while (max_pri_process() != -1)//置当前优先权最高的进程state为n 
		{
			pcblist[max_pri_process()].state = 'n';
		}
		for (i = 0; i<num; i++)
		{
			if (pcblist[i].state == 'n') //
			{
				//pcblist[i].pri-=1; 
				pcblist[i].All_Time--;
				{
					if (pcblist[i].All_Time == 0)
						pcblist[i].state = 'F';
					else
					{
						pcblist[i].state = 'R';
						num--;
					}
				}
				show();
				//	getchar();
				cout << "如果需要增加进程请输入i,否则输入c" << endl;
				char m;
				cin >> m;
				if (m == 'i')
					insert();

			}
		}
	}
}
/**********************************************************************/
/*                                                                    */
/*                       时间片轮转调度等三种算法                     */
/*                                                                    */
/**********************************************************************/
void time()
{
	Proc H;
	Proc t;
	InitPCB(H, t);
	DispInfo(H);
	SJP_Simulator(H, t);
}
void dp_pri()
{
	cout << "请输入进程数目" << endl;
	cin >> num;
	init();
	run2();
}

void pri()
{
	cout << "请输入进程数目" << endl;
	cin >> num;
	init();
	run();
}

/**********************************************************************/
/*                                                                    */
/*                              测试                                  */
/*                                                                    */
/**********************************************************************/
int main()
{
	int way;
	cout << "请选择调度算法" << endl;
	cout << "1:时间片轮转调度算法" << endl;
	cout << "2:静态优先权调度算法" << endl;
	cout << "3:动态优先权调度算法" << endl;
	cin >> way;
	switch (way)
	{

	case 1:	time(); break;
	case 2: dp_pri(); break;
	case 3: pri(); break;

	}

	return 0;

}