#include <stdio.h>
#include <math.h>


int main(void) {

    int length;
    printf("How many elements do you want in your array? ");
    scanf("%d", &length);
    int myArray[length];

    printf("Enter %d integers to add to the array: \n", length);
    for (int i = 0; i < length; i++) {
        printf("element - %d : ", i);
        scanf("%d", &myArray[i]);
    }

    printf("\nYou entered %d values to the array \n", length);
    printf("Array in reverse order: ");    
    
    for (int i = length - 1; i >= 0; i--) {
        printf("%2d", myArray[i]);
    }

    return(0);
}
