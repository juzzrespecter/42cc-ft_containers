#include "vector.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
# include <sys/time.h>


#define N_TESTS 22
#define OK "\033[32m [OK] \033[0m"
#define KO "\033[31m [KO] \033[0m"

typedef ft::vector<int>				ft_vector;
typedef ft_vector::iterator			ft_iterator;
typedef ft_vector::const_iterator	ft_const_iterator;
typedef ft_vector::reverse_iterator	ft_reverse_iterator;

typedef std::vector<int>				std_vector;
typedef std_vector::iterator			std_iterator;
typedef std_vector::const_iterator		std_const_iterator;
typedef std_vector::reverse_iterator	std_reverse_iterator;

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
//		ft_iterator			it_3 = c_it;
	}
	{
		for (int i = 0; i < 1e6; i++) {
			int val = rand();
			ftv.push_back(val);
			stdv.push_back(val);
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
		ft_const_iterator it_c_r = ftv.begin();
		ft_const_iterator it_c_e_r = ftv.end();
		std_const_iterator it_c = stdv.begin();
		std_const_iterator it_c_e = stdv.end();
		test_result = ((it_c_r == it_c_e_r) == (it_c == it_c_e) &&
			    	   (it_c_r != it_c_e_r) == (it_c != it_c_e) &&
					   (it_c_r > it_c_e_r) == (it_c > it_c_e) &&
					   (it_c_r >= it_c_e_r) == (it_c >= it_c_e) &&
					   (it_c_r < it_c_e_r) == (it_c < it_c_e) &&
					   (it_c_r <= it_c_e_r) == (it_c <= it_c_e));
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
	{
		ft_vector	ftv(1e6,234);
		std_vector	stdv(1e6,234);
		test_result = test_result && (ftv.rbegin()==ftv.rend()) == (stdv.rbegin()==stdv.rend()) &&
							 	     (ftv.rbegin()!=ftv.rend()) == (stdv.rbegin()!=stdv.rend()) &&
							 	     (ftv.rbegin()>ftv.rend()) == (stdv.rbegin()>stdv.rend()) &&
							 	     (ftv.rbegin()>=ftv.rend()) == (stdv.rbegin()>=stdv.rend()) &&
							 	     (ftv.rbegin()<ftv.rend()) == (stdv.rbegin()<stdv.rend()) &&
							 	     (ftv.rbegin()<=ftv.rend()) == (stdv.rbegin()<=stdv.rend());
	}
	return test_result;
}

bool	constructor_test(void){
	bool	test_result;
	/*	-- template deduction -- */
	{
		ft::vector<char> fc(1e6,'c');
		ft::vector<char> fc_2(fc.begin(),fc.end());
		ft::vector<double> fd(1e6,3.4);
		ft::vector<double> fd_2(fd.begin(),fd.end());
	}
	/*	-- default -- */
	{
		ft_vector	ftv;
		std_vector	stdv;
		test_result = (ftv.size() == stdv.size() && ft::equal(ftv.begin(), ftv.end(),stdv.begin()));
	}
	/*	-- fill --	*/
	{
		ft_vector	ftv(1e6,5);
		std_vector	stdv(1e6,5);
		test_result = (test_result && 
						ftv.size() == stdv.size() && 
						ft::equal(ftv.begin(), ftv.end(),stdv.begin()));
	}
	/*	-- range --	*/
	{
		ft_vector	ftrange(1e6,5);
		std_vector	stdrange(1e6,5);

		ft_vector	ftv(ftrange.begin(),ftrange.end());
		std_vector	stdv(stdrange.begin(),stdrange.end());		
		test_result = (test_result && 
						ftv.size() == stdv.size() && 
						ft::equal(ftv.begin(), ftv.end(),stdv.begin()));
	}
	/*	-- copy --	*/
	{
		ft_vector	ftcpy(1e6,456);
		std_vector	stdcpy(1e6,456);

		ft_vector	ftv(ftcpy);
		std_vector	stdv(stdcpy);
		test_result = (test_result && 
						ftv.size() == stdv.size() && 
						ft::equal(ftv.begin(), ftv.end(),stdv.begin()));
	}
	return test_result;
}

bool	operatorequal_test(void){
	ft_vector	ftcpy(1e7,234);
	std_vector	stdcpy(1e7,234);

	ft_vector	ftv = ftcpy;
	std_vector	stdv = stdcpy;
	return ftv.size() == stdv.size() && ft::equal(ftv.begin(),ftv.end(),stdv.begin());
}

bool	assign_test(void){
	bool	test_result;
	/*	-- range overload --	*/
	ft_vector	ftrange(1e6,345);
	std_vector	stdrange(1e6,345);
	{
		ft_vector	ftv;
		std_vector	stdv;
		ftv.assign(ftrange.begin(),ftrange.end());
		stdv.assign(stdrange.begin(),stdrange.end());
		test_result = (ftv.size() == stdv.size()) &&
					  (ftv.capacity() == stdv.capacity()) &&
					  (ft::equal(ftv.begin(),ftv.end(),stdv.begin()));
	}
	{
		ft_vector	ftv(500,500);
		std_vector	stdv(500,500);
		ftv.assign(ftrange.begin(),ftrange.end());
		stdv.assign(stdrange.begin(),stdrange.end());
		test_result = (test_result) &&
					  (ftv.size() == stdv.size()) &&
					  (ftv.capacity() == stdv.capacity()) &&
					  (ft::equal(ftv.begin(),ftv.end(),stdv.begin()));
	}
	/*	-- fill overload --	*/
	{
		ft_vector	ftv;
		std_vector	stdv;
		ftv.assign(1e6,777);
		stdv.assign(1e6,777);
		test_result = (test_result) &&
					  (ftv.size() == stdv.size()) &&
					  (ftv.capacity() == stdv.capacity()) &&
					  (ft::equal(ftv.begin(),ftv.end(),stdv.begin()));
	}
	{
		ft_vector	ftv(1e6,666);
		std_vector	stdv(1e6,666);
		test_result = (test_result) &&
					  (ftv.size() == stdv.size()) &&
					  (ftv.capacity() == stdv.capacity()) &&
					  (ft::equal(ftv.begin(),ftv.end(),stdv.begin()));		
	}
	return test_result;
}

bool	at_test(void){
	static size_t 	size = 1e6;
	ft_vector		ftv(size,876);
	std_vector		stdv(size,876);
	for(size_t i = 0; i < size; i++){
		if (ftv.at(i) != stdv.at(i)) return false;
	}
	ft_vector ftv_2(7);
	try{ ftv_2.at(10); }
	catch(std::out_of_range& e){ return true; }
	return false;
}

bool	operatoraccess_test(void){
	static size_t 	size = 1e6;
	ft_vector		ftv(size,876);
	std_vector		stdv(size,876);
	ftv[1000] = 1;
	stdv[1000] = 1;
	for(size_t i = 0; i < size; i++){
		if (!(ftv.at(i) == stdv.at(i))) return false;
	}
	return true;
}

bool	front_test(void){
	ft_vector	ftv(10);
	std_vector	stdv(10);
	for(int i = 0; i < 10; i++) {ftv.push_back(i);stdv.push_back(i);}
	return ftv.front() == stdv.front();
}

bool	back_test(void){
	ft_vector	ftv(10);
	std_vector	stdv(10);
	for(int i = 0; i < 10; i++) {ftv.push_back(i);stdv.push_back(i);}
	return ftv.back() == stdv.back();
}

bool	empty_test(void){
	bool	test_result;
	{
		ft_vector	ftv;
		std_vector	stdv;
		test_result = (ftv.empty() == stdv.empty());
	}
	{
		ft_vector	ftv(1e6,123);
		std_vector	stdv(1e6,123);
		test_result = (test_result) && (ftv.empty() == stdv.empty());
	}
	{
		ft_vector	ftv(1e6,123);
		std_vector	stdv(1e6,123);
		ftv.clear();
		stdv.clear();
		test_result = (test_result) && (ftv.empty() == stdv.empty());
	}
	return test_result;
}

bool	size_test(void){
	bool	test_result;
	{
		ft_vector	ftv;
		std_vector	stdv;
		test_result = ftv.size() == stdv.size();
	}
	{
		ft_vector	ftv;
		std_vector	stdv;
		ftv.push_back(10);stdv.push_back(10);
		test_result = (test_result) && (ftv.size() == stdv.size());
	}
	{
		ft_vector	ftv(1e6);
		std_vector	stdv(1e6);
		test_result = (test_result) && (ftv.size() == stdv.size());
		ftv.clear();stdv.clear();
		test_result = (test_result) && (ftv.size() == stdv.size());		
	}
	return test_result;
}

bool	max_size_test(void){
	return (ft::vector<int>().max_size() == std::vector<int>().max_size() &&
			ft::vector<char>().max_size() == std::vector<char>().max_size() &&
			ft::vector<double>().max_size() == std::vector<double>().max_size() &&
			ft::vector<std::string>().max_size() == std::vector<std::string>().max_size());
}

bool	reserve_test(void){
	bool		test_result;
	ft_vector	ftv;
	std_vector	stdv;

	ftv.reserve(1); stdv.reserve(1);
	test_result = ftv.capacity() == stdv.capacity();

	ftv.reserve(2); stdv.reserve(2);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	ftv.reserve(5); stdv.reserve(5);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	ftv.reserve(1e6); stdv.reserve(1e6);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	ftv.reserve(10); stdv.reserve(10);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	try{ ftv.reserve(ftv.max_size() + 1);}
	catch(std::length_error& e){ return true;}
	return false;
}

bool	capacity_test(void){
	bool		test_result;
	ft_vector	ftv;
	std_vector	stdv;

	test_result = ftv.capacity() == stdv.capacity();

	ftv.assign(10,10);stdv.assign(10,10);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	ftv.push_back(1);stdv.push_back(1);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());
	ftv.push_back(1);stdv.push_back(1);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	ftv.insert(ftv.begin(),1e6,456);stdv.insert(stdv.begin(),1e6,456);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	ftv.resize(100);stdv.resize(100);
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	ftv.clear();stdv.clear();
	test_result = (test_result) && (ftv.capacity() == stdv.capacity());

	return test_result;
}

