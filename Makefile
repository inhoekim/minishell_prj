## minishell
NAME = minishell

# ANSI escape code
CYAN  := \033[1;36;40m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

## directory
INC_DIRS = $(shell brew --prefix readline)/include
INC_DIRS += include libft
LIB_DIRS = $(shell brew --prefix readline)/lib libft
SRC_DIRS = src builtin_func execute parser signal

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

## file
HEADERS = arg_expansion.h execute.h libft.h rule.h exec_node_util.h execute_util.h parser.h 
HEADERS += make_argv_util.h tokenizer.h exec_word_util.h filename_expansion.h minishell.h here_doc.h wait_queue.h

SRCS = minishell.c arg_expansion.c exec_word_util.c execute_util.c make_argv_util.c
SRCS += exec_node_util.c execute.c filename_expansion.c parser_util.c rule3.c tokenizer_utils.c
SRCS += merge_tree.c rule1.c tokenizer.c tree.c parser.c rule2.c tokenizer_scan.c here_doc_static.c
SRCS += builtin_cd.c builtin_utils.c echo_pwd.c env_exit.c export_unset.c order_make_utils.c here_doc.c wait_queue.c
SRCS += signal_default.c signal_fork.c signal_heredoc.c 

OBJS = $(SRCS:.c=.o)

## compile
CC=	gcc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INC_DIRS))
LDFLAGS= $(addprefix -L,$(LIB_DIRS)) -lreadline -lft # -fsanitize=address # -g3  # -fsanitize=leak # export MallocStackLogging=1

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

re:
	@$(LOG) "re"
	@make fclean
	@make all
