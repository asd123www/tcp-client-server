#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }

    // Specify the server address
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // Address family
    server_addr.sin_port = htons(12345); // Port number, converted to network byte order
    server_addr.sin_addr.s_addr = inet_addr("10.10.1.1"); // Server IP address

    // Connect the socket to the server
    int ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        printf("connect failed!\n");
        exit(0);
    }

    puts("Successfully built a connection with server!");

    int epoch = 100000;
    char buff[1024];
    uint32_t size = 512;
    while (epoch --) {
        uint32_t write_len = write(sockfd, buff, size);
        printf("Sent %d bytes to server.\n", write_len);
        uint32_t read_len = read(sockfd, buff, sizeof(buff));
        printf("Received %d bytes from server.\n", read_len);
    }

    // close the socket
    close(sockfd);

    return 0;
}
