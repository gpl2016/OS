#include <stdlib.h> 
#include <iostream>
#include <time.h> 
using namespace std; 
void rand(int n,int p[])//�ú����ǲ���n��1~10��������ŵ�p[]��������
{ 
	int START=1;
    int END=10;
    int v;
    int i;
	int a;
	srand(time(NULL));
	for(i=0; i<n; i++) 
	{
		v=rand()%(END-START+1)+START; 
		p[i]=v;
		cout<<v;
	}
}
struct Pro
{
	int num,time;
	//num��ž�������ݣ�time�ڲ�ͬ�㷨�����в�ͬ������
};               
//������������ҳ������ݽṹ
int Input(int m,int N,Pro *p,Pro *page)
//���p[]�����page[]�ĳ�ʼ������
{   //p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С
	cout<<endl<<"�������ҳ���"<<endl;
    int *p2=new int[m];
    rand(m,p2);
    for(int i=0;i<m;i++)
	{
		p[i].num=p2[i];
		p[i].time=0;
	}
	for(int i=0;i<N;i++)
		//���Ի�ҳ��������
	{
		page[i].num=0;
		page[i].time=N+2-i;
	}
	return m;
}
int  Search(int e,Pro *page,int N)
//�㷨���涼Ҫ�õ�����
{
	//������eҳ�Ƿ���page������У�N�������Ĵ�С
	for(int i=0;i<N;i++)
		if(e==page[i].num)
			return i;
		//����ҵ����ͷ�����������е�λ�ø�Search
		return -1;//�Ҳ������ͷ���-1
}
int Max(Pro *page,int N)//LRU�㷨�õ���
{//�ҳ���page���У�time����ֵ��λ�ã�ͬʱλ�÷���
//time��󣬾ʹ��������û��ʹ�õ���
int e=page[0].time,i=0;
int k=0;
while(i<N)//�ҳ�������ʱ�����ҳ��
{
	if(e<page[i].time)
	{
		k=i;
	}
	i++;
}
return k; 
}
int Compfu(Pro *page,int i,int t,Pro p[],int m)
//OPT�㷨�õ���
{
//�ҳ����page[t]Ҫ����p������zai p[i]~p[m]��������ڣ��ߵĴ�����������
 int count=0;
 //count�Ǳ����ߵĲ���
 for(int j=i;j<m;j++)
 {
	 if(page[t].num==p[j].num )break;
	 //�����ȣ�����ѭ��
     else count++;
	 //���ȾͲ�����1
 }
 return count;
}
int Min(Pro page[],int N)//LFU�㷨�õ���
{    //page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С
  //�ҵ����ִ�����С�ĵ���������λ�÷���
 int k=0;
 int min=page[0].time;
 for(int i=0;i<N;i++)
 {
  if(min>page[i].time)
   k=i;
 }
 return k;

}

 

