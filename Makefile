# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmartine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/14 21:19:36 by cmartine          #+#    #+#              #
#    Updated: 2018/06/21 02:45:47 by cmartine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	# COMPILATION
CC =		clang
C_FLAGS =	-Werror -Wextra -Wall -g #-fsanitize=address -fno-omit-frame-pointer #PENSER A ENLEVER LE G !!
ADD_FLAGS =	

	# BINARY
NAME =		fdf

	# DIRECTORIES
SRC_PATH =	src
OBJ_PATH =	obj
INC_PATH =	include\
			minilibx/\
			libft/

	# SOURCES
SRC_NAME =	draw_line.c\
			draw_point.c\
			free_map.c\
			main.c\
			ornaments.c\
			save_map.c\

OBJ_NAME =		$(SRC_NAME:.c=.o)

	# PREFIXES
LIBFT =		-L libft/ -lft
MLIBX =		-L minilibx/ -lmlx -lm -framework OpenGL -framework AppKit

	# PATHS foreach
LIB_P =		$(addprefix -L, $(LIB_NAME)/)
SRC =		$(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ =		$(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
INC_P =		$(foreach dir, $(INC_DIR), -I $(dir))

# *****************************************************************************

	# COLORS
LOG_CLEAR=		\033[2K
LOG_UP =		\033[A
LOG_NOCOLOR =	\033[0m
LOG_BOLD =		\033[1m
LOG_UNDERLINE =	\033[4m
LOG_BLINKING =	\033[5m
LOG_BLACK =		\033[1;30m
LOG_RED =		\033[1;31m
LOG_GREEN =		\033[1;32m
LOG_YELLOW =	\033[1;33m
LOG_BLUE =		\033[1;34m
LOG_VIOLET =	\033[1;35m
LOG_CYAN =		\033[1;36m
LOG_WHITE =		\033[1;37m

# *****************************************************************************

# RULES

all:	libft_comp mlibx_comp $(NAME)

$(NAME): $(OBJ)
	@echo -e "--$(LOG_CLEAR)$(LOG_CYAN)$(NAME)$(LOG_NOCOLOR) --> $(LOG_YELLOW)assembling$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(C_FLAGS) $(ADD_FLAGS) $(MLIBX) $(LIBFT) -o $@ $^ $(INC_P)
	@echo -e "--$(LOG_CLEAR)$(LOG_CYAN)$(NAME)$(LOG_NOCOLOR) --> $(LOG_GREEN)✓$(LOG_NOCOLOR)"

re:		fclean all

libft_comp:
	@make all -C libft/
	@echo -e "--$(LOG_CLEAR)$(LOG_CYAN)libft$(LOG_NOCOLOR) --> $(LOG_GREEN)✓$(LOG_NOCOLOR)"

mlibx_comp:
	@make all -C minilibx/
	@echo -e "--$(LOG_CLEAR)$(LOG_CYAN)minilibx$(LOG_NOCOLOR) --> $(LOG_GREEN)✓$(LOG_NOCOLOR)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@echo -e "--$(LOG_CLEAR)$(LOG_CYAN)$(NAME)$(LOG_NOCOLOR) --> $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(C_FLAGS) $(ADD_FLAGS) -o $@ -c $< $(INC_P)

.PHONY: clean fclean

clean:
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) -->  $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJ_PATH)
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean minilibx$(LOG_NOCOLOR)"
	@make clean -C minilibx/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean libft$(LOG_NOCOLOR)"
	@make clean -C libft/

fclean: clean
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean minilibx$(LOG_NOCOLOR)"
	@make clean -C minilibx/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean libft$(LOG_NOCOLOR)"
	@make fclean -C libft/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) --> $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJ_PATH)
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) --> $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -f $(NAME)

# NORME
norme: 
	norminette $(SRC_DIR)
	norminette $(INC_DIR)*.h

