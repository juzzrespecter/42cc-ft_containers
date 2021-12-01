#include "stack.hpp"
#include <stack>
#include <list>
#include "tester.hpp"

bool	constructor_test(void){
	bool	test_result;
	/*  -- empty containers -- */
	{
	}
}

bool	operatorequal_test(void){
}

bool	top_test(void){
}

bool	empty_test(void){
}

bool	size_test(void){
}

bool	push_test(void){
}

bool	pop_test(void){
}

bool	comp_operators_test(void){
}

static std::string test_name_table[ N_TESTS ] = {
	"CONSTRUCTOR TEST",	"OPERATOR= TEST",
	"TOP TEST",		"EMPTY TEST",
	"EMPTY TEST",		"SIZE TEST",
	"PUSH TEST",		"POP TEST",
	"COMPARE OPERATORS TEST"
};

static bool	(*func_table[N_TESTS])(void) = {
	constructor_test,	operatorequal_test,
	top_test,		empty_test,
	empty_test,		size_test,
	push_test,		pop_test,
	comp_operators_test
};

int main(void){
	

}
