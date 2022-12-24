//
// Created by dylan on 12/23/22.
//
#include <pthread.h>
#include "service.h"

uint8_t * contentBuf;

int sockfd;
struct sockaddr_in servaddr;

unsigned int frames = 0;
unsigned int currentFrame = 0;
int play = 0;
int repeat = 0;

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
    printf("--- Server started at port %d ---\n",PORT);

    //start listening thread
    pthread_t listenThreadID;
    pthread_create(&listenThreadID, NULL, (void*)listenThread, NULL);
    printf("--- Listening thread started ---\n");

    //start main loop
    mainLoop();

}

void listenThread(){
    while(1) {
        //try to specify maximum of 1 pending connections for the master socket
        if ((listen(sockfd, 1)) != 0) {
            fprintf(stderr, "Listen failed...\n");
            exit(0);
        }

        //accept the data packet from client and verification
        int connfd = accept(sockfd, (struct sockaddr *) NULL, NULL);
        if (connfd < 0) {
            fprintf(stderr, "server acccept failed...\n");
            exit(0);
        }

        //start the handler
        handler(connfd);
        close(connfd);
    }
}

void handler(int connfd){
    char flagBuf[4];
    read(connfd, flagBuf, 4);
    unsigned int flag = *((int*)flagBuf);

    //reset playing state to prevent playing when not supposed to
    play = 0;
    repeat = 0;
    currentFrame = 0;

    //handle instructions
    if(flag == PLAY_CODE){
        printf("Play code received\n");
        play = 1;
    }else if(flag == STOP_CODE){
        printf("Stop code received\n");
        play = 0;
        repeat = 0;
    }else if(flag == REPEAT_CODE){
        printf("Repeat code received\n");
        repeat = 1;
    }else if(flag == SEQ_BEGIN){
        int frameCount;
        read(connfd, &frameCount, 4);
        printf("Sequence begin code received, frame count: %d\n", frameCount);
        read(frameCount * height * width * 4, contentBuf, connfd);
        frames = frameCount;
    }
}

_Noreturn void mainLoop(){
    while(1){
        if(play){
            while(currentFrame < frames){
                //play the current frame
                renderMat(contentBuf + currentFrame * height * width * 4);
                currentFrame++;
                usleep(1000000 / FPS);
            }
            currentFrame = 0;
        }

        while(repeat){
            if(currentFrame < frames){
                //play the current frame
                renderMat(contentBuf + currentFrame * height * width * 4);
                currentFrame++;
            }else{
                currentFrame = 0;
            }
            usleep(1000000 / FPS);
        }
        usleep(1000);
    }
}