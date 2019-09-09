#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

using namespace std;

class klient {
public:
    int connectToServer(string hostname, int port);

    void sendData(int sock, string data);

    string recvData(int sock);

    void disconnectFromServer(int sock);
};
