#include <string.h>
#include <stdio.h>

int main()
{
    char s1[] = "The grey fox", s2[] = " jumped.";
    printf("%s\n", s1);
    printf("The length of s1 is %ld.\n", strlen(s1));
    strcpy(s1,s2);
    printf("s1 is now `%s`\n", s1);
    return 0;
}
