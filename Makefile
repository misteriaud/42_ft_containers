NAME = ex00
SRCS = $(addprefix srcs/, main.cpp)
OBJS = ${SRCS:.cpp=.o}
FLAGS = -Wall -Wextra -Werror -std=c++98 -g
HDRS = hdrs
# $(addprefix hdrs/, vector.hpp)
CC = c++

all: ${NAME} Makefile

${NAME}: ${OBJS} | $(HDRS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o: %.cpp
	${CC} ${FLAGS} -I$(HDRS) -c $< -o ${<:.cpp=.o}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
