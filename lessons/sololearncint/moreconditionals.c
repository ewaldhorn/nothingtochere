#define LEVEL 4

int main()
{
#if LEVEL > 6
    /* do something */
#elif LEVEL > 5
    /* else if branch */
#elif LEVEL > 4
    /* another else if */
#else
    /* last option here */
#endif

    return 0;
}