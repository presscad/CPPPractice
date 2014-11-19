#include<stdio.h>
#include "interview.h"

void printNumbers()
{
    int x = 10;
    while( x --> 0 ) // To better understand, the statement could be as follows:while( (x--) > 0 )
    {
      printf("%d ", x);
    }
}
