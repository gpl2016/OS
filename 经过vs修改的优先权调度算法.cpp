#include"stdio.h"
#include"string.h"
#include <iostream>
using namespace std;

#define maxnum 50//��������Ŀ 
int num,t;
typedef struct PCB{
   char name[10]; 
   int All_Time; 
   int pri; //����Ȩ 
   char state; //״̬ R��ʾû������ F��ʾ�Ѿ����н��� 
}; 

struct PCB pcblist[maxnum]; 

void init() 
{ 
	int i; 
    for(i=0;i<num;i++) 
	{ 
        cout<<"����"<<i+1<<":"<<"������ ����Ȩ ����ʱ�� "<<endl;
        cin>>pcblist[i].name>>pcblist[i].pri>>pcblist[i].All_Time;
		pcblist[i].state='R';
		getchar();
	}
}

int max_pri_process()  
{
	int max=-100; 
	int i;  
	int key; //key��ʾ��ǰ����Ȩ��ߵĽ��̵�num 
    for(i=0;i<num;i++) 
	{
		if(pcblist[i].state=='n')   
	       return -1; 
       else
		   if(max<pcblist[i].pri&&pcblist[i].state=='R')
		   {
			   max=pcblist[i].pri;
	           key=i;
		   }
	}
    if(pcblist[key].state=='F')
        return -1;
    else 
        return key;//����Ȩ��ߵĽ��̵�num 
}

void show()
{
	int i; 
	cout<<endl<<"������ ����Ȩ ����ʱ��"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    for(i=0;i<num;i++) 
	{ 
		//cout<<pcblist[i].ID<<pcblist[i].pri<<pcblist[i].All_Time<<endl;
		printf("%s%6d%8d\n",&pcblist[i].name,pcblist[i].pri,pcblist[i].All_Time);
	} 
    cout<<"��ʼ!"<<endl;
}
int insert() 
{ 
	cout<<"�����ӵĽ�����Ŀ"<<endl;
	int insert_num;	
	cin>>insert_num;
	int count=num+insert_num;
	
    for(int i=num;i<count;i++) 
	{ 
        cout<<"����"<<i+1<<":"<<"������ ����Ȩ ����ʱ�� "<<endl;
        cin>>pcblist[i].name>>pcblist[i].pri>>pcblist[i].All_Time;
		pcblist[i].state='R';
		getchar();
	}
	for(int j=num;j<count;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
	num=count;
	
	
}

void run()//�������к��� 
{
	int i,j; 

    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
		cout<<endl<<"��̬Ϊ"<<endl; 
        show(); 
	//	getchar(); 
        for(j=0;j<t;j++) 
		{
			while(max_pri_process()!=-1)//�õ�ǰ����Ȩ��ߵĽ���stateΪn 
			{ 
				pcblist[max_pri_process()].state='n';
			} 
                for(i=0;i<num;i++) 
				{
					if(pcblist[i].state=='n') //
					{  
						pcblist[i].pri-=1; 
						pcblist[i].All_Time--;
						{
							if(pcblist[i].All_Time==0) 
                                pcblist[i].state='F'; 
							else 
							{
								pcblist[i].state='R'; 
								num--;
						}
                        show(); 
						getchar();
						cout<<"�����Ҫ���ӽ���������i,��������c"<<endl; 
						char m;
						cin >> m;
						if (m == 'i')
						insert();
					}
				}
		}
}

int  main()
{
	cout<<"�����������Ŀ"<<endl;
	cin>>num; 	
	init(); 
	run();
}

