

#include "Webserv.hpp"

int main(int argc, char **argv, char **env) {

    if (argc != 2)
        putError();
    Cluster cluster(env);
    if (cluster.setup(argv[1]))
        return (EXIT_FAILURE);
    if (cluster.run())
        return (EXIT_FAILURE);
    return 0;
}
