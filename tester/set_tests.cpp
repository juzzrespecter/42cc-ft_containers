#include "tester.hpp"

typedef	ft::set<int>	ft_set;
typedef	std::set<int>	std_set;

typedef	ft_set::iterator				ft_iterator;
typedef ft_set::const_iterator			ft_const_iterator;
typedef ft_set::reverse_iterator		ft_reverse_iterator;
typedef ft_set::const_reverse_iterator	ft_const_reverse_iterator;

typedef	std_set::iterator				std_iterator;
typedef std_set::const_iterator			std_const_iterator;
typedef std_set::reverse_iterator		std_reverse_iterator;
typedef std_set::const_reverse_iterator	std_const_reverse_iterator;

typedef ft::pair<ft_iterator,bool>		ins_ret_f;
typedef std::pair<std_iterator,bool>	ins_ret_s;

typedef ft::pair<ft_iterator,ft_iterator>		ret_eq_f;
typedef	std::pair<std_iterator,std_iterator>	ret_eq_s;

static bool	iterator_test( void ) {

	ft_set	fs;
	std_set ss;
	bool	test_result;
	{
		ft_iterator			it = fs.begin();
		ft_iterator			it_2(it);

		ft_const_iterator	c_it(it);
		ft_const_iterator	c_in_2(c_it);
		ft_const_iterator	c_it_3 = fs.begin();

//		ft_iterator			it_3(c_it);
//		ft_iterator			it_3 = c_it;
	}
	{
		fill_tree_set(fs,ss);
		ft_iterator	it = fs.begin()++;
		std_iterator it_s = ss.begin()++;
		test_result = (*it == *it_s && *fs.begin() == *ss.begin() && *(--fs.end()) == *(--ss.end()));
	}
	{
		ft_const_iterator	it = fs.begin();
		std_const_iterator	it_s = ss.begin();
		test_result = (test_result && *it == *it_s && *fs.begin() == *ss.begin() && *(--fs.end()) == *(--ss.end()));
	}
	{
		ft_const_iterator it_c_r = fs.begin();
		ft_const_iterator it_c_e_r = fs.end();
		std_const_iterator it_c = ss.begin();
		std_const_iterator it_c_e = ss.end();
		test_result =  (test_result) &&
					   ((it_c_r == it_c_e_r) == (it_c == it_c_e) &&
			    	   (it_c_r != it_c_e_r) == (it_c != it_c_e));
	}
	return test_result;
}

static bool	reverse_iterator_test(void) {
	bool	test_result;
	{
		ft_set 	fs;
		std_set	ss;
		fill_tree_set(fs, ss);

		ft_reverse_iterator		rft = fs.rbegin();
		ft_reverse_iterator		rft_e = fs.rend();
		std_reverse_iterator	rstd = ss.rbegin();
		std_reverse_iterator	rstd_e = ss.rend();

		test_result = ((rft == rft_e) == (rstd == rstd_e) &&
						(rft != rft_e) == (rstd != rstd_e));
	}
	{
		ft_set	fs;
		std_set	ss;
		fill_tree_set(fs, ss);

		test_result = test_result && (fs.rbegin()==fs.rend()) == (ss.rbegin()==ss.rend()) &&
							 	     (fs.rbegin()!=fs.rend()) == (ss.rbegin()!=ss.rend());
	}
	return test_result;
}

static bool	size_test(void) {
	bool	test_result;
	ft_set	fs;
	std_set	ss;
	test_result = fs.size() == ss.size();
	
	fill_tree_set(fs,ss);
	test_result = (test_result) && (fs.size() == ss.size());

	fs.clear();
	ss.clear();
	return (test_result) && (fs.size() == ss.size());
}

static bool	empty_test(void) {
	bool	test_result;
	ft_set	fs;
	std_set	ss;
	test_result = fs.empty() == ss.empty();

	fill_tree_set(fs,ss);
	test_result = (test_result) && (fs.empty() == ss.empty());

	fs.clear();
	ss.clear();
	return (test_result) && (fs.empty() == ss.empty());
}

static bool	constructor_test(void) {
	bool	test_result;
	/* -- default -- */
	{
		ft_set	fs;
		std_set	ss;
		test_result = equal_test_set(fs,ss);
	}
	/* -- range -- */
	{
		ft_set	fsrange;
		std_set	ssrange;
		
		fill_tree_set(fsrange,ssrange);

		ft_set	fs(fsrange.begin(), fsrange.end());
		std_set	ss(ssrange.begin(), ssrange.end());
		test_result = (test_result) && equal_test_set(fs,ss);
	}
	/* -- copy -- */
	{
		ft_set	fscpy;
		std_set	sscpy;

		fill_tree_set(fscpy,sscpy);

		ft_set	fs(fscpy);
		std_set	ss(sscpy);
		test_result = (test_result) && equal_test_set(fs,ss);
	}
	return test_result;
}

