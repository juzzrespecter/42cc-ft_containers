#include "tester.hpp"
#include <list>

static std::string buff;

typedef ft::vector< int >   vector;
typedef ft::stack< int >    stack;
typedef stack::value_type   value_type;

void stack_constructor_tests( void ) {

    stack   s;
    stack   s_2( s );
    stack   s_3 = s_2;

    vector  v( 10, 5 );
    stack   s_4( v );

    std::list< int > l;
    ft::stack< int, std::list< int > > s_5( l );
    /* placeholder */
}

void stack_element_access_tests( void ) {

    header( "TOP" );
    vector  v;
    v.push_back( 9 );
    std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
    stack   s( v );
    std::cout << "top: "  << s.top( ) << "\n";
}

void stack_capacity_tests( void ) {

    header( "EMPTY" );
    stack   s;
    std::cout << "empty? " << s.empty( ) << "\n";
    s.push( 3 );
    std::cout << "empty? " << s.empty( ) << "\n";

    header( "SIZE" );
    MutantStack< int > ms;
    for ( int i = 0; i < 10; i++ ) {

        ms.push( rand( ) % 100 );
    }
    iterator_loop( ms.begin( ), ms.end( ) );
    std::cout << "size: " << ms.size( ) << "\n";
    for ( int i = 0; i < 3; i++ ) {

        std::cout << "press enter to pop!";
        getline( std::cin, buff );
        ms.pop( );
    }
    iterator_loop( ms.begin( ), ms.end( ) );
    std::cout << "size: " << ms.size( ) << "\n";
}

void stack_modifiers_tests( void ) {

    header( "PUSH" );
    MutantStack< int > ms;
    iterator_loop( ms.begin( ), ms.end( ) );
    for ( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert number to push... ";
        getline( std::cin, buff );
        
        int element = std::atoi( buff.c_str( ) );
        ms.push( element );
        iterator_loop( ms.begin( ), ms.end( ) );
    }

    header( "POP" );
    for( int i = 0; i < N_TEST_USER + 1; i++ ) {

        std::cout << ">> press enter to pop ";
        getline( std::cin, buff );
        ms.pop( );
        iterator_loop( ms.begin( ), ms.end( ) );        
    }
}

void stack_compare_overloads_tests( void ) {

    MutantStack< int > s;
    std::cout << ">> enter an element to first stack: ";
    getline( std::cin, buff );
    s.push( std::atoi( buff.c_str( ) ) );
    std::cout << ">> another one... ";
    getline( std::cin, buff );
    s.push( std::atoi( buff.c_str( ) ) );

    MutantStack< int > s_2;
    std::cout << ">> enter an element to second stack: ";
    getline( std::cin, buff );
    s_2.push( std::atoi( buff.c_str( ) ) );
    std::cout << ">> and another one... ";
    getline( std::cin, buff );
    s_2.push( std::atoi( buff.c_str( ) ) );

    std::cout << " m_1 == s_2 : " << ( s == s_2 ) << "\n"
              << " m_1 != s_2 : " << ( s != s_2 ) << "\n"
              << " m_1 <  s_2 : " << ( s < s_2 )  << "\n"
              << " m_1 <= s_2 : " << ( s <= s_2 ) << "\n"
              << " m_1 >  s_2 : " << ( s > s_2 )  << "\n"
              << " m_1 >= s_2 : " << ( s >= s_2 ) << "\n";
}

static void ( *stack_table[ N_S_TESTS ] )( void ) = {

    stack_constructor_tests,
    stack_element_access_tests,
    stack_capacity_tests,
    stack_modifiers_tests,
    stack_compare_overloads_tests
};

void stack_test( void ) {

    char*   end_buff_ptr;

    while( 1 ) {

        system( "clear" );
        std::cout << BLUE 
                  << " [ *** LIST OF STACK TESTS  *** ]\n"
                  << " | 0           | constr.        |\n"
                  << " | 1           | elem. access   |\n"
                  << " | 2           | capacity       |\n"
                  << " | 3           | modifiers      |\n"
                  << " | 4           | comp. overl.   |\n"
                  << " | _____________________________|\n"
                  << " | 5           | exit           |\n"
                  << " [ **************************** ]\n"
                  << END;
        while( 1 ) {
    
            std::cout << " >> ";
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &end_buff_ptr, 0 );
            if ( !*end_buff_ptr && id >= 0 && id < N_S_TESTS ) {

                system( "clear" );
                stack_table[ id ]( );
                std::cout << BLUE << "\n< press ENTER to continue... >\n" << END;                
                std::getline( std::cin, buff );
                break ;
            }
            if ( !*end_buff_ptr && id == 5 ) return ;
        }
    }

}
