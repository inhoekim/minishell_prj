NAME = parser_test

CC = cc
CFLAGS = -g3 $-fsanitize=address
MAIN = merge_tree.c parser_util.c parser.c rule1.c rule2.c rule3.c tokenizer_scan.c \
tokenizer_utils.c tokenizer.c tree.c

all : $(NAME)

$(NAME) : $(MAIN:.c=.o)
	$(CC) $(CFLAGS) -L../libft -lft -o $(NAME) $^ 

$(MAIN:.c=.o) : %.o : %.c
	$(CC) $(CFLAGS) -c $^ -I../include

clean :
	rm -f $(MAIN:.c=.o)

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all clean fclean re bonus