static bool	operatorequal_test(void) {
	bool	test_result;

	ft_set	fseq;
	std_set	sseq;

	ft_set	fs = fseq;
	test_result = equal_test_set(fs,fseq);

	fill_tree_set(fseq,sseq);
	fs = fseq;
	test_result = (test_result) &&
		      (equal_test_set(fs,fseq)) &&
		      (equal_test_set(fs,sseq));

	fseq.clear();
	sseq.clear();
	fs = fseq;
	test_result = (test_result) &&
		      (equal_test_set(fs,fseq)) &&
		      (equal_test_set(fs,sseq));
	return test_result;
}

static bool	max_size_test(void) {
	ft::set<int> 			fs1;
	ft::set<double>			fs2;
	ft::set<std::string>	fs3;

	std::set<int> 			ss1;
	std::set<double>		ss2;
	std::set<std::string>	ss3;

	return (fs1.max_size() == ss1.max_size()) &&
		   (fs2.max_size() == ss2.max_size()) &&
		   (fs3.max_size() == ss3.max_size());
}

static bool	clear_test(void) {
	ft_set	fs;

	fs.clear();
	for(int i = 0; i < 1e5; i++) fs.insert(i);
	fs.clear();
	return fs.size() == 0 && fs.begin() == fs.end();
}

static bool	insert_test(void) {
	bool	test_result;
	/* -- value overload -- */
	{
		ft_set	fs;
		std_set	ss;

		fill_tree_set(fs,ss);
		test_result = equal_test_set(fs,ss);
	}
	{
		ft_set	fs;
		std_set	ss;

		int key = rand();
		ins_ret_f ret_f = fs.insert(key);
		ins_ret_s ret_s = ss.insert(key);
		test_result = (test_result) && (ret_f.second == ret_s.second);

		ret_f = fs.insert(key);
		ret_s = ss.insert(key);
		test_result = (test_result) && (ret_f.second == ret_s.second);
	}
	/* -- hint overload -- */
	{
		/* -- begin() -- */
		ft_set	fs;
		std_set	ss;

		for(int i = 0; i < 1e6; i++){
			int k = rand();
			ft_iterator it_f = fs.insert(fs.begin(),k);
			std_iterator std_f = ss.insert(ss.begin(),k);
			test_result = (test_result) && (*it_f == *std_f);
		}
		test_result = (test_result) && equal_test_set(fs,ss);
	}
	{
		/* -- lower_bound() -- */
		ft_set	fs;
		std_set	ss;

		for(int i = 0; i < 1e6; i++){
			int k = rand();
			ft_iterator it_f = fs.insert(fs.lower_bound(k),k);
			std_iterator std_f = ss.insert(ss.lower_bound(k),k);
			test_result = (test_result) && (*it_f == *std_f);
		}
		test_result = (test_result) && equal_test_set(fs,ss);
	}
	{
		/* -- end() -- */
		ft_set	fs;
		std_set	ss;

		for(int i = 0; i < 1e6; i++){
			int k = rand();
			ft_iterator it_f = fs.insert(fs.end(),k);
			std_iterator std_f = ss.insert(ss.end(),k);
			test_result = (test_result) && (*it_f == *std_f);
		}
		test_result = (test_result) && equal_test_set(fs,ss);
	}
	/* -- range overload -- */
	{
		/*ft_set	fs;
		std_set	ss;
		for(int i = 0;i < 1e6;i++)ss.insert(rand());
		fs.insert(ss.begin(), ss.end());
		test_result = (test_result) && equal_test_set(fs,ss);*/
		ft_set	fmrange, fm;
		std_set	smrange, sm;

		fill_tree_set(fmrange, smrange);
		fm.insert(fmrange.begin(), fmrange.end());
		sm.insert(smrange.begin(),smrange.end());
		test_result = (test_result) && equal_test_set(fm,sm);
	}
	return test_result;
}

static bool	erase_test(void) {
	bool	test_result;

	/* -- iterator overload -- */
	{
		ft_set	fs;
		std_set	ss;
		fill_tree_set(fs,ss);

		for(int i = 0; i < 100; i++){
			fs.erase(fs.begin());
			ss.erase(ss.begin());
		}
		test_result = equal_test_set(fs,ss);
	}
	/* -- key overload -- */
	{
		ft_set	fs;
		std_set	ss;
		fill_tree_set(fs,ss);

		for(int i = 0; i < 1e6; i++){
			int key = rand();
			fs.erase(key);
			ss.erase(key);
		}
		test_result = (test_result) && (equal_test_set(fs,ss));
	}
	/* -- range overload -- */
	{
		ft_set	fs;
		std_set	ss;
		fill_tree_set(fs,ss);

		fs.erase(fs.begin(),fs.end());
		ss.erase(ss.begin(),ss.end());
		test_result = (test_result) && (equal_test_set(fs,ss));
	}
	return test_result;
}

static bool	swap_test(void) {
	ft_set	fs;
	std_set	ss;

	ft_set	fs_2;
	std_set	ss_2;

	bool	test_result;
	fill_tree_set(fs,ss);
	swap(fs, fs_2);
	swap(ss, ss_2);
	test_result = (equal_test_set(fs,ss)) &&
				  (ft::equal(fs_2.begin(),fs_2.end(),ss_2.begin()));
	fill_tree_set(fs_2,ss_2);
	fs.swap(fs_2);
	ss.swap(ss_2);
	test_result = (test_result) &&
				  (equal_test_set(fs,ss)) &&
				  (ft::equal(fs_2.begin(),fs_2.end(),ss_2.begin()));
	return test_result;
}

