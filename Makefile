# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbondare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/29 17:27:01 by tbondare          #+#    #+#              #
#    Updated: 2018/09/08 21:17:09 by tbondare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tbondare.filler 
SRC = ./*.c

LIBFT = ./libft
LIBFTA = $(LIBFT)/libft.a

OBJ = ./*.o

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc -Wall -Wextra -Werror -c $(SRC)
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) $(LIBFTA) 
	echo tbondare.filler compilation is \done

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJ)
	echo object files have been cleaned

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	echo tbondare.filler has been removed

re: fclean all
