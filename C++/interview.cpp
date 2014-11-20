#include<stdio.h>
#include "interview.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>

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

void oneLoopVSTwoLoops()
{
    const int n = 100000;
//#define ALLOCATE_SEPERATE
//#define ONE_LOOP


#ifdef ALLOCATE_SEPERATE
    double *a1 = (double*)malloc(n * sizeof(double));
    double *b1 = (double*)malloc(n * sizeof(double));
    double *c1 = (double*)malloc(n * sizeof(double));
    double *d1 = (double*)malloc(n * sizeof(double));
#else
    double *a1 = (double*)malloc(n * sizeof(double) * 4);
    double *b1 = a1 + n;
    double *c1 = b1 + n;
    double *d1 = c1 + n;
#endif

    //  Zero the data to prevent any chance of denormals.
    memset(a1,0,n * sizeof(double));
    memset(b1,0,n * sizeof(double));
    memset(c1,0,n * sizeof(double));
    memset(d1,0,n * sizeof(double));

    //  Print the addresses
    std::cout << a1 << std::endl;
    std::cout << b1 << std::endl;
    std::cout << c1 << std::endl;
    std::cout << d1 << std::endl;

    clock_t start = clock();

    int c = 0;
    while (c++ < 10000){

#ifdef ONE_LOOP
        for(int j=0;j<n;j++){
            a1[j] += b1[j];
            c1[j] += d1[j];
        }
#else
        for(int j=0;j<n;j++){
            a1[j] += b1[j];
        }
        for(int j=0;j<n;j++){
            c1[j] += d1[j];
        }
#endif

    }

    clock_t end = clock();
    std::cout << "seconds = " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
}

void denormalFloatVSNormalFloat()
{
#define FLOATING
    //if we flush denormals to zero by adding this to the start of the code:
    //Then the version with 0 is no longer 10x slower and actually becomes faster.
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    clock_t start = clock();

    const float x[16]={1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6};
    const float z[16]={1.123,1.234,1.345,156.467,1.578,1.689,1.790,1.812,1.923,2.034,2.145,2.256,2.367,2.478,2.589,2.690};
    float y[16];
    for(int i=0;i<16;i++)
    {
        y[i]=x[i];
    }
    for(int j=0;j<9000000;j++)
    {
        for(int i=0;i<16;i++)
        {
            y[i]*=x[i];
            y[i]/=z[i];
#ifdef FLOATING
            y[i]=y[i]+0.1f;
            y[i]=y[i]-0.1f;
#else
            y[i]=y[i]+0;
            y[i]=y[i]-0;
#endif

            if (j > 10000)
                std::cout << y[i] << "  ";
        }
        if (j > 10000)
            std::cout << std::endl;
    }

    clock_t end = clock();
    std::cout << "seconds = " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
}

StringVector& splitString(const std::string &s, char delim, StringVector &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
