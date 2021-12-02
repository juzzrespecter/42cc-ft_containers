#include "tester.hpp"
#define MAP_SIZE 1e6

typedef ft::map<int, int>				ft_map;
typedef ft_map::iterator				ft_iterator;
typedef ft_map::const_iterator			ft_const_iterator;
typedef ft_map::reverse_iterator		ft_reverse_iterator;
typedef ft_map::const_reverse_iterator	ft_const_reverse_iterator;

typedef std::map<int, int>					std_map;
typedef std_map::iterator					std_iterator;
typedef std_map::const_iterator				std_const_iterator;
typedef std_map::reverse_iterator			std_reverse_iterator;
typedef std_map::const_reverse_iterator	std_const_reverse_iterator;

typedef ft::pair<ft_iterator,bool>		ins_ret_f;
typedef std::pair<std_iterator,bool>	ins_ret_s;
typedef ft::pair<ft_iterator,ft_iterator>		ret_eq_f;
typedef	std::pair<std_iterator,std_iterator>	ret_eq_s;

static bool	iterator_test( void ) {
	ft_map 	fm;
	std_map sm;
	bool	test_result;
	{
		ft_iterator			it = fm.begin();
		ft_iterator			it_2(it);

		ft_const_iterator	c_it(it);
		ft_const_iterator	c_in_2(c_it);
		ft_const_iterator	c_it_3 = fm.begin();

//		ft_iterator			it_3(c_it);
//		ft_iterator			it_3 = c_it;
	}
	{
		fill_tree_map(fm,sm);
		ft_iterator	it = fm.begin()++;
		std_iterator it_s = sm.begin()++;
		test_result = (it->first == it_s->first) && 
					  (it->second == it_s->second) && 
					  (fm.begin()->first == sm.begin()->first) && 
					  (fm.begin()->second == sm.begin()->second) && 
					  ((--fm.end())->first == (--sm.end())->first);
	}
	{
		ft_const_iterator	it = fm.begin();
		std_const_iterator	it_s = sm.begin();
		test_result = (test_result) && 
					  (it->first == it_s->first) && 
					  (it->second == it_s->second) && 
					  (fm.begin()->first == sm.begin()->first) && 
					  (fm.begin()->second == sm.begin()->second) && 
					  ((--fm.end())->first == (--sm.end())->first);
	}
	{
		ft_const_iterator it_c_r 	= fm.begin();
		ft_const_iterator it_c_e_r 	= fm.end();
		std_const_iterator it_c 	= sm.begin();
		std_const_iterator it_c_e 	= sm.end();
		test_result = (test_result) && ((it_c_r == it_c_e_r) == (it_c == it_c_e) &&
			    	   (it_c_r != it_c_e_r) == (it_c != it_c_e));
	}
	return test_result;
}

static bool	reverse_iterator_test(void) {
	bool	test_result;
	{
		ft_map 	fm;
		std_map	sm;
		fill_tree_map(fm, sm);

		ft_reverse_iterator		rft = fm.rbegin();
		ft_reverse_iterator		rft_e = fm.rend();
		std_reverse_iterator	rstd = sm.rbegin();
		std_reverse_iterator	rstd_e = sm.rend();

		test_result = ((rft == rft_e) == (rstd == rstd_e) &&
						(rft != rft_e) == (rstd != rstd_e));
	}
	{
		ft_map	fm;
		std_map	sm;
		fill_tree_map(fm, sm);

		test_result = test_result && (fm.rbegin()==fm.rend()) == (sm.rbegin()==sm.rend()) &&
							 	     (fm.rbegin()!=fm.rend()) == (sm.rbegin()!=sm.rend());
	}
	return test_result;
}

static bool	constructor_test(void) {
	bool	test_result;
	/* -- default -- */
	{
		ft_map	fm;
		std_map	sm;
		test_result = equal_test_map(fm,sm);
	}
	/* -- range -- */
	{
		ft_map	fmrange;
		std_map	smrange;
		
		fill_tree_map(fmrange,smrange);

		ft_map	fm(fmrange.begin(), fmrange.end());
		std_map	sm(smrange.begin(), smrange.end());
		test_result = (test_result) && equal_test_map(fm,sm);
	}
	/* -- copy -- */
	{
		ft_map	fmcpy;
		std_map	smcpy;

		fill_tree_map(fmcpy,smcpy);

		ft_map	fm(fmcpy);
		std_map	sm(smcpy);
		test_result = (test_result) && equal_test_map(fm,sm);
	}
	return test_result;
}

