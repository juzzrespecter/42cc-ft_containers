#include "tester.hpp"

typedef ft::vector< int >               vector;
typedef vector::iterator                iterator;
typedef vector::const_iterator          const_iterator;
typedef vector::reverse_iterator        reverse_iterator;
typedef vector::const_reverse_iterator  const_reverse_iterator;
typedef vector::value_type              value_type;

static std::string buff;

void init_vector( vector& v ) {

    for ( int i = 0; i < 15; i++ ) {

        v.push_back( ( rand( ) % 100 ) - 50 );
    }
    std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
}

void vector_constructor_tests( void ) {

    vector  v;
    std::cout << "DEF    : "; iterator_loop( v.begin( ), v.end( ) );
    vector  v_2( 10 );
    std::cout << "FILL 1 : "; iterator_loop( v_2.begin( ), v_2.end( ) );
    vector  v_3( 10, 5 );
    std::cout << "FILL 2 : "; iterator_loop( v_3.begin( ), v_3.end( ) );
    vector  v_4( v_3 );
    std::cout << "CPY    : "; iterator_loop( v_4.begin( ), v_4.end( ) );
    vector  v_5( v_4.begin( ), v_4.end( ) );
    std::cout << "RANGE  : "; iterator_loop( v_5.begin( ), v_5.end( ) );    
    vector  v_6 = v_5;
    std::cout << "ASSIGN : "; iterator_loop( v_6.begin( ), v_6.end( ) );
}

void vector_element_access_tests( void ) {

    vector  v;
    init_vector( v );

    header( "AT" );
    for( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert index: ";
        getline( std::cin, buff );
        int id = std::atoi( buff.c_str( ) );
        try {

            value_type& ret = v.at( id );
            std::cout << "Element at index '" << id << "' :" << ret << "\n";
        } catch( std::out_of_range& e ) { std::cout << RED << "CATCHED EXECPTION: " << e.what( ) << "\n" << END; }
    }

    header( "OPERATOR[ ]" );
    for( int i = 0; i < N_TEST_USER; i++ ) {

        std::cout << ">> insert index: ";
        getline( std::cin, buff );
        int id = std::atoi( buff.c_str( ) );
        value_type& ret = v[ id ];
        std::cout << "Element at index '" << id << "' :" << ret << "\n";
    }

    header( "FRONT" );
    std::cout << v.front( ) << "\n";

    header( "BACK" );
    std::cout << v.back( ) << "\n";
}

void vector_iterator_tests( void ) {

    header( "ITERATOR" );
    vector  v;
    init_vector( v );

    iterator    it = v.begin( );
    iterator    it_2( it );
    std::cout << " [ ITERATOR CONSTRUCTOR ]               ";
    if ( *it == *it_2 ) std::cout << GREEN << " [ OK ]\n" << END;
    else                std::cout << RED << " [ KO ]\n" << END;

    const_iterator  it_c = v.begin( );
    const_iterator  it_c_2( it_c );
    //iterator    it_3( it_c );
    std::cout << " [ CONST_ITERATOR CONSTRUCTOR ]         ";
    if ( *it_c == *it_c_2 ) std::cout << GREEN << " [ OK ]\n" << END;
    else                    std::cout << RED << " [ KO ]\n" << END;

    reverse_iterator    it_r = v.rbegin( );
    reverse_iterator    it_r_2( it_r );
    std::cout << " [ REVERSE_ITERATOR CONSTRUCTOR ]       ";
    if ( *it_r == *it_r_2 ) std::cout << GREEN << " [ OK ]\n" << END;
    else                    std::cout << RED << " [ KO ]\n" << END;

    const_reverse_iterator  it_r_c = v.rbegin( );
    const_reverse_iterator  it_r_c_2( it_r_c );
    std::cout << " [ CONST_REVERSE_ITERATOR CONSTRUCTOR ] ";
    if ( *it_r_c == *it_r_c_2 ) std::cout << GREEN << " [ OK ]\n" << END;
    else                        std::cout << RED << " [ KO ]\n" << END;

    const_iterator          it_c_end = v.end( );
    reverse_iterator        it_r_end = v.rend( );
    const_reverse_iterator  it_r_c_end = v.rend( );
    std::cout << "\niterator loop:              "; iterator_loop( it, v.end( ) );
    std::cout << "const_iterator loop:         "; iterator_loop( it_c, it_c_end );
    std::cout << "reverse_iterator loop:       "; iterator_loop( it_r, it_r_end );
    std::cout << "const_reverse_iterator loop: "; iterator_loop( it_r_c, it_r_c_end );

}

