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

extern uint8_t * contentBuf;
extern int bufFrames;

extern int sockfd;
extern struct sockaddr_in servaddr;

void initService(int h, int w, int fbSize);

#endif //LEDCONTROL_SERVICE_H
