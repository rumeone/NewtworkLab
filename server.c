#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main() {

    int sockMain, addLenght, msgLenght;
    struct sockaddr_in servAddr, clientAddr;
    char buf[BUF_SIZE];

    //Создаем socket для udp.

    if(sockMain = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Ошибка открытия socket для UDP");
        exit(1);
    }


    return 0;
}