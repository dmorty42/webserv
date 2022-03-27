//
// Created by Darkside Morty on 3/25/22.
//

#include "Cluster.hpp"

Cluster::Cluster() {
}

int Cluster::setup(const std::string &fileName) {
    _config = new ConfigParser(fileName);
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
