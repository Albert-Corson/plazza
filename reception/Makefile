##
## EPITECH PROJECT, 2020
## CCP_plazza_2019
## File description:
## Makefile
##

CC	=	g++

SRC	=	main.cpp											\
		KitchenSpawner/process/KitchenProcessSpawner.cpp	\
		KitchenSpawner/process/KitchenProcessLink.cpp		\
		KitchenSpawner/network/KitchenNetworkSpawner.cpp	\
		KitchenSpawner/network/KitchenNetworkLink.cpp		\
		KitchenSpawner/AKitchenLink.cpp						\
		KitchenManager/KitchenManager.cpp					\
		Reception.cpp										\
		PizzaMenu/PizzaMenu.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	$(COMMON_CXXFLAGS)	\
				-I./				\
				-I../				\

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
