#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    // Definir IP e porta
    const char* ip = "127.0.0.1";
    const int port = 58031;

    // Criar socket UDP
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erro ao criar o socket." << std::endl;
        return 1;
    }

    // Definir a estrutura do endereço
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    // Associar o socket ao endereço e porta
    if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Erro ao associar o socket ao endereço." << std::endl;
        close(sockfd);
        return 1;
    }

    // Buffer para receber a mensagem
    char buffer[BUFFER_SIZE];
    sockaddr_in sender_addr;
    socklen_t sender_len = sizeof(sender_addr);

    std::cout << "Aguardando mensagens em " << ip << ":" << port << "..." << std::endl;

    // Ler a mensagem recebida
    ssize_t bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (sockaddr*)&sender_addr, &sender_len);
    if (bytes_received < 0) {
        std::cerr << "Erro ao receber a mensagem." << std::endl;
        close(sockfd);
        return 1;
    }

    // Garantir que o buffer é uma string válida
    buffer[bytes_received] = '\0';

    // Imprimir a mensagem recebida
    std::cout << "Mensagem recebida: " << buffer << std::endl;

    // Fechar o socket
    close(sockfd);
    return 0;
} 
