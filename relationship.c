#include <stdio.h>
#include <math.h>

//Zach Wadhams, Week3Work (monday)

int main(void) {
    int inputOne;
    int inputTwo;

    for (int i = 0; i < 5; i++) {
        printf("Enter a number to start with: ");
        scanf("%d", &inputOne);
        printf("Enter a second number to compare: ");
        scanf("%d", &inputTwo);

        if (inputOne == inputTwo) {
            printf("The two numbers are equal \n");
        }

        if (inputOne < inputTwo) {
            printf("Number One is less than Number Two \n");
        }
            
        if (inputOne > inputTwo) {
            printf("Number One is greater than Number Two \n");
        }

        if (inputOne != inputTwo) {
            printf("The two numbers are not equal to eachother \n");
        }

    }

    return(0);
}
