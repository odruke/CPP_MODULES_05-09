###VARIABLES###

# name of the executable
NAME = easyfind

# conditional variable. [make DEBUG=1] to print expanded tests
NOEXCEPT ?= 0

# compilator and compilation flags
CC = c++
CFLAGS = -Wall -Werror -Wextra -g3 -std=c++98
EX = -DNOEXCEPT=$(NOEXCEPT)

# directories
SRC_DIR = ./src/
OBJ_DIR = $(SRC_DIR)target/
INC_DIR = ./include/

# files
FILES = main
INC_FILES = colors.hpp easyfind.hpp easyfind.tpp

SRC = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(FILES)))
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))
INC = $(addprefix $(INC_DIR), $(INC_FILES))




#####RULES####

all:$(NAME)

extra:
	@$(MAKE) NOEXCEPT=1

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@$(MAKE) compilation_success

# create .o file
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "Compiling: %s                                    \r" $<
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(EX) -c $< -o $@

$(OBJ_DIR):
	printf "Starting compilation..."
	@mkdir -p $(OBJ_DIR)

# delete just file OBJ_DIR and o file inside
clean:
	@rm -rf $(OBJ_DIR)

# executes clean and deletes the executable
fclean: clean
	@rm -f $(NAME)

re: fclean all

compilation_success:

	@echo "┌───────────────────────────────────────────────┐"
	@echo "│ ██████████ █████ █████    █████       █████   │"
	@echo "│░░███░░░░░█░░███ ░░███   ███░░░███   ███░░░███ │"
	@echo "│ ░███  █ ░  ░░███ ███   ███   ░░███ ███   ░░███│"
	@echo "│ ░██████     ░░█████   ░███    ░███░███    ░███│"
	@echo "│ ░███░░█      ███░███  ░███    ░███░███    ░███│"
	@echo "│ ░███ ░   █  ███ ░░███ ░░███   ███ ░░███   ███ │"
	@echo "│ ██████████ █████ █████ ░░░█████░   ░░░█████░  │"
	@echo "│░░░░░░░░░░ ░░░░░ ░░░░░    ░░░░░░      ░░░░░░   │"
	@echo "└───────────────────────────────────────────────┘"
	@echo "\n\n Try < make fclean && make extra > to compile a different version without exceptions\n\n"


.PHONY: clean fclean re all compilation_success extra
