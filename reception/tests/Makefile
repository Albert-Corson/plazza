##
## EPITECH PROJECT, 2020
## CCP_plazza_2019
## File description:
## Makefile
##

CC	=	g++

SRC	=	PizzaMenu/PizzaMenu.cpp								\
		tests/PizzaMenuTests.cpp							\
		locateKitchenBin.cpp								\
		tests/locateKitchenBinTests.cpp						\
		tests/ReceptionTests.cpp							\
		Reception.cpp										\
		KitchenManager/KitchenManager.cpp					\
		KitchenSpawner/AKitchenLink.cpp						\
		KitchenSpawner/process/KitchenProcessSpawner.cpp	\
		KitchenSpawner/process/KitchenProcessLink.cpp		\
		tests/KitchenManagerTests.cpp				\

OBJ	=	$(addprefix ../, $(SRC:.cpp=.o))

CXXFLAGS	=	$(COMMON_CXXFLAGS)	\
				-std=c++17			\
				-I./				\
				-I../				\
				-I../../			\
				-lcriterion			\
				--coverage			\

NAME	=	unit_tests

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)
	./unit_tests

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	rm -f ../$(NAME)

re: fclean all

tests_run:
	make -C tests

.PHONY: all clean fclean re tests_run
