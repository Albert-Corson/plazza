##
## EPITECH PROJECT, 2020
## CCP_plazza_2019
## File description:
## Makefile
##

CC	=	g++

SRC	=	main.cpp					\
		Kitchen.cpp					\
		Cook/Cook.cpp				\
		OrderQueue/OrderQueue.cpp	\
		Fridge/Fridge.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	$(COMMON_CXXFLAGS)	\
				-I./				\
				-I../

NAME	=	../bin/kitchen

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -pthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: all

.PHONY: all clean fclean re tests_run
