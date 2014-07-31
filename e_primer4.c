//compute e 
//program 4

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//umber of significant digit
#define N 10000

typedef unsigned int UINT;

int GetLength(int m)
{
	int n=1;
	double x=2.0/2.72;
	while(m)
	{
		while(x<1.0)
		{
		    n++;
			x*=(double)(n+1);
		}
		while(x>=1.0 && m)
		{
			x/=10.0;
			--m;
		}
	}
	while(x<1.0)
	{
	    n++;
		x*=(double)(n+1);
	}
	return n;
}
void main()
{
	const UINT base=1000000;
	int i,j,k,m;
	UINT *r=NULL;
    UINT *euler=NULL;
    UINT y=0;
    
	m=GetLength(N);
	
	r=(UINT *)calloc(m+1,sizeof(UINT));
	euler=(UINT *)calloc(N,sizeof(UINT));
	
	assert(r!=NULL);
	assert(euler!=NULL);
	
	for(i=0;i<=m;++i)
	{
		r[i]=1;
		euler[i]=0;
    }
    
    j=1;
    euler[0] = 2;
    
	for(k=N;k>0;k-=6)
	{
		y=0;
		for(i=m;i>=2;--i)
		{
			y = y + r[i]*base;
			r[i] = y%i;
			y /= i;
		}

   		if(k<6)
		{
			euler[j++] = y%base;
		}
		else
		{
			if(y<base)
				euler[j++] = y;
			else
			{
				if(r)
					free(r);
				return;
			}
		}
	}
	if(r)
		free(r);
		
    printf("\n\nE=%d.\n",euler[0]);
	for(i=1;i<j;i++)
	{
		printf("%.6d ",euler[i]);
		if((i%100)==0)
			printf("\n\tnow it has %d bit\n",i*6);
	}
	printf("\n\neulur number is ok\n");
	
	if(euler)
		free(euler);
	
	return;
}
