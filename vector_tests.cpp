#include "vector.hpp"
//#include "tester.hpp"
#include <vector>
#include <string>
#include <iostream>

#define N_TESTS 21

typedef ft::vector<int>				ft_vector;
typedef ft_vector::iterator			ft_iterator;
typedef ft_vector::const_iterator	ft_const_iterator;
typedef ft_vector::reverse_iterator	ft_reverse_iterator;

typedef std::vector<int>					std_vector;
typedef std_vector::iterator			std_iterator;
typedef std_vector::const_iterator		std_const_iterator;
typedef std_vector::reverse_iterator	std_reverse_iterator;

//long	get_time() {} 

bool	iterator_test(void) {
	ft_vector	ftv;
	std_vector	stdv;
	bool	test_result;
	{
		ft_iterator			it = ftv.begin();
		ft_iterator			it_2(it);

		ft_const_iterator	c_it(it);
		ft_const_iterator	c_in_2(c_it);
		ft_const_iterator	c_it_3 = ftv.begin();

//		ft_iterator			it_3(c_it);
	}
	{
		for (int i = 0; i < 1e6; i++) {
			int val = rand();
			ftv[i] = val;
			stdv[i] = val;
		}
		ft_iterator	it = ftv.begin() + 1e2;
		std_iterator it_s = stdv.begin() + 1e2;
		test_result = (*it == *it_s && *ftv.begin() == *stdv.begin() && *(--ftv.end()) == *(--stdv.end()));
	}
	{
		ft_const_iterator	it = ftv.begin();
		std_const_iterator	it_s = stdv.begin();
		test_result = (test_result && *it == *it_s && *ftv.begin() == *stdv.begin() && *(--ftv.end()) == *(--stdv.end()));
	}
	{
		test_result = ( (rft == rft_e) == (rstd == rstd_e) &&
						(rft != rft_e) == (rstd != rstd_e) &&
						(rft >  rft_e) == (rstd >  rstd_e) &&
						(rft >= rft_e) == (rstd >= rstd_e) &&
						(rft <  rft_e) == (rstd <  rstd_e) &&
						(rft <= rft_e) == (rstd <= rstd_e));
	}
	return test_result;
}

bool	reverse_iterator_test(void) {
	bool	test_result;
	{
		ft_vector	ftv(1e6);
		std_vector	stdv(1e6);
		for(int i = 0; i < 1e6; i++) {
			int	val = rand();
			ftv[i] = val;
			stdv[i] = val;
		}
		ft_reverse_iterator		rft = ftv.rbegin();
		ft_reverse_iterator		rft_e = ftv.rend();
		std_reverse_iterator	rstd = stdv.rbegin();
		std_reverse_iterator	rstd_e = stdv.rend();

		test_result = ( (rft == rft_e) == (rstd == rstd_e) &&
						(rft != rft_e) == (rstd != rstd_e) &&
						(rft >  rft_e) == (rstd >  rstd_e) &&
						(rft >= rft_e) == (rstd >= rstd_e) &&
						(rft <  rft_e) == (rstd <  rstd_e) &&
						(rft <= rft_e) == (rstd <= rstd_e));
	}
	return test_result;
}

bool	max_size_capacity( void ) {
	
	return (ft::vector<int>().max_size() == std::vector<int>().max_size() &&
			ft::vector<char>().max_size() == std::vector<char>().max_size() &&
			ft::vector<double>().max_size() == std::vector<double>().max_size() &&
			ft::vector<std::string>().max_size() == std::vector<std::string>().max_size() &&
			ft::vector<int>().max_size() == std::vector<int>().max_size()); // new class here
}

bool	insert_modifier_part_one( void ) {
	    bool	test_result;
		{
			ft_vector	ftv(100, 25);
			std_vector	stdv(100, 25);
		
			ft_iterator		ft_it = ftv.insert(ftv.begin(), 1918);
			std_iterator	std_it = stdv.insert(stdv.begin(), 1918);
		
			ft_iterator		ft_it_2 = ftv.insert(--(ftv.end()), 1918);
			std_iterator	std_it_2 = stdv.insert(--(stdv.end()), 1918);
			test_result = (*ft_it == *std_it) && (*ft_it_2 == *std_it_2) && ft::equal(ftv.begin(),ftv.end(),stdv.begin());
		}
		{
			ft_vector	ftv;
			std_vector	stdv;
		
			ftv.insert(ftv.begin(), 1918);
			stdv.insert(stdv.begin(), 1918);
		
			ftv.insert(ftv.end(), 1918);
			stdv.insert(stdv.end(), 1918);
			test_result = test_result && ft::equal(ftv.begin(),ftv.end(),stdv.begin());
		}
		{
			ft_vector	ftv;
			std_vector	stdv;
			ftv.reserve(10);
			stdv.reserve(10);

			ft_iterator		ft_it = ftv.insert(ftv.begin(), 1918);
			std_iterator	std_it = stdv.insert(stdv.begin(), 1918);
		
			ft_iterator		ft_it_2 = ftv.insert(ftv.end(), 1918);
			std_iterator	std_it_2 = stdv.insert(stdv.end(), 1918);
			test_result = test_result && (*ft_it == *std_it) && (*ft_it_2 == *std_it_2) && ft::equal(ftv.begin(),ftv.end(),stdv.begin());
		}
		return test_result;
}

