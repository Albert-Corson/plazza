##
## EPITECH PROJECT, 2020
## CCP_plazza_2019
## File description:
## Makefile
##

DEBUG	=	-g -DDEBUG

override COMMON_CXXFLAGS	+=	-std=c++17				\
								-Wall					\
								-Wextra					\
								-Wshadow				\
								-Wsign-compare			\
								-Wno-unused-parameter	\
								-Wno-unused-variable	\

MAKE	=	@make --no-print-directory --jobs=4

RECEPTION	=	$(MAKE) -C ./reception

KITCHEN		=	$(MAKE) -C ./kitchen

all:	reception kitchen

reception:
	$(RECEPTION) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

kitchen:
	$(KITCHEN) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

clean:
	$(RECEPTION) clean
	$(KITCHEN) clean

fclean: clean
	$(RECEPTION) fclean
	$(KITCHEN) fclean

re: fclean all

tests_run: all
	$(RECEPTION) tests_run
	$(KITCHEN) tests_run

debug:
	$(MAKE) all COMMON_CXXFLAGS="$(DEBUG)"

.PHONY: all clean fclean re tests_run debug reception kitchen
