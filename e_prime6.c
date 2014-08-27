#include <stdio.h>
#include <stdlib.h>
#include <math.h>  //Linux, gcc -lm
#include <stdbool.h>
#include <assert.h>

#define MAX_E_BITE_N 1000
#define PRIME_N 1000000

#define Long64 long long

typedef unsigned int UINT;


int get_length(int nbite)
{
	int m = 1;
	double x = 2.0/2.72;
	while(nbite)
	{
		while(x<1.0)
		{
		    m++;
			x *= (double)(m+1);
		}
		while(x >= 1.0 && nbite)
		{
			x /= 10.0;
			--nbite;
		}
	}
	while(x < 1.0)
	{
	    m++;
		x *= (double)(m+1);
	}
	return m;
}


int create_e(Long64 *euler, const UINT base, int m)
{
    UINT *r = NULL;
    UINT y = 0;
    int i = 0,j = 0,k = 0;

	r=(UINT *)calloc(m+1,sizeof(UINT));
	
	assert(r != NULL);
	assert(euler != NULL);
	
	for(i = 0;i <= m; ++i)
	{
		r[i] = 1;
		euler[i] = 0;
    }
    
    j = 1;
    euler[0] = 2;
    
	for(k = MAX_E_BITE_N; k > 0; k -= 5)
	{
		y = 0;
		for(i = m; i >= 2; --i)
		{
			y = y + r[i]*base;
			r[i] = y%i;
			y /= i;
		}

   		if(k < 5)
		{
			euler[j++] = y%base;
		}
		else
		{
			if(y < base)
				euler[j++] = y;
			else
			{
				if(r)
					free(r);
				return 0;
			}
		}
	}
	if(r)
		free(r);
		
    printf("\n\nE=%lld.\n",euler[0]);
	for(i = 1; i < j; i++)
	{
		printf("%.5lld ",euler[i]);
	}
	printf("\n\neulur number is ok j=%d\n",j);
	
	return j;
}

Long64 create_prime_table(bool *prime, Long64 *prime_table, Long64 n)
{
    Long64 i,j,k;

    i = 2;
    k = 0;
    for(i = 2;i <= n;i++)
    {
        if(prime[i] == 0)
        {
            prime_table[k++] = i;
//            printf("%lld : %lld \n",k,i);
        }
        for(j = 0; j < k && (prime_table[j]*i) <= n; j++)
        {
            prime[prime_table[j] * i] = 1;
            if(i%prime_table[j] == 0)
                break;
        }
    }
     
    return k;
}

bool is_prime(Long64 prime_table[], Long64 length, Long64 n)
{
    Long64 i;
    
    for(i = 0; i < length; i++)
    {
        if(n%(prime_table[i]) == 0)
        {
            return false;
        }
    }
    return true;
}


void main()
{
	const UINT base = 100000;
	int m = 0,elength = 0,j = 0,find_number = 10;
	
    Long64 *euler = NULL;
    bool *prime = NULL;
    Long64 *prime_table = NULL;
    
    Long64 i = 0,length = 0,data = 0;
    
    Long64 ten[10] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
    
	m = get_length(MAX_E_BITE_N);

	euler = (Long64 *)calloc(MAX_E_BITE_N,sizeof(Long64));
	
	elength = create_e(euler,base,m);
	

    prime = (bool *)calloc(PRIME_N+1,sizeof(bool));
    prime_table = (Long64 *)calloc(PRIME_N,sizeof(Long64));

    length = create_prime_table(prime,prime_table,PRIME_N);
    
    if(prime)
		free(prime);
    
    m = 0;
    for(i = 1; (i+2) < elength; i++)
	{
	    for(j = 0; j < 5; j++)
	    {
	        data = euler[i]%ten[5-j]*ten[5+j] + euler[i+1] * ten[j] + euler[i+2]/ten[5-j];
	        
//	        printf("data : %lld \n",data);
	    
	        if(is_prime(prime_table,length,data) == true)
            {
                printf("find it! %d:%lld:%lld\n",++m,5*(i-1)+j+1,data);

          	    if(m == find_number)
        	        break;    
            }	    	    
	    }
	    
	    if(m == find_number)
	        break;    
	}
	
	
	if(euler)
		free(euler);
    if(prime_table)
		free(prime_table);
	
}

