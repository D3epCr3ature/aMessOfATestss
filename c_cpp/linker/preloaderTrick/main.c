
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	int arr1[10] = {1, 2, 3, 3};
	int arr2[10];
        int *ptr = NULL;
        int arg1;

        /* Small verification on input */
        if (argc != 2) {
                printf("Wrong usage...\n"
                       "usage: %s {1..10}\n", *argv);
                return -1;
        }

        arg1 = atoi(argv[1]);
        if (arg1 < 1 || arg1 > (sizeof(arr1)/sizeof(*arr1))) {
                printf("Number of elements to copy not valid...\n"
                       "usage: %s {1..10}\n", *argv);
                return -2;
        }
	
        ptr = memcpy(arr2, arr1, arg1);
	printf("arr1: %p\n", arr1);
	printf("arr2: %p\n", arr2);
	printf(" ptr: %p\n", ptr);

	return 0;

}
