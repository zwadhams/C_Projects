#include <stdio.h>

//Zach Wadhams - Lab3

int preCheck(char c, int count) { //gets number of preprocessor statements in the input file
    
    switch (c) {
            
        case '#':  
            count++;
            break;
    
    }
        
    return(count);
}

double commentCheck(char c, double count) { //finds number of one line comments in the input file
    
    switch (c) {
        
        case '/':
            count += 0.5;
            break;

    }
    return count;
}

int curlyBracketCheck(char c, int count) { //checks to see if all brackets are good
    
    switch (c) {
        
        case '{':
            count ++;
            break;
        
        case '}':
            count --;
            break;

    }

    return(count);
}

int parenCheck(char c, int count) { //handles the parentheses

    switch (c) {
        
        case '(':
            count ++;
            break;

        case ')':
            count --;
            break;

    }

    return(count);
}

void printFunction(int hashCount, double slashCount, int curlyCount, int parenCount) { //prints in a specified format

    printf("There are %d pre-processor statements \n", hashCount);
    printf("There are %0.f single line comments \n", slashCount);

    curlyCount = (curlyCount == 0) ? printf("All curly brackets match \n") : printf("Curly bracket error \n");

    parenCount = (parenCount == 0) ? printf("All parentheses match \n") : printf("Parentheses error \n");


    return;
}

int main(void) {
    int pre = 0;
    double comments = -0.5;
    int curly = 0;
    int paren = 0;        
    int character;

    do { //does this for each chatacter in the input file
        character = getchar();
        pre = preCheck(character, pre);
        comments = commentCheck(character, comments);
        curly = curlyBracketCheck(character, curly);
        paren = parenCheck(character, paren);
    } while (character != EOF); 
    printFunction(pre, comments, curly, paren);    //prints from the print function

    return(0);
}