bool	clear_test(void){
	ft_vector	ftv(1e6,123);
	std_vector	stdv(1e6,123);

	ftv.clear();
	stdv.clear();
	return ft::equal(stdv.begin(),stdv.end(),ftv.begin());
}

bool	insert_test(void){
	    bool	test_result;
		/*	-- one element overload --	*/
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
		/*	-- fill overload --	*/
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
			test_result = test_result && ft::equal(ftv.begin(), ftv.end(), stdv.begin());
		}
		/*	-- range overload --	*/
		{
			ft_vector	ftv;
			ft_vector	ftv_2(1e4, 1312);

			std_vector	stdv;
			std_vector	stdv_2(1e4,1312);
			ftv.insert(ftv.begin(), ftv_2.begin(), ftv_2.end());
			ftv.insert(ftv.begin(), ftv_2.end(), ftv_2.end());
			stdv.insert(stdv.begin(), stdv_2.begin(), stdv_2.end());
			stdv.insert(stdv.begin(), stdv_2.end(), stdv_2.end());
			test_result = test_result && ft::equal(ftv.begin(), ftv.end(), stdv.begin());
		}
	return test_result;
}

bool	erase_test(void){
	bool	test_result;
	/*	-- single element overload --	*/
	{
		ft_vector	ftv(1e4, 1312);
		std_vector	stdv(1e4, 1312);

		ft_iterator		ft_it = ftv.begin() + 1234;
		std_iterator	std_it = stdv.begin() + 1234;
		ft_iterator		ft_ret = ftv.erase(ft_it);
		std_iterator	std_ret = stdv.erase(std_it);
		test_result = (*ft_ret == *std_ret) && 
					  ft::equal(ftv.begin(), ftv.end(), stdv.begin()) && 
					  (ftv.size() == stdv.size());
	}
	/*	-- range of elements overload --	*/
	{
		ft_vector	ftv(1e6, 1312);
		std_vector	stdv(1e6, 1312);

		ft_iterator		ft_it = ftv.erase(ftv.begin() + 1312, --ftv.end());
		std_iterator	std_it = stdv.erase(stdv.begin() + 1312, --stdv.end());
		test_result = (test_result) && 
					  (*ft_it == *std_it) && 
					  ft::equal(ftv.begin(), ftv.end(), stdv.begin()) && 
					  (ftv.size() == stdv.size());
	}
	return test_result;
}

