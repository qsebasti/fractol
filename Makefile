# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/08 17:36:58 by qsebasti          #+#    #+#              #
#    Updated: 2019/03/03 18:35:08 by qsebasti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY = all clean fclean re createlib opti

NAME = fractol

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O2

SRC_NAME = main.c \
		   ft_hook.c \
		   ft_draw.c \
		   ft_keyhook.c \
		   ft_mousehook.c \
		   ft_setfrac.c \
		   ft_util.c \
		   ft_settings.c \
		   threading.c \
		   zoom.c \
		   ft_color.c

SRC_PATH = src

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INC = -I ./inc/

LIB = libft/

LFT = -L ./$(LIB) -lft

MLX = minilibx_macos/

FRAMEWORK = -L ./$(MLX) -lmlx -framework OpenGL -framework AppKit -lm

RM = /bin/rm -f

opti:
	@make -j8 all

all:
	@make createlib
	@make $(OBJ_PATH)
	@make $(NAME)

createlib: libft/libft.h minilibx_macos/mlx.h
	@make all -C $(MLX)
	@make all -C $(LIB)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(FRAMEWORK) $(LFT) $(INC)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c inc/fractol.h libft/libft.h
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

clean:
	@make -C $(MLX) clean
	@make -C $(LIB) clean
	@$(RM) -r $(OBJ_PATH)
	@echo "clean complete"

fclean: clean
	@make -C $(LIB) fclean
	@$(RM) $(NAME)
	@echo "fclean complete"

re:
	@make fclean
	@make opti
