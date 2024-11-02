
/* Include for .. */
#include <inttypes.h>   /* .. normalized type, like "uint32_t" */
#include <pthread.h>    /* .. pthread_[create|join]() */
#include <signal.h>     /* .. signal() */
#include <stdio.h>
#include <stdlib.h>     /* .. exit(), atoi(), malloc() */
#include <string.h>     /* .. memset() */
#include <unistd.h>     /* .. usleep(), close() */

#include <asm/byteorder.h>      /* .. __cpu_to_be32p() */
#include <arpa/inet.h>          /* .. inet_pton() */
#include <netinet/in.h>         /* .. htons(), struct sockaddr_in */
#include <sys/socket.h>         /* .. socket(), connect(), recv(), send() */

/* Uncomment to enable debug prints */
//#define ENA_DBG 1
#if defined(ENA_DBG)
        #define DBG(FMT, ...)	printf(FMT, ##__VA_ARGS__)
#else
        #define DBG(FMT, ...)
#endif

#define BUFFER_LEN      300

#define COLOR_OFF	0xAAAAAAAA

#define FPS 3

union color {
        struct {
                uint8_t r;
                uint8_t g;
                uint8_t b;
                uint8_t w;
        } rgbw;
        uint32_t word;
} cOff = { .word = COLOR_OFF };

struct digit {
        union color segments[7];
};

/* Running states */
int running = 1;

/** **************************************************************************
 * @brief Signal SIGINT handler
 *        Receive SIGINT to properly end program and close socket
 *************************************************************************** */
void sigint_handler(int sig) {
        printf(" SIGINT handler w/ code: %d\n", sig);
        running = 0;
}

/** **************************************************************************
 * @brief Prepare digits array to drive Qt application
 *        that will simulate a 7segments display
 * @note  7segments is coded based on the WS2811 chip behavior.
 *        That's why it's an array that is sent and not a simple uint8.
 *************************************************************************** */
