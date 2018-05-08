#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
typedef struct node
{
   char name[10];  /*���̱�ʶ��*/
   int prio;   /*����������*/
   int round;  /*����ʱ����תʱ��Ƭ*/
   int cputime; /*����ռ��CPUʱ��*/
   int needtime; /*���̵���ɻ�Ҫ��ʱ��*/
   int count;  /*������*/
   char state; /*���̵�״̬*/
   struct node *next; /*��ָ��*/
}PCB;
PCB *finish,*ready,*tail,*run; /*����ָ��*/
int N; /*������*/
/*�����������еĵ�һ������Ͷ������*/
firstin()
{
   run=ready;   /*��������ͷָ�븳ֵ������ͷָ��*/
   run->state='R';   /*����״̬��Ϊ����̬*/
   ready=ready->next;  /*��������ͷָ����Ƶ���һ����*/
}
/*�����������*/
void prt1(char a)
{
   if(toupper(a)=='P') /*��������*/
      printf("  name     cputime  needtime  priority  state\n");
   else
      printf("  name     cputime  needtime   count   round     state\n");
}
/*����PCB���*/
void prt2(char a,PCB *q)
{
   if(toupper(a)=='P')  /*�������������*/
      printf("  %-10s%-10d%-10d%-10d %c\n",q->name,
       q->cputime,q->needtime,q->prio,q->state);
   else/*��ת�������*/
      printf("  %-10s%-10d%-10d%-10d%-10d %-c\n",q->name,
       q->cputime,q->needtime,q->count,q->round,q->state);
}
/*�������*/
void prt(char algo)
{
   PCB *p;
   prt1(algo);  /*�������*/
   if(run!=NULL) /*�������ָ�벻��*/
      prt2(algo,run); /*�����ǰ�������е�PCB*/
   p=ready;  /*�����������PCB*/
   while(p!=NULL)
   {
      prt2(algo,p);
      p=p->next;
   }


   p=finish;  /*�����ɶ��е�PCB*/
   while(p!=NULL)
   {
      prt2(algo,p);
      p=p->next;
   }

      p=ready;
   printf("�������У�");
   while(p!=NULL){
    printf("%s\t",p->name);
    p=p->next;
   }
printf("\n");

p=finish;
   printf("��ɶ��У�");
   while(p!=NULL){
    printf("%s\t",p->name);
    p=p->next;
   }
printf("\n");

   getch();  /*ѹ���������*/
}
/*�������Ĳ����㷨*/
insert1(PCB *q)
{
   PCB *p1,*s,*r;
   int b;
   s=q;  /*�������PCBָ��*/
   p1=ready; /*��������ͷָ��*/
   r=p1; /*r��p1��ǰ��ָ��*/
   b=1;
   while((p1!=NULL)&&b)  /*����������ȷ������λ��*/
      if(p1->prio>=s->prio)
      {
     r=p1;
     p1=p1->next;
      }
      else
     b=0;
   if(r!=p1)  /*�����������˵��������r��p1֮��*/
   {
      r->next=s;
      s->next=p1;
   }
   else
   {
      s->next=p1;  /*��������ھ������е�ͷ*/
      ready=s;
   }
}
/*��ת�����뺯��*/
insert2(PCB *p2)
{
   tail->next=p2;  /*���µ�PCB�����ڵ�ǰ�������е�β*/
   tail=p2;
   p2->next=NULL;
}
/*������������ʼPCB��Ϣ*/
void create1(char alg)
{
   PCB *p;
   int i,time;
   char na[10];
   ready=NULL; /*��������ͷָ��*/
   finish=NULL;  /*��ɶ���ͷָ��*/
   run=NULL; /*���ж���ָ��*/
   printf("Enter name and time of process\n"); /*������̱�ʶ������ʱ�䴴��PCB*/
   for(i=1;i<=N;i++)
   {
    p = (struct node *)malloc(sizeof(struct node));
      //p=(PCB)malloc(sizeof(node));
    //  H=(Proc)malloc(sizeof(PNode)); 
      scanf("%s",na);
      scanf("%d",&time);
      strcpy(p->name,na);
      p->cputime=0;
      p->needtime=time;
      p->state='W';
      p->prio=50-time;
      if(ready!=NULL) /*�������в��յ��ò��뺯������*/
     insert1(p);
      else
      {
     p->next=ready; /*�����������еĵ�һ��PCB*/
     ready=p;
      }
   }
 //  clrscr();
 system("CLS");
   printf("          output of priority:\n");
   printf("************************************************\n");
   prt(alg);  /*�������PCB��Ϣ*/
   run=ready; /*���������еĵ�һ������Ͷ������*/
   ready=ready->next;
   run->state='R';
}
/*��ת����������PCB*/
void create2(char alg)
{
   PCB *p;
   int i,time;
   char na[10];
   ready=NULL;
   finish=NULL;
   run=NULL;
   printf("Enter name and time of round process\n");
   for(i=1;i<=N;i++)
   { p = (struct node *)malloc(sizeof(struct node));
     // p=malloc(sizeof(PCB));
      scanf("%s",na);
      scanf("%d",&time);
      strcpy(p->name,na);
      p->cputime=0;
      p->needtime=time;
      p->count=0; /*������*/
      p->state='W';
      p->round=2;  /*ʱ��Ƭ*/
      if(ready!=NULL)
     insert2(p);
      else
      {
     p->next=ready;
     ready=p;
     tail=p;
      }
   }
   //clrscr();
    system("CLS");
   printf("              output of round\n");
   printf("************************************************\n");
   prt(alg);   /*�������PCB��Ϣ*/
   run=ready;  /*���������еĵ�һ������Ͷ������*/
   ready=ready->next;
   run->state='R';
}
/*�����������㷨*/
priority(char alg)
{
   while(run!=NULL)  /*�����ж��в���ʱ���н�����������*/
   {
      run->cputime=run->cputime+1;
      run->needtime=run->needtime-1;
      run->prio=run->prio-3; /*ÿ����һ������������3����λ*/
      if(run->needtime==0)  /*������ʱ��Ϊ0���������ɶ���*/
      {
     run->next=finish;
     finish=run;
     run->state='F';  /*��״̬Ϊ���̬*/
     run=NULL;  /*���ж���ͷָ��Ϊ��*/
     if(ready!=NULL) /*��������в���*/
        firstin(); /*���������еĵ�һ������Ͷ������*/
      }
      else /*û��������ͬʱ������������������Ϊ����̬���뵽��������*/
     if((ready!=NULL)&&(run->prio<ready->prio))
     {
        run->state='W';
        insert1(run);
        firstin(); /*���������еĵ�һ������Ͷ������*/
     }
      prt(alg); /*�������PCB��Ϣ*/
   }
}
/*ʱ��Ƭ��ת��*/
roundrun(char alg)
{
   while(run!=NULL)
   {
      run->cputime=run->cputime+1;
      run->needtime=run->needtime-1;
      run->count=run->count+1;
      if(run->needtime==0)/*�����꽫���Ϊ���̬��������ɶ���*/
      {
     run->next=finish;
     finish=run;
     run->state='F';
     run=NULL;
     if(ready!=NULL)
        firstin(); /*�������в��գ�����һ������Ͷ������*/
      }
      else
     if(run->count==run->round)  /*���ʱ��Ƭ��*/
     {
        run->count=0;  /*��������0*/
        if(ready!=NULL) /*��������в���*/
        {
           run->state='W'; /*�����̲��뵽���������еȴ���ת*/
           insert2(run);
           firstin(); /*���������еĵ�һ������Ͷ������*/
        }

     }
       prt(alg); /*���������Ϣ*/
   }
}
/*������*/
main()
{
   char algo;  /*�㷨���*/
   //clrscr();
    system("CLS");
   printf("type the algorithm:P/R(priority/roundrobin)\n");
   scanf("%c",&algo); /*�����ַ�ȷ���㷨*/
   printf("Enter process number\n");
   scanf("%d",&N); /*���������*/
   if(algo=='P'||algo=='p')
   {
      create1(algo); /*��������*/
      priority(algo);
   }
   else
      if(algo=='R'||algo=='r')
      {
     create2(algo); /*��ת��*/
     roundrun(algo);
      }
}

