#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#define furthest 5
struct process       /*PCB STRUCTURE*/
{ 
  int id;
  int priority;
  int cputime;
  int alltime;
  char state;
  int next;
}prochain[furthest-1];  
int procnum;
int rand();
int algo;
int run,head,tail,j;
int init();
int prisch();
int timesch();

main()    /*MAIN PROGRAM*/
{  agan: printf("type the algorithm is (1:RR,2:PRIO):");
        scanf("%d",&algo);
        if (algo==2)
        {
            printf("output of priority.\n");
          init ( );
          prisch();
        }
        else{ 
                 if (algo==1)
               { 
                  printf("output of round robin.\n");
                  init();
                  timesch();
               }
               else
               { 
                  printf("try again,please\n");
                  goto agan;
               }
             }
   for (j=1;j<=40;j++)
   { printf("="); }
   printf("\n\n");
   for (j=1;j<=40;j++)
   { printf("="); }
   printf("\n\n");
   printf("system finished\n");
   getch();
}
print()    /*PRINT THE RUNNING PROCESS,WAITING QUEUE AND PCB SEQUENCE LIST*/
{       
     int k,p;
   for (k=1;k<=40;k++)
      printf("=");
   printf("\nrunning proc.   ");
   printf("%d",prochain[run].id);
   printf("\n          waiting queue.");
   /*printf("\n    %d     ",prochain[run].id);*/
   p=head;
   while(p!=0)
   { 
      printf("%5d",p);
      p=prochain[p].next;
   }
   printf("\n");
   for (k=1;k<=40;k++)
      printf("=");
   printf("\n");
   printf(" id            ");
   for (k=1;k<furthest+1;k++)
      printf("%5d",prochain[k].id);
   printf("\n");
   printf("priority       ");
   for (k=1;k<furthest+1;k++)
      printf("%5d",prochain[k].priority);
   printf("\n");
   printf("cputime        ");
   for (k=1;k<furthest+1;k++)
      printf("%5d",prochain[k].cputime);
   printf("\n");
   printf("alltime        ");
   for (k=1;k<furthest+1;k++)
      printf("%5d",prochain[k].alltime);
   printf("\n");
   printf("state          ");
   for (k=1;k<furthest+1;k++)
      printf("%5c",prochain[k].state);
   printf("\n");
   printf("next           ");
   for (k=1;k<furthest+1;k++)
      printf("%5d",prochain[k].next);
   printf("\n");
}

int insert(int q)      /*INSERT A PROCESS*/
{       
     int p,s;
   p=head;
   s=prochain[head].next;
   while((prochain[q].priority<prochain[s].priority)&&(s!=0))
   { 
      p=s;
      s=prochain[s].next;

   prochain[p].next=q;
   prochain[q].next=s;
   }
   return 0;
}

int insert2()    /*PUT A PROCESS ONTO THE TAIL OF THE QUEUE*/
{      
     prochain[tail].next=run;
   tail=run;
   prochain[run].next=0;
   return 0;
}

int init()     /*CREATE A WAITING QUEUE*/
{       
   int i;
   head=0;

   if (algo==2)
   {
      for (i=1;i<furthest+1;i++)
      { 
          prochain[i].id=i;
          prochain[i].priority=(rand()+11)%41;
          prochain[i].cputime=0;
          prochain[i].alltime=(rand()+1)%7;
          prochain[i].state='W';
          prochain[i].next=0;
          if((prochain[i].priority<prochain[head].priority)&&(head!=0))
               insert(prochain[i].id);
          else
          { 
            prochain[i].next=head;
            head= prochain[i].id;

          }
      }
   }
   else
   { 
      for (i=1;i<furthest+1;i++)
      { 
         prochain[i].id=i;
         prochain[i].priority=(rand()+1)%3+1;
         prochain[i].cputime=0;
         prochain[i].alltime=(rand()+1)%7;
         prochain[i].state='W';
         prochain[i].next=(i+1)%(furthest+1);
      }
      head=1;
      tail=furthest;
      prochain[furthest].next=0;
   }
   run=head;
   prochain[run].state='R';
   head=prochain[head].next;
   prochain[run].next=0;
   print();
   return 0;
}

int  prisch()      /*THE PROCESS WITH PRIO ALGORITHM */
{       
     while(run!=0)
  { 
     prochain[run].cputime+=1;
     prochain[run].priority-=3;
     prochain[run].alltime-=1;
     if(prochain[run].alltime<=0)
     { 
          prochain[run].state='F';
        prochain[run].next=0;
        if(head==0)
        { 
             run=head;
           prochain[run].state='R';
           head=prochain[head].next;
        }
        else
        { 
             prochain[0].id=prochain[run].id;
           run=0;
        }
     }
     else
     { 
          if((prochain[run].priority< prochain[head].priority)&&(head!=0))
        { 
             prochain[run].state='W';
           insert(run);
           run=head;
           prochain[run].state='R';
           head= prochain[head].next;
        }
     }
     print();
  }
  return 0;
}
int timesch()      /*THE PROCESS WITH RR ALRORITHM  */
{     
      while(run!=0)
   { 
      prochain[run].alltime-=1;
      prochain[run].cputime+=1;
      if(prochain[run].alltime==0)
      {
         prochain[run].state='F';
         prochain[run].next=0;
         if(head!=0)
         {
             run=head;
           prochain[run].state='R';
           head=prochain[head].next;
         }
         else
         { 
             prochain[0].id=prochain[run].id;
           run=0;
         }
      }
      else
      { 
         if((prochain[run].cputime==prochain[run].priority)&&(head!=0))
         { 
              prochain[run].state='W';
            prochain[run].cputime=0;
            insert2();
            run=head;
            prochain[run].state='R';
            head=prochain[head].next;}
      }
      print();
   }
   return 0;
}

