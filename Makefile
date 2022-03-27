.PHONY: all clean fclean re

NAME = webserv

SRCS =	Cluster/Cluster.cpp\
        Cluster/Server.cpp\
        Cluster/Server_utils.cpp\
        ConfigParser/Config.cpp\
        ConfigParser/ConfigParser.cpp\
        ConfigParser/Location.cpp\
        main.cpp\
        Utils.cpp
HDRS =	Webserv.hpp
OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

%.o: %.cpp $(HDRS)
	c++ -c $(CFLAGS) $< -o $@

CC = c++ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	$(CC) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all