static bool	operatorequal_test_map(void) {
	bool	test_result;

	ft_map	fmeq;
	std_map	smeq;

	ft_map	fm = fmeq;
	test_result = ft::equal(fm.begin(),fm.end(),fmeq.begin());

	fill_tree_map(fmeq,smeq);
	fm = fmeq;
	test_result = (test_result) &&
		      (equal_test_map(fm,fmeq)) &&
		      (equal_test_map(fm,smeq));

	fmeq.clear();
	smeq.clear();
	fm = fmeq;
	test_result = (test_result) &&
		      (equal_test_map(fm,fmeq)) &&
		      (equal_test_map(fm,smeq));
	return test_result;
}

static bool	at_test(void) {
	std_map	sm;
	ft_map	fm;
	for(int i = 0; i < 1e6; i++){
		int	val = rand();
		sm[i] = val;
		fm[i] = val;
	}
	for(int i = 0; i < 1e6; i++){
		if(sm.at(i) != fm.at(i)) return false;
	}
	ft_map	try_test;
	try{ try_test.at(5); }
	catch(std::out_of_range& e){ return true;}
	return false;
}

static bool	operatoraccess_test(void) {
	ft_map	fm;
	std_map	sm;
	fill_tree_map(fm,sm);

	long	fm_res = 0, sm_res = 0;
	for(size_t i = 0; i < 1e5; i++){
		fm_res = fm[i];
		sm_res = sm[i];
	}
	return (fm_res == sm_res && fm.size() == sm.size());
}

static bool	empty_test(void) {
	bool	test_result;
	ft_map	fm;
	std_map	sm;
	test_result = fm.empty() == sm.empty();

	fill_tree_map(fm,sm);
	test_result = (test_result) && (fm.empty() == sm.empty());

	fm.clear();
	sm.clear();
	return (test_result) && (fm.empty() == sm.empty());
}

static bool	size_test(void) {
	bool		test_result;
	ft_map		fm;
	std_map		sm;
	test_result = fm.size() == sm.size();
	
	fill_tree_map(fm,sm);
	test_result = (test_result) && (fm.size() == sm.size());

	fm.clear();
	sm.clear();
	return (test_result) && (fm.size() == sm.size());
}

static bool	max_size_test(void) {
	ft::map<int,char> 			m1;
	ft::map<double,std::string> m2;
	ft::map<float,size_t>		m3;

	std::map<int,char> 			ms1;
	std::map<double,std::string> ms2;
	std::map<float,size_t>		ms3;

	return (m1.max_size() == ms1.max_size()) &&
		   (m2.max_size() == ms2.max_size()) &&
		   (m3.max_size() == ms3.max_size());
}

static bool	clear_test(void) {
	ft_map	mp;

	mp.clear();
	for(int i = 0; i < 1e5; i++) mp.insert(ft::make_pair(rand(),rand()));
	mp.clear();
	return mp.size() == 0 && mp.begin() == mp.end();
}

static bool	insert_test(void) {
	bool	test_result;
	/* -- value overload -- */
	{
		ft_map	fm;
		std_map	sm;

		fill_tree_map(fm,sm);
		test_result = equal_test_map(fm,sm);
	}
	{
		ft_map	fm;
		std_map	sm;

		int key = rand(), val = rand();
		ins_ret_f ret_f = fm.insert(ft::make_pair(key,val));
		ins_ret_s ret_s = sm.insert(std::make_pair(key,val));
		test_result = (test_result) && (ret_f.second == ret_s.second);

		ret_f = fm.insert(ft::make_pair(key,val));
		ret_s = sm.insert(std::make_pair(key,val));
		test_result = (test_result) && (ret_f.second == ret_s.second);
	}
	/* -- hint overload -- */
	{
		/* -- begin() -- */
		ft_map	fm;
		std_map	sm;

		for(int i = 0; i < 1e6; i++){
			int k = rand(), v = rand();
			ft_iterator it_f = fm.insert(fm.begin(),ft::make_pair(k,v));
			std_iterator std_f = sm.insert(sm.begin(),std::make_pair(k,v));
			test_result = (test_result) && ((*it_f).first == (*std_f).first);
		}
		test_result = (test_result) && equal_test_map(fm,sm);
	}
	{
		/* -- lower_bound() -- */
		ft_map	fm;
		std_map	sm;

		for(int i = 0; i < 1e6; i++){
			int k = rand(), v = rand();
			ft_iterator it_f = fm.insert(fm.lower_bound(k),ft::make_pair(k,v));
			std_iterator std_f = sm.insert(sm.lower_bound(k),std::make_pair(k,v));
			test_result = (test_result) && ((*it_f).first == (*std_f).first);
		}
		test_result = (test_result) && equal_test_map(fm,sm);
	}
	{
		/* -- end() -- */
		ft_map	fm;
		std_map	sm;

		for(int i = 0; i < 1e6; i++){
			int k = rand(), v = rand();
			ft_iterator it_f = fm.insert(fm.end(),ft::make_pair(k,v));
			std_iterator std_f = sm.insert(sm.end(),std::make_pair(k,v));
			test_result = (test_result) && ((*it_f).first == (*std_f).first);
		}
		test_result = (test_result) && equal_test_map(fm,sm);
	}
	/* -- range overload -- */
	{
		ft_map	fmrange, fm;
		std_map	smrange, sm;

		fill_tree_map(fmrange, smrange);
		fm.insert(fmrange.begin(), fmrange.end());
		sm.insert(smrange.begin(),smrange.end());
		test_result = (test_result) && equal_test_map(fm,sm);
	}
	return test_result;
}

