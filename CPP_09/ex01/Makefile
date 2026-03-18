###VARIABLES###

# name of the executable
NAME = RPN

# conditional variable. [make re DEBUG] to verbose error messages.

DEBUG ?= 0
# colors for prints
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
# compilator and compilation flags
CC = c++
CFLAGS = -Wall -Werror -Wextra -g -std=c++98

# directories
SRC_DIR = ./src/
OBJ_DIR = $(SRC_DIR)target/
INC_DIR = ./include/

# files
FILES = main RPN
INC_FILES = colors RPN

SRC = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(FILES)))
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))
INC = $(addprefix $(INC_DIR)%.hpp, $(INC_FILES))



#####RULES####

all:$(NAME)

debug:
	@$(MAKE) re DEBUG=1


$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@$(MAKE) compilation_success

# create .o file
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "Compiling: %s                                    \r" $<
	@$(CC) $(CFLAGS) -I$(INC_DIR) -DDEBUG=$(DEBUG) -c $< -o $@

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

ifeq ($(DEBUG),1)
compilation_success:

	@echo "┌─────────────────────────────┐"
	@echo "│███████╗██╗  ██╗ ██████╗  ██╗│"
	@echo "│██╔════╝╚██╗██╔╝██╔═████╗███║│"
	@echo "│█████╗   ╚███╔╝ ██║██╔██║╚██║│"
	@echo "│██╔══╝   ██╔██╗ ████╔╝██║ ██║│"
	@echo "│███████╗██╔╝ ██╗╚██████╔╝ ██║│"
	@echo "│╚══════╝╚═╝  ╚═╝ ╚═════╝  ╚═╝│"
	@echo "└─────────────────────────────┘"
	@echo "\nDebug mode: $(GREEN)enabled$(RESET)\n"
else
compilation_success:

	@echo "┌─────────────────────────────┐"
	@echo "│███████╗██╗  ██╗ ██████╗  ██╗│"
	@echo "│██╔════╝╚██╗██╔╝██╔═████╗███║│"
	@echo "│█████╗   ╚███╔╝ ██║██╔██║╚██║│"
	@echo "│██╔══╝   ██╔██╗ ████╔╝██║ ██║│"
	@echo "│███████╗██╔╝ ██╗╚██████╔╝ ██║│"
	@echo "│╚══════╝╚═╝  ╚═╝ ╚═════╝  ╚═╝│"
	@echo "└─────────────────────────────┘"
	@echo "\nDebug mode: $(RED)disabled$(RESET)\n"
endif


.PHONY: clean fclean re all compilation_success debug
