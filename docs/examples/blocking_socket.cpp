#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int listeningFd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listeningFd, (sockaddr*)&addr, sizeof(addr));
    listen(listeningFd, 10);
    std::clog << "Listening on port " << PORT << std::endl;

    std::vector<int> connectedFds;
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientFd = accept(listeningFd, (sockaddr*)&clientAddr,
            &clientAddrLen); // blocks until a connection is accepted

        connectedFds.push_back(clientFd);

        for (const auto &fd : connectedFds) {
            char buf[BUFFER_SIZE];
            ssize_t n = read(fd, buf, BUFFER_SIZE); // blocks until data is available

            std::clog << "Read " << n << " bytes, content: " << buf << std::endl;

            std::string message = "Message received";
            write(fd, message.c_str(), message.size());
        }
    }

    return 0;
}