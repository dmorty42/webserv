

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Request.hpp"
#include "fstream"
#include "sstream"
#include "Page.hpp"

#define PORT 8080

int main() {
    struct sockaddr_in address;
    long int valread;
    int serverFd, newSocket;
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 1070\n\n";
//    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    int addrLen = sizeof(address);
    std::stringstream page;
    Request *request;
    size_t len;


    Page index("city.html");
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error\n");
        return (0);
    }
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind error\n");
        return (0);
    }
    if (listen(serverFd, 10) < 0) {
        perror("listen error\n");
        return (0);
    }
    while (1) {
        std::cout << "\n Waiting connection \n";
        if ((newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrLen)) < 0) {
            perror("accept error\n");
            return (0);
        }
        char buff[10000];
        valread = read(newSocket, &buff, 10000);
        request = new Request(buff);
        write(newSocket, hello, 63);
        std::string temp1 = index.getContent();
        write(newSocket, &temp1, 1070);
        std::cout << temp1 << std::endl;
//        index.sendPage(newSocket);
//        write(newSocket, "\n\n", 2);
//        char *temp;
//        page.get(temp, len);
//        std::string aa = page.str();
//        std::cout << aa << std::endl;
//        write(newSocket, &aa, len);
        std::cout << "message sent\n";
        close(newSocket);
    }
//    close(serverFd);
    return 0;
}
