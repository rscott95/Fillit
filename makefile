# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rscott <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 11:02:55 by rscott            #+#    #+#              #
#    Updated: 2018/05/23 13:33:59 by rscott           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CFLAGS += -Wall -Wextra -Werror
CFLAGS += -I libft/

SRC = fillit.c solver.c maptools.c othertools.c inputchecker.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(OBJ): %.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[32mCompiled Executable\033[0m"

clean:
	@rm -rf $(OBJ)
	@make -C libft clean
	@echo "\033[32mRemoved Object Files\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@echo "\033[32mRemoved Executable\033[0m"

re: fclean all

.PHONY = all clean fclean clean re
