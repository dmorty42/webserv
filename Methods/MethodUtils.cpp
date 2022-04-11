//
// Created by Darkside Morty on 11/04/2022.
//

#include "Methods.hpp"

std::map<std::string, std::string> splitBody(const std::string& body, const std::string& delim) {
    std::map<std::string, std::string> temp;
    size_t z[2];
    int i = body.find(delim);
    for (std::string filename; i != (int)std::string::npos;) {
        z[0] = body.find("filename", i) + 10;
        z[1] = body.find('\"', z[0]);
        filename = body.substr(z[0], z[1] - z[0]);
        if (filename.empty())
            break;
        z[0] = body.find("Content-Type", i);
        z[0] = body.find('\n', z[0]) + 2;
        i = body.find(delim, i + 1);
        temp[filename] = body.substr(z[0], i - z[0]);
    }
    return temp;
}

std::map<std::string, std::string> oneBody(Request& request) {
    std::map<std::string, std::string> temp;
    std::string fileName = request.getPath().substr(request.getPath().rfind("/") + 1,
                                                    request.getPath().size() -
                                                    request.getPath().rfind("/") - 1);
    temp[fileName] = request.getBody();
    return temp;
}

void creatingFile(std::string fileName, Location& location,
                  std::string& content) {
    std::string path = location.getRoot().append("/");
    path.append(fileName);
    std::ofstream ofs;
    for (int i = 1;  ; ++i) {
        if (!access(path.c_str(), 0)) {
            if (i != 1)
                path.erase(path.size() - 1);
            path.append(std::to_string(i));
        }
        else {
            ofs.open(path);
            if (!ofs.is_open())
                std::cerr << "Error: can't create file!!!" << std::endl;
            ofs << content;
            break;
        }
    }
    ofs.close();
}

