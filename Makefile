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

FT_CONTAINERS	= std_containers
STD_CONTAINERS	= ft_containers
TEST			= ft_containers_test

RM   = rm -rf
CXX  = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
DEBUG	 = -fsanitize=address -g3

GREEN = "\033[32m"
RED   = "\033[31m"
END   = "\033[0m"

OK	  = $(GREEN) "( ͡° ͜ʖ ͡°)" $(END)
KO 	  = $(RED) "¯\_(ツ)_/¯" $(END)

all:	$(FT_BIN)

$(FT_BIN)	$(HEADER) $(FT_OBJ)
	@$(CXX) $(CXXFLAGS) $(DEBUG) -o $(FT_BIN) 

$(STD_BIN)	$(HEADER) $(STD_OBJ)
	@$(CXX) $(CXXFLAGS) $(DEBUG) -o $(FT_BIN) 

test:	$(TEST)

$(TEST):	$(OBJ_TEST) $(HEADER_TEST) $(HEADER)
	@$(CXX) $(CXXFLAGS) $(DEBUG) -o $(TEST) $(OBJ_TEST)
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
	@echo $(KO) "\t removed $(NAME)"
	@echo $(KO) "\t removed $(TEST)"
	@$(RM) $(NAME) $(TEST)

fclean: clean
	@echo $(KO) "\t removed $(DIR_OBJ)"
	@$(RM) $(DIR_OBJ)

re:	fclean all
