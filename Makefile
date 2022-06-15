.PHONY: all clean fclean re

NAME = webserv

SRCS =	Cluster/Cluster.cpp\
        Cluster/Server.cpp\
        Cluster/Server_utils.cpp\
        Request/Request.cpp\
        Request/RequestUtils.cpp\
        ConfigParser/Config.cpp\
        ConfigParser/ConfigParser.cpp\
        ConfigParser/Location.cpp\
        Methods/Methods.cpp\
        Methods/MethodUtils.cpp\
        Response/Response.cpp\
        AutoIndex/AutoIndex.cpp\
        CgiHandler/CgiHandler.cpp\
        main.cpp\
        Utils.cpp
HDRS =	Webserv.hpp
OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror -std=c++98

%.o: %.cpp $(HDRS)
	c++ -c $(CFLAGS) $< -o $@

CC = c++ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	$(CC) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS) drunksite/.ilnur.txt drunksite/downloads/*

fclean: clean
	rm -f $(NAME)

re: fclean all