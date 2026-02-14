/**
 * Find the 2nd largest number in a list, without sorting
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

void printArray(uint32_t *arr, size_t size) {
        size_t i = 0;

        if (size < 1) {
                printf("Array is empty\n");
                return;
        }

        printf("Array's content:\n[ ");
        for (i = 0; i < size; i++) {
                printf("%d ", arr[i]);
        }
        printf("]\n");
}

bool secondLargest(uint32_t *arr, size_t size, uint32_t *res) {
        int32_t firstMax = 0;
        size_t i = 0;

        if (size < 2 || !res || !arr) {
                return false;
        } else if (size == 2) {
                *res = arr[0] < arr[1] ? arr[0] : arr[1];
                return true;
        }

        firstMax = *res = *arr;

        for (i = 0; i < size; i++) {
                if (arr[i] > firstMax) {
                        *res      = firstMax;
                        firstMax  = arr[i];
                } else if (arr[i] > *res) {
                        *res = arr[i];
                }
        }

        return true;
}

int main(void) {
        //uint32_t arr[] = {10,  4,  2,  6, 20, 15, 30, 12, 18};
        //uint32_t arr[] = {20,  4,  2,  6, 10, 15, 30, 12, 18};
        //uint32_t arr[] = {18,  4,  2,  6, 10, 15, 30, 12, 20};
        uint32_t arr[] = {18, 20,  2,  6, 10, 15, 30, 12,  4};
        uint32_t res   = 0;

        printArray(arr, sizeof(arr)/sizeof(*arr));

        if ( ! secondLargest(arr, sizeof(arr)/sizeof(*arr), &res) ) {
                printf("Illegal size, input array or return address\n");
                return EXIT_FAILURE;
        }
        printf("Second max. is: %d\n", res);

        return EXIT_SUCCESS;
}
