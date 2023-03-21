# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 18:05:23 by hboissel          #+#    #+#              #
#    Updated: 2023/03/21 10:09:08 by hboissel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d

SRC_DIR = src

BIN_DIR = obj

SRC = $(SRC_DIR)/main.c\
	  $(SRC_DIR)/init.c\
	  $(SRC_DIR)/img.c\
	  $(SRC_DIR)/get_coord_wall.c\
	  $(SRC_DIR)/raycasting.c\
	  $(SRC_DIR)/point.c\
	  $(SRC_DIR)/test.c\
	  $(SRC_DIR)/error.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(BIN_DIR)/%.o)

MLX_PATH = ./minilibx-linux

MLX = -L$(MLX_PATH) -lmlx

MLX_REQUIRES = -lXext -lX11 -lz

MATH = -lm

LIBFT_PATH = ./libft

LIBFT = -L$(LIBFT_PATH) -lft

INCLUDES = ./inc

CFLAGS = -Werror -Wextra -Wall -I$(INCLUDES) -I$(MLX_PATH) -I$(LIBFT_PATH) -g3

all :	$(NAME)


$(BIN_DIR):
	@ mkdir -p $(BIN_DIR)

$(OBJ) : $(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(BIN_DIR)
	@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@ $(MAKE) -s -C $(MLX_PATH)
	@ $(MAKE) -s -C $(LIBFT_PATH)
	@ $(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLX_REQUIRES) $(MATH) $(LIBFT) -o $(NAME)
	@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

clean :
	@ make -sC $(LIBFT_PATH) clean
	@ make -sC $(MLX_PATH) clean
	@ rm -f $(OBJ)
	@ rm -rf $(BIN_DIR)
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
	@ make -sC $(LIBFT_PATH) fclean
	@ rm -f $(NAME)
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"

re : fclean
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRecompile .. 🔄"
	@ $(MAKE) -s $(NAME)

.PHONY: all clean fclean re
