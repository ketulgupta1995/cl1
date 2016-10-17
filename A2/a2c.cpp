
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
int n;
using namespace std;

struct array{
int *a;
int l;
int r;
};


void swap(int a[],int x,int y)
{
int temp=a[x];
a[x]=a[y];
a[y]=temp;
}


int partition(int a[],int p,int q)
{
int m=p;

cout<<"partition";
int piv=a[p];
int i=p;
int j=q;
while(i<j)
{
while(a[i]<=piv && i<j)
{
i++;
}
while(a[j]>piv && i<=j)
{
j--;
}
if(i<j)
swap(a,i,j);

}

a[m]=a[j];
a[j]=piv;
m=j;
return m;
}


void* qs(void * argm)
{

array * ar=(array *)argm;
//cout<<"came here";
if(ar->l<ar->r)
{
int s=partition(ar->a,ar->l,ar->r);
cout<<"pivot "<<s<<"\n";

cout<<"thrad id "<<pthread_self();
array a1,a2;
a1.a=new int[n];
a2.a=new int[n];

a1.a=ar->a;
a2.a=ar->a;

a1.l=ar->l;
a1.r=s-1;

a2.l=s+1;
a2.r=ar->r;

pthread_t p[2];
pthread_create(&p[0],NULL,&qs,(void*)&a1);
pthread_create(&p[1],NULL,&qs,(void*)&a2);
pthread_join(p[0],NULL);
pthread_join(p[1],NULL);

}
}



int main()
{
cin>>n;
int a[n];
for (int i=0;i<n;i++)
{
cin>>a[i];
}
array me;
me.a=a;
me.l=0;
me.r=n-1;
qs((void *)&me);

for (int i=0;i<n;i++)
{
cout<<me.a[i]<<"\n";
}

return 0;

}


