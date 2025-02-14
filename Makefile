NAME=pipex
BONUSS=pipex_bonus

SRC= pipex.c help.c ft_strjoin.c split.c first_cmd.c ft_split.c
OBJ=$(SRC:.c=.o)
CC=cc
HEADER=pipex.h
CFLAGS=-Wall -Werror -Wextra

BSRC= pipex_bonus.c help.c ft_split.c ft_strjoin.c first_cmd.c heper_bonus.c split.c heredoc.c get_next_line_bonus.c get_next_line_utils_bonus.c 
BOBJ=$(BSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

bonus: $(BONUSS)

$(BONUSS): $(BOBJ)
	$(CC) $(CFLAGS) $^ -o $(BONUSS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BOBJ)

re : clean all

fclean: clean
	@rm -f $(NAME) $(BONUSS)
