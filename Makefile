NAME = pipex
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src/
INC_DIR = include/

SRC_NAMES =	main.c pipex.c pipex_utils.c
SRC_NAMES_B = main_bonus.c pipex.c pipex_utils.c

FLAGS = -Wall -Wextra -Werror
FLAGS_DBG = -Wall -Wextra -Werror -g -fsanitize=address
FLAGS_G = -Wall -Wextra -Werror -g

SRC = $(addprefix $(SRC_DIR), $(SRC_NAMES))
SRC_B = $(addprefix $(SRC_DIR), $(SRC_NAMES_B))
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

HEADERS = -I./include -I./libft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT) 
	cc $(FLAGS_G) $(OBJ) $(LIBFT) $(HEADERS) -o $(NAME)

%.o: %.c
	cc $(FLAGS_G) -c $^ -o $@ $(HEADERS)

bonus: .bonus

.bonus: $(OBJ_B) $(LIBFT) 
	cc $(FLAGS) $(OBJ_B) $(LIBFT) $(HEADERS) -o $(NAME)
	touch .bonus

clean:
	rm -f ${OBJ}
	rm -f ${OBJ_B}
	rm -f .bonus
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f ${NAME}
	rm -f ${NAME_B}

re: fclean all

.PHONY: all clean fclean re
