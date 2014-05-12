#include "alg.h"

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
    int j, len;
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
