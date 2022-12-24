//
// Created by dylan on 12/23/22.
//

#ifndef LEDCONTROL_SERVICE_H
#define LEDCONTROL_SERVICE_H

#include "driver.h"

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 4090

#define PLAY_CODE 0xabcdfedc
#define STOP_CODE 0xabcdfedf
#define REPEAT_CODE 0xabcdfede
#define SEQ_BEGIN 0xabcdfed1

#define FPS 50

extern uint8_t * contentBuf;
extern int bufFrames;

extern int sockfd;
extern struct sockaddr_in servaddr;

extern int frames;
extern int currentFrame;
extern int play;
extern int repeat;

void initService(int h, int w, int fbSize);

//the main loop of the server listening
//This server will only accept one client!
void handler(int connfd);

void listenThread();

_Noreturn void mainLoop();

#endif //LEDCONTROL_SERVICE_H
