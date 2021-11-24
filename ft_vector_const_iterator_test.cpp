#include "vector.hpp"
#include <vector>
#include <map>
#include <iostream>

template< bool B, class T = void >
	struct enable_if { };

template< class T >
	struct enable_if< true, T > { typedef T type; };

template< class T, T v >
struct integral_constant {

	public:
		typedef T								value_type;
		typedef ft::integral_constant< T, v >	type;

		static const T value = v;

		operator value_type( ) const {

			return value;
		}
};

typedef	ft::integral_constant< bool, true > true_type;
typedef	ft::integral_constant< bool, false > false_type;

template< class T >
struct is_const : public ft::false_type { };

template< class T >
struct is_const< const T > : public ft::true_type { };

template< class T >
class A {

    T   val;
    public:
        A( void ) { std::cout << "DefaultConstructor\n"; }
        A( const A& other ) { std::cout << "CopyConstructor\n"; }
        
        template< class U >
        A( const A< U >& other,
           typename enable_if< !is_const< T >::value, T >::type* switch = NULL ) { std::cout << "nonConst-to-ConstCopyConstructor\n"; }

};

int main( void ) {

    A <int>a;
    A <const int> a_const;

    A <int> b( a_const );
    A <const int> b_2( a );

}