#include <stdio.h>
#include <conio.h>
int main()
{
printf("C语言中文网\n");
//模拟暂停功能
printf("如果想要增加进程请按i键，否则继续进行");
char c=getchar();
if(c!='i')
return 0;
else 
printf("请增加进程"); 
}
