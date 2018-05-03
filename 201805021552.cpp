#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
typedef struct pcb
{
  int name;
  int needtime;
  int arrivetime;
  int pri;
  int state;
  int cputime;
}plist;
void action(plist * nowpro);
void action(plist * nowpro)
{
   Sleep(1000);// 将程序的执行暂停一段时间（1000毫秒）
   printf(" 进程 %d 正在运行",nowpro->name);
   nowpro->needtime--;
   if(nowpro->needtime==0)
   {
     printf(" 进程 %d 结束\n",nowpro->name);
    /* nowpro->state=1;  */
    printf("-----------------------------\n");
   }
   else
   {
     printf(" 进程 %d 剩余完成时间  %d\n",nowpro->name,nowpro->needtime);

     printf("-----------------------------\n");
   }
}
 void  creatpro(int n,plist * process )
{
   int j;
   for(j=0;j<n;j++)
   {
     process[j].name= j+1;
     process[j].needtime=rand()%10+1;
     process[j].arrivetime=rand()%10;
     process[j].pri=rand()%4;
     process[j].state=0;
     process[j].cputime=0;
   }
}
void show( int n,plist * process)
{
    int j;
    for (j=0 ;j<n;j++)
    {
       printf(" 进程 %d\t",process[j].name);
       printf(" 剩余完成时间 %d\t",process[j].needtime);
       printf(" 到达时间 %d\t",process[j].arrivetime);
       printf(" 优先级 %d\t",process[j].pri);
       printf(" 状态 %d\t",process[j].state);
       printf(" cputime %d\n",process[j].cputime);
    }
}
int main()
{
   void  creatpro(int n,plist * process );
   void show( int n,plist * process);
   void fcfs(int n,plist * process);
   void sjf(int n,plist * process);
   void rr(int n,plist * pro1);
   int n;  /*the number of process*/
   int k;
   plist process[10];
   printf(" 请输入进程个数(1-10)\n");
   scanf("%d",&n);
   creatpro(n,process);
   show(n,process);
    printf(" 请选择所需要的调度算法 \n");
    printf("1 FCFS\t 2 SJF\t 3 RR\n");
    scanf("%d",&k);
    switch(k)
    {
      case 1:  fcfs(n,process);     break;
      case 2:  sjf(n,process);      break;
      case 3:  rr(n,process);       break;
      default : break;
    }
   getch();
}
void fcfs(int n,plist * pro1)
{
   void show( int n,plist * process);
   int i,j,k;

   int m=0;
   int time;
   plist temp;
   plist pro2[10];
   for(i=0;i<n;i++)
   {
      k=0;
     while(pro1[k].state==1)
     {
         k++;
     }
     temp=pro1[k];
     for(j=k+1;j<n;j++)
     {
       if(temp.arrivetime>pro1[j].arrivetime&&pro1[j].state!=1)
       {
          temp=pro1[j];
          k=j;
       }
     }
     pro2[m++]=temp;
     pro1[k].state=1;
   }
   show(n,pro2);
   for(i=0;i<n;i++)
   {
      while(pro2[i].needtime>0)
      {
         action(&pro2[i]);

      }
   }
}
void sjf(int n,plist * pro1)
{
   void show( int n,plist * process);
   int i,j,k;
   int m=0;
   plist temp;
   plist pro2[10];
   for(i=0;i<n;i++)
   {
     k=0;
     while(pro1[k].state==1)
     {
        k++;
     }
     temp=pro1[k];
     for(j=k+1;j<n;j++)
     {
        if(temp.needtime>pro1[j].needtime&&pro1[j].state!=1)
       {
          temp=pro1[j];
          k=j;
       }
     }
     pro2[m++]=temp;
     pro1[k].state=1;
   }
   show(n,pro2);
   for(i=0;i<n;i++)
   {
      while(pro2[i].needtime>0)
      {
         action(&pro2[i]);
      }
   }
}
void rr(int n,plist * pro1)
{
  void show( int n,plist * process);
   int i,j,k;
   int m=0;
   int time;
   plist temp;
   plist pro2[10];
   for(i=0;i<n;i++)
   {
      k=0;
     while(pro1[k].state==1)
     {
         k++;
     }
     temp=pro1[k];
     for(j=k+1;j<n;j++)
     {
       if(temp.arrivetime>pro1[j].arrivetime&&pro1[j].state!=1)
       {
          temp=pro1[j];

          k=j;
       }
     }
     pro2[m++]=temp;
     pro1[k].state=1;
   }
   show(n,pro2);
   time=pro2[0].needtime;
   for(i=0;i<n;i++)
   {
      if(time<pro2[i].needtime)
      {
         time=pro2[i].needtime;
      }
   }
   while(time>0)
   {
      for(i=0;i<n;i++)
      {
          if(pro2[i].needtime>0)
          {
            action(&pro2[i]);
          }
      }
      time--;
   }
}
int cal(int a ,plist * pro2)
 {
     int pr;
     if((a-pro2->arrivetime)<=0)
     { pr=1;   }
      else
     {
            pr=(a-pro2->arrivetime+pro2->needtime)/pro2->needtime;
     }
     return pr;
 }