void prepareDigits(struct digit *arr, union color c) {
        /* ****** 0 ****** */
        arr[ 0].segments[0] = c;
        arr[ 0].segments[1] = c;
        arr[ 0].segments[2] = c;
        arr[ 0].segments[3] = c;
        arr[ 0].segments[4] = c;
        arr[ 0].segments[5] = c;
        arr[ 0].segments[6] = cOff;

        /* ****** 1 ****** */
        arr[ 1].segments[0] = cOff;
        arr[ 1].segments[1] = c;
        arr[ 1].segments[2] = c;
        arr[ 1].segments[3] = cOff;
        arr[ 1].segments[4] = cOff;
        arr[ 1].segments[5] = cOff;
        arr[ 1].segments[6] = cOff;

        /* ****** 2 ****** */
        arr[ 2].segments[0] = c;
        arr[ 2].segments[1] = c;
        arr[ 2].segments[2] = cOff;
        arr[ 2].segments[3] = c;
        arr[ 2].segments[4] = c;
        arr[ 2].segments[5] = cOff;
        arr[ 2].segments[6] = c;

        /* ****** 3 ****** */
        arr[ 3].segments[0] = c;
        arr[ 3].segments[1] = c;
        arr[ 3].segments[2] = c;
        arr[ 3].segments[3] = c;
        arr[ 3].segments[4] = cOff;
        arr[ 3].segments[5] = cOff;
        arr[ 3].segments[6] = c;

        /* ****** 4 ****** */
        arr[ 4].segments[0] = cOff;
        arr[ 4].segments[1] = c;
        arr[ 4].segments[2] = c;
        arr[ 4].segments[3] = cOff;
        arr[ 4].segments[4] = cOff;
        arr[ 4].segments[5] = c;
        arr[ 4].segments[6] = c;

        /* ****** 5 ****** */
        arr[ 5].segments[0] = c;
        arr[ 5].segments[1] = cOff;
        arr[ 5].segments[2] = c;
        arr[ 5].segments[3] = c;
        arr[ 5].segments[4] = cOff;
        arr[ 5].segments[5] = c;
        arr[ 5].segments[6] = c;

        /* ****** 6 ****** */
        arr[ 6].segments[0] = c;
        arr[ 6].segments[1] = cOff;
        arr[ 6].segments[2] = c;
        arr[ 6].segments[3] = c;
        arr[ 6].segments[4] = c;
        arr[ 6].segments[5] = c;
        arr[ 6].segments[6] = c;

        /* ****** 7 ****** */
        arr[ 7].segments[0] = c;
        arr[ 7].segments[1] = c;
        arr[ 7].segments[2] = c;
        arr[ 7].segments[3] = cOff;
        arr[ 7].segments[4] = cOff;
        arr[ 7].segments[5] = cOff;
        arr[ 7].segments[6] = cOff;

        /* ****** 8 ****** */
        arr[ 8].segments[0] = c;
        arr[ 8].segments[1] = c;
        arr[ 8].segments[2] = c;
        arr[ 8].segments[3] = c;
        arr[ 8].segments[4] = c;
        arr[ 8].segments[5] = c;
        arr[ 8].segments[6] = c;

        /* ****** 9 ****** */
        arr[ 9].segments[0] = c;
        arr[ 9].segments[1] = c;
        arr[ 9].segments[2] = c;
        arr[ 9].segments[3] = c;
        arr[ 9].segments[4] = cOff;
        arr[ 9].segments[5] = c;
        arr[ 9].segments[6] = c;

        /* ****** A ****** */
        arr[10].segments[0] = c;
        arr[10].segments[1] = c;
        arr[10].segments[2] = c;
        arr[10].segments[3] = cOff;
        arr[10].segments[4] = c;
        arr[10].segments[5] = c;
        arr[10].segments[6] = c;

        /* ****** b ****** */
        arr[11].segments[0] = cOff;
        arr[11].segments[1] = cOff;
        arr[11].segments[2] = c;
        arr[11].segments[3] = c;
        arr[11].segments[4] = c;
        arr[11].segments[5] = c;
        arr[11].segments[6] = c;

        /* ****** C ****** */
        arr[12].segments[0] = c;
        arr[12].segments[1] = cOff;
        arr[12].segments[2] = cOff;
        arr[12].segments[3] = c;
        arr[12].segments[4] = c;
        arr[12].segments[5] = c;
        arr[12].segments[6] = cOff;

        /* ****** d ****** */
        arr[13].segments[0] = cOff;
        arr[13].segments[1] = c;
        arr[13].segments[2] = c;
        arr[13].segments[3] = c;
        arr[13].segments[4] = c;
        arr[13].segments[5] = cOff;
        arr[13].segments[6] = c;

        /* ****** E ****** */
        arr[14].segments[0] = c;
        arr[14].segments[1] = cOff;
        arr[14].segments[2] = cOff;
        arr[14].segments[3] = c;
        arr[14].segments[4] = c;
        arr[14].segments[5] = c;
        arr[14].segments[6] = c;

        /* ****** F ****** */
        arr[15].segments[0] = c;
        arr[15].segments[1] = cOff;
        arr[15].segments[2] = cOff;
        arr[15].segments[3] = cOff;
        arr[15].segments[4] = c;
        arr[15].segments[5] = c;
        arr[15].segments[6] = c;
}

/** **************************************************************************
 * @brief  Read response from server and detect "Leaving" msg.
 * @return 0xDEADBEEF: Client leaves server,
 *                  0: Server disconnects itself an make client leave
 *               NULL: Allocation has failed
 *************************************************************************** */
