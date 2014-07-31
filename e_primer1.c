//computer e 
//program 1

#include <stdio.h>
#define N 20

int main()
{
    double e = 1.0, t = 1.0;
    int i = 0;

    for(i = 1; i <= N; i++){
        t = t / i;
        e = e + t;
    }

    printf ("e=%.20lf\n",e );
    return 0;
}


