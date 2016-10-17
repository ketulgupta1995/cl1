#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

class kmeans
{
int k;
int n;
float data[100][2];
float means[100][2];
float newmeans[100][2];
int label[100];

public:
kmeans()
{
cin>>k;
cin>>n;
for(int i=0;i<n;i++)
{
for(int j=0;j<2;j++)
cin>>data[i][j];
}

for(int i=0;i<k;i++)
{
for(int j=0;j<2;j++)
means[i][j]=data[i][j];
}

}

int perform_clus(){
	int max;
	cin>>max;
	while(max!=0)
	{

	assig_lables();

	printmeansandlables();

	calc_means();


	if (check_means()==0)
	{
	break;
	}
	else
	{
	copymeans();
	}

	max--;

	}

	return 0;

}


void printmeansandlables()
{
cout<<"means";
for(int i=0;i<k;i++)
{
	for(int j=0;j<2;j++)
	{
		cout<<means[i][j]<<"\n";
	}
	
}
cout<<"labels";
for(int i=0;i<n;i++)
{
cout<<label[i]<<"\n";
}


}

int assig_lables()
{
	for(int i=0;i<n;i++)
{
label[i]=leastdist(i);
}
return 0;
}

int leastdist(int num)
{
int min=0;
float min_dist=99999.0;
float dist[100];
	for(int j=0;j<k;j++)
	{	
		dist[j]=0;
		for(int h=0;h<2;h++)
		{
		dist[j]+=((fabs(data[num][h]-means[j][h]))*(fabs(data[num][h]-means[j][h])));
		}	
		if(min_dist>dist[j])
		{
			min_dist=dist[j];
			min=j;
		}
	}
return min; 
}

int calc_means()
{
float sum[100][2];
int count[100]={0};
for(int i=0;i<k;i++)
{
for(int j=0;j<2;j++)
{
count[i]=0;
sum[i][j]=0;
}
}

for(int i=0;i<n;i++)
{
count[label[i]]+=1;
	for(int j=0;j<2;j++)
	{
		sum[label[i]][j]+=data[i][j];
	}
}

for(int i=0;i<k;i++)
{
	for(int j=0;j<2;j++)
	{
		if(count[i]==0)
		{
			newmeans[i][0]=data[1+rand()%n-2][0];
			newmeans[i][1]=data[1+rand()%n-2][1];
			break;		
		}	
		newmeans[i][j]=sum[i][j]/count[i];
	}
	
}

return 0;
}

int check_means()
{
int diff=0;
for(int i=0;i<k;i++)
{
	for(int j=0;j<2;j++)
	{
		if(newmeans[i][j]!=means[i][j])
		{
			diff=1;
			break;
		}
	}
	
}

return diff;
}

void copymeans()
{

for(int i=0;i<k;i++)
{
	for(int j=0;j<2;j++)
	{
		means[i][j]=newmeans[i][j];
	}
	
}

}


};



int main()
{
kmeans *pk=new kmeans();


pk->perform_clus();
return 0;
}

