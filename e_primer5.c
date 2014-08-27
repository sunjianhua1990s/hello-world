#include <stdio.h>
#include <stdlib.h>
#include <math.h>  //Linux, gcc -lm
#include <stdbool.h>

#define Long64 long long
#define MAX_N 100000

//Long64 prime_table[1000]={0};

////judge prime 
////program 1
//bool prime_1(int n)
//{
    //int i;
    //for(i=2;i<n;i++)
    //{
        //if(n%i==0)
        //{
            //return false;
        //}
    //}
    //return true;
//}

////judge prime 
////program 2
//bool prime_2(int n)
//{
    //int i,n2;
    
    //n2=sqrt(n);
    //for(i=2;i<=n2;i++)
    //{
        //if(n%i==0)
        //{
            //return false;
        //}
    //}
    //return true;
//}

////create prime less then n 
////program 3

//void create_prime_table(Long64 n)
//{
    //Long64 i,j,n2;
    //bool prime[MAX_N+1]={0};

    //n2=sqrt(n);
    
    //i=2;
    //for(i=2;i<=n2;i++)
    //{
        //if(prime[i]==0)
        //{
            //for(j=i+i;j<=n;j+=i)
            //{
                //prime[j]=1;
            //}
        //}
    //}
    
    //j=0;
    //for(i=2;i<=n;i++)
    //{
        //if(prime[i]==0)
        //{
            //prime_table[j]=i;
            //j++;
            //printf("%lld : %lld \n",j,i);
        //}
    //}
//}

//create prime less then n 
//program 4

    void create_prime_table2(Long64 n)
    {
        Long64 i,j,k;
        bool *prime;
        Long64 *prime_table;

        prime=(bool *)calloc(MAX_N+1,sizeof(bool));
        prime_table=(Long64 *)calloc(MAX_N/100,sizeof(Long64));

        i=2;
        k=0;
        for(i=2;i<=n;i++)
        {
            if(prime[i]==0)
            {
                prime_table[k++]=i;
                //printf("%lld : %lld \n",k,i);
            }
            for(j=0;j<k && prime_table[j]*i <= n;j++)
            {
                prime[prime_table[j]*i]=1;
                if(i%prime_table[j]==0)
                    break;
            }
        }
        printf("k = %lld\n",k);

        if(prime_table)
            free(prime_table);
        if(prime)
            free(prime);
    }

    void main()
    {
        create_prime_table2(MAX_N);
    }


//create prime less then n 
//program 5

Long64 create_prime_table3(bool *prime, Long64 *prime_table, Long64 n)
{
    Long64 i,j,k;
    
    i=2;
    k=0;
    for(i=2;i<=n;i++)
    {
        if(prime[i]==0)
        {
            prime_table[k++]=i;
            //printf("%lld : %lld \n",k,i);
        }
        for(j=0;j<k && prime_table[j]*i <= n;j++)
        {
            prime[prime_table[j]*i]=1;
            if(i%prime_table[j]==0)
                break;
        }
    }
     
    return k;
}

bool prime3(Long64 prime_table[], Long64 length, Long64 n)
{
    Long64 i;
    
    for(i=0;i<length;i++)
    {
        if(n%(prime_table[i])==0)
        {
            return false;
        }
    }
    return true;
}

void main()
{   
    bool *prime;
    Long64 *prime_table,i=0,j=0,length=0;
    
    prime=(bool *)calloc(MAX_N+1,sizeof(bool));
    prime_table=(Long64 *)calloc(MAX_N,sizeof(Long64));

    length = create_prime_table3(prime,prime_table,MAX_N);
    
    for(i=1000000000; i<10000000000; i++)
        if(prime3(prime_table,length,i)!=false)
            printf("%lld : %lld\n",j++,i);
}
