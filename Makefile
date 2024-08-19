# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlow <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 18:14:15 by mlow              #+#    #+#              #
#    Updated: 2024/04/17 18:43:20 by mlow             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g #-fsanitize=address
CFLAGS = -g -Wall -Werror -Wextra
#If they do make -n, if they see this:
#gcc -g  -g "-Wall -Werror -Wextra" -I ./includes -c main_src/main.c -o main_src/main.o
#when you compile it should show this along with the others

SRC_DIR = ./main_src
INC_DIR = ./includes

#LIBFT file names and paths
LIBFT_SRC_DIR = ./other_srcs/libft_project
LIBFT = $(LIBFT_SRC_DIR)/libft.a
LIB_FLAGS = -L $(LIBFT_SRC_DIR) -lft

#PRINTF file names and paths
PRINTF_SRC_DIR = ./other_srcs/printf_project
PRINTF = $(PRINTF_SRC_DIR)/libftprintf.a
PRINTF_FLAGS = -L $(PRINTF_SRC_DIR) -lftprintf

#GET_NEXT_LINE file names and paths
GNL_SRC_DIR = ./other_srcs/get_next_line_project
GNL = $(GNL_SRC_DIR)/libft_get_next_line.a
GNL_FLAGS = -L $(GNL_SRC_DIR) -lft_get_next_line


# ************************************************************************** */
#	SOURCE                                                               */
# ************************************************************************** */
#List of SOURCE(SRC) files
SRC_FILE_NAMES = main.c \
			./utils/ft_strcmp.c \
			./utils/ftps_lst.c \
			./utils/export_helper.c \
			./utils/index_quotes_helper.c \
			./utils/ft_split_export.c \
			./utils/write_helper.c \
			./signal/signal.c \
			./signal/executor_signal.c \
			./signal/heredoc_signal.c \
			./dollar_checker/dollar_tester.c \
			./dollar_checker/dollar_tester_helper.c \
			./dollar_checker/dollar_expand_question.c \
			./built_in_functions/builtin_function.c \
			./built_in_functions/echo_function.c \
			./built_in_functions/cd_function.c \
			./built_in_functions/pwd_function.c \
			./built_in_functions/env_function.c \
			./built_in_functions/unset_function.c \
			./built_in_functions/export_tester.c \
			./built_in_functions/exit_function.c \
			./non_builtin/non_builtin.c\
			./non_builtin/nonbuiltin_or_builtin.c \
			./frontend/component_free.c \
			./frontend/compress_tokens.c \
			./frontend/lexer_utils.c \
			./frontend/lexer_utils2.c \
			./frontend/lexer_utils3.c \
			./frontend/lexer.c \
			./frontend/parser.c \
			./frontend/parser_utils.c \
			./frontend/parser_utils2.c \
			./frontend/token_free.c \
			./frontend/token_utils.c \
			./executor/executor.c \
			./executor/executor_utils.c \
			./executor/executor_utils2.c \
			./executor/component_utils.c \
			./executor/piping.c \
			./executor/piping_2.c \
			./executor/redirections.c \
			./freeing/freeing_struc.c \
			
		
		

# ************************************************************************** */
#	FILE_LOCATION                                                        */
# ************************************************************************** */
SRC_FILE_PATHS = $(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
GNL_FILE_PATHS = $(addprefix $(GNL_SRC_DIR)/, $(GNL_FILE_NAMES))

OBJ_FILE_PATHS = $(SRC_FILE_PATHS:.c=.o)
GNL_OBJ_FILE_PATHS = $(GNL_FILE_PATHS:.c=.o)

# ************************************************************************** */
#	RULES                                                                */
# ************************************************************************** */
all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJ_FILE_PATHS) $(LIBFT) $(PRINTF) $(GNL)
	$(CC) $(OBJ_FILE_PATHS) -lreadline $(LIB_FLAGS) $(PRINTF_FLAGS) $(GNL_FLAGS) -o $(NAME)

$(LIBFT): 
	@make -sC $(LIBFT_SRC_DIR)
#make -C goes to that path directory's makefile and make using that makefile

$(PRINTF): 
	@make -sC $(PRINTF_SRC_DIR)
	
$(GNL): 
	@make -sC $(GNL_SRC_DIR)

$(MLX_LIB):
	@make -sC $(MLX_DIR)

$(OBJ_FILE_PATHS): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@


#Creating rules to compile individual source files for bonus to object files
clean: 
	rm -f $(OBJ_FILE_PATHS) $(GNL_OBJ_FILE_PATHS)
	@make clean -sC $(LIBFT_SRC_DIR)
	@make clean -sC $(PRINTF_SRC_DIR)
	@make fclean -sC $(GNL_SRC_DIR)

#clear .o files including static library $(NAME)
fclean: clean
	rm -f $(NAME)
	@make fclean -sC $(LIBFT_SRC_DIR)
	@make fclean -sC $(PRINTF_SRC_DIR)
	@make fclean -sC $(GNL_SRC_DIR)
#	@make fclean -sC $(MLX_DIR) Dont need cause the make file no fclean

#clean files and remake "all"
re: fclean all

.PHONY: all clean fclean re
