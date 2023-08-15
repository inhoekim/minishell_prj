## minishell
NAME = minishell

## directory
HEADERS = ./include/*.h
SRC_DIRS = src builtin_func execute parser
SRCS = 
OBJS = $(SRCS:.c=.o)

## desktop env 
INC_DIRS = /opt/homebrew/opt/readline/include 
LIB_DIRS = /opt/homebrew/opt/readline/lib ../libft

# INC_DIRS = /Users/dasong/.brew/opt/readline/include
# LIB_DIRS = /Users/dasong/.brew/opt/readline/lib

## compile
CC=	gcc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address
LDFLAGS= $(addprefix -L,$(LIB_DIRS)) -lreadline -lft

.PHONY: clean, fclean, re, all, bonus

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(addprefix -I,$(INC_DIRS)) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make clean -C ../libft
	@rm -f $(OBJS) 

fclean: clean
	@make fclean -C ../libft
	@rm -f $(NAME)

re: fclean all
