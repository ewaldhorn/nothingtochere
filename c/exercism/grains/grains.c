#include "grains.h"

uint64_t square(uint8_t index) {
    uint64_t tmp = 0;

    if (index == 1) {
        tmp = 1;
    } else if (index > 1 && index <= 64) {
        tmp = 2;
        
        for (int i = 2; i < index; i++) {
            tmp *= 2;
        }
    }
    
    return tmp;
}

uint64_t total(void) {
    uint64_t tmp = 2;

    for (int i = 2; i < 64; i++) {
        tmp *= 2;
    }

    // do this last one like this to prevent overflow
    tmp += tmp - 1;
    
    return tmp;
}