bool	push_back_test(void){
	ft_vector	ftv;
	std_vector	stdv;
	int			value;
	for(int i = 0; i < 1e6; i++) {
		value = rand();
		ftv.push_back(value);
		stdv.push_back(value);
	}
	return ft::equal(stdv.begin(),stdv.end(),ftv.begin()) && (ftv.size()==stdv.size());
}

bool	pop_back_test(void){
	ft_vector	ftv(1e6,3635);
	std_vector	stdv(1e6,3635);
	for(int i = 0; i < 1e6; i++) {
		if(((i+(i*3))%2)) {
			ftv.pop_back();
			stdv.pop_back();
		}
	}
	return ft::equal(stdv.begin(),stdv.end(),ftv.begin()) && (ftv.size()==stdv.size());
}

bool	resize_test(void){
	bool	test_result;
	{
		ft_vector	ftv;
		std_vector	stdv;

		ftv.resize(1e6);
		stdv.resize(1e6);
		test_result = (ftv.size() == stdv.size()) &&
					  (ftv.capacity() == stdv.capacity()) &&
					  ft::equal(ftv.begin(),ftv.end(),stdv.begin());
	}
	{
		ft_vector	ftv(1e6,56);
		std_vector	stdv(1e6,56);
		ftv.resize(2);
		stdv.resize(2);
		test_result = (test_result) &&
					  (ftv.size() == stdv.size()) &&
					  (ftv.capacity() == stdv.capacity()) &&
					  ft::equal(ftv.begin(),ftv.end(),stdv.begin());	
	}
	{
		ft_vector	ftv(1e6,56);
		std_vector	stdv(1e6,56);
		ftv.resize(1e7);
		stdv.resize(1e7);
		test_result = (test_result) &&
					  (ftv.size() == stdv.size()) &&
					  (ftv.capacity() == stdv.capacity()) &&
					  ft::equal(ftv.begin(),ftv.end(),stdv.begin());
	}
	return test_result;
}

