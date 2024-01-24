void print_sum(a, b) {
    printf("%d", a + b);
}

// should print 9, because the assumed type is integer
// in C23 it will be undefined because, well, it IS undefined.
int main(void) {
    print_sum(1.5, 8.5);
}



// this becomes an integer=42 in C
// in C23 it will be a float=42.24 because of the "f" hint
void funcAutoType(void){
    auto number = 42.24f;
}


// needs a header include in C
// in C23, bool is a type, so no worries or includes needed
void funcCompileOrNot(void){
    bool enable = false;
}

// the size of the numbers array is TWELVE because, well, C!
double numbers[] = {0, [10]=55, 89, [5]=5, 8, [1]=1, 1, 2};



// sizeof(int) == 4
// sizeof(int*) == 8
// will allocate 400 bytes of memory
size_t sz = 10;
int (*pK)[sz][sz] = malloc(sizeof(*pK));