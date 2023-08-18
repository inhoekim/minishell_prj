## minishell
NAME = minishell

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

## directory
## seykim readline 설정 8/16
INC_DIRS = /Users/seykim/.brew/Cellar/readline/include
INC_DIRS += include
LIB_DIRS = /Users/seykim/.brew/Cellar/readline/lib libft
SRC_DIRS = src builtin_func execute parser

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

## file
HEADERS = arg_expansion.h execute.h libft.h rule.h exec_node_util.h execute_util.h parser.h 
HEADERS += make_argv_util.h tokenizer.h exec_word_util.h filename_expansion.h minishell.h here_doc.h

SRCS = minishell.c msh_utils.c arg_expansion.c exec_word_util.c execute_util.c make_argv_util.c
SRCS += exec_node_util.c execute.c filename_expansion.c parser_util.c rule3.c tokenizer_utils.c
SRCS += merge_tree.c rule1.c tokenizer.c tree.c parser.c rule2.c tokenizer_scan.c wait_queue.c
SRCS += builtin_cd.c builtin_utils.c echo_pwd.c env_exit.c export_unset.c order_make_utils.c here_doc.c

OBJS = $(SRCS:.c=.o)

## compile
CC=	gcc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INC_DIRS)) -g3 -fsanitize=address
LDFLAGS= $(addprefix -L,$(LIB_DIRS)) -lreadline -lft -g3 -fsanitize=address

.PHONY: clean, fclean, re, all

all: $(NAME)

$(NAME): $(OBJS)
	@$(LOG) "Linking.."
	@make -C libft
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): %.o: %.c $(HEADERS)
	@$(LOG) "Compiling.."
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(LOG) "clean"
	@make clean -C libft
	@rm -f $(OBJS) 

fclean: clean
	@$(LOG) "fclean"
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
