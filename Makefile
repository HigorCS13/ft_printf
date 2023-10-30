# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hicunha- <hicunha-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/29 10:54:43 by hicunha-          #+#    #+#              #
#    Updated: 2023/10/29 10:54:43 by hicunha-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprinft.a

CC = cc

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra

SRCS = 

OBJS = $(SRCS:.c=.o)

BONUS = 

BONUS_OBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rc $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJS)
		ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
		$(RM) $(BONUS_OBJS) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all