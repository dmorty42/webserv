//
// Created by Darkside Morty on 3/25/22.
//

#include "Webserv.hpp"

void checkFileName(std::string fileName) {
   if (fileName.compare(fileName.length() - 5, 5, ".conf") != 0) {
       std::cerr << "Error: bad configuration file name extension" << std::endl;
   }
}

void putError() {
    std::cerr << "Error: wrong number of arguments" << std::endl;
    exit(EXIT_FAILURE);
}
