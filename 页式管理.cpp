#include <stdlib.h> 
#include <iostream>
#include <time.h> 
using namespace std; 
void rand(int n,int p[])//该函数是产生n个1~10的随机数放到p[]数组里面
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
	//num存放具体的内容，time在不同算法里面有不同的意义
};               
//它们是物理块和页面的数据结构
int Input(int m,int N,Pro *p,Pro *page)
//完成p[]数组和page[]的初始化工作
{   //p[]数组是存放页面的空间，m是页面的长度
	//page[]是可以使用的物理块，N是物理块的大小
	cout<<endl<<"请输入各页面号"<<endl;
    int *p2=new int[m];
    rand(m,p2);
    for(int i=0;i<m;i++)
	{
		p[i].num=p2[i];
		p[i].time=0;
	}
	for(int i=0;i<N;i++)
		//初试化页面基本情况
	{
		page[i].num=0;
		page[i].time=N+2-i;
	}
	return m;
}
int  Search(int e,Pro *page,int N)
//算法里面都要用到它。
{
	//它是找e页是否在page物理块中，N是物理块的大小
	for(int i=0;i<N;i++)
		if(e==page[i].num)
			return i;
		//如果找到，就返回在物理块中的位置给Search
		return -1;//找不到，就返回-1
}
int Max(Pro *page,int N)//LRU算法用到的
{//找出在page块中，time最大的值和位置，同时位置返回
//time最大，就代表了最久没被使用的数
int e=page[0].time,i=0;
int k=0;
while(i<N)//找出离现在时间最长的页面
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
//OPT算法用到的
{
//找出如果page[t]要等于p，并且zai p[i]~p[m]这个区间内，走的次数，最大的数
 int count=0;
 //count是保存走的步数
 for(int j=i;j<m;j++)
 {
	 if(page[t].num==p[j].num )break;
	 //如果相等，跳出循环
     else count++;
	 //不等就步数加1
 }
 return count;
}
int Min(Pro page[],int N)//LFU算法用到的
{    //page[]是可以使用的物理块，N是物理块的大小
  //找到出现次数最小的的数，并把位置返回
 int k=0;
 int min=page[0].time;
 for(int i=0;i<N;i++)
 {
  if(min>page[i].time)
   k=i;
 }
 return k;

}

 

void FIFO(Pro p[],Pro page[],int m,int N)//p[]数组是存放页面的空间，m是页面的长度
{    //page[]是可以使用的物理块，N是物理块的大小
 float n=0;//n用来保存缺页的次数
 int i=0;//i是循环变量，它是表示走到页面的位置。
 int t=0;//t是用来表示物理块走到的位置
 cout<<"页面置换情况:   "<<endl;
 for(i=0;i<m;i++)
 {
  if(Search(p[i].num,page,N)>=0)
   continue;//找到相同的页面，就跳到下一次循环，不做处理。
  else //在找不到的时候，通过t=t%N,求出这次来替换物理块的位置
   {  
   t=t%N;
   n++;//缺页数加1
   page[t].num=p[i].num;
        
   t++;//位置加1
   }
 }
  cout<<"缺页次数："<<n<<"    缺页率："<<n/m<<"    命中率："<<1-n/m<<endl;  

}
void LFU(Pro p[],Pro page[],int m,int N)
//p[]数组是存放页面的空间，m是页面的长度
{    
	//page[]是可以使用的物理块，N是物理块的大小，
 float n=0;
 int i=0;
 int t=0;
 for(i=0;i<N;i++)
  page[i].time=0;
 cout<<"页面置换情况:   "<<endl;
 for(i=0;i<m;i++)
 {
  if(Search(p[i].num,page,N)>=0)
  {
   page[i].time++;
   //找到相同的页面，time加1
   continue;//
  }
  else 
   {//找出使用最少的页面进行调换
   t=Min(page,N);//找到出现次数最小的的数，并把位置返回t
   page[t].num=p[i].num;
   page[t].time=0;//该页time清零
   n++;//缺页数加1

  }
 }
  cout<<"缺页次数："<<n<<"    缺页率："<<n/m<<"    命中率："<<1-n/m<<endl;  

}
void OPT(Pro p[],Pro page[],int m,int N)//p[]数组是存放页面的空间，m是页面的长度
{    //page[]是可以使用的物理块，N是物理块的大小

     float n=0;//n用来保存缺页的次数
        int i=0;//i是循环变量，它是表示走到页面的位置。
         int t=0; //t是用来表示物理块走到的位置
   while(i<m)
   {
    if(Search(p[i].num,page,N)>=0)
     i++;//如果找到了，就不做处理。
    else//如果找不到
    {
     int temp=0,cn;//cn用来保存离后面最远的数
     for(t=0;t<N;t++)//对物理块里面的每个数进行遍历
     {
      if(temp<Compfu(page,i,t,p,m))//temp用来保存
      {//page[t]= p[i]~p[m]这个区间内，走的次数，最大的数
       temp=Compfu(page,i,t,p,m);
       cn=t;
      }
     }
     page[cn]=p[i];//把当前的值放要发生要走最远的数，也就最不可能最近出现的数
     n=n+1;//缺页数加1
     i++;//跳到下一次循环
    }
   }
   cout<<"缺页次数："<<n<<"    缺页率："<<n/m<<"    命中率："<<1-n/m<<endl;  

}

void LRU(Pro p[],Pro page[],int m,int N)//p[]数组是存放页面的空间，m是页面的长度
{    //page[]是可以使用的物理块，N是物理块的大小

    float n=0;//n用来保存缺页的次数
 int i=0;//i是循环变量，它是表示走到页面的位置。
 int t=0;  //t是用来表示物理块走到的位置       
 
 cout<<"页面置换情况:   "<<endl; 
       while(i<m)
    {    
      int k;
      k=t=Search(p[i].num,page,N);
      if(t>=0)
      page[t].time=0;//如果找到，就要把当前的page[t].time次数
                             //清零
         else//找不到的时候，发生缺页
    {  
        n++; //缺页数加1
        t=Max(page,N);//找出page物理块里面，最久没被时候的数
                      //同时把最久没被时候的数在物理块里的位置传给t
        page[t].num=p[i].num;//最久没被使用的是被现在的数代替
        page[t].time=0;//同时清零
    }
         for(int j=0;j<N;j++)//把缺页以外的数，把它没被使用的次数加1
     {
     if(j==t)
      continue;
     page[t].time++;
     }
         i++;//跳到下一次循环
    }
       cout<<"缺页次数："<<n<<"    缺页率："<<n/m<<"    命中率："<<1-n/m<<endl;  
}
int  main()
{
 int m=0,t=0,N=0;
 cout<<"请输入实际页数：";
 cin>>m;
    Pro *p=new Pro[m];//p是用来放页面的地方
    cout<<"可用内存页面数"<<endl;
 cin>>N;   
 Pro *page=new Pro[N];//page是放物理块的地方
 char c;
 float n=0;
 Input(m,N,p,page);//m是页面的总长，N是物理块的长度 
 do{
  cout<<"f:FIFO页面置换"<<endl;
  cout<<"l:LRU页面置换"<<endl;
  cout<<"o:OPT页面置换"<<endl;
  cout<<"u:LFU页面置换"<<endl;
  cout<<"按其它键结束"<<endl;
  cin>>c;
  if(c=='f')//FIFO页面置换
  {
  FIFO(p,page,m,N); 
  }
  if(c=='l')//LRU页面置换
  {   
   LRU(p,page,m,N);
  }
  if(c=='o')//OPT页面置换
  { 
   OPT(p,page,m,N); 
  }
    if(c=='u')//OPT页面置换
  {
   LFU(p,page,m,N); 
  }
 }while(c=='f'||c=='l'||c=='o'||c=='u');
}