bool	swap_test(void){
	bool	test_result;
	{
		ft_vector	ftv_1(1e6,678);
		ft_vector 	ftv_2;

		std_vector	stdv_1(1e6,678);
		std_vector	stdv_2;
		swap(ftv_1,ftv_2);
		stdv_1.swap(stdv_2);
		test_result = (ft::equal(ftv_1.begin(),ftv_1.end(),stdv_1.begin())) &&
					  (ft::equal(ftv_2.begin(),ftv_2.end(),stdv_2.begin()));
	}
	{
		ft_vector	ftv_1;
		ft_vector 	ftv_2(1e6,678);

		std_vector	stdv_1;
		std_vector	stdv_2(1e6,678);
		ftv_1.swap(ftv_2);
		stdv_1.swap(stdv_2);
		test_result = (test_result) &&
					  (ft::equal(ftv_1.begin(),ftv_1.end(),stdv_1.begin())) &&
					  (ft::equal(ftv_2.begin(),ftv_2.end(),stdv_2.begin()));
	}
	{
		ft_vector	ftv_1(1e6,678);
		ft_vector 	ftv_2(1e5,345);

		std_vector	stdv_1(1e6,678);
		std_vector	stdv_2(1e5,345);
		ftv_1.swap(ftv_2);
		stdv_1.swap(stdv_2);
		test_result = (test_result) &&
					  (ft::equal(ftv_1.begin(),ftv_1.end(),stdv_1.begin())) &&
					  (ft::equal(ftv_2.begin(),ftv_2.end(),stdv_2.begin()));
	}
	return test_result;
}

