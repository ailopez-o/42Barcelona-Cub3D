# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 18:00:24 by bmoll-pe          #+#    #+#              #
#    Updated: 2023/04/12 13:17:03 by ailopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# Project Variables
################################################################################

# Name value
NAME =			cub3D

# Makefile file
MKF =			Makefile

################################################################################
# Compiler & Flags
################################################################################

# Variable to compile .c files
GCC =			gcc

# Flags for the gcc compilation
FLAGS =			-g
# FLAGS =			-Wall -Werror -Wextra -MMD -MP

MINILIBXCC :=	-I mlx -L $(MLX_DIR) -lmlx

OPENGL :=		-framework OpenGL -framework AppKit

################################################################################
# Root Folders
################################################################################

SRC_ROOT := src/
DEP_ROOT := .dep/
OBJ_ROOT := .obj/
INC_ROOT := inc/
LIB_ROOT := lib/

################################################################################
# Content Folders
################################################################################

# List of folders with header files.Each folder needs to end with a '/'. The
# path to the folders is relative to the root of the makefile. Library includes
# can be specified here.

INC_DIRS += ${INC_ROOT}



################################################################################
# Libraries
################################################################################


# Makefile LIBFT
LIBFT_DIR =		${LIB_ROOT}libft/
INC_DIRS += 	${LIBFT_DIR}

# LIBFT libraries
LIBFT =			${LIBFT_DIR}libft.a

# Makefile mlx
MLX_DIR =		${LIB_ROOT}mlx/
INC_DIRS += 	${MLX_DIR}

# Mlx libraries
MLX =		${MLX_DIR}libmlx.a

################################################################################
# Files
################################################################################

FILES =		src/mlx_window/key_hook.c \
			src/mlx_window/mouse_hook.c \
			src/mlx_window/draw_utils.c \
			src/geometry/vectors.c \
			src/geometry/raycast.c \
			src/main.c

#	----------------------------------------	INLCUDES

INCS 	:= $(addprefix -I, $(INC_DIRS))

#	----------------------------------------	OBJECTS

OBJS 	:= $(addprefix $(OBJ_ROOT), $(notdir $(FILES:.c=.o)))

#	----------------------------------------	DEPENDENCIES

DEPS 	:= $(addprefix $(OBJ_ROOT), $(notdir $(FILES:.c=.d)))

################################################################################
# Colors
################################################################################

# Colors
DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

################################################################################
# Project Target
################################################################################


all:
					@$(MAKE) -C $(LIBFT_DIR)
					@$(MAKE) -C $(MLX_DIR)
					@$(MAKE) $(NAME)

clean:
					@rm -f $(DEPS)
					@rm -f $(OBJS)
					@printf "All cub3d objects removed\n"

fclean:
					@rm -f $(DEPS)
					@rm -f $(OBJS)
					@rm -f $(NAME)					
					@printf "All cub3d files $(RED)removed\n$(DEF_COLOR)"

fcleanall:
					@$(MAKE) fclean -C $(LIBFT_DIR)
					@printf "All libft files $(RED)removed\n$(DEF_COLOR)"
					@$(MAKE) clean -C $(MLX_DIR)
					@printf "All mlx files $(RED)removed\n$(DEF_COLOR)"
					@$(MAKE) fclean

re:
					@$(MAKE) fclean
					@$(MAKE) all

reall:
					@$(MAKE) fcleanall
					@$(MAKE) all

test:
		echo $(OBJS)


$(NAME) ::			$(OBJS)
					@printf "$(DEL_LINE)\r Compiling $@"
					@$(GCC) $(FLAGS) $^ $(LIBFT) $(MLX) $(OPENGL) -o $@

$(NAME) ::
					@printf "$(DEL_LINE)\r$(BOLD)$(DARK_GREEN)CUB3D COMPILED ✅$(DEF_COLOR)\n"


$(OBJ_ROOT):
		@mkdir -p -m700 $@
$(DEP_ROOT):
		@mkdir -p -m700 $@

$(OBJ_ROOT)%.o:$(SRC_ROOT)mlx_window/%.c $(LIBFT) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled Cube3D file: <$(notdir $<)>"

$(OBJ_ROOT)%.o:$(SRC_ROOT)geometry/%.c $(LIBFT) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled Cube3D file: <$(notdir $<)>"

$(OBJ_ROOT)%.o:$(SRC_ROOT)%.c $(LIBFT) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled Cube3D file: <$(notdir $<)>"

# Include the deps when compile
-include $(DEPS)

.PHONY:			all update clean fclean re reall
