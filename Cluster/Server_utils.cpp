//
// Created by Darkside Morty on 3/27/22.
//

#include "../Webserv.hpp"

int setReadFlag(int &kq, int &sock) {
    struct kevent ke;
    EV_SET(&ke, sock, EVFILT_READ, EV_ADD, 0, 0, 0);
    if (kevent(kq, &ke, 1, NULL, 0, NULL) < 0) {
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int setWriteFlag(int& kq, int& sock) {
    struct kevent ke;
    EV_SET(&ke, sock, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, 0);
    if (kevent(kq, &ke, 1, NULL, 0, NULL) < 0) {
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
