# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchonvil <dchonvil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 21:53:14 by dchonvil          #+#    #+#              #
#    Updated: 2021/12/31 01:20:05 by dchonvil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MK = make

CC = clang

RM = rm -rf

NAME = philo

BNS = philo_bonus

SPATH = ./philos/philo/

BPATH = ./philos/philo_bonus/

SRC = $(SPATH)philo.c \
	$(SPATH)check.c \
	$(SPATH)init.c \
	$(SPATH)lst_mng.c \
	$(SPATH)moves.c \
	$(SPATH)utils.c \
	$(SPATH)writer.c

SRC_BNS = $(BPATH)philo_bonus.c \
	$(BPATH)check_bonus.c \
	$(BPATH)init_bonus.c \
	$(BPATH)lst_mng_bonus.c \
	$(BPATH)moves_bonus.c \
	$(BPATH)utils_bonus.c \
	$(BPATH)writer_bonus.c

HEAD_PATH = -I philos/inc

CFLAGS = -Wall -Werror -Wextra -pthread

OBJ = $(SRC:.c=.o)

OBJ_BNS = $(SRC_BNS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(HEAD_PATH) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(HEAD_PATH)

clean:
	(cd $(SPATH) && $(RM) *.o)
	(cd $(BPATH) && $(RM) *.o)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BNS)

bonus:	$(OBJ_BNS)
	$(CC) $(SRC_BNS) -o $(BNS) $(CFLAGS) $(HEAD_PATH)

re: fclean all