static bool	count_test(void) {
	ft_set	fs;
	std_set	ss;

	fill_tree_set(fs,ss);
	for(size_t i = 0; i < fs.size(); i++){
		if(fs.count(i) != ss.count(i)) return false;
	}
	return true;
}

static bool	find_test(void) {
	ft_set	fs;
	std_set	ss;

	for(int i = 0; i < 1e4; i++){
		fs.insert(i);
		ss.insert(i);
	}
	for(int i = 0; i < 1e4; i++){
		ft_iterator		f_it = fs.find(i);
		std_iterator	s_it = ss.find(i);
		if (*f_it != *s_it) return false;
	}
	ft_iterator		f_end = fs.find(1e4 + 1);
	std_iterator	s_end = ss.find(1e4 + 1);
	return ((f_end == fs.end()) == (s_end == ss.end()));
}

static bool	equal_range_test(void) {
	ft_set	fs;
	std_set	ss;

	for(int i = 0; i < 1e4; i++){
		int v = rand();
		fs.insert(v);
		ss.insert(v);
	}
	for(int i = 0; i < 1e2; i++){
		ret_eq_f ret_f = fs.equal_range(i);
		ret_eq_s ret_s = ss.equal_range(i);
		if ((*ret_f.first != *ret_s.first) ||
			(*ret_f.second != *ret_s.second)) return false;
	}
	return true;
}

static bool	upper_bound_test(void) { // here
	ft_set	fs;
	std_set	ss;

	for(int i = 0; i < 1e4; i++){
		if (i%2) {
			int v = rand();
			fs.insert(v);
			ss.insert(v);
		}
	}
	for(int i = 0; i < 1e2; i++){
		ft_iterator		it_f = fs.upper_bound(i);
		std_iterator	it_s = ss.upper_bound(i);
		if (*it_f != *it_s) return false;
	}
	return true;
}

static bool	lower_bound_test(void) { // here
	ft_set	fs;
	std_set	ss;

	for(int i = 0; i < 1e4; i++){
		if (i%2) {
			int v = rand();
			fs.insert(v);
			ss.insert(v);
		}
	}
	for(int i = 0; i < 1e2; i++){
		ft_iterator		it_f = fs.lower_bound(i);
		std_iterator	it_s = ss.lower_bound(i);
		if (*it_f != *it_s) return false;
	}
	return true;
}

bool observers_test(void){
	ft_set fs;
	return (fs.key_comp()(3,4) &&
		   !fs.key_comp()(4,3) &&
		   !fs.key_comp()(3,3));
}

static bool	comp_operators_test(void){
	bool	test_result;
	ft_set	fm;
	std_set	sm;

	ft_set	fm_2;
	std_set	sm_2;
	test_result = (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);

	fill_tree_set(fm_2,sm_2);
	test_result = (test_result) &&
				  (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);
	
	fill_tree_set(fm,sm);
	test_result = (test_result) &&
				  (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);

	fm.insert(2);
	sm.insert(2);
	test_result = (test_result) &&
				  (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);
	return test_result;
}

static bool	(*func_table[N_SET_TEST])(void) = {
	iterator_test,		reverse_iterator_test,
	constructor_test,	operatorequal_test,
	empty_test,			size_test,
	max_size_test,		clear_test,
	insert_test,		erase_test,
	swap_test,			count_test,
	find_test,			equal_range_test,
	lower_bound_test,	upper_bound_test,
	observers_test,		comp_operators_test
};

static std::string test_name_table[N_SET_TEST] = {
	"ITERATOR TEST",	"REVERSE_ITERATOR TEST",
	"CONSTRUCTOR TEST",	"OPERATOR= TEST",
	"EMPTY TEST",		"SIZE TEST",
	"MAX_SIZE TEST",	"CLEAR TEST",
	"INSERT TEST",		"ERASE TEST",
	"SWAP TEST",		"COUNT TEST",
	"FIND TEST",		"EQUAL_RANGE TEST",
	"LOWER_BOUND TEST",	"UPPER_BOUND TEST",
	"OBSERVERS TEST",	"compARE OPERATORS TEST"
};

// stress test
//
// rbtree test
//void	rbtree(void){
//	ft::set<char>	s;
	//insert loop
	//delete loop
//}

//bool	stress_test(void){


//}

void set_tests(void){
	static std::string buffer;
	std::cout << "[ set test: compare behaviour with std::set ]\n\n";
	for (int i = 0; i < N_SET_TEST; i++)
		std::cout << std::setw(30) << test_name_table[i] << ": " << ((func_table[i])() ? OK : KO) << "\n";
	std::cout << "\n< demo rb ? (y/n) >";
	std::getline(std::cin,buffer);
	//if(buffer[0] == 'y' && !buffer[1]) rbtree();
	//std::cout << "\n< performance test... : " << ((stress_test()) ? OK : KO) << " >\n";
}
