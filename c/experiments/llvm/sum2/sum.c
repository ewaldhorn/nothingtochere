// compile with
// clang -S -O3 -emit-llvm sum.c
// -S only run preprocess and compile steps
// -O3 generate well-optimized code
// --emil-llvm emit LLVM code 
unsigned sum(unsigned a, unsigned b) {
    return a + b;
}