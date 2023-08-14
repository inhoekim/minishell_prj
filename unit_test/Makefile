## unit_test
# NAME = $(patsubst %.c, %, $(SRCS))
NAME = test

## directory
HEADERS = 
SRCS = 6_wildcard.c
OBJS = $(SRCS:.c=.o)

## desktop env 
INC_DIRS = /opt/homebrew/opt/readline/include
LIB_DIRS = /opt/homebrew/opt/readline/lib ../libft

# INC_DIRS = /Users/dasong/.brew/opt/readline/include
# LIB_DIRS = /Users/dasong/.brew/opt/readline/lib

## compile
CC=	gcc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INC_DIRS)) #-fsanitize=address
LDFLAGS= $(addprefix -L,$(LIB_DIRS)) -lreadline -lft

.PHONY: clean, fclean, re, all, bonus

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS);\ 

$(OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make clean -C ../libft
	@rm -f $(OBJS) 

fclean: clean
	@make fclean -C ../libft
	@rm -f $(NAME)

re: fclean all
