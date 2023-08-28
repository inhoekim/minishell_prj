## unit_test
# NAME = $(patsubst %.c, %, $(SRCS))
NAME = test

## directory
# HEADERS = 
SRCS = test13.c
OBJS = $(SRCS:.c=.o)

## desktop env 
INC_DIRS = /opt/homebrew/opt/readline/include
LIB_DIRS = /opt/homebrew/opt/readline/lib ../libft

## compile
CC=	gcc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INC_DIRS)) # -fsanitize=address
LDFLAGS= $(addprefix -L,$(LIB_DIRS)) -lreadline -lft -lncurses

.PHONY: clean, fclean, re, all

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../libft
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make clean -C ../libft
	@rm -f $(OBJS) 

fclean: clean
	@make fclean -C ../libft
	@rm -f $(NAME)

re: fclean all
