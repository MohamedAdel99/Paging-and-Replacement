#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int s[100],n,count=0;
int* pages;
char* algo;
void Fifo(void);
void LRU(void);
void clock(void);
void optim(void);

int main()
{
 int input;
 scanf("%d",&n);
 algo=(char*)malloc(8*sizeof(char));
 scanf("%s",algo);
while(input!=-1){
    scanf("%d",&input);
     s[count++]=input;
     }
     count--;
     if(!strcasecmp(algo,"fifo"))
     {
      Fifo();
     }
      if(!strcasecmp(algo,"lru"))
     {
      LRU();
     }
      if(!strcasecmp(algo,"clock"))
     {
      clock();
     }
      if(!strcasecmp(algo,"optimal"))
     {
      optim();
     }
    return 0;
}
void Fifo(void)
{
    int i,j,k,avail,fault=0,temp;
 pages = (int*)malloc(n * sizeof(int));
 printf("Replacement Policy = FIFO\n");
printf("-------------------------------------\n");
for(i=0;i<n;i++)
pages[i]= -2;
j=0;
printf("Page   Content of Frames\n");
printf("----   -----------------\n");
for(i=0;i<=(count-1);i++)
{
avail=0;
for(k=0;k<n;k++)
if(pages[k]==s[i])
avail=1;
if (avail==0)
{
if (pages[j]==-2)
{pages[j]=s[i];
j=(j+1)%n;
}
else
{
    pages[j]=s[i];
j=(j+1)%n;
fault++;
}
}
if(fault>0 && avail==0)
printf("%02d F   ",s[i]);
else
printf("%02d     ",s[i]);
for(k=0;k<n;k++)
if(pages[k]==-2)
    printf(" ");
else
printf("%02d ",pages[k]);
printf("\n");
}
printf("-------------------------------------\n");
printf("Number of page faults = %d\n",fault);
}
void LRU(void)
{
  int i,j,k,l,pos,avail[10],fault=0,f1=0,f2=0,counter=0,minimum;
 pages = (int*)malloc(n * sizeof(int));
 printf("Replacement Policy = LRU\n");
printf("-------------------------------------\n");
for(i=0;i<n;i++)
pages[i]= -1;
j=0;
printf("Page   Content of Frames\n");
printf("----   -----------------\n");
for(i=0;i<count;i++)
{
f1=f2=0;
for(j=0;j<n;j++)
{
    if(pages[j]==s[i])
{
    counter++;
	    		avail[j] = counter;
f1=f2=1;

break;
}
}
 if(f1==0)
  {

   for(j=0;j< n;j++)
   {
    if(pages[j]==-1)
    {
   	counter++;
	    			pages[j] = s[i];
	    			avail[j] = counter;
     f2=1;
     break;
    }
   }
  }
  if(f2==0)
  {
   minimum = avail[0], pos = 0;
	for(k =0; k<n; ++k)
		if(avail[k] < minimum){
			minimum = avail[k];
			pos=k;
		}
			   pages[pos] = s[i];
   counter++;
    		fault++;
    		 avail[pos] = counter;
  }

if(fault>0 && f1==0 && f2==0)
printf("%02d F   ",s[i]);
else
printf("%02d     ",s[i]);
for(k=0;k<n;k++)
if(pages[k]==-1)
    printf(" ");
else
printf("%02d ",pages[k]);
printf("\n");
}
printf("-------------------------------------\n");
printf("Number of page faults = %d\n",fault);
}
void clock(void)
{
     int i,j,k,chance[10],temp,avail,fault=(-1*n);
 pages = (int*)malloc(n * sizeof(int));
 printf("Replacement Policy = CLOCK\n");
printf("-------------------------------------\n");
for(i=0;i<n;i++)
{pages[i]= -1;
chance[i]= 0;}
j=0;
printf("Page   Content of Frames\n");
printf("----   -----------------\n");
for(i=0;i<=(count-1);i++)
{
avail=0;
for(k=0;k<n;k++)
if(pages[k]==s[i])
{avail=1;
chance[k]=1;
break;
}
if (avail==0)
{
 if(chance[j]==1)
   while(chance[j]==1)
{
            chance[j]=0;
          j=(j+1)%n;
}
if(pages[j]==-1 || chance[j]==0)
   {pages[j]=s[i];
   chance[j]= 1;
    j=(j+1)%n;
      fault++;
     }
}
if(fault>0 && avail==0)
printf("%02d F   ",s[i]);
else
printf("%02d     ",s[i]);
for(k=0;k<n;k++)
if(pages[k]==-1)
    printf(" ");
else
printf("%02d ",pages[k]);
printf("\n");
}
printf("-------------------------------------\n");
printf("Number of page faults = %d\n",fault);
}
void optim(void)
{
 int i,j,k,fault=0,index,flag1,flag2,flag3,max;
 pages = (int*)malloc(n * sizeof(int));
 printf("Replacement Policy = OPTIMAL\n");
 int* temp;
 temp =(int*)malloc(n * sizeof(int));
printf("-------------------------------------\n");
for(i=0;i<n;i++)
pages[i]= -1;
j=0;
printf("Page   Content of Frames\n");
printf("----   -----------------\n");
for(i = 0; i < count; ++i){
        flag1 = flag2 = 0;
 for(j = 0; j < n; ++j){
   if(pages[j] == s[i]){
    flag1 = flag2 = 1;
        break;
               }
        }
if(flag1 == 0){
  for(j = 0; j < n; ++j){
    if(pages[j] == -1){
    pages[j] = s[i];
    flag2 = 1;
    break;
                }
        }
        }
if(flag2 == 0){
    flag3 =0;
for(j = 0; j <n; ++j){
    temp[j] = -1;
for(k = i + 1; k <count; ++k){
    if(pages[j] == s[k]){
        temp[j] = k;
            break;}
}
}
for(j = 0; j < n; ++j){
 if(temp[j] == -1){
    flag3 = 1;
    index = j;
     break;}
}
if(flag3 ==0){
max = temp[0];
index=0;
for(j = 1; j < n; ++j){
  if(temp[j] > max){
    max = temp[j];
     index = j;}
}
}
pages[index] = s[i];
fault++;
}
if(fault>0 && flag2==0)
printf("%02d F   ",s[i]);
else
printf("%02d     ",s[i]);
for(k=0;k<n;k++)
if(pages[k]==-1)
    printf(" ");
else
printf("%02d ",pages[k]);
printf("\n");
}
printf("-------------------------------------\n");
printf("Number of page faults = %d\n",fault);
}
