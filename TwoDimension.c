#include <stdio.h>
#include <math.h>


int main(void) {
    
    int fd = 0, sd = 0;    
    int myArray[6][8];
    
    FILE *myFile = fopen("/public/examples/chap7/wed_2-3_in.txt", "r");

    int input;
    while (fscanf(myFile, "%d", &input) != EOF) {
        myArray[fd][sd] = input;
        
        if (input == 0) {
             fd++, sd = 0;
        }

        else {
            sd ++;
        }
    }
    
    fclose(myFile);    

    int sum = 0;
    for (int i = 0; i < fd; i++) {
        for (int j = 0; myArray[i][j] != 0; j++) {
            sum += myArray[i][j];
        } 

    }        

    printf("Sum of array: %d", sum); //should be 296

    return(0);
}
