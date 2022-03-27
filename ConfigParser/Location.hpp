//
// Created by Darkside Morty on 24/03/2022.
//

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "../Webserv.hpp"
#define MEGA 1048576

class Location {
private:
    std::string root;
    std::vector<std::string> allowedMethods;
    std::string index;
    long bodySize;
public:
    Location() {};
    Location(std::string block);
    std::string getRoot() const;
    std::vector<std::string> getAllowedMethods() const;
    std::string getIndex() const;
    long getBodySize() const;

};


#endif
