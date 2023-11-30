# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 15:36:06 by framos-p          #+#    #+#              #
#    Updated: 2023/11/30 11:38:08 by framos-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	----------------------------------------	NAMES

# Name value
NAME =		cub3D

# Makefile file
MKF =		Makefile
MAKE = 		make --no-print-directory

#	----------------------------------------	COLORS

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#	----------------------------------------	FILES

# All files into src/
FILES =		main.c \
			startup/init.c \
			mlx_window/hooks.c \
			mlx_window/key_events.c \
			mlx_window/key_events_utils.c \
			mlx_window/mouse_events.c \
			mlx_window/window_init.c \
			geometry/vectors.c \
			geometry/vutils.c \
			geometry/raycast.c \
			geometry/utils.c \
			drawers/basics.c \
			drawers/geometry.c \
			drawers/utils_1.c \
			drawers/utils_2.c \
			drawers/utils_3.c \
			drawers/render.c \
			drawers/render_3d.c \
			drawers/render_map.c \
			drawers/render_player.c \
			parser/reader.c \
			parser/reader_utils.c \
			parser/utils.c \
			parser/utils_1.c \
			parser/gnl.c \
			parser/check_1.c \
			parser/check_2.c \


# Root folders
SRC_ROOT := src/
DEP_ROOT := .dep/
OBJ_ROOT := .obj/
LIB_ROOT := lib/

# Objects and dependencies defines
SRC 	:=	$(addprefix $(SRC_ROOT), $(FILES))
OBJS 	:=	$(addprefix $(OBJ_ROOT), $(FILES:.c=.o))
DEPS 	:=	$(addprefix $(DEP_ROOT), $(FILES:.c=.d))
INCS 	:=	$(addprefix -I, $(INC_DIRS))


#	----------------------------------------	HEADERS DIR

# Header of LIBFT
DIR_LIBFT =	lib/libft

# Headers of mlx
DIR_MLX =	lib/mlx

# Headers of project
DIR_HEDS =	inc/


#	----------------------------------------	LIBRARIES

# LIBFT libraries
LIBFT =		lib/libft/libft.a

# Makefile LIBFT
LIBFT_DIR =	lib/libft

# Mlx libraries
MLX =		lib/mlx/libmlx.a

# Makefile mlx
MLX_DIR =	lib/mlx


#	----------------------------------------	COMPILATION

# Variable to compile .c files
GCC =		gcc

# Flags for the gcc compilation
FLAGS =		-g -MMD -MP
#FLAGS +=	-O3
# FLAGS =		-Wall -Werror -Wextra -MMD -MP

MINILIBXCC := -I mlx -L $(DIR_MLX) -lmlx

OPENGL :=	-framework OpenGL -framework AppKit

# Address sanitizing flags
ASAN :=	-fsanitize=address -fsanitize-recover=address
ASAN +=	-fno-omit-frame-pointer -fno-common
ASAN +=	-fsanitize=pointer-subtract -fsanitize=pointer-compare


#	----------------------------------------	RULES

all:
		@$(MAKE) -sC $(LIBFT_DIR)
		@$(MAKE) -sC $(MLX_DIR)
		@$(MAKE) $(NAME)

clean:
		@rm -rf $(DEP_ROOT) $(OBJ_ROOT)
		@printf "$(RED)All cub3d objects removed\n$(DEF_COLOR)"

fclean:
		@rm -rf $(DEP_ROOT) $(OBJ_ROOT)
		@rm -f $(NAME)
		@printf "$(RED)All cub3d files removed\n$(DEF_COLOR)"

fcleanall:
		@$(MAKE) fclean -sC $(LIBFT_DIR)
		@printf "$(RED)All libft files removed\n$(DEF_COLOR)"
		@$(MAKE) clean -sC $(MLX_DIR)
		@printf "$(RED)All mlx files removed\n$(DEF_COLOR)"
		@$(MAKE) fclean

re:
		@$(MAKE) fclean
		@$(MAKE) all

reall:
		@$(MAKE) fcleanall
		@$(MAKE) all

$(NAME) :: $(OBJS)
		@printf "$(DEL_LINE)\r Compiling $@"
		@$(GCC) -v $(FLAGS) $^ $(LIBFT) $(MLX) $(MINILIBXCC) $(OPENGL) -o $@

$(NAME) ::
		@printf "$(DEL_LINE)$(GREEN)\rCUB3D COMPILED ✅$(DEF_COLOR)\n"

$(OBJ_ROOT)%.o : $(SRC_ROOT)%.c $(MKF) $(LIBFT) $(MKF)
		@mkdir -p $(dir $@) $(dir $(subst $(OBJ_ROOT), $(DEP_ROOT), $@))
		@printf "$(DEF_COLOR)[CUB3D] compiling: $< \n"
		@$(GCC) $(FLAGS) -I $(DIR_HEDS) -I $(LIBFT_DIR) -I $(DIR_MLX) -c $< -o $@
		@mv $(patsubst %.o, %.d, $@) $(dir $(subst $(OBJ_ROOT), $(DEP_ROOT), $@))


-include $(DEPS)

.PHONY:	all bonus update clean fclean re
