include extras/ascii_art.sh
include extras/colors.sh

#*-------------links for downloads-------------
MAPS_URL = https://cdn.intra.42.fr/document/document/47662/maps.zip
MLX_OSX = https://cdn.intra.42.fr/document/document/21666/minilibx_macos_sierra_20161017.tgz
# MLX_OSX = https://cdn.intra.42.fr/document/document/21664/minilibx_mms_20191025_beta.tgz;
MLX_LINUX = https://cdn.intra.42.fr/document/document/47665/minilibx-linux.tgz
#* flags
MLX_LIBS_OSX =  -L$(MLX_F) -lmlx -framework OpenGL -framework AppKit
MLX_LIBS_LINUX = -L$(MLX_F) -lmlx_Linux -lXext -lX11 -lm
LIBFT_INCLUDES = -I$(LIBFT_F) -I$(LIBFT_F)/src/ft_printf/ -I$(LIBFT_F)/src/get_next_line/
LIBFLAGS = -L$(LIBFT_F) -lft $(LIBFT_INCLUDES)
CC_FLAGS = -Wall -Wextra -Werror -O3 -g $(DEPFLAGS)
DEPFLAGS = -MP -MMD
CC = gcc
# maps
MAPS_F = maps
MAPS_ARCH = maps.zip
MLX_ARCH = minilibx.tgz
# libs
LIBFT_F = ../../common/libft-dyarkovs
LIBFT_A = $(LIBFT_F)/libft.a

#*-------------OS dependent flags for libs-------------
UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
	#*MacOS
  CC_FLAGS += -DOSX
  MLX_F = mlx-osx
  MLX_URL = $(MLX_OSX)
  MLX_LIBS = $(MLX_LIBS_OSX)
else
	#*Linux
  CC_FLAGS += -DLINUX
  MLX_F = ../../common/minilibx-linux
  MLX_URL = $(MLX_LINUX)
  MLX_LIBS = $(MLX_LIBS_LINUX)
endif

CC_FLAGS += -I$(MLX_F) $(LIBFT_INCLUDES)


#*-------------COMPILATION-------------
NAME = fdf
SRC =	main.c \
		map.c utils.c set_val.c px_position.c center.c error.c clean.c isometric.c \
		window.c draw_line_algorithm.c menu.c \
		hooks.c events.c event_act.c safe_check.c sub_event.c mouse_events.c \
		print_map_helper.c

OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))
VPATH = $(SRC_F) $(SRC_F)utils/ $(SRC_F)move/ $(SRC_F)draw/
SRC_F = src/
OBJ_F = obj/



.SILENT:
all: $(NAME)

$(NAME): $(MLX_F) $(LIBFT_A) $(OBJ)
	make mlx;
	$(CC) -o $@ $(OBJ) $(MLX_LIBS) $(LIBFLAGS)
	@echo "$(GREEN)$$ASCII_ART\n\n———————————————✣ FDF COMPILED ✣————————————\n$(RE)"

$(OBJ_F)%.o: %.c fdf.h keycode.h Makefile
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -o $@ -c $<
	@printf "$(GREEN). $(RE)"

clean:
	rm -rf $(OBJ_F)
	@echo "$(YELLOW)\n CLEAN FDF		🧹✨$(RE)"

fclean:	clean
	rm -f $(NAME)
	@echo "$(YELLOW)FCLEAN FDF		🧹✨\n$(RE)"

re:	fclean all





#*-------------extra functional-------------
install: $(LIBFT_A) $(MAPS_F) $(MLX_F)

run: $(NAME)
	./$(NAME) extras/pyramide.fdf

jul: $(NAME) $(MAPS_F)
	./$(NAME) maps/julia.fdf


#make mlx
mlx:
	@if [ ! -d "$(MLX_F)" ] || [ ! -f "$(MLX_F)/libmlx.a" ]; then \
		echo "$(GREEN)\nCompiling $(MLX_F) ...$(RE)"; \
		$(MAKE) -C $(MLX_F) > /dev/null 2>&1; \
		echo "$(GREEN)\n$(MLX_F) compiled successfully$(RE)"; \
	fi

#*-------------install (shared libft, mlx and maps)-------------
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_F)

$(MLX_F):
	if [ ! -d $(MLX_F) ]; then \
		mkdir -p $(dir $(MLX_F)); \
		echo "$(YELLOW)\n\nDownloading $(MLX_F) ...$(RE)"; \
		curl -sS -o $(MLX_ARCH) $(MLX_URL); \
		tar -xvf $(MLX_ARCH) -C ./ > /dev/null; \
		rm $(MLX_ARCH); \
		mv minilibx* $(MLX_F); \
	fi

$(MAPS_F):
	if	[ ! -d "$(MAPS_F)" ]; then \
			echo "$(YELLOW)\nDownloading $(MAPS_F) ...$(RE)"; \
			if curl -fsSL -o $(MAPS_ARCH) $(MAPS_URL) && unzip -tq $(MAPS_ARCH); then \
				unzip -qq $(MAPS_ARCH); \
				rm -f $(MAPS_ARCH); \
				rm -rf __MACOSX; \
				mv test_maps $@; \
			else \
				echo "$(YELLOW)Warning: unable to download maps; creating a demo map.$(RE)"; \
				rm -f $(MAPS_ARCH); \
				mkdir -p $@; \
				printf "0 0 0 0 0\n0 1 2 1 0\n0 2 4 2 0\n0 1 2 1 0\n0 0 0 0 0\n" > $@/demo.fdf; \
				cp $@/demo.fdf $@/julia.fdf; \
			fi \
		fi

.PHONY:	all clean fclean re run uninstall instal mlx






#  -g flag in cc flags is helpful when you need to debug program
# as it allows to trace execution of the program back to the original source code.

#preprocessor definition, define macros name, used in .h files depending on OS
#   CC_FLAGS += -D OSX

# -s silent, -S show-error, -o output download into MLX_ARCH, from MLX_URL
# curl -sS -o $(MLX_ARCH) $(MLX_URL)

# $(CC) -o $@ $(OBJ) $(MLX_LIBS) $(LIBFLAGS) - the libs included in the proj, must always be written after the final object that needs these libs,
#  so the compiler can go and search further in the line for the path where these needed libs are located and find them

#-I is used to specify where to find the .h files for the library. You need this to include the library's function declarations and definitions in your code.
#-L is used to specify where to find the compiled library (.a, .dylib, .lib) files. You need this so that the linker knows where to find the actual code for the library functions.
#-l is used to specify which library to link against, NAME (without lib (libft.a => -lft)). You need this so that the linker knows which library file to include in the final executable.
