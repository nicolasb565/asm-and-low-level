#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void merge(int A[], int temp[], int left, int mid, int right){
    int cur_left = left;
    int cur_right = mid;
    int temp_pos = left;
    
    /*go over element in sub arrays and put them sorted into temp array until we get to the end of one of the sub array*/
    while(cur_left < mid && cur_right <= right){
        if(A[cur_left] < A[cur_right]){
            temp[temp_pos] = A[cur_left];
            temp_pos++, cur_left++;
        }
        else{
            temp[temp_pos] = A[cur_right];
            temp_pos++, cur_right++;
        }
    }
    
    /*if we did not go over all the element in the left sub array, put them at the end of the temp array*/
    while(cur_left < mid){
        temp[temp_pos] = A[cur_left];
        temp_pos++, cur_left++;
    }
    
    /*if we did not go over all the element in the right sub array, put them at the end of the temp array*/
    while(cur_right <= right){
        temp[temp_pos] = A[cur_right];
        temp_pos++, cur_right++;
    }
    
    int i;
    for(i = left; i <= right; i++){
        A[i] = temp[i];
    }
}

void merge_sort(int A[], int temp[], int left, int right){
    int mid;
    if(right > left){
        mid = (right + left) / 2;
        merge_sort(A, temp, left, mid);
        merge_sort(A, temp, mid + 1, right);
        merge(A, temp, left, mid + 1, right);
    }
}

int main(void){
    int A[20];
    int temp[20];
    
    time_t t;
    srand((unsigned) time(&t));
    
    int i;
    for(i = 0; i < 20; i++){
        A[i] = rand() % 20;
    }
    
    merge_sort(A, temp, 0, 19);
    
    for(i = 0; i < 20; i++){
        printf("%i ", A[i]);
    }
    printf("\n");
    
    return 0;
}
