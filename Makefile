# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 22:15:45 by kibotrel          #+#    #+#              #
#    Updated: 2019/06/19 16:34:28 by reda-con         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable's name (Can be changed)

NAME		= wolf3d

# All the directories needed to know where files should be (Can be changed)

ABSDIR		= $(shell pwd)
OBJDIR		= objs/
OBJSUBDIRS	= core usage parsing utils raycasting setup events maths hud
SRCDIR		= srcs/
LFTDIR		= libft/
SDLDIR		= $(ABSDIR)/SDL2-2.0.9/
INCDIR		= ./incs/ ./libft/incs/ ./SDL2-2.0.9/include/

# Source files (Can be changed)

INCS		= incs/env.h							incs/wolf3d.h

SRC			= core/main.c					core/hooks.c						\
			 																	\
			raycasting/raycast.c			raycasting/collisions.c				\
																				\
			events/update_cam.c			events/movements.c						\
			events/resize.c														\
																				\
			setup/setup.c					setup/raycasting.c					\
			setup/camera.c				setup/graphic.c							\
																				\
			parsing/map.c														\
																				\
			  hud/hud.c						 hud/objects.c						\
			  hud/minimap.c														\
																				\
			  utils/clean.c					utils/parsing.c						\
			  utils/draw_line.c				utils/image.c						\
																				\
			maths/maths.c														\
																				\
			usage/usage.c

LFT			= ./libft/libft.a

# Some tricks in order to get the makefile doing his job the way I want (Can't be changed)

CSRC		= $(addprefix $(SRCDIR), $(SRC))
COBJ		= $(addprefix $(OBJDIR), $(OBJ))
SUBDIRS		= $(foreach dir, $(OBJSUBDIRS), $(OBJDIR)$(dir))
INCLUDES	= $(foreach include, $(INCDIR), -I$(include))

# How files should be compiled with set flags (Can be changed)

CC			= gcc
OBJ			= $(SRC:.c=.o)
LIBS		= -L$(LFTDIR) -lft $(shell $(ABSDIR)/SDL2/bin/sdl2-config --libs)
CFLAGS		= $(INCLUDES) -Wall -Wextra -Werror -O3 -g

# Color codes

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# Check if object directory exists, build libs and then the Project

all: $(SUBDIRS) SDL2 $(NAME)

SDL2:
	@mkdir -p SDL2/
	@mkdir -p SDL2/build
	@cd SDL2/build; \
		$(SDLDIR)/configure --prefix $(ABSDIR)/SDL2; \
		make -j6; \
		make install \

$(NAME): $(LFT) $(OBJDIR) $(COBJ)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@$(CC) $(CFLAGS) $(LIBS) $(FRAMEWORKS) -o $(NAME) $(COBJ)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(SUBDIRS):
	@mkdir -p $(SUBDIRS)

# Redefinition of implicit compilation rule to prompt some colors and file names during the said compilation

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation rule for function library "libft"

$(LFT):
	@make -sC $(LFTDIR) -j

$(SDL):

# Deleting all .o files and then the directory where they were located

clean:
	@make -sC $(LFTDIR) clean
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@rm -rf $(OBJDIR)

# Deleting the executable after cleaning up all .o files

fclean: clean
	@make -sC $(LFTDIR) fclean
	@rm -rf SDL2
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
