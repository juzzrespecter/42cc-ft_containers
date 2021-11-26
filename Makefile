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

DIR_TEST = test/
DIR_OBJ = obj/
DIR_HEADER = headers/
DIR_UTILS = $(DIR_HEADER)utils/
SRC_TEST = test.cpp \
		   vector_test.cpp \
		   stack_test.cpp \
		   map_test.cpp \
		   set_test.cpp 
#		   subject_main.cpp
OBJ_TEST = $(patsubst %.cpp, $(DIR_OBJ)%.o, $(SRC_TEST))
HEADER_TEST = $(DIR_TEST)test.hpp

NAME = stlft.a
TEST = containers_test

RM   = rm -rf
AR	 = ar rcs
CXX  = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g3

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	$(AR) $(NAME) $(OBJ)

test:	$(TEST)

$(TEST):	$(NAME) $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(OBJ_TEST) $(NAME)

$(DIR_OBJ)%.o:	$(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) -c $(SRC)
	mkdir -p $(DIR_OBJ)
	mv $(@F) $(DIR_OBJ)

$(DIR_OBJ)%.o:	$(DIR_TEST)%.cpp $(HEADER_TEST)
	$(CXX) $(CXXFLAGS) -c $< -I.
	mkdir -p $(DIR_OBJ)
	mv $(@F) $(DIR_OBJ)

clean:
	$(RM) $(NAME) $(TEST)

fclean: clean
	$(RM) $(DIR_OBJ)
