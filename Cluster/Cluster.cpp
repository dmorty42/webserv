//
// Created by Darkside Morty on 3/25/22.
//

#include "Cluster.hpp"

Cluster::Cluster() {
    _env = NULL;
}

Cluster::Cluster(char **env) {
    _env = env;
}

int Cluster::setup(const std::string &fileName) {
    _config = new ConfigParser(fileName, _env);
    _kq = kqueue();
    for (size_t i = 0; i < _config->getConfig().size(); ++i) {
        Server newServer;
        if (newServer.setup(_kq, *_config, i))
            continue;
        _listener[newServer.getSocket()] = newServer;
    }
    if (_listener.size() == 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int Cluster::run() {
    struct kevent events[_config->getConfig().size()];
    for (int n = 0; ; ) {
        if ((n = kevent(_kq, NULL, 0,
                        events, _config->getConfig().size(), NULL)) < 0) {
            perror("Error: kevent: ");
            continue;
        }
        for (int i = 0; i < n; ++i) {
            int fd = events[i].ident;
            if (events[i].filter == EVFILT_READ) {
                ServerIterator it = _listener.find(fd);
                if (it != _listener.end()) {
                    int conn = accept(fd, NULL, NULL);
                    if (conn < 0) {
                        perror("Error: accept: ");
                        continue;
                    }
                    _connection[conn] = it->second;
                    setReadFlag(_kq, conn);
                } else {
                   if (_connection[fd].receive(fd))
                       continue;
                   setWriteFlag(_kq, fd);
                }
            } else {
                _connection[fd].send(fd);
                _connection.erase(fd);
//                setReadFlag(_kq, fd);
                close(fd);
            }
        }
    }
    return (1);
}