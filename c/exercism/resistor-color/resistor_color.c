#include "resistor_color.h"

resistor_band_t allColours[]={BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY,WHITE};

int color_code(resistor_band_t col) {
    return col;
}

const resistor_band_t * colors()
{
   return allColours;
}