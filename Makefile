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

KITCHEN_INTERFACE	=	$(MAKE) -C ./kitchen_interface

all:	reception kitchen kitchen_interface

reception:
	$(RECEPTION) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

kitchen:
	$(KITCHEN) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

kitchen_interface:
	$(KITCHEN_INTERFACE) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

clean:
	$(RECEPTION) clean
	$(KITCHEN) clean
	$(KITCHEN_INTERFACE) clean

fclean: clean
	$(RECEPTION) fclean
	$(KITCHEN) fclean
	$(KITCHEN_INTERFACE) fclean
	$(RM) ./fifo*

re: fclean all

tests_run: all
	$(RECEPTION) tests_run
	$(KITCHEN) tests_run
	$(KITCHEN_INTERFACE) tests_run

debug:
	$(MAKE) all COMMON_CXXFLAGS="$(DEBUG)"

clear_log:
	rm -rf plazza.log

.PHONY: all reception kitchen kitchen_interface clean fclean re tests_run debug clear_log
