NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude -g3

SRC = src/main.c src/parsing.c src/init.c src/threads.c src/utils.c src/routines.c src/monitor.c
INCLUDE = include

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all