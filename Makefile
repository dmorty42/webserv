NAME	=	webserver

SRCS	=	Cluster/Cluster.cpp\
			Cluster/Server.cpp\
			Cluster/Server_utils.cpp\
			ConfigParser/Config.cpp\
			ConfigParser/ConfigParser.cpp\
			ConfigParser/Location.cpp\
			main.cpp\
			Utils.cpp

HEADERS	=	Webserv.hpp\
			Cluster/Cluster.hpp\
            Cluster/Server.hpp\
			ConfigParser/Location.hpp\
			ConfigParser/ConfigParser.hpp\
			ConfigParser/Config.hpp\

CC		=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -g -std=c++98

OBJS	=	$(SRCS:.cpp=.o)

%.o: %.c
	$(CC) $(CXXFLAGS) $(SRCS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $^

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

.PHONY:	all clean fclean re