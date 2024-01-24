struct Rect{ struct {long n;}; } will_it_run(bool yes_or_no){
    typeof(yes_or_no) should_segfault = {!yes_or_no};
    constexpr int SZ = {6};

    double array[SZ] = {
        [4]=-1.21570011103803167e-262, 4.94065645841246544e-323,
        [0]= 2.85312613025819859e-153, 3.98568242114839056e+252,
             5.20628304629909446e+58,  5.81238365411700493e+180
    };

    auto num = puts((void*)(array));
    auto ptr = &(struct Rect){.n=num};

    if (should_segfault){
        ptr = nullptr;
    }

    return *ptr;
}

int main(void) {
    return will_it_run(true).n;
}