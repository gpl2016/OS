#include"stdio.h"
#include"string.h"
#include <iostream>
using namespace std;

#define num 4  //假定系统中进程个数为5

struct PCB{
   char ID; 
   int runtime; 
   int pri; 
   char state;  
}; 

struct PCB pcblist[num];

void init() 
{ 
	int i; 
    for(i=0;i<num;i++) 
	{ 
        printf("进程%d:进程名 优先权 运行时间 \n",i+1);
		scanf("%s%d%d",&pcblist[i].ID,&pcblist[i].pri,&pcblist[i].runtime);
		pcblist[i].state='R';
		getchar();
	}
}

int max_pri_process()  
{
	int max=-100; 
	int i;  
	int key; 
    for(i=0;i<num;i++) 
	{
		if(pcblist[i].state=='r')   
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
        return key;
}

void show()
{
	int i; 
    printf("\n 进程名 优先权 运行时间\n"); 
    printf("-------------------------------------------------\n"); 
    for(i=0;i<num;i++) 
	{ 
		printf("%s%6d%8d\n",&pcblist[i].ID,pcblist[i].pri,pcblist[i].runtime);
	} 
    printf("开始!\n");
}

void run()
{
	int i,j; 
    int t=0; 
    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].runtime;}
	    printf("\n 初态为:\n"); 
        show(); 
		getchar(); 
        for(j=0;j<t;j++) 
		{
			while(max_pri_process()!=-1)
			{ 
				pcblist[max_pri_process()].state='r';
			} 
                for(i=0;i<num;i++) 
				{
					if(pcblist[i].state=='r') 
					{  
						pcblist[i].pri-=1; 
						pcblist[i].runtime--;
						{
							if(pcblist[i].runtime==0) 
                                pcblist[i].state='F'; 
							else 
								pcblist[i].state='R'; 
						}
                        show(); 
						getchar();
					}
				}
		}
}

int  main()
{
	cout<<"此程序默认运行4个进程。"<<endl<<endl;
	init(); 
	run();
}

