## minishell
NAME = minishell

# ANSI escape code
CYAN  := \033[1;36;40m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

## directory
INC_DIRS = $(shell brew --prefix readline)/include
INC_DIRS += include # libft
LIB_DIRS = $(shell brew --prefix readline)/lib libft
SRC_DIRS = src builtin_func execute parser signal expansion grammar

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

## file
HEADERS = builtin.h execute.h expansion.h grammar.h minishell.h parser.h ft_signal.h util.h

SRCS = minishell.c arg_expansion.c exec_util.c exec_word_util.c
SRCS += exec_etc.c execute.c filename_expansion.c rule3.c tokenizer_utils.c
SRCS += merge_tree.c rule1.c tokenizer.c tree.c parser.c rule2.c tokenizer_scan.c
SRCS += builtin_cd.c builtin_utils.c echo_pwd.c env_exit.c export_unset.c order_make_utils.c heredoc.c wait_process.c
SRCS += signal_default.c signal_fork.c signal_heredoc.c parameter_expansion.c exec_redirect.c exec_subshell.c exec_redirect_util.c
SRCS += exec_fork.c exec_builtin.c exec_word.c wildcard.c wait_process_util.c heredoc_util.c heredoc_static.c
SRCS += signal_util.c

OBJS = $(SRCS:.c=.o)

## compile
CC=	gcc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INC_DIRS))
LDFLAGS= $(addprefix -L,$(LIB_DIRS)) -lreadline -lft  # -g3  # -fsanitize=leak # export MallocStackLogging=1

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