static bool	erase_test(void) {
	bool	test_result;

	/* -- iterator overload -- */
	{
		ft_map	fm;
		std_map	sm;
		fill_tree_map(fm,sm);

		for(int i = 0; i < 100; i++){
			fm.erase(fm.begin());
			sm.erase(sm.begin());
		}
		test_result = equal_test_map(fm,sm);
	}
	/* -- key overload -- */
	{
		ft_map	fm;
		std_map	sm;
		fill_tree_map(fm,sm);

		for(int i = 0; i < 1e6; i++){
			int key = rand();
			fm.erase(key);
			sm.erase(key);
		}
		test_result = (test_result) && (equal_test_map(fm,sm));
	}
	/* -- range overload -- */
	{
		ft_map	fm;
		std_map	sm;
		fill_tree_map(fm,sm);

		fm.erase(fm.begin(),fm.end());
		sm.erase(sm.begin(),sm.end());
		test_result = (test_result) && (equal_test_map(fm,sm));
	}
	return test_result;
}

static bool	swap_test(void) {
	ft_map	fm;
	std_map	sm;

	ft_map	fm_2;
	std_map	sm_2;

	bool	test_result;
	fill_tree_map(fm,sm);
	swap(fm, fm_2);
	swap(sm, sm_2);
	test_result = (equal_test_map(fm,sm)) &&
				  (equal_test_map(fm_2,sm_2));
	fill_tree_map(fm_2,sm_2);
	fm.swap(fm_2);
	sm.swap(sm_2);
	test_result = (test_result) &&
				  (equal_test_map(fm,sm)) &&
				  (equal_test_map(fm_2,sm_2));
	return test_result;
}

static bool	count_test(void) {
	ft_map	fm;
	std_map	sm;

	fill_tree_map(fm,sm);
	for(int i = 0; i < MAP_SIZE; i++){
		if(fm.count(i) != sm.count(i)) return false;
	}
	return true;
}

static bool	find_test(void) {
	ft_map	fm;
	std_map	sm;

	for(int i = 0; i < 1e4; i++){
		int v = rand();
		fm[i] = v;
		sm[i] = v;
	}
	for(int i = 0; i < 1e4; i++){
		ft_iterator		f_it = fm.find(i);
		std_iterator	s_it = sm.find(i);
		if ((f_it->first != s_it->first)||(f_it->second != s_it->second)) return false;
	}
	ft_iterator		f_end = fm.find(1e4 + 1);
	std_iterator	s_end = sm.find(1e4 + 1);
	return ((f_end == fm.end()) == (s_end == sm.end()));
}

static bool	equal_range_test(void) {
	ft_map	fm;
	std_map	sm;

	for(int i = 0; i < 1e4; i++){
		int v = rand();
		fm[i] = v;
		sm[i] = v;
	}
	for(int i = 0; i < 1e2; i++){
		ret_eq_f ret_f = fm.equal_range(i);
		ret_eq_s ret_s = sm.equal_range(i);
		if ((ret_f.first->first != ret_s.first->first) ||
		    (ret_f.first->second != ret_s.first->second) ||
			(ret_f.second->first != ret_s.second->first) ||
			(ret_f.second->second != ret_s.second->second)) return false;
	}
	return true;
}

static bool	upper_bound_test(void) { // here
	ft_map	fm;
	std_map	sm;

	for(int i = 0; i < 1e4; i++){
		if (i%2) {
			int v = rand();
			fm[i] = v;
			sm[i] = v;
		}
	}
	for(int i = 0; i < 1e2; i++){
		ft_iterator		it_f = fm.upper_bound(i);
		std_iterator	it_s = sm.upper_bound(i);
		if ((it_f->first != it_s->first) ||
			(it_f->second != it_s->second)) return false;
	}
	return true;
}

