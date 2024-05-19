# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aattak <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 16:14:22 by aattak            #+#    #+#              #
#    Updated: 2024/05/19 15:52:29 by aattak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(SERVER) $(CLIENT)

B_NAME = $(B_SERVER) $(B_CLIENT)

C_SERVER = mandatory/server.c
C_CLIENT = mandatory/client.c

CB_SERVER = bonus/server_bonus.c
CB_CLIENT = bonus/client_bonus.c

O_SERVER = $(C_SERVER:.c=.o)
O_CLIENT = $(C_CLIENT:.c=.o)

OB_SERVER = $(CB_SERVER:.c=.o)
OB_CLIENT = $(CB_CLIENT:.c=.o)

SERVER = server
CLIENT = client

B_SERVER = server_bonus
B_CLIENT = client_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(SERVER): $(O_SERVER)
		$(CC) $(CFLAGS) $(O_SERVER) -o $(SERVER)

$(CLIENT): $(O_CLIENT)
		$(CC) $(CFLAGS) $(O_CLIENT) -o $(CLIENT)

bonus: $(B_NAME)

$(B_SERVER): $(OB_SERVER)
		$(CC) $(CFLAGS) $(OB_SERVER) -o $(B_SERVER)

$(B_CLIENT): $(OB_CLIENT)
		$(CC) $(CFLAGS) $(OB_CLIENT) -o $(B_CLIENT)

clean:
		$(RM) $(O_SERVER) $(O_CLIENT)
		$(RM) $(OB_SERVER) $(OB_CLIENT)

fclean: clean
		$(RM) $(NAME)
		$(RM) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
.SECONDARY: $(O_SERVER) $(O_CLIENT) $(OB_SERVER) $(OB_CLIENT)
