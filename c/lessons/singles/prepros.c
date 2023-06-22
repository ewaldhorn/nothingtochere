#include <stdio.h>

#define AND &&
#define OR ||

int main()
{
  int number1 = 22, number2 = 43;

  if ((number1 % 2 == 0) AND (number2 % 2 == 0))
  {
    printf("Both numbers are divisible by 2.\n");	  
  } else {
    if ((number1 % 2 == 0) OR (number2 % 2 == 0))
    {
      printf("At least one number is divisible by 2.\n");
    } else 
    {
      printf("Nah, this is unexpected!\n");
    }
  }

  return 0;
}