void FIFO(Pro p[],Pro page[],int m,int N)//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{    //page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С
 float n=0;//n��������ȱҳ�Ĵ���
 int i=0;//i��ѭ�����������Ǳ�ʾ�ߵ�ҳ���λ�á�
 int t=0;//t��������ʾ������ߵ���λ��
 cout<<"ҳ���û����:   "<<endl;
 for(i=0;i<m;i++)
 {
  if(Search(p[i].num,page,N)>=0)
   continue;//�ҵ���ͬ��ҳ�棬��������һ��ѭ������������
  else //���Ҳ�����ʱ��ͨ��t=t%N,���������滻������λ��
   {  
   t=t%N;
   n++;//ȱҳ����1
   page[t].num=p[i].num;
        
   t++;//λ�ü�1
   }
 }
  cout<<"ȱҳ������"<<n<<"    ȱҳ�ʣ�"<<n/m<<"    �����ʣ�"<<1-n/m<<endl;  

}
void LFU(Pro p[],Pro page[],int m,int N)
//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{    
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С��
 float n=0;
 int i=0;
 int t=0;
 for(i=0;i<N;i++)
  page[i].time=0;
 cout<<"ҳ���û����:   "<<endl;
 for(i=0;i<m;i++)
 {
  if(Search(p[i].num,page,N)>=0)
  {
   page[i].time++;
   //�ҵ���ͬ��ҳ�棬time��1
   continue;//
  }
  else 
   {//�ҳ�ʹ�����ٵ�ҳ����е���
   t=Min(page,N);//�ҵ����ִ�����С�ĵ���������λ�÷���t
   page[t].num=p[i].num;
   page[t].time=0;//��ҳtime����
   n++;//ȱҳ����1

  }
 }
  cout<<"ȱҳ������"<<n<<"    ȱҳ�ʣ�"<<n/m<<"    �����ʣ�"<<1-n/m<<endl;  

}
void OPT(Pro p[],Pro page[],int m,int N)//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{    //page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С

     float n=0;//n��������ȱҳ�Ĵ���
        int i=0;//i��ѭ�����������Ǳ�ʾ�ߵ�ҳ���λ�á�
         int t=0; //t��������ʾ������ߵ���λ��
   while(i<m)
   {
    if(Search(p[i].num,page,N)>=0)
     i++;//����ҵ��ˣ��Ͳ�������
    else//����Ҳ���
    {
     int temp=0,cn;//cn���������������Զ����
     for(t=0;t<N;t++)//������������ÿ�������б���
     {
      if(temp<Compfu(page,i,t,p,m))//temp��������
      {//page[t]= p[i]~p[m]��������ڣ��ߵĴ�����������
       temp=Compfu(page,i,t,p,m);
       cn=t;
      }
     }
     page[cn]=p[i];//�ѵ�ǰ��ֵ��Ҫ����Ҫ����Զ������Ҳ�������������ֵ���
     n=n+1;//ȱҳ����1
     i++;//������һ��ѭ��
    }
   }
   cout<<"ȱҳ������"<<n<<"    ȱҳ�ʣ�"<<n/m<<"    �����ʣ�"<<1-n/m<<endl;  

}

void LRU(Pro p[],Pro page[],int m,int N)//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{    //page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С

    float n=0;//n��������ȱҳ�Ĵ���
 int i=0;//i��ѭ�����������Ǳ�ʾ�ߵ�ҳ���λ�á�
 int t=0;  //t��������ʾ������ߵ���λ��       
 
 cout<<"ҳ���û����:   "<<endl; 
       while(i<m)
    {    
      int k;
      k=t=Search(p[i].num,page,N);
      if(t>=0)
      page[t].time=0;//����ҵ�����Ҫ�ѵ�ǰ��page[t].time����
                             //����
         else//�Ҳ�����ʱ�򣬷���ȱҳ
    {  
        n++; //ȱҳ����1
        t=Max(page,N);//�ҳ�page��������棬���û��ʱ�����
                      //ͬʱ�����û��ʱ���������������λ�ô���t
        page[t].num=p[i].num;//���û��ʹ�õ��Ǳ����ڵ�������
        page[t].time=0;//ͬʱ����
    }
         for(int j=0;j<N;j++)//��ȱҳ�������������û��ʹ�õĴ�����1
     {
     if(j==t)
      continue;
     page[t].time++;
     }
         i++;//������һ��ѭ��
    }
       cout<<"ȱҳ������"<<n<<"    ȱҳ�ʣ�"<<n/m<<"    �����ʣ�"<<1-n/m<<endl;  
}
int  main()
{
 int m=0,t=0,N=0;
 cout<<"������ʵ��ҳ����";
 cin>>m;
    Pro *p=new Pro[m];//p��������ҳ��ĵط�
    cout<<"�����ڴ�ҳ����"<<endl;
 cin>>N;   
 Pro *page=new Pro[N];//page�Ƿ������ĵط�
 char c;
 float n=0;
 Input(m,N,p,page);//m��ҳ����ܳ���N�������ĳ��� 
 do{
  cout<<"f:FIFOҳ���û�"<<endl;
  cout<<"l:LRUҳ���û�"<<endl;
  cout<<"o:OPTҳ���û�"<<endl;
  cout<<"u:LFUҳ���û�"<<endl;
  cout<<"������������"<<endl;
  cin>>c;
  if(c=='f')//FIFOҳ���û�
  {
  FIFO(p,page,m,N); 
  }
  if(c=='l')//LRUҳ���û�
  {   
   LRU(p,page,m,N);
  }
  if(c=='o')//OPTҳ���û�
  { 
   OPT(p,page,m,N); 
  }
    if(c=='u')//OPTҳ���û�
  {
   LFU(p,page,m,N); 
  }
 }while(c=='f'||c=='l'||c=='o'||c=='u');
}

