//
// Created by Darkside Morty on 3/25/22.
//

#include "Webserv.hpp"

typedef std::__1::map<std::__1::string, Location>::const_iterator LocIter;

void checkFileName(std::string fileName) {
   if (fileName.compare(fileName.length() - 5, 5, ".conf") != 0) {
       std::cerr << "Error: bad configuration file name extension" << std::endl;
   }
}

void putError() {
    std::cerr << "Error: wrong number of arguments" << std::endl;
    exit(EXIT_FAILURE);
}

const Location &search_location(std::string path, const std::map<std::string, Location> &locations){
    LocIter it = locations.find(path);
    while (it == locations.end()){
        path.erase(path.rfind("/"));
        if (path.empty())
            return locations.find("/")->second;
    }
    return locations.find(path)->second;
}

