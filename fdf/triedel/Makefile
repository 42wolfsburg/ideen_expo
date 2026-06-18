# compilation
NAME = fdf
SRC = color.c color_chns.c cvector.c display.c display_draw.c display_project.c display_utils.c events.c \
	events_mouse.c fdf.c image.c input.c load_fdf.c load_model.c load_stl.c matrix.c model.c point.c \
	point_ops.c utils.c vector.c main.c
OBJ = $(SRC:.c=.o)
OBJT = $(filter-out $(OBJ),main.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
CFLAGS += -I$(LIBMLX_DIR) -I$(LIBFT_DIR)
# CFLAGS += -g -fsanitize=address -fno-omit-frame-pointer
LDLIBS = -L$(LIBFT_DIR) -L$(LIBMLX_DIR) -lft -lm

# extra stuff
LIBMLX_URL_OSX = https://cdn.intra.42.fr/document/document/22378/minilibx_mms_20200219_beta.tgz
LIBMLX_URL_LINUX = https://cdn.intra.42.fr/document/document/47665/minilibx-linux.tgz
LIBMLX_SHARED_LINUX_DIR = ../../common/minilibx-linux
ARC = libmlx.tgz

LIBFT_DIR = ../../common/libft
LIBFT = $(LIBFT_DIR)/libft.a

MAPS_DIR = maps
MAPS_URL = https://cdn.intra.42.fr/document/document/47662/maps.zip

FDF_LINUX = fdf_linux
FDF_LINUX_URL = https://cdn.intra.42.fr/document/document/47663/fdf_linux

# OS dependent flags
UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
  # osx
  CFLAGS += -D OSX
  LIBMLX_DIR = libmlx-osx
  LIBMLX = $(LIBMLX_DIR)/libmlx.dylib
  LIBMLX_URL = $(LIBMLX_URL_OSX)
  LDLIBS += -lmlx -framework OpenGL -framework AppKit -g
else
  # Linux
  CFLAGS += -D LINUX
  LIBMLX_DIR = $(LIBMLX_SHARED_LINUX_DIR)
  LIBMLX = $(LIBMLX_DIR)/libmlx.a
  LIBMLX_URL = $(LIBMLX_URL_LINUX)
  LDLIBS += -lmlx_Linux -lXext -lX11
endif

all: $(NAME)
run: $(NAME) maps
	./$(NAME) m maps/*

ref: $(FDF_LINUX) maps
	./$(FDF_LINUX) m maps/*

# modified built-in rule to allow for different executable name
$(NAME): $(LIBMLX) $(OBJ) $(LIBFT)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS)

re: fclean
	$(MAKE) all

# "recursive" rebuilding, also rebuilds libft and libmlx
rere: fclean
	$(MAKE) -C $(LIBFT_DIR) fclean
	# $(MAKE) -C $(LIBMLX_DIR) clean
	$(MAKE) all

clean:
	# $(MAKE) -C $(LIBFT_DIR) $@
	# $(MAKE) -C $(LIBMLX_DIR) $@
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

# set up mlx
$(LIBFT_DIR): $(LIBFT)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(LIBMLX_DIR): $(LIBMLX)
$(LIBMLX):
	@if [ ! -d "$(LIBMLX_DIR)" ]; then \
		mkdir -p "$(dir $(LIBMLX_DIR))"; \
		echo Downloading "$(LIBMLX_URL)"; \
		curl -fsSL -o $(ARC) $(LIBMLX_URL); \
		tar xf $(ARC); \
		rm $(ARC); \
		mv minilibx* $(LIBMLX_DIR); \
	fi
	$(MAKE) -C $(LIBMLX_DIR)
	-@cp $(LIBMLX_DIR)/libmlx.dylib ./

maps:
	rm -f maps.zip
	if curl -fsSL -o maps.zip "$(MAPS_URL)" && unzip -tq maps.zip; then \
		unzip -q maps.zip; \
		rm maps.zip; \
		rm -rf __MACOSX/test_maps; \
		rm -rf __MACOSX/; \
		mv test_maps "$@"; \
	else \
		echo "Warning: unable to download 42 maps archive; creating a demo map."; \
		rm -f maps.zip; \
		mkdir -p "$@"; \
		printf "0 0 0 0 0\n0 1 2 1 0\n0 2 4 2 0\n0 1 2 1 0\n0 0 0 0 0\n" > "$@/demo.fdf"; \
	fi

$(FDF_LINUX):
	curl -fsSL -o "$@" "$(FDF_LINUX_URL)"
	chmod +x "$@"

leaks:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./fdf m maps/42.fdf _empty.fdf

# profiling, gcc only
profile:
	rm -f gmon.out
	make CFLAGS="$(CFLAGS) -pg -g -O3" fclean $(NAME)
	./$(NAME) m stl/colosseum.stl
	gprof ./$(NAME) | less

# norm check
norm:
	watch -n 1 "norminette $(SRC) *.h"

test: $(OBJT)
	c++ -std=c++14 -fpermissive -g $(CFLAGS) $(shell pkg-config --cflags gtest) test.cpp $(OBJT) $(LDLIBS) $(shell pkg-config --libs gtest) && clear && ./a.out

.PHONY: all run ref re rere clean fclean leaks profile norm test
