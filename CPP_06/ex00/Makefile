###VARIABLES###

# name of the executable
NAME = converter

# compilator and compilation flags
CC = c++
CFLAGS = -Wall -Werror -Wextra -g3 -std=c++98

# directories
SRC_DIR = ./src/
OBJ_DIR = $(SRC_DIR)target/
INC_DIR = ./include/

# files
FILES = main printTypes ScalarConverter
INC_FILES = colors ScalarConverter

SRC = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(FILES)))
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))
INC = $(addprefix $(INC_DIR)%.hpp, $(INC_FILES))



#####RULES####

all:$(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@$(MAKE) compilation_success

# create .o file
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "Compiling: %s                                    \r" $<
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

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

.PHONY: clean fclean re all compilation_success
