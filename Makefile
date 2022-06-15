.PHONY:		all clean fclean re test

SRC 	= vector_tests.cpp \
		  map_tests.cpp \
		  stack_tests.cpp \
		  set_tests.cpp \
		  tester.cpp
DIR_SRC = tester/

OBJ = $(SRC:%.cpp=$(DIR_OBJ)%.o)

FT_HEADER = vector.hpp \
	  	    stack.hpp \
		    map.hpp \
		    set.hpp
UT_HEADER = iterator.hpp \
		    utility.hpp \
		    algorithm.hpp \
	 	    type_traits.hpp \
		    tree.hpp
DIR_HEADER = ./headers/
DIR_UTILS  = $(DIR_HEADER)utils/
DIR_OBJ = obj/

HEADER  = $(addprefix $(DIR_HEADER),$(FT_HEADER)) 
HEADER += $(addprefix $(DIR_UTILS),$(UT_HEADER))  

NAME	= ft_containers_test

RM   = rm -rf
CXX  = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3

GREEN = "\033[32m"
RED   = "\033[31m"
END   = "\033[0m"

OK	  = $(GREEN) "( ͡° ͜ʖ ͡°)" $(END)
KO 	  = $(RED) "¯\_(ツ)_/¯" $(END)

all:	$(NAME)

$(NAME):	$(OBJ) $(INC)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@echo $(OK) "\t $(NAME) created successfully"

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp $(HEADER)
	@$(CXX) $(CXXFLAGS) -c $< -I$(DIR_HEADER)
	@echo $(OK) "\t $< compiled successfully"
	@mkdir -p $(DIR_OBJ)
	@mv $(@F) $(DIR_OBJ)

$(SRC):
	@echo $(KO) "\t $(SRC): file not found."

clean:
	@echo $(KO) "\t removed $(NAME)"
	@echo $(KO) "\t removed $(TEST)"
	@$(RM) $(NAME) $(TEST)

fclean: clean
	@echo $(KO) "\t removed $(DIR_OBJ)"
	@$(RM) $(DIR_OBJ)

re:	fclean all