void *receiveServerMsg(void *arg) {
        int  socketFd = *((int *)arg);
        char buff[15+1] = {0};
        char *buffRecvData = buff+4;
        int  streamLen;
        uint32_t dataLenLE;
        int  *exitValue;

        exitValue  = (int *) malloc(sizeof(exitValue));
        if ( ! exitValue )      return exitValue;
        *exitValue = 0xDEADBEEF;

        while (running) {
                streamLen = recv(socketFd, (void *) buff,
                                 sizeof(buff)-1, MSG_DONTWAIT);

                /* 4 bytes of stream length + 7 for "Leaving" msg */
                if (streamLen != 11)    continue;

                dataLenLE = __cpu_to_le32p((uint32_t *)buff);
                /* Security for printing it later on */
                buffRecvData[dataLenLE] = '\0';
                #if defined(ENA_DBG)
                printf("CLT-DBG: dataLenLE[%d] | Msg[%s]\n",
                       dataLenLE, buffRecvData);
                /* Tips: From threaded fn(), flush output to
                 *       actually print it */
                fflush(stdout);
                #endif

                if ( ! strcmp(buffRecvData, "Leaving") ) {
                        *exitValue = 0;
                        running = 0;
                }
        }

        return exitValue;
}

/** **************************************************************************
 * @brief Main application function
 *************************************************************************** */
