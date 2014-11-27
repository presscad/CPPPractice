#ifndef ALG_H
#define ALG_H

#include<string>

//Caculate a string length
size_t slenth(const char *s);

//Reverse a string
void reverse(char *b);

//Insert sort:worst case O(n^2)
void insertSort(int arr[],size_t size);

//Merge sort:worst case O(nlogn)
void merge_array(int *list1, int list1_size, int *list2, int list2_size);
void merge_sort(int *list, int list_size);

//Radix sort:worst case O(kn),k is digit count.
void radixSort(int arr[],size_t size);

//Print the count occurence of each ASCII character in given string.
void countASIICs(const char *s);

#endif // ALG_H
