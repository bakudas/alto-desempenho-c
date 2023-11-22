/*
 * Cliente UDP para sistemas Unix
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    int porta_servidor = 2000;
    char ip_servidor[] = "127.0.0.1";
    unsigned char mensagem[7];
    int sock, retorno;
    struct sockaddr_in endereco_servidor;

    mensagem[0] = 6; // Define o tamanho da mensagem
    strcpy((char *)(mensagem + 1), "Pablo"); // Copia a mensagem

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Não foi possível abrir o socket");
        exit(EXIT_FAILURE);
    }

    memset(&endereco_servidor, 0, sizeof(endereco_servidor));
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = inet_addr(ip_servidor);
    endereco_servidor.sin_port = htons(porta_servidor);

    retorno = sendto(sock, mensagem, sizeof(mensagem), 0,
                     (struct sockaddr *) &endereco_servidor,
                     sizeof(endereco_servidor));

    if (retorno < 0) {
        perror("Não foi possível enviar a mensagem");
        close(sock);
        exit(EXIT_FAILURE);
    } else {
        printf("Mensagem enviada.\n");
    }

    close(sock);
    return EXIT_SUCCESS;
}

