#include <stdio.h>
#include <math.h>
#include <stdbool.h>
int sets[10][6];

//Zach Wadhams - Lab2

int seperate(long int n, int column) { //function to seperate the long int into single integers
    int count = 0;
    while(n > 1) {
        sets[column][count] = n % 10;
        n /= 10;
        count++;
    }
    sets[column][count] = n % 10;
    return(1);
}

int compare(int set1[], int set2[]) { //function to compare the two sets to determine if an item 
    int j;                            //from the firtst set is is the second set
    for (int i = 0; set2[i] != 0; ++i) { //repeats this until all are found, if one isn't - reutrn false
        for (j = 0; set1[j] != 0 ; ++j) {
            if (set2[i] == set1[j]) {
                break;
            }
        }
        if (set1[j] == 0) {
            return 0;
        }
    }
    return 1;
}

void printSets(int set1[], int set2[]) { //function to print out the sets in a set format
    printf("Set ");
    for (int i = 0; set2[i] != 0; ++i) {
        printf("%d", set2[i]);
    }
    printf(" is a subset of Set ");
    for (int i = 0; set1[i]; ++i) {
        printf("%d", set1[i]);
    }
    printf("\n");
    return;
}

int main(void) {
    
    int fd = 0;
    FILE *file = fopen("/public/lab2/sets.txt", "r");
    long int input;

    while (fscanf(file, "%ld", &input) != EOF) { //scans in each number and calls the seperate function
        seperate(input, fd);                     //to put it in the 2d array
        fd++;
    }
        
    fclose(file);

    for (int i = 0; i < fd; i++) {      //check to make sure that you aren't comparing the same sets
        for (int j = 0; j < fd; j++) {
            if (i != j) {
                if (compare(sets[i], sets[j])) {
                    printSets(sets[i], sets[j]);                  
                }   
            }
        }

    }
     

    return(0);
}
