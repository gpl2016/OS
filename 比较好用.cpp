#include<iostream>
#include<cstdlib>
using namespace std; 
typedef struct PNode{  
	struct PNode *next; //ָ�� 
	char name[10]; 
	int All_Time; 
	int Runed_Time; 
    char state; 
}*Proc; 

	int insert_flag=0;
int ProcNum,insert_num; //�������� 
void InitPCB(Proc &H)//�������� 
{ 
	cout<<"�������������:";
	cin>>ProcNum;
	int Num=ProcNum; 
    H=(Proc)malloc(sizeof(PNode)); 
	H->next=NULL;
    Proc p=H;  
    cout<<"�밴��ʽ���������Ϣ:\n"; 
    while(Num--) 
	{   
		p=p->next=(Proc)malloc(sizeof(PNode)); 
		cout<<"������ ���軨����ʱ�� �Ѿ�����ʱ��"<<endl;
		cin>>p->name>>p->All_Time>>p->Runed_Time;
		p->state='R';
		p->next=NULL;
	}
    p->next=H->next;
}
//void insert_InitPCB(Proc &H)//���ӽ��� 
//{  
//	cout<<"���������ӽ�������:";
//	cin>>insert_num;
//	ProcNum+=insert_num;
//	int Num=insert_num;//ProcNum; 
//  H=(Proc)malloc(sizeof(PNode)); 
//H->next=NULL;
//    Proc p=H; 
//    cout<<"�밴��ʽ���������Ϣ:\n"; 
//    while(Num--) 
//	{ 
//		p=p->next=(Proc)malloc(sizeof(PNode)); 
//		cout<<"������ ���軨����ʱ�� �Ѿ�����ʱ��"<<endl;
//		cin>>p->name>>p->All_Time>>p->Runed_Time;
//		p->state='R';
//		p->next=NULL;
//	}
//    p->next=H->next;
//}
void DispInfo1(Proc H)//��������������� 
{
	Proc p=H->next; 
	do{ 
		if(p->state!='E')
		{
			cout<<"������:"<<p->name<<"\t������ʱ��:"<<p->All_Time<<"\t������ʱ��:"<<p->Runed_Time<<"\t״̬:"<<p->state<<endl;
			p=p->next;
		}
        else p=p->next; 
	}
	while (p!=H->next);

}
void SJP_Simulator1(Proc &H)
{//�������� 
	cout<<endl<<"��ʼ:\n";
	int flag=ProcNum;
    int round=0; 
	Proc p=H->next; 
	Proc H1;
    while(p->All_Time > p->Runed_Time)
	{
		cout<<"�����Ҫ���ӽ���������i,�˳�����e������������������"<<endl; 
		char c=getchar();
		if(c=='i')
		{InitPCB(H1);
		insert_flag++ ;		
		} 
		else if(c=='e')
		exit(0);
		round++;
        cout<<endl<<"��"<<round<<"��"<<p->name<<"����������"<<endl;
        p->Runed_Time++;
		DispInfo1(H); 
		
		if(p->All_Time == p->Runed_Time)
		{
			p->state='E';
			flag--;
			cout<<p->name<<"���̽���,ɾ���ý���!\n";

		}
		p=p->next;
        while(flag && p->All_Time == p->Runed_Time)
			p=p->next;
	}

    cout<<endl<<"���������������!\n";
   
}
void DispInfo(Proc H)//��������������� 
{
	Proc p=H->next; 
	do{ 
		if(p->state!='E')
		{
			cout<<"������:"<<p->name<<"\t������ʱ��:"<<p->All_Time<<"\t������ʱ��:"<<p->Runed_Time<<"\t״̬:"<<p->state<<endl;
			p=p->next;
		}
        else p=p->next; 
	}
	while (p!=H->next);

}
void SJP_Simulator(Proc &H)
{//�������� 
	cout<<endl<<"��ʼ:\n";
	int flag=ProcNum;
    int round=0; 
	Proc p=H->next; 
	Proc H1;
    while(p->All_Time > p->Runed_Time)
	{
		cout<<"�����Ҫ���ӽ���������i,�˳�����e������������������"<<endl; 
		char c=getchar();
		if(c=='i')
		{InitPCB(H1);
		insert_flag++ ;		
		} 
		else if(c=='e')
		exit(0);
		round++;
        cout<<endl<<"��"<<round<<"��"<<p->name<<"����������"<<endl;
        p->Runed_Time++;
		DispInfo(H); 
		
		if(p->All_Time == p->Runed_Time)
		{
			p->state='E';
			flag--;
			cout<<p->name<<"���̽���,ɾ���ý���!\n";

		}
		p=p->next;
        while(flag && p->All_Time == p->Runed_Time)
			p=p->next;
	}
	if(insert_flag!=0)
	{DispInfo1(H1);
	SJP_Simulator1(H1);
	insert_flag--;
	}
	 if(insert_flag==0)
    cout<<endl<<"���������������!\n";
   
}
//void Insert() //��ʱ���ӽ��� 
//{
//	int insert_num;
//	cout<<("���������ӵĽ�����Ŀ");
//	cin>>insert_num;
//	ProcNum+=insert_num;
//	
//}

 
int main( )
{
	Proc H; 
	Proc H1;
    InitPCB(H);
    DispInfo(H);
	SJP_Simulator(H);
	
		system("pause");
//		cout<<"�����Ҫ���ӽ���������i"<<endl; 
//		char c=getchar();
//		if(c=='i')
//		insert_InitPCB(H); 
	return 0; 
}

