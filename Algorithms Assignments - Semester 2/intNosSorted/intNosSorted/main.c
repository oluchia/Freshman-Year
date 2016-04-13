//
//  main.c
//  intNosSorted
//
//  Created by Oluchi Anyabuike on 14/01/2016.
//  Copyright © 2016 Oluchi Anyabuike. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 100000

void merge(int[], int, int, int);
void mergeSort(int[], int, int);
void quickSort(int[], int, int);
void countSort(int [], int []);
void selectionSort(int []);

int main(void)
{
    int i;
    int arrA[SIZE];
    int arrB[SIZE];
    int val = 0;
    
    FILE *fptr;
    
    fptr = fopen("//Users/OluchiAnyabuike/Desktop/intNos1.txt", "r");
    
    i = 0;
    
    fscanf(fptr, "%d\n", &arrA[i]);
    printf("%d\n", arrA);
    
    i++;
    
    while (!feof(fptr))
    
    {
        fscanf(fptr, "%d\n", &arrA[i]);
        printf("%d\n", arrA[i]);
        i++;
    }
    
    val = i;

    mergeSort(arrA, 0, SIZE -1);
    // quickSort(arrA, 0, SIZE - 1);
    // countSort(arrA, arrB);
    // selectionSort(arrA);
    
    printf("\n Printing Sorted Array \n");
    // prints quickSort output
    /* for (i= 0; i <SIZE; i++)
    {
        printf("%d\n", arrA[i]);
        
    } */
    
    // prints selectionSort/mergeSort output
    i = 0;
    while (i < SIZE)
    
    {
        printf("%d\n", arrA[i]);
        i = i+1;
    }
    
    //write arrB back to arrA - for counting Sort
    /* for(i=0; i < SIZE; i++)
    {
        arrA[i] = arrB[i];
        printf("%d \n", arrA[i]);
    } */
    
    
    clock_t time;
    time = clock();
    
    //do work
    
    time = clock() - time;
    
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
    
    printf("\nSelection Sort took %lf seconds to execute \n", time_taken);
    
    fclose(fptr);
    
    fptr = fopen("//Users/OluchiAnyabuike/Desktop/intNosSorted.txt", "w+");
    
    if (fptr != NULL)
    {
    
        for(i = 0; i < SIZE; i++)
            {
                fprintf(fptr, "%d\n", arrA[i]);
            }
    }
    
    fclose(fptr);
    return 0;
}

void mergeSort(int A[], int lb, int ub)
{
    int mid;
    
    if (lb < ub)
    {
        mid = ((lb + ub) /2);
        mergeSort(A, lb, mid);
        mergeSort(A, mid + 1, ub);
        merge(A, lb, mid, ub);
    }
    
}


// merge two sorted portions of A: lb to mid and mid+1 to ub
void merge(int A[], int lb, int mid, int ub)
{
    int i, j, k;
    int arrC[100000];	//temporary array to hold sorted values
    
    i = lb;			//index to lower half of array A[]
    j = mid+1;		//index to upper half of array A[]
    k = lb;			//index to arrC[]
    
    //keep iterating until reach end of one portion of array
    while(i <= mid && j <= ub) {
        if(A[i] < A[j]){
            arrC[k] = A[i];
            i++;
            k++;
        }
        else{
            arrC[k] = A[j];
            j++;
            k++;
        }
        
    } // end while
    
    //check which condition was true on exit from loop
    if(j == ub + 1){
        while(i <= mid){
            arrC[k] = A[i];
            i++;
            k++;
        }
    }
    else{
        while(j <= ub){
            arrC[k] = A[j];
            j++;
            k++;
        }
    }
    
    //write back sorted array arrC[] over A[] as will be needed in further calls
    for(k = lb; k <= ub; k++){
        A[k] = arrC[k];
    }
    
}

void quickSort(int A[], int startval, int endval){
    
    int i, k, temp, pivot;
    
    //i and k will traverse array: initialise
    i = startval;
    k = endval;
    
    if((endval - startval) < 1){
        return;
    }
    else
        //partition
        pivot = A[startval];
    while(k > i){
        
        //keep traversing from startval up ...
        while (A[i] <= pivot && i <= k && i <= endval){
            ++i;
        }
        
        //keep traversing from endval down ...
        while (A[k] > pivot && k >= i && k >= startval){
            --k;
        }
        
        //if i at value > pivot and k at value <= pivot but k still > i
	       if(k > i){ //swap values at k and i
               temp = A[i];
               A[i] = A[k];
               A[k] = temp;
           }
        
    } // end outer loop
    
    
    //out of this loop when k > i not true, i.e. k and i have crossed
    temp = A[startval];
    A[startval] = A[k];
    A[k] = temp;
    
    //now sort the two sub-arrays
    quickSort(A, startval, k - 1);  //left partition
    quickSort(A, k + 1, endval);   //right partition
    
}

void countSort(int arrA[], int arrB[])
{
    int i, value, count;
    int k = 1000;
    int freq[1001];
    
    
    for(i = 0; i <= k; i++)
    {
        freq[i] = 0;
    }
    
    //count frequencies of values in arrA[] and store in freq[]
    for(i=0; i < SIZE; i++)
    {
        freq[arrA[i]] = freq[arrA[i]] + 1;
    }
    
    
    //get lessthan or equal to in freq
    for(i=1; i <= k; i++)
    {
        freq[i] = freq[i] + freq[i-1];
    }
    
    //put sorted data in to arrB
    for(i=0; i < SIZE; i++)
    {
        value = arrA[i]; //value to place in B
        count = freq[value];  //freq of value
        arrB[count-1] = value; //place value in arrB
        freq[value] = freq[value] - 1; //decrement values <= current value
    }//next value in arrA

    
}

void selectionSort(int arrA[])
{
    int i, j, min, temp;
    
    
    i = 0;
    while (i < SIZE-1){
        min = i;
        j = min + 1;
        
        //find next smallest
        while (j < SIZE){
            if (arrA[j] < arrA[min]){
                min = j;
            }
            j =  j + 1;
        }
        //swap
        
        temp = arrA[i];
        arrA[i] = arrA[min];
        arrA[min] = temp;
        
        i = i + 1;
        
    } //end outer while
    
}




