//
// Created by dylan on 12/23/22.
//
#include "service.h"

uint8_t * contentBuf;

int sockfd;
struct sockaddr_in servaddr;

void initService(int h, int w, int fbSize){

    //construct the led driver
    contentBuf = malloc(fbSize * 4 * h * w * sizeof(uint8_t));
    initP(h, w);

    //create server socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr," socket creation failed...\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));

    //assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    //bind the socket with the server address
    if ((bind(sockfd, (const struct sockaddr*) &servaddr, sizeof(servaddr))) != 0) {
        fprintf(stderr," socket bind failed...\n");
        exit(0);
    }

    //print start message
    printf("--- Server started at port %d ---",PORT);
}