##
## EPITECH PROJECT, 2020
## CCP_plazza_2019
## File description:
## Makefile
##

CC	=	g++

SRC	=	main.cpp			\
		main_reception.cpp	\
		load_args.cpp		\
		parse_pizza.cpp		\
		load_config.cpp		\

OBJ	=	$(addprefix src/, $(SRC:.cpp=.o))

CXXFLAGS	=	$(COMMON_CXXFLAGS) -Iinclude

NAME	=	../plazza

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: all

.PHONY: all clean fclean re tests_run
