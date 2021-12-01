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

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	$(AR) $(NAME) $(OBJ)

test:	$(TEST)

$(TEST):	$(NAME) $(OBJ_TEST) $(HEADER_TEST)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(TEST) $(OBJ_TEST) $(NAME)

$(DIR_OBJ)%.o: $(DIR_TEST)%.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -I $(DIR_HEADER)
	mkdir -p $(DIR_OBJ)
	mv $(@F) $(DIR_OBJ)

$(DIR_OBJ)%.o:	$(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) -c $(SRC)
	mkdir -p $(DIR_OBJ)
	mv $(@F) $(DIR_OBJ)

clean:
	$(RM) $(NAME) $(TEST)

fclean: clean
	$(RM) $(DIR_OBJ)