static bool	lower_bound_test(void) { // here
	ft_map	fm;
	std_map	sm;

	for(int i = 0; i < 1e4; i++){
		if (i%2) {
			int v = rand();
			fm[i] = v;
			sm[i] = v;
		}
	}
	for(int i = 0; i < 1e2; i++){
		ft_iterator		it_f = fm.lower_bound(i);
		std_iterator	it_s = sm.lower_bound(i);
		if ((it_f->first != it_s->first) ||
			(it_f->second != it_s->second)) return false;
	}
	return true;
}

static bool	observers_test(void) {
	ft_map	fm;
	bool	test_result;
	/* -- key compare -- */
	{
		test_result = fm.key_comp()(2, 3) &&
					 !fm.key_comp()(3, 2) &&
					 !fm.key_comp()(3, 3);
	}
	/* -- value compare -- */
	{
		ft::pair<int,int> a(2, 3);
		ft::pair<int,int> b(3, 2);
		ft::pair<int,int> c(3, 3);
		ft::pair<int,int> d(3, 3);
		test_result = (test_result) &&
					  fm.value_comp()(a, b) &&
					 !fm.value_comp()(b, a) &&
					 !fm.value_comp()(d, c) && !fm.value_comp()(c, d);
	}
	return test_result;
}

static bool	comp_operators_test(void){
	bool	test_result;
	ft_map	fm;
	std_map	sm;

	ft_map	fm_2;
	std_map	sm_2;
	test_result = (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);

	fill_tree_map(fm_2,sm_2);
	test_result = (test_result) &&
				  (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);
	
	fill_tree_map(fm,sm);
	test_result = (test_result) &&
				  (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);

	fm.erase(fm.begin());
	sm.erase(sm.begin());
	test_result = (test_result) &&
				  (fm == fm_2) == (sm == sm_2) &&
				  (fm != fm_2) == (sm != sm_2) &&
				  (fm >  fm_2) == (sm >  sm_2) &&
				  (fm >= fm_2) == (sm >= sm_2) &&
				  (fm <  fm_2) == (sm <  sm_2) &&
				  (fm <= fm_2) == (sm <= sm_2);
	return test_result;
}


static std::string test_name_table[N_MAP_TEST] = {
	"ITERATOR TEST",	"REVERSE_ITERATOR TEST",
	"CONSTRUCTOR TEST",	"OPERATOR= TEST",
	"AT TEST",			"OPERATOR[] TEST",	
	"EMPTY TEST",		"SIZE TEST",		
	"MAX_SIZE TEST",	"CLEAR TEST",		
	"INSERT TEST", 		"ERASE TEST",		
	"SWAP TEST",		"COUNT TEST",		
	"FIND TEST",		"UPPER_BOUND TEST",	
	"LOWER_BOUND TEST",	"EQUAL_RANGE TEST",		
	"OBSERVERS TEST",	"COMP. OPERATORS TESTS"
};

static bool (*func_table[N_MAP_TEST])(void) = {
	iterator_test,						reverse_iterator_test,
	constructor_test,					operatorequal_test_map,
	at_test,							operatoraccess_test,	
	empty_test,							size_test,
	max_size_test,						clear_test,
	insert_test,						erase_test,
	swap_test,							count_test,
	find_test,							upper_bound_test,
	lower_bound_test,					equal_range_test,
	observers_test,						comp_operators_test
};

static bool stress_test(void){

	long	time_std = get_time();
	std_map sm;
	for(int i = 0; i < 1e7; i++)
		sm.insert(std::pair<int,int>(rand(),rand()));
	sm.erase(sm.begin(),sm.end());

	time_std = get_time() - time_std;
	long	time_ft = get_time();
	ft_map fm;
	for(int i = 0; i < 1e7; i++)
		fm.insert(ft::pair<int,int>(rand(),rand()));
	fm.erase(fm.begin(),fm.end());

	time_ft = get_time() - time_ft;
	return (time_ft < time_std * 10) ? true : false;
}

void map_tests( void ) {
	std::cout << "\n[ map test: compare behaviour with std::map ]\n\n";
	for (int i = 0; i < N_MAP_TEST; i++) {
		std::cout << std::setw(30) << test_name_table[i] << ": "; std::cout.flush();
		std::cout << ((func_table[i]( )) ? OK : KO) << "\n";
	}
	std::cout << "\n< performance test... : "; std::cout.flush();
	std::cout << ((stress_test()) ? OK : KO) << " >\n";
}

