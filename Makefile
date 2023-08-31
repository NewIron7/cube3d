# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 18:05:23 by hboissel          #+#    #+#              #
#    Updated: 2023/08/31 14:56:09 by ddelhalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

DBG		=	$(DBG_DIR)/$(NAME)

SRC_DIR =	src

BIN_DIR =	obj

DBG_DIR =	dbg

SRC = $(SRC_DIR)/main.c\
	  $(SRC_DIR)/init_raycasting.c\
	  $(SRC_DIR)/img.c\
	  $(SRC_DIR)/get_coord_wall.c\
	  $(SRC_DIR)/raycasting.c\
	  $(SRC_DIR)/print_wall_textured.c\
	  $(SRC_DIR)/point.c\
	  $(SRC_DIR)/textures.c\
	  $(SRC_DIR)/key_handle.c\
	  $(SRC_DIR)/check_line.c\
	  $(SRC_DIR)/load_file.c\
	  $(SRC_DIR)/load_map.c\
	  $(SRC_DIR)/process_setting.c\
	  $(SRC_DIR)/read_file.c\
	  $(SRC_DIR)/write_error.c\
	  $(SRC_DIR)/error.c\
	  $(SRC_DIR)/free_map.c\
	  $(SRC_DIR)/get_dist_wall.c\
	  $(SRC_DIR)/get_first_step.c\
	  $(SRC_DIR)/next_wall.c\
	  $(SRC_DIR)/is_wall.c\
	  $(SRC_DIR)/do_player_move.c\
	  $(SRC_DIR)/do_mouse_move.c\
	  $(SRC_DIR)/get_screen.c\
	  $(SRC_DIR)/minimap.c\
	  $(SRC_DIR)/ft_plotline.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

DBG_OBJ = $(SRC:$(SRC_DIR)/%.c=$(DBG_DIR)/%.o)

DEPS = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.d)

DBG_DEPS = $(SRC:$(SRC_DIR)/%.c=$(DBG_DIR)/%.d)

MLX_PATH = ./minilibx-linux

MLX = -L$(MLX_PATH) -lmlx

MLX_REQUIRES = -lXext -lX11 -lz

MATH = -lm

LIBFT_PATH = ./libft

LIBFT = -L$(LIBFT_PATH) -lft

INCLUDES = ./inc

CFLAGS = -Werror -Wextra -Wall -I$(INCLUDES) -I$(MLX_PATH) -I$(LIBFT_PATH)

all :	$(NAME)

debug	:	$(DBG)

$(BIN_DIR) $(DBG_DIR):
	@ mkdir -p $@

$(DBG_OBJ) : $(DBG_DIR)/%.o: $(SRC_DIR)/%.c | $(DBG_DIR)
	@ $(CC) $(CFLAGS) -g3 -MMD -c $< -o $@

$(OBJ) : $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	@ $(CC) $(CFLAGS) -MMD -c $< -o $@

$(DBG) : $(DBG_OBJ)
	@ $(MAKE) -sC $(LIBFT_PATH)
	@ $(MAKE) -sC $(MLX_PATH)
	@ $(CC) $(CFLAGS) -g3 $(DBG_OBJ) $(MLX) $(MLX_REQUIRES) $(MATH) $(LIBFT) -o $(DBG)
	@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

$(NAME) : $(OBJ)
	@ $(MAKE) -sC $(LIBFT_PATH)
	@ $(MAKE) -sC $(MLX_PATH)
	@ $(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLX_REQUIRES) $(MATH) $(LIBFT) -o $(NAME)
	@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

clean :
	@ make -sC $(MLX_PATH) clean
	@ make -sC $(LIBFT_PATH) clean
	@ rm -f $(OBJ)
	@ rm -f $(OBJ:.o=.d)
	@ rm -rf $(BIN_DIR) $(DBG_DIR)
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
	@ make -sC $(LIBFT_PATH) fclean
	@ rm -f $(NAME)
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"

re : fclean all

-include	${DEPS} ${DBG_DEPS}

.PHONY: all clean fclean re debug
