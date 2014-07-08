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