int main(int argc, char **argv) {
        /* Socket parameters */
        int socketFd, port;
        struct sockaddr_in srv_addr;
        uint8_t connectionSuccessful = 0;
        /* Exchanging buffer */
        char buff[BUFFER_LEN+1] = {0};
        char *buffRecvData = buff+4;    /* buff+4 to skip stream length info. */
        /* Data treatment */
        int streamLen;
        uint32_t streamLenLE, dataLenLE;
        union color c = { .rgbw = { .w = 0, .r = 0, .g = 0xBB, .b = 0xFF } };
        struct digit digits[16];
        /* Thread about detecting server leaving */
        pthread_t svrLeavingThread;
        int *threadRc;
        /* Others */
        int rc, state = 0;

        if (argc != 3) {
                fprintf(stderr, "usage: %s <SERVER_IP> <PORT>\n", argv[0]);
                fprintf(stderr, "\tSERVER_IP: 10's base for IPv4\n");
                fprintf(stderr, "\t           16's base for IPv6\n");
                fprintf(stderr, "\tPORT     : Port's communication\n");
                exit(EXIT_FAILURE);
        }

        /* Parsing server's IP */
        if (inet_pton(AF_INET, argv[1], &srv_addr.sin_addr) <= 0) {
                fprintf(stderr, "Converting server's IP failed\n");
                exit(EXIT_FAILURE);
        }

        /* Parsing server's port */
        port = atoi(argv[2]);

        /* Socket's creation */
        socketFd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFd < 0) {
                fprintf(stderr, "Could not create socket client side\n");
                exit(EXIT_FAILURE);
        }
        DBG("CLT-DBG: Step passed[socket]\n");

        /* Fill server's infos */
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port = htons(port);

        printf("CLT: Connecting to server at %s:%d...\n", argv[1], port);
        if (connect(socketFd, (struct sockaddr *) &srv_addr,
                                sizeof(srv_addr)) < 0) {
                fprintf(stderr, "FAILURE\n");
                /* Clean ressource(s) that could be used */
                close(socketFd);
                exit(EXIT_FAILURE);
        }
        DBG("CLT-DBG: Step passed[connect]\n");

        /* Prepare digits & Fully initiate srv_addr struct to 0 */
        prepareDigits(digits, c);
        memset(&srv_addr, 0, sizeof(srv_addr));

        /* Connect signal to handler */
        signal(SIGINT, sigint_handler);

        printf("~~~ WELCOME TO THE PROGRAM ~~~\n");
        printf("CLT: Wait for connection validation...\n");
        while ( ! connectionSuccessful ) {
                /* Use MSG_DONTWAIT as MSG_WAITALL wait for buffer
                 * to be filled with BUFFER_LEN elements (if no error occurs).
                 * Other flags, like MSG_TRUNC, are in evaluation
                 * as possibilities. */
                streamLenLE = recv(socketFd, (void *) buff,
                                   BUFFER_LEN, MSG_DONTWAIT);

                /* 4 bytes of stream length + 21 for "Connection successful" */
                if (streamLenLE != 25)    continue;

                dataLenLE = __cpu_to_le32p((uint32_t *)buff);
                /* Security for printing it later on */
                buffRecvData[dataLenLE] = '\0';
                DBG("Server's response (length: %d, actual data: %d):\n",
                    streamLenLE, dataLenLE);

                printf("SVR: %s\n", buffRecvData);

                if ( ! strcmp(buffRecvData, "Connection successful") )
                        connectionSuccessful = 1;
        }

        printf("CLT: Launching task to detect if server kills itself...\n");
        rc = pthread_create(&svrLeavingThread, NULL,
                            receiveServerMsg, &socketFd);
        if (rc) {
                printf("CLT: Thread could not be created. Program aborted!\n");
                /* 1st 4 bytes are stream length info. in Little Endian */
                if (send(socketFd, (void *) "\x07\0\0\0Leaving", 11, 0) != 11)
                        fprintf(stderr, "Sending failed\n");
                /* Clean ressource(s) that could be used */
                close(socketFd);
                exit(EXIT_FAILURE);
        }

        printf("CLT: Start communication with server to "
               "drive 7Segments display!\n");
        while (running) {
                snprintf(buff, BUFFER_LEN, "!C%dN%04x,", 3, 7);
                buff[9] = 0;

                streamLen = strlen(buff) +
                            7*sizeof(digits[state].segments->word) + 1;
                DBG("CLT-DBG: Built string(len[%d])\n", streamLen);

                streamLenLE = __cpu_to_le32p((uint32_t *)&streamLen);
                if (send(socketFd, &streamLenLE,
                         sizeof(streamLenLE), 0) != sizeof(streamLenLE))
                        printf("CLT: Packet's preamble could not "
                               "be sent properly\n");

                if (send(socketFd, (void *) buff,
                         strlen(buff), 0) != strlen(buff))
                        printf("CLT: Data's header could not "
                               "be sent properly\n");

                /* Works because host machine operates with Little Endian  */
                /* TODO/IDEA: Only change endianess treatment Qt side
                 *            Otherwise, a loop would be needed to
                 *            transform and ensure data's endianess, like: */
                /*for (uint32_t i = 0; i < 7; i++) {
                        uint32_t tmp = __cpu_to_le32p(
                                        &(digits[state].segments+i)->word);
                        if (send(socketFd, (void *) &tmp, sizeof(tmp), 0)
                            != sizeof(tmp))
                                printf("CLT: Data[state=%d] segment[%d] could "
                                       "not be sent properly\n", state, i);
                }*/
                if (send(socketFd, (void *) digits[state].segments,
                          7*sizeof(digits[state].segments->word), 0)
                          != 7*sizeof(digits[state].segments->word))
                        printf("CLT: Data[state=%d] could not "
                               "be sent properly\n", state);

                if (send(socketFd, (void *) "$", 1, 0) != 1)
                        printf("CLT: Data's terminating char could not "
                               "be sent properly\n");

                state = (state + 1) % 16;

                usleep(1000000 / FPS);
        }

        pthread_join(svrLeavingThread, (void **) &threadRc);

        if (threadRc && *threadRc) {
                /* 1st 4 bytes are stream length info. in Little Endian */
                if (send(socketFd, (void *) "\x07\0\0\0Leaving", 11, 0) != 11)
                        fprintf(stderr, "Sending failed\n");

                printf("CLT: Leaving server\n");

        } else {
                printf("SVR: Forcing client to leave\n");
        }

        /* Resources cleaning */
        free(threadRc);
        close(socketFd);

        return 0;
}
