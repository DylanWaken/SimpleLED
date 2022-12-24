#include "driver.h"

int main() {
    uint8_t* arr = malloc(4 * 16 * 16 * sizeof(uint8_t));
    for(int prime = 1; prime < 256; prime++) {
        for (int i = 0; i < prime; i++) {
            arr[i] = i;
            arr[i + 16 * 16] = 255;
            arr[i + 2 * 16 * 16] = 255;
            arr[i + 3 * 16 * 16] = 255;
        }

        init();

        renderMat(arr);
        usleep(200000);
        fprintf(stdout, "prime: %d", prime);
    }

    clearMat();

}