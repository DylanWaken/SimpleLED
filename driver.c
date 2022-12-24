//
// Created by dylan on 12/23/22.
//
#include "driver.h"


ws2811_return_t init() {

    ws2811_return_t ret;
    ws2811_t ledstringTmp = {
        .freq = TARGET_FREQ,
        .dmanum = DMA,
        .channel = {
             [0] = {
                   .gpionum = GPIO_PIN,
                   .invert = 0,
                   .count = LED_COUNT,
                   .strip_type = STRIP_TYPE,
                   .brightness = 255,
             },
             [1] = {
                   .gpionum = 0,
                   .invert = 0,
                   .count = 0,
                   .brightness = 0,
             },
        },
    };

    ledstring = ledstringTmp;

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init failed");
        return ret;
    }

    matrix = malloc(sizeof(ws2811_led_t) * LED_COUNT);
    memset(matrix, 0, sizeof(ws2811_led_t) * LED_COUNT);

    return ret;
}

ws2811_return_t initP(int h, int w, int stripType) {
    ws2811_return_t ret;
    return ret;
}

void castRGBA2mat(uint8_t* arr, ws2811_led_t* mat, int h, int w){
    int i, j;
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
            mat[i * w + j] =
                    (arr[0 * (h * w) + (i * w + j)] << 24) |
                    (arr[1 * (h * w) + (i * w + j)] << 16) |
                    (arr[2 * (h * w) + (i * w + j)] << 8) |
                    (arr[3 * (h * w) + (i * w + j)]);
        }
    }
}

void matrixRender(uint8_t* arr){
    //cast matrix
    castRGBA2mat(arr, matrix, height, width);

    //render the matrix
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            ledstring.channel[0].leds[(y * width) + x] = matrix[y * width + x];
        }
    }

    ws2811_return_t ret;
    if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS){
        fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
    }
}

void matrixClear(){
    memset(matrix, 0, sizeof(ws2811_led_t) * LED_COUNT);

    //render the matrix
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            ledstring.channel[0].leds[(y * width) + x] = matrix[y * width + x];
        }
    }

    ws2811_return_t ret;
    if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS){
        fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
    }
}