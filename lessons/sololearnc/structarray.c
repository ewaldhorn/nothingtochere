#include <stdio.h>

typedef struct
{
    int h, w, l;
} box;

int main()
{
    box boxes[3] = {{2, 6, 8}, {4, 6, 6}, {2, 6, 9}};

    for (int i = 0; i < 3; i++)
    {
        printf("A box of %dx%dx%d has a volume of %d.\n", boxes[i].h, boxes[i].l, boxes[i].w,
               boxes[i].h * boxes[i].l * boxes[i].w);
    }

    return 0;
}