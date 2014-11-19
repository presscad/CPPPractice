#include<stdio.h>
#include "interview.h"
#include <algorithm>
#include <ctime>
#include <iostream>

void printNumbers()
{
    int x = 10;
    while( x --> 0 ) // To better understand, the statement could be as follows:while( (x--) > 0 )
    {
      printf("%d ", x);
    }
}

void sortedArrayVSUsorted()
{
    // Generate data
    const unsigned arraySize = 32768;
    int data[arraySize];

    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = std::rand() % 256;

    // !!! With this, the next loop runs faster
    std::sort(data, data + arraySize);

    // Test
    clock_t start = clock();
    long long sum = 0;

    for (unsigned i = 0; i < 100000; ++i)
    {
        // Primary loop
        for (unsigned c = 0; c < arraySize; ++c)
        {
            if (data[c] >= 128) //the culprit is this if-statement
                sum += data[c];
            //int t = (data[c] - 128) >> 31;
            //sum += ~t & data[c];
            //sum += data[c] >=128 ? data[c] : 0;
        }
    }

    double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;

    std::cout << elapsedTime << std::endl;
    std::cout << "sum = " << sum << std::endl;
}