void vector_capacity_tests( void ) {

    vector  v;

    header( "EMPTY" );
    std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
    std::cout << "empty? " << v.empty( ) << "\n";
    init_vector( v );
    std::cout << "empty? " << v.empty( ) << "\n";

    header( "SIZE" );
    std::cout << "size: " << v.size( ) << "\n";
    v.clear( );
    std::cout << "size: " << v.size( ) << "\n";

    header( "MAX_SIZE" );
    std::cout << v.max_size( ) << "\n";

    header( "CAPACITY" );
    std::cout << "capacity: " << v.capacity( ) << "\n";

    header( "RESERVE" );
    v.reserve( 1 );
    std::cout << "capacity: " << v.capacity( ) << "\n";
    v.reserve( 10 );
    std::cout << "capacity: " << v.capacity( ) << "\n";
    v.reserve( 100 );
    std::cout << "capacity: " << v.capacity( ) << "\n";
}

void vector_modifiers_tests( void ) {

    vector  v;

    header( "CLEAR" );
    init_vector( v );
    v.clear( );
    std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );

    header( "INSERT" );
    {
        std::cout << " [ iterator overload ]\n";
        for ( int i = 0; i < N_TEST_USER; i++ ) {
        
            std::cout << ">> insert pos: ";
            getline( std::cin, buff );
            int         id = std::atoi( buff.c_str( ) ) % v.size( );
            std::cout << ">> insert new element: ";
            getline( std::cin, buff );
            int         elem = std::atoi( buff.c_str( ) );
            iterator    it = v.insert( ( v.begin( ) + id ), elem );
            std::cout << "Inserted element " << *it << "\n";    
            std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
        }
    }

    {
        std::cout << "\n [ fill overload ]\n";
        std::cout << ">> insert pos: ";
        getline( std::cin, buff );
        int         id = std::atoi( buff.c_str( ) ) % v.size( );
        std::cout << ">> insert size: ";
        getline( std::cin, buff );
        int         size = std::atoi( buff.c_str( ) );
        std::cout << ">> insert new element: ";
        getline( std::cin, buff );
        int elem = std::atoi( buff.c_str( ) );
        v.insert( ( v.begin( ) + id ), size, elem );
        std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
    }

    {
        std::cout << "\n [ range overload ]\n";
        vector      v_aux;
        init_vector( v_aux );
        std::cout << ">> insert pos: ";
        getline( std::cin, buff );
        int         pos = std::atoi( buff.c_str( ) ) % v.size( );
        v.insert( ( v.begin( ) + pos ), v_aux.begin( ), v_aux.end( ) );
        std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
    }

    header( "ERASE" );
    { 
        std::cout << " [ iterator overload ]\n";
        for ( int i = 0; i < N_TEST_USER; i++ ) {

            std::cout << ">> insert pos: ";
            getline( std::cin, buff );
            int         pos = std::atoi( buff.c_str( ) ) % v.size( );
            iterator    it = v.erase( ( v.begin( ) + pos ) );
            if ( it != v.end( ) ) std::cout << "Returned iterator: " << *it << "\n";
            else                  std::cout << "Returned end iterator\n";
            std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
        }
    }
    {
        std::cout << " [ range overload ]\n";
        v.erase( v.begin( ), v.end( ) );
        std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
    }

    header( "PUSH_BACK" );
    {
        for ( int i = 0; i < N_TEST_USER; i++ ) {

            std::cout << ">> insert element: ";
            getline( std::cin, buff );
            int         elem = std::atoi( buff.c_str( ) );
            v.push_back( elem );
            std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
        }
    }

    header( "POP_BACK" );
    {
        for ( int i = 0; i < N_TEST_USER; i++ ) {

            std::cout << "press to pop... ";
            getline( std::cin, buff );
            v.pop_back( );
            std::cout << "VEC : "; iterator_loop( v.begin( ), v.end( ) );
        }
    }

    header( "RESIZE" );
    {
        for ( int i = 0; i < N_TEST_USER; i++ ) {

            std::cout << ">> insert size: ";
            getline( std::cin, buff );
            int         size = std::atoi( buff.c_str( ) );
            v.resize( size );
            std::cout << "Size: " << v.size( ) << ", VEC : "; iterator_loop( v.begin( ), v.end( ) );
        }
    }

    header( "SWAP" );
    {
        std::cout << "1. "; iterator_loop( v.begin( ), v.end( ) );
        vector  v_aux;
        std::cout << "2. "; init_vector( v_aux );
        v.swap( v_aux );
        std::cout << "1. "; iterator_loop( v.begin( ), v.end( ) );
        std::cout << "2. "; iterator_loop( v_aux.begin( ), v_aux.end( ) );
    }
}

