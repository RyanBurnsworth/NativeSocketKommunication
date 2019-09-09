
#include "klient.h"

/**
 *
 * @param hostname - IP address of remote server
 * @param port - port number to connect to on remote server
 * @return - returns a socket or -1 if an error
 */
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

/**
 *
 * @param sock - active socket to send data through
 * @param data - data to be sent to the remote server
 */
void klient::sendData(int sock, string data) {
    send(sock, data.c_str(), sizeof(data), 0);
}

/**
 *
 * @param sock - active socket to listen for incoming data on
 * @return - incoming data from remote server
 */
string klient::recvData(int sock) {
    char buffer[1024] = {0};
    int valread = read(sock, buffer, 1024);
    if (valread != -1)
        return buffer;
    else return "Error";
}

/**
 *
 * @param sock - active socket to disconnect from
 */
void klient::disconnectFromServer(int sock) {
    close(sock);
}
