

#include "Webserv.hpp"

int main(int argc, char **argv, char **env) {

    if (argc != 2)
        putError();
    env = NULL;
    Cluster cluster;
    if (cluster.setup(argv[1]))
        return (EXIT_FAILURE);

    return 0;
}
