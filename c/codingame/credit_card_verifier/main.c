#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------------------------- stepOne
int stepOne(char *card) {
  int total = 0;

  for (int pos = strlen(card) - 2; pos >= 0; pos -= 2) {
    int val = 2 * (card[pos] - '0');
    if (val >= 10) {
      val = val - 9;
    }
    total += val;
  }

  return total;
}

// -------------------------------------------------------------------- stepTwo
int stepTwo(char *card) {
  int total = 0;

  for (int pos = strlen(card) - 1; pos >= 0; pos -= 2) {
    int val = card[pos] - '0';
    total += val;
  }

  return total;
}

// --------------------------------------------------------------- unpspaceCard
void unspaceCard(char *tgt, char *card) {
  int cardLen = strlen(card);
  int pos = 0;

  for (int i = 0; i < cardLen; i++) {
    if (card[i] != ' ') {
      tgt[pos] = card[i];
      pos++;
    }
  }

  // make sure it's null terminated!
  tgt[pos] = 0;
}

// ======================================================================= MAIN
int main() {
  int n;
  scanf("%d", &n);
  fgetc(stdin);
  char readCard[21];

  for (int i = 0; i < n; i++) {
    scanf("%[^\n]", readCard);
    fgetc(stdin);

    char card[21];
    unspaceCard(card, readCard);

    // fprintf(stderr, "The card number is '%s'\n", readCard);
    // fprintf(stderr, "The card number is '%s'\n", card);
    // fprintf(stderr, "Step one gives %d\n", stepOne(card));
    // fprintf(stderr, "Step two gives %d\n", stepTwo(card));
    if ((stepOne(card) + stepTwo(card)) % 10 == 0) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }

  return EXIT_SUCCESS;
}

/*

1.Double every second digit from right to left. If this “doubling” results in a
two-digit number, subtract 9 from it get a single digit. 2.Now add all single
digit numbers from step 1. 3.Add all digits in the odd places from right to left
in the credit card number. 4.Sum the results from steps 2 & 3. 5.If the result
from step 4 is divisible by 10, the card number is valid; otherwise, it is
invalid. for example:

Test 1:
4556 7375 8689 9855

1.
5*2 9*2 8*2 8*2 7*2 7*2 5*2 4*2
5 9 8 8 7 7 5 4

10 18 16 16 14 14 10 8

1 9 7 7 5 5 1 8

2.
1+9+7+7+5+5+1+8=43

3.
5+8+9+6+5+3+6+5=47

4.
43+47=90

The number is valid
*/
