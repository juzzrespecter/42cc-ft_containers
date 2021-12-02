.PHONY:		all clean fclean re test

SRC = lib_containers_ft.cpp
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

HEADER  = $(addprefix $(DIR_HEADER),$(FT_HEADER)) 
HEADER += $(addprefix $(DIR_UTILS),$(UT_HEADER))  

DIR_TEST = tester/
DIR_OBJ = obj/
SRC_TEST = tester.cpp \
		   vector_tests.cpp \
		   stack_tests.cpp \
		   map_tests.cpp \
		   set_tests.cpp
OBJ_TEST = $(patsubst %.cpp, $(DIR_OBJ)%.o, $(SRC_TEST))
HEADER_TEST = $(DIR_TEST)tester.hpp

NAME = stlft.a
TEST = ft_containers_test

RM   = rm -rf
AR	 = ar rcs
CXX  = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
DEBUG	 = -fsanitize=address -g3

GREEN = "\033[32m"
RED   = "\033[31m"
END   = "\033[0m"

OK	  = $(GREEN) "( ͡° ͜ʖ ͡°)" $(END)
KO 	  = $(RED) ¯\_(ツ)_/¯ $(END)

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	@$(AR) $(NAME) $(OBJ)
	@echo $(GREEN) "$(NAME) created successfully" $(END)

test:	$(TEST)

$(TEST):	$(NAME) $(OBJ_TEST) $(HEADER_TEST)
	@$(CXX) $(CXXFLAGS) $(DEBUG) -o $(TEST) $(OBJ_TEST) $(NAME)
	@echo $(GREEN) "$(TEST) created successfully" $(END)

$(DIR_OBJ)%.o: $(DIR_TEST)%.cpp $(HEADER_TEST)
	@$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -I $(DIR_HEADER)
	@echo $(OK) "\t $< compiled successfully"
	@mkdir -p $(DIR_OBJ)
	@mv $(@F) $(DIR_OBJ)

$(DIR_OBJ)%.o:	$(SRC) $(HEADER)
	@$(CXX) $(CXXFLAGS) -c $(SRC)
	@echo $(OK) "\t $< compiled successfully"
	@mkdir -p $(DIR_OBJ)
	@mv $(@F) $(DIR_OBJ)

$(DIR_TEST)%.cpp:
	@echo $(KO) "\t $<: file not found."
$(SRC):
	@echo $(KO) "\t $(SRC): file not found."

clean:
	@echo " removed $(NAME)"
	@echo " removed $(TEST)"
	@$(RM) $(NAME) $(TEST)

fclean: clean
	@echo " removed $(DIR_OBJ)"
	@$(RM) $(DIR_OBJ)

re:	fclean all
