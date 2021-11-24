#include <map>
#include <set>
#include <iostream>

template< class Key, class Val >
class wrap_iterator : public std::map< Key, Val >::iterator {

    wrap_iterator& operator++( void ) {

        std::cout << "inc operator called...\n";

    }
};

template< class It >
void prunt( It begin, It end ) {

    std::cout << "[ ";
    for ( ; begin != end; begin++ ) {

        std::cout << *begin << " ";
    }
    std::cout << "]\n";
}

int main( void ) {

    std::set< int > a;
    std::set< int > b;

    for ( int i = 0; i < 15; i++ ) {

       // a.insert( i );
        b.insert( i );        
    }
    prunt( a.begin( ), a.end( ) );
    prunt( b.begin( ), b.end( ) );

    std::set< int >::iterator it = a.begin( );
    //a.begin( )++; a.begin( )++;

    a.insert( a.end( ), -4 );

    prunt( a.begin( ), a.end( ) );
    prunt( b.begin( ), b.end( ) );
}