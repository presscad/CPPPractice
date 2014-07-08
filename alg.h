#ifndef ALG_H
#define ALG_H

#include<iostream>
#include<string>

using namespace std;

size_t slenth(const char *s);
void reverse(char *b);


//Insert sort:worst case O(n^2)
void insertSort(int arr[],size_t size);

//Merge sort:wost case O(nlogn)
void merge_array(int *list1, int list1_size, int *list2, int list2_size);
void merge_sort(int *list, int list_size);

#endif // ALG_H
