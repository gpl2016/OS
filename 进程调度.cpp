#include<iostream>
#include<cstdlib>
#define maxnum 50//��������Ŀ 
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
/*                            ȫ�ֱ�������                            */  
/*                                                                    */  
/**********************************************************************/ 
int ProcNum;
int flag,num,t;
struct PCB pcblist[maxnum]; 

/**********************************************************************/  
/*                                                                    */  
/*                         ��ʾ����������Ϣ                           */  
/*                                                                    */  
/**********************************************************************/ 
void time_show()
{
	int i; 
	cout<<endl<<"������  ����ʱ�� ������ʱ��"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    for(i=0;i<num;i++) 
	{ 
	    if(pcblist[i].state!='F')
		printf("%s%9d%10d\n",&pcblist[i].name,pcblist[i].All_Time,pcblist[i].Runed_Time);
	} 
    cout<<"��ʼ!"<<endl;
}
void show()
{
	int i; 
	cout<<endl<<"������ ����Ȩ ����ʱ�� ������ʱ��"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    for(i=0;i<num;i++) 
	{ 
	    if(pcblist[i].state!='F')
		printf("%s%7d%9d%10d\n",&pcblist[i].name,pcblist[i].pri,pcblist[i].All_Time,pcblist[i].Runed_Time);
	} 
    cout<<"��ʼ!"<<endl;
}

/**********************************************************************/  
/*                                                                    */  
/*                           �������                                 */  
/*                                                                    */  
/**********************************************************************/ 
int insert() 
{ 
	cout<<"�����ӵĽ�����Ŀ"<<endl;
	int insert_num;	
	cin>>insert_num;
	int count=num+insert_num;
	
    for(int i=num;i<count;i++) 
	{ 
        cout<<"����"<<i+1<<":"<<"������ ����Ȩ ����ʱ�� ������ʱ�� "<<endl;
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
/*                           ʱ��Ƭ��ת���к���                       */  
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
		cout<<endl<<"��̬Ϊ"<<endl; 
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
				cout<<"����"<<pcblist[c].name<<"��ɾ��"<<endl; 
				}
				round++;
				cout<<endl<<"��"<<round<<"��"<<pcblist[c].name<<"����������"; 
				time_show();
				cout<<"�����Ҫ���ӽ���������i,��������c"<<endl; 
						char m;
						cin>>m;
						if (m == 'i')
						insert();
			}
}
/**********************************************************************/  
/*                                                                    */  
/*                           ���̳�ʼ������                           */  
/*                                                                    */  
/**********************************************************************/ 
void init() 
{ 
	int i; 
    for(i=0;i<num;i++) 
	{ 
        cout<<"����"<<i+1<<":"<<"������ ����Ȩ ����ʱ�� ������ʱ��"<<endl;
        cin>>pcblist[i].name>>pcblist[i].pri>>pcblist[i].All_Time>>pcblist[i].Runed_Time;
		pcblist[i].state='R';
		getchar();
	}
}

/**********************************************************************/  
/*                                                                    */  
/*                         �ж����ȼ�����                             */  
/*                                                                    */  
/**********************************************************************/ 
int max_pri_process()  
{
	int max=-100; 
	int i;  
	int key=0; //key��ʾ��ǰ����Ȩ��ߵĽ��̵�num 
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




/**********************************************************************/  
/*                                                                    */  
/*                      ��̬����Ȩ���к���                            */  
/*                                                                    */  
/**********************************************************************/ 
void dp_run()
{
	int i,j; 

    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
		cout<<endl<<"��̬Ϊ"<<endl; 
        show(); 
	    getchar(); 
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
						pcblist[i].Runed_Time++;
						{
							if(pcblist[i].All_Time==pcblist[i].Runed_Time) 
                               { pcblist[i].state='F'; 
                               	cout<<"����"<<pcblist[i].name<<"���н������Ѿ�ɾ��"<<endl; 
                               } 
							else 
							pcblist[i].state='R'; 
						}
                        show(); 
						cout<<"�����Ҫ���ӽ���������i,��������c"<<endl; 
						char m;
						cin>>m;
						if (m == 'i')
						insert();
					
					}
				}
		}
		cout<<"���Ͻ�����ȫ���������"<<endl; 
}

/**********************************************************************/  
/*                                                                    */  
/*                      ��̬����Ȩ���к���                            */  
/*                                                                    */  
/**********************************************************************/ 
void run()
{
	int i,j; 

    for(j=0;j<num;j++) 
	{
		t+=pcblist[j].All_Time;		
	}
		cout<<endl<<"��̬Ϊ"<<endl; 
        show(); 
	    getchar(); 
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
						pcblist[i].Runed_Time++;
						{
							if(pcblist[i].All_Time==pcblist[i].Runed_Time) 
                               { pcblist[i].state='F'; 
                               	cout<<"����"<<pcblist[i].name<<"���н������Ѿ�ɾ��"<<endl; 
                               } 
							else 
							pcblist[i].state='R'; 
						}
                        show(); 
					//	getchar();
						cout<<"�����Ҫ���ӽ���������i,��������c"<<endl; 
						char m;
						cin>>m;
						if (m == 'i')
						insert();
					
					}
				}
		}
		cout<<"���Ͻ�����ȫ���������"<<endl; 
}





/**********************************************************************/  
/*                                                                    */  
/*                              ����                                  */  
/*                                                                    */  
/**********************************************************************/ 
int main()
{
	int way;
	cout<<"�����������Ŀ"<<endl;
	cin>>num; 	
	init(); 
	cout<<"��ѡ������㷨"<<endl;
	cout<<"1:ʱ��Ƭ��ת�����㷨"<<endl;
	cout<<"2:��̬����Ȩ�����㷨"<<endl;
	cout<<"3:��̬����Ȩ�����㷨"<<endl;
	cin>>way;
	switch(way)
	{
	
	case 1:	time_run();break;		
	case 2: run();break;
	case 3: dp_run();break;
		
	} 
	return 0;	
	
}
