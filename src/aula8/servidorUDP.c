/*
 * Servidor UDP para sistemas Unix
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int porta_servidor = 2000;
    unsigned char *mensagem;
    int sock, retorno;
    struct sockaddr_in endereco_cliente, endereco_servidor;
    socklen_t len;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Nao foi possivel abrir o socket");
        exit(EXIT_FAILURE);
    }

    memset(&endereco_servidor, 0, sizeof(endereco_servidor));
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = htonl(INADDR_ANY);
    endereco_servidor.sin_port = htons(porta_servidor);

    if (bind(sock, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor)) < 0) {
        close(sock);
        perror("Bind falhou");
        exit(EXIT_FAILURE);
    }

    printf("Aguardando mensagens na porta UDP %d\n", porta_servidor);

    while (1) {
        len = sizeof(endereco_cliente);
        mensagem = (unsigned char *)malloc(7);
        if (!mensagem) {
            perror("Erro ao alocar memoria");
            continue;
        }
        memset(mensagem, 0, 7);
        retorno = recvfrom(sock, mensagem, 7, 0, (struct sockaddr *)&endereco_cliente, &len);

        if (retorno < 0) {
            perror("Problema com o recebimento de dados");
            free(mensagem);
            continue;
        }

        // Assumindo que a mensagem é uma string ASCII terminada em null
        printf("Mensagem recebida: %s\n", mensagem + 1);

        free(mensagem);
    }
    // O loop é infinito, mas se você tiver um caso de saída, lembre-se de fechar o socket
    // close(sock);

    return EXIT_SUCCESS;
}

