//
// Created by dylan on 12/23/22.
//
#include "driver.h"

int width = WIDTH;
int height = HEIGHT;
int dynamicDim = 1;

ws2811_t ledStr;
ws2811_led_t* mat0;

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

    ledStr = ledstringTmp;

    if ((ret = ws2811_init(&ledStr)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init failed");
        return ret;
    }

    mat0 = malloc(sizeof(ws2811_led_t) * LED_COUNT);
    memset(mat0, 0, sizeof(ws2811_led_t) * LED_COUNT);

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

void renderMat(uint8_t* arr){
    //cast mat0
    castRGBA2mat(arr, mat0, height, width);

    //render the mat0
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            ledStr.channel[0].leds[(y * width) + x] = mat0[y * width + x];
        }
    }

    dynamicDimming(arr, height, width);

    ws2811_return_t ret;
    if ((ret = ws2811_render(&ledStr)) != WS2811_SUCCESS){
        fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
    }
}

void dynamicDimming(const uint8_t* arr, int h, int w){
    int i, j;
    int totalBright = 0;
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
            totalBright += arr[0 * (h * w) + (i * w + j)];
            totalBright += arr[1 * (h * w) + (i * w + j)];
            totalBright += arr[2 * (h * w) + (i * w + j)];
        }
    }

    if(totalBright > MAX_TOTAL_BRIGHT){
        float scale = (float)MAX_TOTAL_BRIGHT / (float)totalBright;
        int bright = (int)(255 * scale);
        ledStr.channel[0].brightness = bright;
    }
}

void clearMat(){
    memset(mat0, 0, sizeof(ws2811_led_t) * LED_COUNT);

    //render the mat0
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            ledStr.channel[0].leds[(y * width) + x] = mat0[y * width + x];
        }
    }

    ws2811_return_t ret;
    if ((ret = ws2811_render(&ledStr)) != WS2811_SUCCESS){
        fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
    }
}