bool	comp_operators_test(void){
	bool	test_result;
	ft_vector	ftv;
	std_vector	stdv;

	ft_vector	ftv_2;
	std_vector	stdv_2;
	test_result = (ftv == ftv_2) == (stdv == stdv_2) &&
				  (ftv != ftv_2) == (stdv != stdv_2) &&
				  (ftv >  ftv_2) == (stdv >  stdv_2) &&
				  (ftv >= ftv_2) == (stdv >= stdv_2) &&
				  (ftv <  ftv_2) == (stdv <  stdv_2) &&
				  (ftv <= ftv_2) == (stdv <= stdv_2);

	ftv_2.assign(1e6,3);
	stdv_2.assign(1e6,3);
	test_result = (test_result) &&
				  (ftv == ftv_2) == (stdv == stdv_2) &&
				  (ftv != ftv_2) == (stdv != stdv_2) &&
				  (ftv >  ftv_2) == (stdv >  stdv_2) &&
				  (ftv >= ftv_2) == (stdv >= stdv_2) &&
				  (ftv <  ftv_2) == (stdv <  stdv_2) &&
				  (ftv <= ftv_2) == (stdv <= stdv_2);
	
	ftv.assign(1e6,3);
	stdv.assign(1e6,3);
	test_result = (test_result) &&
				  (ftv == ftv_2) == (stdv == stdv_2) &&
				  (ftv != ftv_2) == (stdv != stdv_2) &&
				  (ftv >  ftv_2) == (stdv >  stdv_2) &&
				  (ftv >= ftv_2) == (stdv >= stdv_2) &&
				  (ftv <  ftv_2) == (stdv <  stdv_2) &&
				  (ftv <= ftv_2) == (stdv <= stdv_2);

	ftv.assign(1,4);
	stdv.assign(1,4);
	test_result = (test_result) &&
				  (ftv == ftv_2) == (stdv == stdv_2) &&
				  (ftv != ftv_2) == (stdv != stdv_2) &&
				  (ftv >  ftv_2) == (stdv >  stdv_2) &&
				  (ftv >= ftv_2) == (stdv >= stdv_2) &&
				  (ftv <  ftv_2) == (stdv <  stdv_2) &&
				  (ftv <= ftv_2) == (stdv <= stdv_2);
	
	return test_result;
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
	iterator_test, 			reverse_iterator_test,
	constructor_test,		operatorequal_test,
	assign_test,			at_test,
	operatoraccess_test,	front_test,
	back_test,				empty_test,
	size_test,				max_size_test,
	reserve_test,			capacity_test,
	clear_test,				insert_test,
	erase_test,				push_back_test,
	pop_back_test,			resize_test,
	swap_test,				comp_operators_test
};

long get_time(void){
	struct timeval	time_s;
	long			time;

	gettimeofday(&time_s, NULL);
	time = time_s.tv_sec * 1000 + (long)time_s.tv_usec / 1000;
	return (time);
}

bool stress_test(void){

	long	time_std = get_time();
	std_vector s(1e7,1312);
	s.assign(1e6,56);
	s.insert(s.begin(),1e8,4);
	s.erase(s.begin(),s.end());

	time_std = get_time() - time_std;
	
	long	time_ft = get_time();
	ft_vector f(1e7,1312);
	f.assign(1e6,56);
	f.insert(f.begin(),1e8,4);
	f.erase(f.begin(),f.end());

	time_ft = get_time() - time_ft;
	return (time_ft < time_std * 10) ? true : false;
}

int main( void ) {
	system("clear");
	std::cout << "\n[ vector test: compare behaviour with std::vector ]\n\n";
	for (int i = 0; i < N_TESTS; i++)
		std::cout << std::setw(30) << test_name_table[i] << ": " << ((func_table[i])() ? OK : KO) << "\n";
	std::cout << "\n< performance test... : " << ((stress_test()) ? OK : KO) << " >\n";
   	return EXIT_SUCCESS;
}
