//��1 flag������ִ�к������ֶ�����һ�Σ���������ӵ�ʱ���޸�flag����
#include<iostream>
#include<cstdlib>
#define maxnum 50//��������Ŀ 
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
ȫ�ֱ�������
***** */
int ProcNum;
int flag, num, t;
struct PCB pcblist[maxnum];



void InitPCB(Proc &H, Proc &t)
{
	cout << "�������������:";
	cin >> ProcNum;
	int Num = ProcNum;
	H = (Proc)malloc(sizeof(PCB));
	H->next = NULL;
	Proc p = H;
	cout << "�밴��ʽ���������Ϣ:\n";
	while (Num--)
	{
		p = p->next = (Proc)malloc(sizeof(PCB));
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
		if (p->state != 'F')
		{
			cout << "������:" << p->name << "\t������ʱ��:" << p->All_Time << "\t������ʱ��:" << p->Runed_Time << "\t״̬:" << p->state << endl;
			p = p->next;
		}
		else p = p->next;
	} while (p != H->next);
}
void insert_InitPCB(Proc &H, Proc &t)
{
	int insertNum;
	cout << "��������ӽ�������:";
	cin >> insertNum;
	int Num = insertNum;
	Proc q = t;
	cout << "�밴��ʽ���������Ϣ:\n";
	while (Num--)
	{


		q = q->next = (Proc)malloc(sizeof(PCB));
		cout << "������ ���軨����ʱ�� �Ѿ�����ʱ��" << endl;
		cin >> q->name >> q->All_Time >> q->Runed_Time;
		q->state = 'R';
		q->next = NULL;
	}
	q->next = H->next;
	t = q;
	flag += insertNum;
}



void SJP_Simulator(Proc &H, Proc &t) {
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
			p->state = 'F';
			flag--;
			cout << p->name << "���̽���,ɾ���ý���!\n";
		}
		cout << "�����Ҫ���ӽ���������i,��������c" << endl;
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
	cout << endl << "���������������!\n";
}

/************************************************************
*************************************************************
*************************************************************
����Ȩ�����㷨
****************************************************************
*****************************************************************
*****************************************************************/
void init()
{
	int i;
	for (i = 0; i<num; i++)
	{
		cout << "����" << i + 1 << ":" << "������ ����Ȩ ����ʱ�� " << endl;
		cin >> pcblist[i].name >> pcblist[i].pri >> pcblist[i].All_Time;
		pcblist[i].state = 'R';
		getchar();
	}
}

int max_pri_process()
{
	int max = -100;
	int i;
	int key; //key��ʾ��ǰ����Ȩ��ߵĽ��̵�num 
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
		return key;//����Ȩ��ߵĽ��̵�num 
}

void show()
{
	int i;
	cout << endl << "������ ����Ȩ ����ʱ��" << endl;
	cout << "-------------------------------------------------" << endl;
	for (i = 0; i<num; i++)
	{
		//cout<<pcblist[i].ID<<pcblist[i].pri<<pcblist[i].All_Time<<endl;
		printf("%s%6d%8d\n", &pcblist[i].name, pcblist[i].pri, pcblist[i].All_Time);
	}
	cout << "��ʼ!" << endl;
}
int insert()
{
	cout << "�����ӵĽ�����Ŀ" << endl;
	int insert_num;
	cin >> insert_num;
	int count = num + insert_num;

	for (int i = num; i<count; i++)
	{
		cout << "����" << i + 1 << ":" << "������ ����Ȩ ����ʱ�� " << endl;
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

void run()//�������к��� 
{
	int i, j;

	for (j = 0; j<num; j++)
	{
		t += pcblist[j].All_Time;
	}
	cout << endl << "��̬Ϊ" << endl;
	show();
	//	getchar(); 
	for (j = 0; j<t; j++)
	{
		while (max_pri_process() != -1)//�õ�ǰ����Ȩ��ߵĽ���stateΪn 
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
				cout << "�����Ҫ���ӽ���������i,��������c" << endl;
				char m;
				cin >> m;
				if (m == 'i')
					insert();

			}
		}
	}
}
void run2()//�������к��� 
{
	int i, j;

	for (j = 0; j<num; j++)
	{
		t += pcblist[j].All_Time;
	}
	cout << endl << "��̬Ϊ" << endl;
	show();
	getchar();
	for (j = 0; j<t; j++)
	{
		while (max_pri_process() != -1)//�õ�ǰ����Ȩ��ߵĽ���stateΪn 
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
				cout << "�����Ҫ���ӽ���������i,��������c" << endl;
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
/*                       ʱ��Ƭ��ת���ȵ������㷨                     */
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
	cout << "�����������Ŀ" << endl;
	cin >> num;
	init();
	run2();
}

void pri()
{
	cout << "�����������Ŀ" << endl;
	cin >> num;
	init();
	run();
}

/**********************************************************************/
/*                                                                    */
/*                              ����                                  */
/*                                                                    */
/**********************************************************************/
int main()
{
	int way;
	cout << "��ѡ������㷨" << endl;
	cout << "1:ʱ��Ƭ��ת�����㷨" << endl;
	cout << "2:��̬����Ȩ�����㷨" << endl;
	cout << "3:��̬����Ȩ�����㷨" << endl;
	cin >> way;
	switch (way)
	{

	case 1:	time(); break;
	case 2: dp_pri(); break;
	case 3: pri(); break;

	}

	return 0;

}