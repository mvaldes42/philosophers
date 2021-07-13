# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/05 17:59:50 by mvaldes           #+#    #+#              #
#    Updated: 2021/07/13 15:43:43 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

SRCS =	srcs/main.c\
		srcs/init_inputs.c\
		srcs/utils.c\
		srcs/utils_g.c\
		srcs/states.c\
		srcs/t_philos.c\
		srcs/t_death_clock.c\

OBJS = $(SRCS:.c=.o)
CC = @gcc
RM = @/bin/rm -f
CC_FLAGS = -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	compile $(OBJS)
			$(CC) $(CC_FLAGS) $(OBJS) -o $(NAME) -pthread
			@echo ">> compile done"

clean:
			$(RM) $(OBJS)
			@echo ">> clean done"

fclean:		clean
			$(RM) $(NAME)
			@echo ">> fclean done"

re:			fclean all

.PHONY: clean fclean re compile all