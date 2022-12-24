//
// Created by dylan on 12/23/22.
//

/**
 * This file is the direct communication with the ws2811 library.
 * We use the library to drive the LEDs.
 * The driver.c includes necessary components to render an rgb array to the LEDs.
 */

#ifndef LEDCONTROL_DRIVER_H
#define LEDCONTROL_DRIVER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>


#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"

#include "ws2811.h"


#define ARRAY_SIZE(stuff)       (sizeof(stuff) / sizeof(stuff[0]))

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define WIDTH                   16
#define HEIGHT                  16
#define LED_COUNT               (WIDTH * HEIGHT)

int width = WIDTH;
int height = HEIGHT;
int led_count = LED_COUNT;

int clear_on_exit = 0;

ws2811_t ledStr;
ws2811_led_t* mat0;

ws2811_return_t init();

ws2811_return_t initP(int h, int w, int stripType);

//NCHW 4 * H * W
void renderMat(uint8_t* arr);

void clearMat();





#endif //LEDCONTROL_DRIVER_H
