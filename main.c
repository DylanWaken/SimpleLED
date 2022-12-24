#include "driver.h"

int main() {
    uint8_t* arr = malloc(4 * 16 * 16 * sizeof(uint8_t));
    for(int i = 0; i < 80; i++){
        arr[i] = i;
        arr[i + 16 * 16] = i;
        arr[i + 2 * 16 * 16] = i;
        arr[i + 3 * 16 * 16] = i;
    }

    init();

    renderMat(arr);
    usleep(1000);

    clearMat();

}