#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *printFile; //output file
FILE *inputFile; //input file

int readIn(char* data[]) { //function to read in data while alloticating 
                           //memory. returns the number of hurricanes
    inputFile = fopen("/public/lab4/hurricanes.csv", "r");
        
    if (inputFile == NULL) { //checks to see if the file opened correctly
        printf("ERROR: File has not opened correctly");
        exit(0);
    }

    int i = 0;
    do {
        data[i] = malloc(sizeof(char) * 100);
    } while (fgets(data[i++], 100, inputFile) != NULL);
        
    --i;

    fclose(inputFile);    

    return i;
}

void sortData(char* data[], int num) { //function that orders the data 
                                       //alphabetically using strcmp
    char *temp; //used to hold data for swap

    for (int i = 0; i < num; i++) {
        for (int j = i; j < num; j++) {
            
            if (strcmp(data[i], data[j]) > 0) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    return;
}

void printData(char* data[], int num) { //function to print out data 
    printFile = fopen("output.txt", "w"); //in a specified format 

    fprintf(printFile, "Hurricanes in Florida with category and date \n"); 
    
    char *token; //token used to seperate data for printing
    
    for (int i = 0; i < num; i++) {
        
        token = strtok(data[i], ",");
        
        fprintf(printFile, "%-10s", token);

        token = strtok(NULL, ",");

        fprintf(printFile, "%c   ", token[9]);

        token = strtok(NULL, ",");

        fprintf(printFile, "%s ", token);

        token = strtok(NULL, ",");        

        fprintf(printFile, "%s", token);

    }

    fclose(printFile);

    return;
}


int main(void) {
    int size = 0;

    char *hurricanes[100];    
    
    size = readIn(hurricanes);
    
    sortData(hurricanes, size); 

    printData(hurricanes, size);

    return(0);
}
