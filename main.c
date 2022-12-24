#include "driver.h"

int main() {
    uint8_t* arr = malloc(4 * 16 * 16 * sizeof(uint8_t));
    for(int i = 0; i < 40; i++){
        arr[i] = i;
        arr[i + 16 * 16] = 255;
        arr[i + 2 * 16 * 16] = 255;
        arr[i + 3 * 16 * 16] = 255;
    }

    init();

    renderMat(arr);
    usleep(10000000);

    clearMat();

}