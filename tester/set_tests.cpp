#include "tester.hpp"
#include "set.hpp"
#include <set>

static std::string test_name_table[N_SET_TEST] = {
	iterator_test,		reverse_iterator_test,
	constructor_test,	operatorequal_test,
	empty_test,		size_test,
	max_size_test,		clear_test,
	insert_test,		erase_test,
	swap_test,		count_test,
	find_test,		equal_range_test,
	lower_bound_test,	upper_bound_test,
	observers_test,		comp_operators_test
};

static bool	(*func_table[N_TESTS])(void) = {
	"ITERATOR TEST",	"REVERSE_ITERATOR TEST",
	"CONSTRUCTOR TEST",	"OPERATOR= TEST",
	"EMPTY TEST",		"SIZE TEST",
	"MAX_SIZE TEST",	"CLEAR TEST",
	"INSERT TEST",		"ERASE TEST",
	"SWAP TEST",		"COUNT TEST",
	"FIND TEST",		"EQUAL_RANGE TEST",
	"LOWER_BOUND TEST",	"UPPER_BOUND TEST",
	"OBSERVERS TEST",	"COMPARE OPERATORS TEST"
};

// stress test
//
// rbtree test
void	rbtree(void){
	ft::set<char>	s;
	//insert loop
	//delete loop
}

void set_tests(void){
	static std::string buffer;
	std::cout << "[ set test: compare behaviour with std::set ]\n\n";
	for (int i = 0; i < N_SET_TEST; i++)
		std::cout << std::setw(30) << test_name_table[i] << ": " << ((func_table[i])() ? OK : KO) << "\n";
	std::cout << "\n< demo rb ? (y/n) >";
	std::getline(std::cin,buffer);
	if(buffer[0] == 'y' && !buffer[1]) rbtest();
	std::cout << "\n< performance test... : " << ((stress_test()) ? OK : KO) << " >\n";
}
