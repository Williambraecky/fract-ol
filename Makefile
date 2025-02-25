# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/25 13:02:54 by wbraeckm          #+#    #+#              #
#    Updated: 2018/11/15 15:11:44 by wbraeckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
FLAGS = -O3 -Wall -Wextra -Werror
INCLUDES = ./includes/
SRCSFOLDER = ./srcs/
OBJFOLDER = ./obj/
LIBFOLDER = ./libft/
LIBINCLUDES = ./libft/includes/
LIBFT = $(LIBFOLDER)libft.a
MLXFOLDER = ./minilibx/
MLXINCLUDES = ./minilibx/
MLX = $(MLXFOLDER)libmlx.a

ITEMS = $(shell find srcs -type f | grep -E "\.c$$" | sed 's/srcs//g')
SRCS = $(addprefix $(SRCSFOLDER), $(ITEMS))
OBJ = $(addprefix $(OBJFOLDER), $(ITEMS:.c=.o))
SRCSUBS = $(shell find ./srcs -type d)
OBJSUBS = $(SRCSUBS:./srcs%=./obj%)
LONGEST = $(shell echo $(notdir $(SRCS)) | tr " " "\n" | \
	awk ' { if ( length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

ccblue = "\33[0;34m"
ccred = "\033[0;91m"
ccgreen = "\033[0;92m"
ccgreenhard = "\033[0;32m"
cccyan = "\033[0;96m"
ccreset = "\033[0;0m"
cclightgray = "\033[0;37m"

all: lib mlx $(NAME)

$(OBJFOLDER)/%.o:$(SRCSFOLDER)/%.c
	@printf $(ccblue)
	@printf "Compiling %-$(LONGEST)s" $(notdir $<)
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -I$(LIBINCLUDES) -I $(MLXINCLUDES)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "\r"

$(OBJSUBS):
	@mkdir $@

mlx:
	@make -C $(MLXFOLDER)

lib:
	@make -C $(LIBFOLDER)

$(NAME): $(OBJSUBS) $(OBJ)
	@printf $(cccyan)
	@printf "Compiling $(NAME) "
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -I$(INCLUDES) -I $(MLXINCLUDES) \
-I$(LIBINCLUDES) $(LIBFT) -framework OpenGL -framework AppKit $(MLX) -lpthread
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "                                                     \n"

clean:
	@printf $(ccred)
	rm -rf obj/
	@make -C $(LIBFOLDER) clean
	@make -C $(MLXFOLDER) clean
	@printf $(ccreset)

fclean: clean
	@printf $(ccred)
	rm -rf $(NAME_PUSHSWAP) $(NAME_CHECKER)
	@make -C $(LIBFOLDER) fclean
	@printf $(ccreset)

re: fclean all

norm:
	@norminette $(SRCSFOLDER) $(INCLUDES)

.PHONY: norm clean fclean re
