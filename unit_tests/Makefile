NAME = unit_test
VECTORS_SRCS = $(addprefix vector/, \
	constructor.cpp \
	assign.cpp \
	iterator.cpp )

SRCS = $(addprefix srcs/, main.cpp common.cpp $(VECTORS_SRCS))
OBJS = ${SRCS:.cpp=.o}
FLAGS = -Wall -Wextra -Werror -g
HDRS = ../hdrs
CC = g++

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
