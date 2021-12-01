#include "map.hpp"
#include <map>
#include "tester.hpp"

typedef ft::map<int, int>			ft_map;
typedef ft_map::iterator			ft_iterator;
typedef ft_map::const_iterator		ft_const_iterator;
typedef ft_map::reverse_iterator	ft_reverse_iterator;

typedef std::map<int, int>			std_map;
typedef std_map::iterator			std_iterator;
typedef std_map::const_iterator		std_const_iterator;
typedef std_map::reverse_iterator	std_reverse_iterator;

typedef ft::pair<ft_iterator,bool>		ins_ret_f;
typedef std::pair<std_iterator,bool>	ins_ret_s;

typedef ft::pair<ft_iterator,ft_iterator>		ret_eq_f;
typedef	std::pair<std_iterator,std_iterator>	ret_eq_s;

void	fill_maps(ft_map& fm, std_map& sm) {
	for(int i = 0; i < 1e7; i++){
		int k = rand(), v = rand();
		fm.insert(ft::make_pair(k,v));
		sm.insert(std::make_pair(k,v));
	}
}

bool	iterator_test(void) {
	bool	test_result;
	/* -- iterator -- */
	{
		ft_map	mf;
		std_map	sm;
		fill_maps(fm,sm);

		ft_iterator	f_it = mf.begin();
		ft_iterator	f_it_e = mf.end();
		std_iterator	s_it = ms.begin();
		std_iterator	s_it_e = ms.end();
	}
	/* -- const_iterator -- */
	{
	}
}

bool	reverse_iterator_test(void) {

}

bool	constructor_test(void) {
	bool	test_result;
	/* -- default -- */
	{
		ft_map	fm;
		std_map	sm;
		test_result = ft::equal(fm.begin(),fm.end(),sm.begin());
	}
	/* -- range -- */
	{
		ft_map	fmrange;
		std_map	smrange;
		
		fill_maps(fmrange,smrange);

		ft_map	fm(fmrange.begin(), fmrange.end());
		std_map	sm(smrange.begin(), smrange.end());
		test_result = (test_result) && ft::equal(fm.begin(),fm.end(),sm.begin());
	}
	/* -- copy -- */
	{
		ft_map	fmcpy;
		std_map	smcpy;

		fill_maps(fmcpy,smcpy);

		ft_map	fm(fmcpy);
		std_map	sm(smcpy);
		test_result = (test_result) && ft::equal(fm.begin(),fm.end(),sm.begin());
	}
	return test_result;
}

bool	operatorequal_test(void) {
	bool	test_result;

	ft_map	fmeq;
	std_map	smeq;

	ft_map	fm = fmeq;
	test_result = ft::equal(fm.begin(),fm.end(),fmeq.begin());

	fill_maps(fmeq,smeq);
	fm = fmeq;
	test_result = (test_result) &&
		      (ft::equal(fm.begin(),fm.end(),fmeq.begin()) &&
		      (ft::equal(fm.begin(),fm.end(),smeq.begin());

	fmeq.clear();
	smeq.clear();
	fm = fmeq;
	test_result = (test_result) &&
		      (ft::equal(fm.begin(),fm.end(),fmeq.begin()) &&
		      (ft::equal(fm.begin(),fm.end(),smeq.begin());
	return test_result;
}

bool	at_test(void) {
	std_map	sm;
	ft_map	fm;
	fill_maps(fm,sm);

	// ...
}

bool	operatoraccess_test(void) {
	ft_map	fm;
	std_map	sm;
	fill_maps(fm,sm);

	long	fm_res = 0, sm_res = 0;
	for(int i = 0; i < fm.size(); i++){
		fm_res = fm[i];
		sm_res = sm[i];
	}
	return (fm_res == sm_res && fm.size() == sm.size());
}

bool	empty_test(void) {
	bool	test_result;
	ft_map	fm;
	std_map	sm;
	test_result = fm.empty() == sm.empty();

	fill_maps(fm,sm);
	test_result = (test_result) && (fm.empty() == sm.empty());

	fm.clear();
	sm.clear();
	return (test_result) && (fm.empty() == sm.empty());
}

bool	size_test(void) {
	bool		test_result;
	ft_map		fm;
	std_map		sm;
	test_result = fm.size() == sm.size();
	
	fill_maps(fm,sm);
	test_result = (test_result) && (fm.size() == sm.size());

	fm.clear();
	sm.clear();
	return (test_result) && (fm.size() == sm.size());
}

bool	max_size_test(void) {
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

bool	clear_test(void) {
	ft_map	mp;

	mp.clear();
	for(int i = 0; i < 1e7; i++) mp.insert(ft::make_pair(rand(),rand()));
	mp.clear();
	return mp.size() == 0 && mp.begin() == mp.end();
}

bool	insert_test(void) {
	bool	test_result;
	/* -- value overload -- */
	{
		ft_map	fm;
		std_map	sm;

		fill_maps(fm,sm);
		test_result = ft::equal(fm.begin(),fm.end(),sm.begin());
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
		test_result = (test_result) && ft::equal(fm.begin(),fm.end(),sm.begin());
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
		test_result = (test_result) && ft::equal(fm.begin(),fm.end(),sm.begin());
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
		test_result = (test_result) && ft::equal(fm.begin(),fm.end(),sm.begin());
	}
	/* -- range overload -- */
	{
		ft_map	fm;
		std_map	sm;
		for(int i = 0;i < 1e6;i++)sm.insert(std::make_pair(rand(),rand()));
		fm.insert(sm.begin(), sm.end());
		test_result = (test_result) && ft::equal(fm.begin(),fm.end(),sm.begin());
	}
}

bool	erase_test(void) {
	ft_map	fm;
	std_map	sm;

	/* -- iterator overload -- */
	{
		ft_map	fm;
		std_map	sm;
	}
}

bool	swap_test(void) {
}

bool	count_test(void) {
	ft_map	fm;
	std_map	sm;

	fill_maps(fm,sm);
	for(int i = 0; i < MAP_SIZE < i++){
		if(fm.count(i) != sm.count(i)) return false;
	}
	return true;
}

bool	find_test(void) {
	ft_map	fm;
	std_map	sm;
}
bool	upper_bound_test(void) {}
bool	lower_bound_test(void) {}
bool	equal_bound_test(void) {}
bool	observers_bound_test(void) {}
bool	comp_operators_test(void) {}


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
	iterator_test, 			reverse_iterator_test,
	constructor_test,		operatorequal_test,
	at_test,				operatoraccess_test,	
	empty_test,				size_test,
	max_size_test,			clear_test,
	insert_test,			erase_test,
	swap_test,				count_test,
	find_test,				upper_bound_test,
	lower_bound_test,		equal_bound_test,
	observers_test,			comp_operators_test
};

void map_tests( void ) {
	std::cout << "\n[ map test: compare behaviour with std::map ]\n\n";
	for (int i = 0; i < N_MAP_TEST; i++)
		std::cout << std::setw(30) << test_name_table[i] << ": " << ((func_table[i])() ? OK : KO) << "\n";
	std::cout << "\n< performance test... : " << ((stress_test()) ? OK : KO) << " >\n";
}

