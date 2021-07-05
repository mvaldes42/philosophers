# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/05 17:59:50 by mvaldes           #+#    #+#              #
#    Updated: 2021/07/05 18:46:21 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

SRCS =	srcs/main.c\

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