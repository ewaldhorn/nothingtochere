#include <stdlib.h>

// Assuming a constant for bytes per pixel, similar to your Go code
#define BYTES_PER_PIXEL 4 // For example, RGBA

typedef struct {
    int width;
    int height;
    unsigned char* pixelBuffer;
} MyCanvas;

// A global canvas instance, similar to how your Go code creates a single canvas
MyCanvas* canvas = NULL;

// This function creates a new canvas and allocates the memory buffer
// It's similar to your NewCanvas function
void createCanvas(int width, int height) {
    if (canvas != NULL) {
        // Free existing canvas memory to prevent leaks
        free(canvas->pixelBuffer);
        free(canvas);
    }
    
    canvas = (MyCanvas*)malloc(sizeof(MyCanvas));
    canvas->width = width;
    canvas->height = height;

    int bufferSize = width * height * BYTES_PER_PIXEL;
    canvas->pixelBuffer = (unsigned char*)malloc(bufferSize);
}

// Similar to your ClearBuffer function
void clearBuffer() {
    if (canvas != NULL) {
        int bufferSize = canvas->width * canvas->height * BYTES_PER_PIXEL;
        for (int i = 0; i < bufferSize; i++) {
            canvas->pixelBuffer[i] = 0;
        }
    }
}

// Similar to your GetBufferPointer function
unsigned char* getBufferPointer() {
    if (canvas != NULL) {
        return canvas->pixelBuffer;
    }
    return NULL;
}

// Similar to your GetBufferLength function
int getBufferLength() {
    if (canvas != NULL) {
        return canvas->width * canvas->height * BYTES_PER_PIXEL;
    }
    return 0;
}
