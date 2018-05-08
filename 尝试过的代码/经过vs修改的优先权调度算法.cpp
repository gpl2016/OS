#include"stdio.h"
#include"string.h"
#include <iostream>
using namespace std;

#define maxnum 50//最大进程数目 
int num,t;
typedef struct PCB{
   char name[10]; 
   int All_Time; 
   int pri; //优先权 
   char state; //状态 R表示没运行完 F表示已经运行结束 
}; 

struct PCB pcblist[maxnum]; 

void init() 
{ 
	int i; 
    for(i=0;i<num;i++) 
	{ 
        cout<<"进程"<<i+1<<":"<<"进程名 优先权 运行时间 "<<endl;
        cin>>pcblist[i].name>>pcblist[i].pri>>pcblist[i].All_Time;
		pcblist[i].state='R';
		getchar();
	}
}

int max_pri_process()  
{
	int max=-100; 
	int i;  
	int key; //key表示当前优先权最高的进程的num 
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
        return key;//优先权最高的进程的num 
}

void show()
{
	int i; 
	cout<<endl<<"进程名 优先权 运行时间"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    for(i=0;i<num;i++) 
	{ 
		//cout<<pcblist[i].ID<<pcblist[i].pri<<pcblist[i].All_Time<<endl;
		printf("%s%6d%8d\n",&pcblist[i].name,pcblist[i].pri,pcblist[i].All_Time);
	} 
    cout<<"开始!"<<endl;
}
int insert() 
{ 
	cout<<"请增加的进程数目"<<endl;
	int insert_num;	
	cin>>insert_num;
	int count=num+insert_num;
	
    for(int i=num;i<count;i++) 
	{ 
        cout<<"进程"<<i+1<<":"<<"进程名 优先权 运行时间 "<<endl;
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

void run()//进程运行函数 
{
	int i,j; 

    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
		cout<<endl<<"初态为"<<endl; 
        show(); 
	//	getchar(); 
        for(j=0;j<t;j++) 
		{
			while(max_pri_process()!=-1)//置当前优先权最高的进程state为n 
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
						cout<<"如果需要增加进程请输入i,否则输入c"<<endl; 
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
	cout<<"请输入进程数目"<<endl;
	cin>>num; 	
	init(); 
	run();
}

