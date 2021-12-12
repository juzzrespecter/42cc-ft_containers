#include <list>
#include "tester.hpp"

static bool	constructor_test(void){
	bool	test_result;
	/*  -- empty containers -- */
	{
		ft::stack<int> s;
		ft::stack<int, std::list<int> > slist;
		ft::stack<int, std::vector<int> > svec;
	}
	/* -- non-empty containers -- */
	{
		ft::vector<int> fv(1e7,2425);
		std::vector<int> sv(1e7,2425);

		MutantStack<int,ft::vector<int> >	s(fv);
		MutantStack<int,std::vector<int> >	s2(sv);

		test_result = (ft::equal(fv.begin(),fv.end(),s.begin())) &&
					  (ft::equal(sv.begin(),sv.end(),s2.begin())) &&
					  (ft::equal(s.begin(),s.end(),s2.begin()));
	}
	/* -- copy constructor -- */
	{
		ft::stack<int>	scpy;
		for(int i = 0; i < 1e7; i++) scpy.push(i);

		ft::stack<int> s(scpy);
		test_result = (test_result) && (scpy==s);
	}
	return test_result;
}

static bool	operatorequal_test(void){
	ft::vector<char> v(1e6,'u');
	ft::stack<char> scpy(v);

	ft::stack<char> s = scpy;
	return (s==scpy);
}

static bool	top_test(void){
	bool	test_result;
	ft::vector<int>		fv(1e8,234);
	{
		ft::stack<int,ft::vector<int> >		fs(fv);
		std::stack<int,ft::vector<int> >	ss(fv);
		test_result = fs.top() == ss.top();
	}
	{
		ft::stack<int,std::list<int> >	fs;
		std::stack<int,std::list<int> > ss;
		test_result = (test_result) && (fs.top() == ss.top());
	}
	return test_result;
}

static bool	empty_test(void){
	bool	test_result;

	ft::stack<std::string,ft::vector<std::string> >		fs;
	std::stack<std::string,ft::vector<std::string> >	ss;
	test_result = fs.empty() == ss.empty();

	fs.push("string");
	ss.push("string");
	test_result = (test_result) && (fs.empty() == ss.empty());

	fs.pop();
	ss.pop();
	test_result = (test_result) && (fs.empty() == ss.empty());
	return test_result;
}

static bool	size_test(void){
	ft::vector<int> v(1e7,345);

	ft::stack<int>	s_empty;
	ft::stack<int>	s_size(v);
	return (s_empty.size() == 0) && (s_size.size() == v.size());
}

static bool	push_test(void){
	std::vector<int>					v;
	MutantStack<int, std::vector<int> >	ms;

	for(int i = 0; i < 1e7; i++){
		int	val = rand();
		v.push_back(val);
		ms.push(val);
	}
	return ft::equal(v.begin(),v.end(),ms.begin());
}

static bool	pop_test(void){
	std::vector<int>					v;
	MutantStack<int, std::vector<int> >	ms;

	for(int i = 0; i < 1e7; i++){
		int	val = rand();
		v.push_back(val);
		ms.push(val);
	}
	for(int i = 0; i < 1e5; i++){
		v.pop_back();
		ms.pop();
	}
	return ft::equal(ms.begin(),ms.end(),v.begin());
}

static bool	comp_operators_test(void){
	bool	test_result;
	ft::stack<int>	fs;
	std::stack<int>	ss;

	ft::stack<int>	fs_2;
	std::stack<int>	ss_2;
	test_result = (fs == fs_2) == (ss == ss_2) &&
				  (fs != fs_2) == (ss != ss_2) &&
				  (fs >  fs_2) == (ss >  ss_2) &&
				  (fs >= fs_2) == (ss >= ss_2) &&
				  (fs <  fs_2) == (ss <  ss_2) &&
				  (fs <= fs_2) == (ss <= ss_2);

	fs_2.push(23);
	ss_2.push(23);
	test_result = (test_result) &&
				  (fs == fs_2) == (ss == ss_2) &&
				  (fs != fs_2) == (ss != ss_2) &&
				  (fs >  fs_2) == (ss >  ss_2) &&
				  (fs >= fs_2) == (ss >= ss_2) &&
				  (fs <  fs_2) == (ss <  ss_2) &&
				  (fs <= fs_2) == (ss <= ss_2);
	
	fs.push(23);
	ss.push(23);
	test_result = (test_result) &&
				  (fs == fs_2) == (ss == ss_2) &&
				  (fs != fs_2) == (ss != ss_2) &&
				  (fs >  fs_2) == (ss >  ss_2) &&
				  (fs >= fs_2) == (ss >= ss_2) &&
				  (fs <  fs_2) == (ss <  ss_2) &&
				  (fs <= fs_2) == (ss <= ss_2);

	fs.pop();
	ss.pop();
	test_result = (test_result) &&
				  (fs == fs_2) == (ss == ss_2) &&
				  (fs != fs_2) == (ss != ss_2) &&
				  (fs >  fs_2) == (ss >  ss_2) &&
				  (fs >= fs_2) == (ss >= ss_2) &&
				  (fs <  fs_2) == (ss <  ss_2) &&
				  (fs <= fs_2) == (ss <= ss_2);
	return test_result;
}

static std::string test_name_table[N_STACK_TEST] = {
	"CONSTRUCTOR TEST",	"OPERATOR= TEST",
	"TOP TEST",			"EMPTY TEST",		
	"SIZE TEST",		"PUSH TEST",		
	"POP TEST",			"COMPARE OPERATORS TEST"
};

static bool	(*func_table[N_STACK_TEST])(void) = {
	constructor_test,	operatorequal_test,
	top_test,			empty_test,
	size_test,			push_test,
	pop_test,			comp_operators_test
};

void stack_tests(void){
	std::cout << "[ stack test: compare behaviour with std::stack ]\n\n";
	for (int i = 0; i < N_STACK_TEST; i++)
		std::cout << std::setw(30) << test_name_table[i] << ": " << ((func_table[i])() ? OK : KO) << "\n";
}