bool	insert_modifier_part_two(){
	bool	test_result;
	{
		ft_vector	ftv;
		std_vector	stdv;

		ftv.insert(ftv.begin(), 1, 10);
		stdv.insert(stdv.begin(), 1, 10);
		ftv.insert(ftv.begin(), 1e4, 1000);
		stdv.insert(stdv.begin(), 1e4, 1000);

		ftv.insert(ftv.end(), 1, 10);
		stdv.insert(stdv.end(), 1, 10);
		ftv.insert(ftv.end(), 1e4, 1000);
		stdv.insert(stdv.end(), 1e4, 1000);
		test_result = ft::equal(ftv.begin(), ftv.end(), stdv.begin());
	}
	return test_result;
}

bool	insert_modifier_part_three(){
	bool	test_result;
	{
		ft_vector	ftv;
		ft_vector	ftv_2(1e4, 1312);

		std_vector	stdv;
		std_vector	stdv_2(1e4,1312);
		ftv.insert(ftv.begin(), ftv_2.begin(), ftv_2.end());
		ftv.insert(ftv.begin(), ftv_2.end(), ftv_2.end());
		stdv.insert(stdv.begin(), stdv_2.begin(), stdv_2.end());
		stdv.insert(stdv.begin(), stdv_2.end(), stdv_2.end());
		test_result = ft::equal(ftv.begin(), ftv.end(), stdv.begin());
	}
	return test_result;
}

bool	erase_modifier_part_one(){
	bool	test_result;
	{
		ft_vector	ftv(1e4, 1312);
		std_vector	stdv(1e4, 1312);

		ft_iterator		ft_it = ftv.begin() + 1234;
		std_iterator	std_it = stdv.begin() + 1234;
		ft_iterator		ft_ret = ftv.erase(ft_it);
		std_iterator	std_ret = stdv.erase(std_it);
		test_result = (*ft_ret == *std_ret) && ft::equal(ftv.begin(), ftv.end(), stdv.begin());
	}
//	ft::vector<std::string> ftv(1e6, "hola");
//	ftv.erase(ftv.begin() + 1e5);
	return test_result;
}

bool	erase_modifier_part_two(){

}

static std::string test_name_table[N_TESTS] = {
	"ITERATOR TEST",	"REVERSE_ITERATOR TEST",
	"CONSTRUCTOR TEST",	"OPERATOR= TEST",
	"ASSIGN TEST",		"AT TEST",
	"OPERATOR[] TEST",	"FRONT TEST",
	"BACK TEST",		"EMPTY TEST",
	"SIZE TEST",		"MAX_SIZE TEST",
	"RESERVE TEST",		"CAPACITY TEST",
	"CLEAR TEST",		"INSERT TEST",	
	"ERASE TEST",		"PUSH_BACK TEST",
	"POP_BACK TEST",	"RESIZE TEST",
	"SWAP TEST",		"COMP. OPERATORS TESTS"
};

static bool (*func_table[N_TESTS])(void) = {
	iterator_test, 		reverse_iterator_test,
	constructor_test,	operatorequal_test,
	assign_test,		at_test,
	operatoraccess_test,	front_test,
	back_test,		empty_test,
	size_test,		max_size_test,
	reserve_test,		capacity_test,
	clear_test,		insert_test,
	erase_test,		push_back_test,
	pop_back_test,		resize_test,
	swap_test,		comp_operators_test
};

/* stress test */

int main( void ) {
	for (i = 0; i < N_TESTS; i++) 
	(reverse_iterator_test()) ? std::cout << "[OK]\n" : std::cout << "[KO]\n";	
	(insert_modifier_part_one()) ? std::cout << "[OK]\n" : std::cout << "[KO]\n";	
	(insert_modifier_part_two()) ? std::cout << "[OK]\n" : std::cout << "[KO]\n";
	(insert_modifier_part_three()) ? std::cout << "[OK]\n" : std::cout << "[KO]\n";
	(erase_modifier_part_one()) ? std::cout << "[OK]\n" : std::cout << "[KO]\n";
   return 3445;
}
