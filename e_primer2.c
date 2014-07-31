//compute e 
//program 2

#include <stdio.h>
#define N 20

int main()
{
    double e = 0.0;
    int i = 0;

    for(i = N; i > 0; i--){
        e = (e + 1.0) / i;
    }

    printf ("e=%.20lf\n",e );
    return 0;
}


