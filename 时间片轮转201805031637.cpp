//��1 flag������ִ�к������ֶ�����һ�Σ���������ӵ�ʱ���޸�flag����
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
	cout << "�������������:";
	cin >> ProcNum;
	int Num = ProcNum;
	H = (Proc)malloc(sizeof(PNode));
	H->next = NULL;
	Proc p = H;
	cout << "�밴��ʽ���������Ϣ:\n";
	while (Num--)
	{
		p = p->next = (Proc)malloc(sizeof(PNode));
		cout << "������ ���軨����ʱ�� �Ѿ�����ʱ��" << endl;
		cin >> p->name >> p->All_Time >> p->Runed_Time;
		p->state = 'R';
		p->next = NULL;
	}
	t = p;//��¼β����� 
	p->next = H->next;
}
void DispInfo(Proc H)
{
	Proc p = H->next;
	do {
		if (p->state != 'E')
		{
			cout << "������:" << p->name << "\t������ʱ��:" << p->All_Time << "\t������ʱ��:" << p->Runed_Time << "\t״̬:" << p->state << endl;
			p = p->next;
		}
		else p = p->next;
	} while (p != H->next);
}
void insert_InitPCB(Proc &H,Proc &t)
{
	int insertNum;
	cout << "��������ӽ�������:";
	cin >>insertNum;
	int Num = insertNum;	
	Proc q = t;
	cout << "�밴��ʽ���������Ϣ:\n";
	while (Num--)
	{


		q = q->next = (Proc)malloc(sizeof(PNode));
		cout << "������ ���軨����ʱ�� �Ѿ�����ʱ��" << endl;
		cin >> q->name >> q->All_Time >> q->Runed_Time;
		q->state = 'R';
		q->next = NULL;
	}
	q->next = H->next;
	t = q;
	flag+=insertNum; 
}



void SJP_Simulator(Proc &H,Proc &t) {
	cout << endl << "��ʼ:\n";
	flag = ProcNum;
	int round = 0;
	Proc p = H->next;
	while (p->All_Time > p->Runed_Time)
	{
		round++;
		cout << endl << "��" << round << "��" << p->name << "����������" << endl;
		p->Runed_Time++;
		DispInfo(H);
		if (p->All_Time == p->Runed_Time)
		{
			p->state = 'E';
			flag--;
			cout << p->name << "���̽���,ɾ���ý���!\n";
		}	
		cout<<"�����Ҫ���ӽ���������i,��������c"<<endl; 
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
	cout << endl << "���������������!\n";
}

int main()
{
	Proc H;
	Proc t;
	InitPCB(H,t);
	DispInfo(H);
	SJP_Simulator(H,t);
}


