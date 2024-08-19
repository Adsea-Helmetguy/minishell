# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlow <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 18:14:15 by mlow              #+#    #+#              #
#    Updated: 2023/09/29 18:39:46 by mlow             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc 
CFLAGS = -Wall -Werror -Wextra
SRC_DIR =./ft_files
INC_DIR =.

# ************************************************************************** */
#	SOURCE                                                               */
# ************************************************************************** */
#List of source files
SRC_FILE_NAMES = ft_printf.c \
		ft_putc.c \
		ft_putdi.c \
		ft_putp.c \
		ft_putstr.c \
		ft_putu.c \
		ft_putx.c 

#List of TEST files (DETELE/COMMENT LATER)
#TEST_FILE_NAMES = testcase.c

# ************************************************************************** */
#	FILE_LOCATION                                                        */
# ************************************************************************** */
SRC_FILE_PATHS = $(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))

#List of TEST files (DETELE/COMMENT LATER)
#TEST_FILE_PATH = $(addprefix $(SRC_DIR)/, $(TEST_FILE_NAMES))

OBJ_FILE_PATHS = $(SRC_FILE_PATHS:.c=.o)

# ************************************************************************** */
#	RULES                                                                */
# ************************************************************************** */
all: $(NAME)

$(NAME): $(OBJ_FILE_PATHS)
	ar rcs $(NAME) $(OBJ_FILE_PATHS)

$(OBJ_FILE_PATHS): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

#Creating rules to compile individual source files for bonus to object files
clean: 
	rm -f $(OBJ_FILE_PATHS)

#clear .o files including static library $(NAME)
fclean: clean
	rm -f $(NAME)

#clean files and remake "all"
re: fclean all

.PHONY: all clean fclean re

#List of TEST files (DETELE/COMMENT LATER ALL 3 of them)
#test: $(TEST_FILE_PATH) $(SRC_FILE_PATHS)
#	$(CC) $(CFLAGS) -I $(INC_DIR) $^
#	echo $(OBJ_FILE_PATHS)
