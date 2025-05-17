# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 13:18:29 by anpollan          #+#    #+#              #
#    Updated: 2025/05/06 14:20:32 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= while-not.out

SRCS		= ./src/main.c

OBJS		= $(SRCS:%.c=%.o)
CC			= cc
C_FLAGS		= -Wall -Wextra -Werror -g -I include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -L lib -lraylib -lm -ldl -lpthread -lGL -lrt -lX11 -lcurl -o $(NAME)

%.o: %.c $(HEADER) $(LIBFT_H)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	
fclean:	clean
	rm -rf $(NAME) compile_commands.json

re: fclean all

.PHONY: all clean fclean re
