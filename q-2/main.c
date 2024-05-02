#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int es_q3(int arr[], int n);

int *readArr(int *n);


int main() {
    int n;
    int *arr = readArr(&n);
    if (!arr) {
        return 1;
    }

    printf("%d", es_q3(arr, n));
    free(arr);
    return 0;
}

int *readArr(int *n) {
    if (scanf("%d", n) != 1) {
        return NULL;
    }
    int *arr = malloc(*n * sizeof(int));
    if (!arr) {
        return NULL;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", arr + i) != 1) {
            free(arr);
            return NULL;
        }
    }
    return arr;
}

int es_q3(int arr[], int n) {
    //initializing variables
    int high = n - 1;
    int low = 0;
    int mid;
    //binary searching correct index
    while (high >= low) {
        mid = (high + low) / 2;
        //checking for a possible match - there are 2 types of
        // checks in order to handle boundaries issues
        if (mid < n - 1 && arr[mid] % 10 == 0 && arr[mid + 1] % 10 != 0) {
            return mid;
        }
        if (mid > 0 && arr[mid] % 10 != 0 && arr[mid - 1] % 10 == 0) {
            return (mid - 1);
        }
        //if the number%10 is 0, it means that necessarily a
        // match is on the right (could be on the left too but no guarantee),
        // this is because last number is -1
        if (arr[mid] % 10 == 0) {
            low = mid + 1;
        }
        //opposite condition to the one listed above, this
        // is also correct because first number is 0
        if (arr[mid] % 10 != 0) {
            high = mid - 1;
        }
    }
    //returning result. note that there has to be at least one
    // match given that first number is 0 and last one is -1
    return mid;
}