void vector_compare_overloads_tests( void ) {

    header( "OP. OVERLOAD" );
    vector v;
    std::cout << "1. "; init_vector( v );
    vector v_2;
    std::cout << "2. "; init_vector( v_2 );
    std::cout << " \nv_1 == v_2 : " << ( v == v_2 ) << "\n"
              << " v_1 != v_2 : " << ( v != v_2 ) << "\n"
              << " v_1 <  v_2 : " << ( v < v_2 )  << "\n"
              << " v_1 <= v_2 : " << ( v <= v_2 ) << "\n"
              << " v_1 >  v_2 : " << ( v > v_2 )  << "\n"
              << " v_1 >= v_2 : " << ( v >= v_2 ) << "\n";

    header( "SWAP OVERLOAD ]" );
    swap( v, v_2 );
    std::cout << "1. "; iterator_loop( v.begin( ), v.end( ) );
    std::cout << "2. "; iterator_loop( v_2.begin( ), v_2.end( ) );
}

static void ( *vector_table[ N_V_TESTS ] )( void ) = {

    vector_constructor_tests,
    vector_element_access_tests,
    vector_iterator_tests,
    vector_capacity_tests,
    vector_modifiers_tests,
    vector_compare_overloads_tests
};

void vector_test( void ) {

    char*       buff_end_ptr;

    while( 1 ) {

        system( "clear" );
        std::cout << BLUE 
                  << " [ *** LIST OF VECTOR TESTS *** ]\n"
                  << " | 0           | constr.        |\n"
                  << " | 1           | elem. access   |\n"
                  << " | 2           | iterators      |\n"
                  << " | 3           | capacity       |\n"
                  << " | 4           | modifiers      |\n"
                  << " | 5           | comp. overl.   |\n"
                  << " | _____________________________|\n"
                  << " | 6           | exit           |\n"
                  << " [ **************************** ]\n"
                  << END;
        while( 1 ) {
    
            std::cout << "\n >> ";
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &buff_end_ptr, 0 );
            if ( !*buff_end_ptr && id >= 0 && id < N_V_TESTS ) {

                system( "clear" );
                vector_table[ id ]( );
                std::cout << BLUE << "\n< press ENTER to continue... >\n" << END;
                std::getline( std::cin, buff );
                break ;
            }
            if ( !*buff_end_ptr && id == N_V_TESTS ) return ;
        }
    }

}