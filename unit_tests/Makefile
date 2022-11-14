NAME = unit_test
VECTORS_SRCS = $(addprefix vector/, \
	constructor.cpp \
	assign.cpp \
	iterator.cpp \
	capacity.cpp \
	element_access.cpp \
	modifier.cpp \
	non_members_and_miscs.cpp )
SRCS = $(addprefix srcs/, main.cpp common.cpp $(VECTORS_SRCS))
OBJS = ${SRCS:.cpp=.o}
# https://github.com/tsduck/tsduck/issues/205
FLAGS = -Wall -Wextra -Werror -std=c++98 -g
# -D DEBUG
# HDRS = ft_container
HDRS = ../hdrs
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
