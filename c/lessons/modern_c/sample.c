#include <stdio.h>
#include <time.h>

int main(void) {
    struct tm * today = &(struct tm){
        .tm_year = 123,
        .tm_mon = 3,
        .tm_mday=20
    };

    mktime(today);

    auto buffer = (char [42]){};
    strftime(buffer, 42, "%A, %F", today);
    puts(buffer);
}