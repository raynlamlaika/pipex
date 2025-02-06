NAME=pipex
BONUSS=pipex_bonus

SRC= pipex.c help.c ft_strjoin.c split.c first_cmd.c ft_split.c
OBJ=$(SRC:.c=.o)
CC=cc
HEADER=pipex.h
CFLAGS=-Wall -Werror -Wextra

BSRC= pipex_bonus.c help.c ft_split.c ft_strjoin.c first_cmd.c bonus_heper.c

BOBJ=$(BSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $^ -o $(NAME)

bonus: $(BONUSS)

$(BONUSS): $(BOBJ) $(HEADER)
	@$(CC) $(CFLAGS) $^ -o $(BONUSS)


clean:
	@rm -f $(OBJ) $(BOBJ)

re : clean all

fclean: clean
	@rm -f $(NAME) $(BONUSS)
