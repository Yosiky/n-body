CC = clang
CCX = clang++

# Choose compiler
UCC = $(CCX)

# CFLAGS = -Wall -Werror -Wextra

# Choose file type
TYPE		= cpp

SRC_DIR		= src
SRC			= main					\
			  simulation			\
			  planet

SRC_TYPE	= $(addsuffix .$(TYPE),$(SRC))

OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC_TYPE:.$(TYPE)=.o))

NAME		= n-body.elf

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(TYPE) Makefile
	$(UCC) $(CFLAGS) -o $@ -c $< -Iinclude

$(NAME): $(OBJ)
	$(UCC) -o $@ $(OBJ)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
