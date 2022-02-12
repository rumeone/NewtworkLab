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

    if((sockMain = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Ошибка открытия socket для UDP");
        exit(1);
    }

    bzero((char*) &servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = 0;

    //функция bind () назначает сокету определенный адрес в семействе адресов. 
    if (bind (sockMain, &servAddr, sizeof(servAddr))) {
        perror("Ошибка bind");
        exit(1);
    }

    //извлекаем номер портра и копируем порт в servAddr
    addLenght = sizeof(servAddr);
    if (getsockname(sockMain, &servAddr, &addLenght)) {
        perror("Вызов getsocketname неудачен ");
        exit(1);
    }

    printf("SERVER: номер порта: %d\n", ntohs(servAddr.sin_port));

    while(1) {
        addLenght = sizeof(clientAddr);
        bzero(buf, BUF_SIZE);
        if ((msgLenght = recvfrom(sockMain, buf, BUF_SIZE, 0, &clientAddr, &addLenght)) < 0) {
            perror("Ошибка socket клиента");
            exit(1);
        }

        printf("SERVER: Адрес клиента %s:%d\n",
            inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    
        printf("SERVER: Сообщение клиента:  \"%s\"\n", buf);

        buf = strcat(buf, "World");

        if(sendto(sockMain, buf, sizeof(buf), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) < 0 ) {
            perror("Ошибка отправки");
            exit(1);
        }
        printf("Сообщение изменено на %s\n", buf);
    }
    
    close(sockMain);

    return 0;
}

