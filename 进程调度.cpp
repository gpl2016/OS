#include<iostream>
#include<cstdlib>
#define maxnum 50//最大进程数目 
using namespace std;
class PCB {
public:
	char name[10];
	int All_Time;
	int Runed_Time;
	int pri;
	char state;
};


/**********************************************************************/  
/*                                                                    */  
/*                            全局变量定义                            */  
/*                                                                    */  
/**********************************************************************/ 
int ProcNum;
int flag,num,t;
struct PCB pcblist[maxnum]; 

/**********************************************************************/  
/*                                                                    */  
/*                         显示进程运行信息                           */  
/*                                                                    */  
/**********************************************************************/ 
void time_show()
{
	int i; 
	cout<<endl<<"进程名  运行时间 已运行时间"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    for(i=0;i<num;i++) 
	{ 
	    if(pcblist[i].state!='F')
		printf("%s%9d%10d\n",&pcblist[i].name,pcblist[i].All_Time,pcblist[i].Runed_Time);
	} 
    cout<<"开始!"<<endl;
}
void show()
{
	int i; 
	cout<<endl<<"进程名 优先权 运行时间 已运行时间"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    for(i=0;i<num;i++) 
	{ 
	    if(pcblist[i].state!='F')
		printf("%s%7d%9d%10d\n",&pcblist[i].name,pcblist[i].pri,pcblist[i].All_Time,pcblist[i].Runed_Time);
	} 
    cout<<"开始!"<<endl;
}

/**********************************************************************/  
/*                                                                    */  
/*                           插入进程                                 */  
/*                                                                    */  
/**********************************************************************/ 
int insert() 
{ 
	cout<<"请增加的进程数目"<<endl;
	int insert_num;	
	cin>>insert_num;
	int count=num+insert_num;
	
    for(int i=num;i<count;i++) 
	{ 
        cout<<"进程"<<i+1<<":"<<"进程名 优先权 运行时间 已运行时间 "<<endl;
        cin>>pcblist[i].name>>pcblist[i].pri>>pcblist[i].All_Time>>pcblist[i].Runed_Time;
		pcblist[i].state='R';
		getchar();
	}
	for(int j=num;j<count;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
	num=count;
	
	return 0;
}	

/**********************************************************************/  
/*                                                                    */  
/*                           时间片轮转运行函数                       */  
/*                                                                    */  
/**********************************************************************/ 
void time_run()
{
	int i,j; 
	int round=0;
    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
		cout<<endl<<"初态为"<<endl; 
        time_show(); 
	    getchar(); 
			for(i=0;i<t;i++)
			{					
				int c;
				c=i%num;
				while(pcblist[c].state=='F')
				{
					i++;
					c=i%num;
				}
				pcblist[c].Runed_Time+=1;
				
				if(pcblist[c].Runed_Time==pcblist[c].All_Time)
				{
				pcblist[c].state='F';
				cout<<"进程"<<pcblist[c].name<<"已删除"<<endl; 
				}
				round++;
				cout<<endl<<"第"<<round<<"轮"<<pcblist[c].name<<"进程运行中"; 
				time_show();
				cout<<"如果需要增加进程请输入i,否则输入c"<<endl; 
						char m;
						cin>>m;
						if (m == 'i')
						insert();
			}
}
/**********************************************************************/  
/*                                                                    */  
/*                           进程初始化函数                           */  
/*                                                                    */  
/**********************************************************************/ 
void init() 
{ 
	int i; 
    for(i=0;i<num;i++) 
	{ 
        cout<<"进程"<<i+1<<":"<<"进程名 优先权 运行时间 已运行时间"<<endl;
        cin>>pcblist[i].name>>pcblist[i].pri>>pcblist[i].All_Time>>pcblist[i].Runed_Time;
		pcblist[i].state='R';
		getchar();
	}
}

/**********************************************************************/  
/*                                                                    */  
/*                         判断优先级函数                             */  
/*                                                                    */  
/**********************************************************************/ 
int max_pri_process()  
{
	int max=-100; 
	int i;  
	int key=0; //key表示当前优先权最高的进程的num 
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




/**********************************************************************/  
/*                                                                    */  
/*                      动态优先权运行函数                            */  
/*                                                                    */  
/**********************************************************************/ 
void dp_run()
{
	int i,j; 

    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
		cout<<endl<<"初态为"<<endl; 
        show(); 
	    getchar(); 
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
						pcblist[i].Runed_Time++;
						{
							if(pcblist[i].All_Time==pcblist[i].Runed_Time) 
                               { pcblist[i].state='F'; 
                               	cout<<"进程"<<pcblist[i].name<<"运行结束，已经删除"<<endl; 
                               } 
							else 
							pcblist[i].state='R'; 
						}
                        show(); 
						cout<<"如果需要增加进程请输入i,否则输入c"<<endl; 
						char m;
						cin>>m;
						if (m == 'i')
						insert();
					
					}
				}
		}
		cout<<"线上进程已全部运行完毕"<<endl; 
}

/**********************************************************************/  
/*                                                                    */  
/*                      静态优先权运行函数                            */  
/*                                                                    */  
/**********************************************************************/ 
void run()
{
	int i,j; 

    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
		cout<<endl<<"初态为"<<endl; 
        show(); 
	    getchar(); 
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
						pcblist[i].Runed_Time++;
						{
							if(pcblist[i].All_Time==pcblist[i].Runed_Time) 
                               { pcblist[i].state='F'; 
                               	cout<<"进程"<<pcblist[i].name<<"运行结束，已经删除"<<endl; 
                               } 
							else 
							pcblist[i].state='R'; 
						}
                        show(); 
					//	getchar();
						cout<<"如果需要增加进程请输入i,否则输入c"<<endl; 
						char m;
						cin>>m;
						if (m == 'i')
						insert();
					
					}
				}
		}
		cout<<"线上进程已全部运行完毕"<<endl; 
}





/**********************************************************************/  
/*                                                                    */  
/*                              测试                                  */  
/*                                                                    */  
/**********************************************************************/ 
int main()
{
	int way;
	cout<<"请输入进程数目"<<endl;
	cin>>num; 	
	init(); 
	cout<<"请选择调度算法"<<endl;
	cout<<"1:时间片轮转调度算法"<<endl;
	cout<<"2:静态优先权调度算法"<<endl;
	cout<<"3:动态优先权调度算法"<<endl;
	cin>>way;
	switch(way)
	{
	
	case 1:	time_run();break;		
	case 2: run();break;
	case 3: dp_run();break;
		
	} 
	return 0;	
	
}
