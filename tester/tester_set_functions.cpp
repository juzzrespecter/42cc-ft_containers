#include "tester.hpp"
#define N_SET_TESTS 7

static std::string buff;

typedef ft::set< int >              set;
typedef set::iterator               iterator;
typedef set::const_iterator         const_iterator;
typedef set::reverse_iterator       reverse_iterator;
typedef set::const_reverse_iterator const_reverse_iterator;

typedef set::key_type               key_type;
typedef set::value_type             value_type;

void    init_set( set& s ) {

    for ( int i = 0; i < 15; i++ ) {

        s.insert( rand( ) % 30 );
    }
    std::cout << "SET : "; 
    iterator_loop( s.begin( ), s.end( ) );
}

void set_constructor_tests( void ) {

    /* placeholder */
    set s;
    init_set( s );

    set s_2( s );
    set s_3( s.begin( ), s.end( ) );
    set s_4 = s;
}

void set_iterator_tests( void ) {

    set s;
    init_set( s );

    iterator    it = s.begin( );
    iterator    it_2( it );

    const_iterator  it_c = s.begin( );
    const_iterator  it_c_2( it );
    //iterator    it_3( it_c );

    reverse_iterator it_r = s.rbegin( );
    reverse_iterator it_r_2( it_r );

    const_reverse_iterator  it_r_c = s.rbegin( );
    const_reverse_iterator  it_r_c_2( it_r_c );
    //reverse_iterator    it_r_3( it_r_c );
}

void set_capacity_tests( void ) {

    set s;

    header( "EMPTY" );
    std::cout << s.empty( ) << "\n";
    init_set( s );
    std::cout << s.empty( ) << "\n";

    header( "SIZE" );
    std::cout << s.size( ) << "\n";
    s.erase( s.begin( ) );
    std::cout << s.size( ) << "\n";
    s.clear( );
    std::cout << s.size( ) << "\n";
    
    header( "MAX_SIZE" );
    std::cout << s.max_size( ) << "\n";
}

void set_modifiers_tests( void ) {

    set s;

    init_set( s );
    s.clear( );
    std::cout << "SET : "; iterator_loop( s.begin( ), s.end( ) );

    for( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert key: ";
        getline( std::cin, buff );
        ft::pair< iterator, bool > ins_ret = s.insert( buff[0] );
        std::cout << "Inserted element: " << value( *ins_ret.first ) << ", " << ins_ret.second << "\n";
        std::cout << "SET : "; iterator_loop( s.begin( ), s.end( ) );
    }

    for( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert key: ";
        getline( std::cin, buff );
        iterator    it = s.insert( ( i % 2 ) ? s.begin( ) : s.lower_bound( buff[0] ), buff[0] );
        std::cout << "Inserted element: " << value( *it ) << "\n";
        std::cout << "SET : "; iterator_loop( s.begin( ), s.end( ) );
    }

    set s_aux;
    init_set( s_aux );
    s.insert( s_aux.begin( ), s_aux.end( ) );
    std::cout << "SET : "; iterator_loop( s.begin( ), s.end( ) );

    for( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert key: ";
        getline( std::cin, buff );
        int erase_ret = s.erase( buff[0] );
        if ( !erase_ret ) std::cout << "No node with key '" << buff[0] << "' in set\n";
        else              std::cout << "Erased node with key '" << buff[0] << "'\n";
        std::cout << "SET : "; iterator_loop( s.begin( ), s.end( ) );        
    }

    s.erase( s.begin( ) );
    s.erase( ++s.begin( ) );
    std::cout << "SET : "; iterator_loop( s.begin( ), s.end( ) );

    s.erase( s.begin( ), s.end( ) );

    std::cout << "1. "; init_set( s );
    set s_2;
    std::cout << "2. "; init_set( s_2 );
    s.swap( s_2 );
    std::cout << "1. "; iterator_loop( s.begin( ), s.end( ) );
    std::cout << "2. "; iterator_loop( s_2.begin( ), s_2.end( ) );
}

void set_lookup_tests( void ) {

    set s;
    init_set( s );

    for( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert key: ";
        getline( std::cin, buff );
        std::cout << "N. of nodes with key '" << buff[0] << "': " << s.count( buff[0] ) << "\n";
    }

    for( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert key: ";
        getline( std::cin, buff );
        iterator    it_find = s.find( buff[0] );
        if ( it_find == s.end( ) ) std::cout << RED << "[ NOT FOUND ]\n" << END;
        else                       std::cout << "Found " << value( *it_find ) << "\n";
    }
    s.clear( );
    iterator it_find_2 = s.find( ';' );
    if ( it_find_2 == s.end( ) ) std::cout << "[ OK ]\n";

    init_set( s );
    for ( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert key: ";
        getline( std::cin, buff );
        ft::pair< iterator, iterator > ret = s.equal_range( buff[0] );
        if ( ret.first != s.end( ) ) std::cout << "Lower bound: " << value( *ret.first ) << "\n";
        else                         std::cout << "No lower bound.\n";
        if ( ret.second != s.end( ) ) std::cout << "Upper bound: " << value( *ret.second ) << "\n";
        else                          std::cout << "No upper bound.\n";
    }
}

void set_observers_tests( void ) {

    /* placeholder */
}
void set_compare_overloads_tests( void ) {

    /* placeholder */
}

void ( *set_table[ N_SET_TESTS ] )( void ) = {

    set_constructor_tests,
    set_iterator_tests,
    set_capacity_tests,
    set_modifiers_tests,
    set_lookup_tests,
    set_observers_tests,
    set_compare_overloads_tests
};


void set_test( void ) {

    char*   end_buff_ptr;
    std::cout << std::boolalpha;

    while ( 1 ) {

        system( "clear" );
        std::cout << BLUE 
                  << " [ *** LIST OF SET TESTS *** ]\n"
                  << " | 0          | constr.      |\n"
                  << " | 1          | iterators    |\n"
                  << " | 2          | capacity     |\n"
                  << " | 3          | modifiers    |\n"
                  << " | 4          | lookup       |\n"
                  << " | 5          | observers    |\n"
                  << " | 6          | comp. overl. |\n"
                  << " | __________________________|\n"
                  << " | 7          | exit         |\n"
                  << " [ ************************* ]\n"
                  << END;
        while ( 1 ) {

            std::cout << " >> ";
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &end_buff_ptr, 0 );            
            if ( !*end_buff_ptr && id >= 0 && id < N_SET_TESTS ) {

                system( "clear" );
                set_table[ id ]( );
                std::cout << RED << "\n< press ENTER to continue... >\n" << END;
                std::getline( std::cin, buff );
                break ;
            }
            if ( id == N_SET_TESTS ) return ;
        }
                  
    }
}
