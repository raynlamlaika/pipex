NAME=pipex
SRC= pipex.c help.c ft_strjoin.c split.c first_cmd.c ft_split.c
OBJ=$(SRC:.c=.o)
CC=cc
CFLAGS=-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	rm -f $(OBJ)

re : clean all

fclean: clean
	rm -f $(NAME) 