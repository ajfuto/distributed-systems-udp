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

    // configuring timeout
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;

    int sd = UDP_Open(20000);
    int rc = UDP_FillSockAddr(&addrSnd, "localhost", 10000);

    char message[BUFFER_SIZE];
    sprintf(message, "hello world");

    printf("client:: send message [%s]\n", message);
    rc = UDP_Write(sd, &addrSnd, message, BUFFER_SIZE);
    if (rc < 0) {
	printf("client:: failed to send\n");
	exit(1);
    }

    printf("client:: waiting for reply...\n");
    for (int i = 0; i < NUM_RETRIES; i++)
    {
        
    }

    rc = UDP_Read(sd, &addrRcv, message, BUFFER_SIZE);
    printf("client:: got reply [size:%d contents:(%s)\n", rc, message);
    return 0;
}

