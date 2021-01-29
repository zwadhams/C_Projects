#include <stdio.h>
#include <math.h>

#define PI 3.14159265

//Zach Wadhams, week 2 class work

int main(void) {

    double radius = 1.0;
    double area = 0.0;

    while (radius != 0.0) {
         
        
        printf("Enter the Radius: ");
        scanf("%lf", &radius);
        
        if (radius == 0.0) {
            break;
        }


        area = PI * (radius * radius);
        
        printf("The area of the circle with radius %.2f ", radius);
        printf("is %.2f ", area);
        printf("\n");
    }   

    return(0);
}
