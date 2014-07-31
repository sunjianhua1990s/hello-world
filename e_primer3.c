//compute e 
//program 3

#include <stdio.h>

//umber of significant digit=(DN-1)*4
#define DN 2504

int euler[DN], data[DN];
int step,n;

void precise_division()
{
	int i=0;
	long y=0,r=0;
	
	for(i=step;i<DN;i++)
	{
		y = 10000*r + data[i];
		data[i] = y/n;
		euler[i] += data[i];
		r = y%n;
	}
}

void revise()
{
	int c=0,i=0;
	
	for(i=DN-1;i>=0;i--)
	{
		euler[i] += c;
		if(euler[i]>9999)
		{
			c = euler[i]/10000;
			euler[i] = euler[i]%10000;
		}
		else
			c = 0;
	}
}

void euler_print()
{
	int i=0;
	
	printf("\n\nE=%d.\n",euler[0]);
	for(i=1;i<DN;i++)
	{
		printf("%.4d ",euler[i]);
		if((i%250)==0)
			printf("\n\tnow it has %d bit\n",i*4);
	}
	printf("\n\neulur number is ok\n");
}

void main()
{
	int i=0;
	step=0;
	n=1;
	
	for(i=0;i<DN;i++)
	{
		euler[i]=0;
		data[i]=0;
	}
	euler[0]=1;
	data[0]=1;
	
	while(1)
	{
		i=step;
		while(data[i]==0)
		{
			i++;
			if(i>=DN)
			goto _EXT;
		}
		
		step=i;
		precise_division();
		revise();
		n++;
	}

_EXT:
	euler_print();
}
