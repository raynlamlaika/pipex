NAME = pipex

SRC = pipex.c help.c ft_strjoin.c split.c first_cmd.c ft_split.c
BSRC = bonus/pipex_bonus.c bonus/help.c bonus/ft_split.c bonus/ft_strjoin.c bonus/first_cmd.c bonus/heper_bonus.c bonus/split.c bonus/heredoc.c \
       bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c 

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

HEADER = pipex.h
HEADERB = bonus/pipexb.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

bonus: $(BOBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(HEADERB)
	$(CC) $(CFLAGS) -Ibonus -c $< -o $@

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

