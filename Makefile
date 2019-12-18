# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 15:50:08 by hbrulin           #+#    #+#              #
#    Updated: 2019/12/18 11:27:55 by hbrulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
OS	= $(shell uname)

SRCS = main.c parser.c env.c image.c color.c floor_ceiling.c events.c move_W.c

HEADER = cub3d.h 
KEYCODE = keycode.h

CFLAGS = -Wall -Werror -Wextra -MMD -I$(HEADER) -I$(KEYCODE) -g
BUILD_DIR = obj

OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(BUILD_DIR)/,$(OBJS))
DPD = $(OBJ:.o=.d)

# mlx library
ifeq ($(OS), Linux)
	MLXDIR	= minilibx_mms
	MLX_LNK	= -l mlx -lXext -lX11
else
	MLXDIR	= miniLibx_opengl
	MLX_LNK	= -l mlx -framework OpenGL -framework AppKit

endif

MLX_LNK	+= -L $(MLXDIR) -l mlx
MLX_INC	= -I $(MLXDIR)
MLX_LIB	= $(addprefix $(MLX)/,mlx.a)

# ft library
FTDIR	= libft
FT_LIB	= $(addprefix $(FTDIR)/,libft.a)
FT_INC	= -I $(FTDIR)
FT_LNK	= -L $(FTDIR) -l ft

opti :
	@make -j all

all : make_ft make_mlx $(NAME)

make_ft:
	@make -C $(FTDIR)

make_mlx: 
	@make -C $(MLXDIR)

$(NAME): $(OBJ) make_ft make_mlx
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME) -fsanitize=address -g
	@echo "$(NAME) created"

$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -o $@ -c $<

clean:
	@/bin/rm -rf $(BUILD_DIR)
	@echo "Object and DPD files deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Lib deleted"

re : 
	@make fclean
	@make opti

.PHONY: all, clean, fclean, re

-include $(DPD)
