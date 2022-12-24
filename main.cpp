#include <iostream>

#include "driver.h"

int main() {
    uint8_t* arr = (uint8_t*)malloc(4 * 16 * 16 * sizeof(uint8_t));
    for(int i = 0; i < 16 * 16; i++){
        arr[i] = i;
        arr[i + 16 * 16] = i;
        arr[i + 2 * 16 * 16] = i;
        arr[i + 3 * 16 * 16] = i;
    }

    init();
    matrixRender(arr);
}