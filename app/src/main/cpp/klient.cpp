
#include "klient.h"

int klient::connectToServer(string hostname, int port) {
    int sockets =0;
    struct sockaddr_in addr;
    if ((sockets = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, hostname.c_str(), &addr.sin_addr) <= 0) {
        return -1;
    }

    if (connect(sockets, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        return -1;
    }
    return sockets;
}

void klient::sendData(int sock, string data) {
    send(sock, data.c_str(), sizeof(data), 0);
}

string klient::recvData(int sock) {
    char buffer[1024] = {0};
    int valread = read(sock, buffer, 1024);
    if (valread != -1)
        return buffer;
    else return "Error";
}

void klient::disconnectFromServer(int sock) {
    close(sock);
}
