#include "alg.h"
#include<iostream>
#include<string>

using namespace std;

size_t slenth(const char *s){
    if(NULL == s)
        return 0;
    const char *p = s;
    size_t len = 0;
    while(*p++ != '\0')
        ++len;
    return len;
}

void reverse(char *b){
    char c;
    int j;
    size_t len;
    len=strlen(b);
    j=len/2-1;
    while(j>=0)
    {
        c=*(b+j);
        *(b+j)=*(b+len-j-1);
        *(b+len-j-1)=c;
        j--;
    }
    b[len]='\0';
}

void insertSort(int arr[],size_t size){
    size_t i,j;
    int tmp;
    for(i=1;i<size;++i){
        tmp = arr[i];
        j = i - 1;
        while((j>=0) && arr[j]>tmp){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = tmp;
    }
}

void merge_array(int *list1, int list1_size, int *list2, int list2_size){
    int i, j, k;
    i = j = k = 0;

    int *list = (int*)malloc((list1_size + list2_size)*sizeof(int));

    while (i < list1_size && j < list2_size){
        list[k++] = list1[i] < list2[j] ? list1[i++] : list2[j++];
    }

    while (i < list1_size){
        list[k++] = list1[i++];
    }

    while (j < list2_size){
        list[k++] = list2[j++];
    }

    for (int ii = 0; ii < (list1_size + list2_size); ++ii){
        list1[ii] = list[ii];
    }
    free(list);
}

void merge_sort(int *list, int list_size){
    if (list_size > 1){
        int *list1 = list;
        int list1_size = list_size / 2;
        int *list2 = list + list_size / 2;
        int list2_size = list_size - list1_size;

        merge_sort(list1, list1_size);
        merge_sort(list2, list2_size);

        merge_array(list1, list1_size, list2, list2_size);
    }
}

void radixSort(int a[], size_t n){
    int i, m = a[0], exp = 1;
    int b[20] = {0};

    //Get the greatest value in the array a and assign it to m
    for (i = 1; i < n; i++){
        if (a[i] > m)
        m = a[i];
    }

    //Loop until exp is bigger than the largest number
    while (m / exp > 0)
    {
        int bucket[10] = { 0 };

        //Count the number of keys that will go into each bucket
        for (i = 0; i < n; i++)
            bucket[(a[i] / exp) % 10]++;

        //Add the count of the previous buckets to acquire the indexes after the end of each bucket location in the array
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1]; //similar to count sort algorithm i.e. c[i]=c[i]+c[i-1];

        //Starting at the end of the list, get the index corresponding to the a[i]'s key, decrement it, and use it to place a[i] into array b.
        for (i = n - 1; i >= 0; i--)
            b[--bucket[(a[i] / exp) % 10]] = a[i];

        //Copy array b to array a
        for (i = 0; i < n; i++)
            a[i] = b[i];

        //Multiply exp by the BASE to get the next group of keys
        exp *= 10;
    }
}

void countASIICs(const char *s){
    char asc[256];

    for(int i=0;i<256;i++){
        asc[i] = 0;
    }

    while(*s != '\0'){
        asc[*s++]++;
    }

    for(int i=0;i<256;i++){
        printf("%d ",asc[i]);
    }
}
