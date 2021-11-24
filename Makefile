.PHONY:		all clean fclean re test

SRC = lib_containers_ft.cpp
OBJ = $(SRC:%.cpp=$(DIR_OBJ)%.o)
HEADER_CONT = vector.hpp \
	  		  stack.hpp \
			  map.hpp \
			  set.hpp
HEADER_UTILS = iterator_traits.hpp \
			   enable_if.hpp \
			   is_integral.hpp \
	 		   reverse_iterator.hpp \
	 		   equal.hpp \
	  		   lexicographical_compare.hpp \
			   pair.hpp
#			   _rb_tree.hpp

DIR_TEST = test/
DIR_OBJ = obj/
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

$(NAME):	$(OBJ) $(HEADER_CONT) $(HEADER_UTILS)
	$(AR) $(NAME) $(OBJ)

test:	$(TEST)

$(TEST):	$(NAME) $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(OBJ_TEST) $(NAME)

$(DIR_OBJ)%.o:	$(SRC) $(HEADER_CONT) $(HEADER_UTILS)
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
