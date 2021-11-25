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

template< class S, class T >
class A {

    T   val;
    S   otherVal;
    public:
        A( void ) : val( ) { std::cout << "DefaultConstructor\n"; }
        A( const A& other ) : val( other.getVal( ) ) { std::cout << "CopyConstructor\n"; }

        const T& getVal( void ) const { return val; }
        
        template< class U >
        A( const A< S, U* >& other,
           typename enable_if< !is_const< U >::value, U >::type* value = NULL ) : val( other.getVal( ) )
           { std::cout << "nonConst-to-ConstCopyConstructor\n"; }

};

int main( void ) {

    A <char, int* >a;
    A <char, const int* > a_const;

    A <char, int* > b( a_const );
    A <char, const int* > b_2( a );

    ft::vector< int >::iterator it;
    ft::vector< int >::const_iterator const_it;

    it = const_it;
    const_it = it;

    it = it;
    const_it = const_it;

}