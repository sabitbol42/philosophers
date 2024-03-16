# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabitbol <sabitbol@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 16:12:13 by sabitbol          #+#    #+#              #
#    Updated: 2024/03/10 16:48:20 by sabitbol         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -MMD -MP -I.
THREAD_FLAG = -pthread
SRC = 	main	\
		utils	\
		init	\
		clear	\
		philo	\
		fork	\
		eat		\
		sleep	\
		think	\
			
NAME = philo
SRC_DIR = src/
NAMEBONUS = philo_bonus
OBJ = $(patsubst %, fobj/%.o, $(SRC))
DEP = $(patsubst %.o, %.d, $(OBJ))

all : $(NAME)

-include $(DEP)

fobj/%.o : $(SRC_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(THREAD_FLAG) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(THREAD_FLAG)

clean :
	rm -rf fobj

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re

FORCE : 