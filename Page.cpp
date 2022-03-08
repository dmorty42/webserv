//
// Created by Darkside Morty on 3/7/22.
//

#include "Page.hpp"

int	ft_intlen(int c)
{
    int	len;

    len = 0;
    if (c == 0)
        return (1);
    if (c < 0)
    {
        c = -c;
        len++;
    }
    while (c)
    {
        c /= 10;
        len++;
    }
    return (len);
}

char	*ft_itoa(int n)
{
    char	*temp;
    int		len;

    len = ft_intlen(n);
    temp = (char *)malloc(len + 1);
    if (!temp)
        return (nullptr);
    if (n < 0)
    {
        temp[0] = '-';
        n = -n;
    }
    if (n == 0)
    {
        temp[len - 1] = '0';
    }
    temp[len] = '\0';
    while (n)
    {
        temp[--len] = n % 10 + '0';
        n /= 10;
    }
    return (temp);
}

Page::Page(const char* pageDirection) {
    std::ifstream ifs;
    std::string temp;
    ifs.open(pageDirection);
    if (!ifs.is_open())
        std::cerr << "Error: can't open html page: "
        << pageDirection << std::endl;
    for (; !ifs.eof() ; ) {
        ifs >> temp;
        content.append(temp);
        content.append("\n");
    }
    ifs.close();
    len = content.length();
    std::cout << "len = " << len << std::endl;
}

std::string Page::getContent() const {
    return (content);
}

size_t Page::getLen() const {
    return (len);
}

void Page::sendPage(int socket) const {
//    char* temp = ft_itoa(len);
//    write(socket, &temp, strlen(temp));
//    write(socket, "\n\n", 2);
//    std::cout << content;
//    char *temp = strdup(content.c_str());
    write(socket, &content, len);
//    write(socket, "\n\n", 2);
}