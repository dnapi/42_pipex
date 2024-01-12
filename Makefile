NAME = pipex
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src/
INC_DIR = include/

SRC_NAMES =	pipex.c pipex_utils.c

FLAGS = -Wall -Wextra -Werror

SRC = $(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJ = $(SRC:.c=.o)

HEADERS = -I./include -I./libft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT) 
	cc $(FLAGS) $(OBJ) $(LIBFT) $(HEADERS) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $^ -o $@ $(HEADERS)
	

clean:
	rm -f ${OBJ}
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
