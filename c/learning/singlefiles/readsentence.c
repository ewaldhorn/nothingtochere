#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    char ch;
    char s1[100];
    char s2[100];
    
    scanf("%c", &ch);
    scanf("%s", s1);
    scanf("\n");
    scanf("%[^\n]%*c", s2); // read entire sentence until newline character is found.
        
    printf("%c\n", ch);
    printf("%s\n", s1);
    printf("%s\n", s2);
        
    return 0;
}
