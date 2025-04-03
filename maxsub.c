#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100

int* bruteForce(int* arr, int size) {
    int* result = (int*) malloc(3*sizeof(int)); // {left, right, sum}
    int sum = arr[0];
    int left = 0, right = 0;
    for (int i = 0; i < size; i++) {
        int curSum = 0;
        for (int j = i; j < size; j++) {
            curSum += arr[j];
            if (curSum > sum) {
                sum = curSum;
                left = i;
                right = j;
            }
        }
    }
    result[0] = left, result[1] = right, result[2] = sum;
    return result;
}

int* findCrossing(int* arr, int low, int mid, int high) {
    int leftSum = INT_MIN;
    int sum = 0;
    int left;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
            left = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int right;
    for (int i = mid+1; i <= high; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
            right = i;
        }
    }

    int* result = (int*) malloc(3*sizeof(int));
    result[0] = left, result[1] = right, result[2] = leftSum+rightSum;
    return result;
}

int* divideAndConquer(int* arr, int low, int high) {    
    if (low==high) {
        int* elem = (int*) malloc(3*sizeof(int));
        elem[0] = low, elem[1] = low, elem[2] = arr[low]; // elem = {low, low, arr[low]}
        return elem;
    } else {
        int mid = (high+low)/2;
        int* left = divideAndConquer(arr, low, mid);
        int leftsum = left[2];
      
        int* right = divideAndConquer(arr, mid+1, high);
        int rightsum = right[2];
       
        int* cross = findCrossing(arr, low, mid, high);
        int crosssum = cross[2];

        if (leftsum >= rightsum && leftsum >= crosssum) {
            free(right);
            free(cross);
            return left;
        } else if (rightsum >= leftsum && rightsum >= crosssum) {
            free(left);
            free(cross);
            return right;
        } else {
            free(left);
            free(right);
            return cross;
        }
    }
}

int main() {
    int arr[] = {-97, -98, 67, 81, 25, 55, 16, -30, 54, 51, 51, 76, -87, 9, -46, -11, 15, -73, 38, 9, 84, 43, -31, 61, 16, -65, -12, 99, -26, 26, 56, -48, 62, 38, 33, 1, -86, 84, -29, 43, 83, 5, 92, -58, 61, 28, 18, -47, 28, -39, 20, -75, -26, -69, 53, -24, 23, 81, -60, 84, 41, 97, -13, 5, 5, -82, -13, -65, 21, 52, -75, 12, 62, 73, 87, -44, 47, 29, 97, -55, 90, 98, 69, -66, -14, -83, -44, -3, 54, -3, -20, 3, 35, 61, -30, -81, 45, -9, 48, -11};
    
    clock_t begin = clock();
    int* r = bruteForce(arr, SIZE);
    clock_t end = clock();
    double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("(%d, %d, %d, %lf)\n", r[0], r[1], r[2], time_spent);
    free(r);

    begin = clock();
    r = divideAndConquer(arr, 0, SIZE-1);
    end = clock();
    time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("(%d, %d, %d, %lf)\n", r[0], r[1], r[2], time_spent);
    free(r);

    return 0;
}
