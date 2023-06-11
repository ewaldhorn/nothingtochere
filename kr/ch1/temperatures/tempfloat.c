#include <stdio.h>

int main() {
    float fahr, celsius; 
    float lower=0, upper=500, step=20;
    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0); 
        printf("%3.0f %6.1f\n", fahr, celsius); 
        fahr = fahr + step;
    }
   
    return 0; 
}
