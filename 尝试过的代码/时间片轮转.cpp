#include<iostream>
#include<cstdlib>
using namespace std; 
typedef struct PNode{  
	struct PNode *next; //ָ�� 
	char name[10]; 
	int All_Time; 
	int Runed_Time; 
    char state;
	int end_flag; 
}*Proc; 

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
		cout<<"������ ���軨����ʱ�� �Ѿ�����ʱ�� �Ƿ�Ϊ���һ������Ľ���(0/1)"<<endl;
		cin>>p->name>>p->All_Time>>p->Runed_Time>>p->end_flag;
		p->state='R';
		p->next=NULL;
	}
    p->next=H->next;
}

//ѭ��������ı���  
void insert_InitPCB(Proc &H)  
{  
    Proc pHead = H->next;   //pHeadָ��ͷ���  
    Proc p = pHead->next;   //pָ���׽ڵ㣬��һ����Ч�ڵ�  
  
    while(p != pHead)  //ѭ���������ֹ����:��p != ͷָ�룩  
    {  
       // printf("%d ", p->data);  
        p = p->next;  
    } 
	cout<<"�������������:";
	cin>>insert_num;
	int Num=insert_num; 
	ProcNum+=insert_num; 
 //   H=(Proc)malloc(sizeof(PNode)); 
//	H->next=NULL;
  //  Proc p=H;  
    cout<<"�밴��ʽ���������Ϣ:\n"; 
    while(Num--) 
	{   
		p=p->next=(Proc)malloc(sizeof(PNode)); 
		cout<<"������ ���軨����ʱ�� �Ѿ�����ʱ�� �Ƿ�Ϊ���һ������Ľ���(0/1)"<<endl;
		cin>>p->name>>p->All_Time>>p->Runed_Time>>p->end_flag;
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
//    //H=(Proc)malloc(sizeof(PNode)); 
////	H->next=NULL;W
//    Proc p=(Proc)malloc(sizeof(PNode)); 
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
    while(p->All_Time > p->Runed_Time)
	{
		round++;
        cout<<endl<<"��"<<round<<"��"<<p->name<<"����������"<<endl;
        p->Runed_Time++;
		DispInfo(H); 
	//	system("pause");
		
		if(p->All_Time == p->Runed_Time)
		{
			p->state='E';
			flag--;
			cout<<p->name<<"���̽���,ɾ���ý���!\n";
		}
		
		
		cout<<"�����Ҫ���ӽ���������i"<<endl; 
		char c=getchar();
		if(c=='i')
		insert_InitPCB(H); 
		p=p->next;
        while(flag && p->All_Time == p->Runed_Time)
			p=p->next;
	}
    cout<<endl<<"���������������!\n";
}
void Insert() //��ʱ���ӽ��� 
{
	int insert_num;
	cout<<("���������ӵĽ�����Ŀ");
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
//		cout<<"�����Ҫ���ӽ���������i"<<endl; 
//		char c=getchar();
//		if(c=='i')
//		insert_InitPCB(H); 
	return 0; 
}

