## unit_test
# NAME = $(patsubst %.c, %, $(SRCS))
NAME = test

## directory
HEADERS = 
SRCS = test1.c
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
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS);\

$(OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
