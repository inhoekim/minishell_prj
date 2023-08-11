## unit_test
# NAME = $(patsubst %.c, %, $(SRCS))
NAME = test

## directory
HEADERS = 
SRCS = test.c
OBJS = $(SRCS:.c=.o)

## desktop env 
INC_DIRS = /opt/homebrew/opt/readline/include
LIB_DIRS = /opt/homebrew/opt/readline/lib

# INC_DIRS = /Users/dasong/.brew/opt/readline/include
# LIB_DIRS = /Users/dasong/.brew/opt/readline/lib

## compile
CC=	cc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INC_DIRS)) #-fsanitize=address
LDFLAGS= $(addprefix -L,$(LIB_DIRS)) -lreadline

.PHONY: clean, fclean, re, all, bonus

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ ../libft/libft.a $(OBJS);\ 

$(OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make clean -C ../libft
	@rm -f $(OBJS) 

fclean: clean
	@make fclean -C ../libft
	@rm -f $(NAME)

re: fclean all
