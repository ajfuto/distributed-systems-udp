#include <stdio.h>
#include <sys/socket.h>
#include "udp.h"

#define BUFFER_SIZE (1000)
#define NUM_RETRIES 10
#define TIMEOUT_SEC 5

// client code
int main(int argc, char *argv[]) {
    struct sockaddr_in addrSnd, addrRcv;
    struct timeval timeout;

    int sd = UDP_Open(20000);
    int rc = UDP_FillSockAddr(&addrSnd, "localhost", 10000);

    // configuring timeout
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
    setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    char message[BUFFER_SIZE];
    sprintf(message, "hello world");

    // try a total of NUM_RETRIES (10) times
    for (int i = 0; i < NUM_RETRIES; i++)
    {
        // only print this the first time
        if (i == 0)
            printf("client:: send message [%s]\n", message);

        // send the data
        rc = UDP_Write(sd, &addrSnd, message, BUFFER_SIZE);
        if (rc < 0) {
	        printf("client:: failed to send\n");
	        exit(1);
        }

        rc = 0;

        // only print this the first time
        if (i == 0)
            printf("client:: waiting for reply...\n");

        // attempt to recieve a response
        rc = UDP_Read(sd, &addrRcv, message, BUFFER_SIZE);
        if (rc > 0)
        {
            printf("client:: got reply [size:%d contents:(%s)\n", rc, message);
            return 0;
        }
    }

    // if we get here, this means we did not recieve a message
    return -1;
    
}

