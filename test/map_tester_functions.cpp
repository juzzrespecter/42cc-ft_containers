#include "test.hpp"
#define N_M_TESTS 8
#define N_LOOP 10

static std::string buff;

typedef ft::map< char, int >        map;
typedef map::iterator               iterator;
typedef map::const_iterator         const_iterator;
typedef map::reverse_iterator       reverse_iterator;
typedef map::const_reverse_iterator const_reverse_iterator;

typedef map::key_type               key_type;
typedef map::mapped_type            mapped_type;
typedef map::value_type             value_type;

void init_map( map& m ) {

    for ( int i = 0; i < N_LOOP; i++ ) {

        key_type      key = 'a' + rand( ) % ( 'z' - 'a' );
        mapped_type   val = rand( ) % 100;

        m.insert( ft::make_pair( key, val ) );
    }
    std::cout << "MAP : ";
    iterator_loop( m.begin( ), m.end( ) );
}

void map_constructor_tests( void ) {

    std::cout << BLUE << "\n[ DEFAULT CONSTRUCTOR TEST ]\n" << END;
    map map_def;
    std::cout << "DEF : ";
    iterator_loop( map_def.begin( ), map_def.end( ) );

    std::cout << BLUE << "\n[ RANGE CONSTRUCTOR TEST ]\n" << END;
    init_map( map_def );
    map map_range( map_def.begin( ), map_def.end( ) );
    std::cout << "RAN : ";
    iterator_loop( map_range.begin( ), map_range.end( ) );

    std::cout << BLUE << "\n[ COPY CONSTRUCTOR ]\n" << END;
    map map_copy( map_range );
    std::cout << "CPY : ";
    iterator_loop( map_copy.begin( ), map_copy.end( ) );

    std::cout << BLUE << "\n[ ASSIGNMENT COPY TEST ] \n" << END;
    map new_map;
    init_map( new_map );
    map_range = new_map;
    std::cout << " EQ : ";
    iterator_loop( map_range.begin( ), map_range.end( ) );
}

void map_element_access_tests( void ) {

    map map;

    std::cout << BLUE << "\n[ AT TEST ]\n" << END;

    init_map( map );
    std::cout << "( try accesses... )\n";
    for ( int i = 0; i < 3; i++ ) {

        getline( std::cin, buff );
        try {

            int ret = map.at( buff[0] );
            std::cout << BLUE << "\tfound element " << ret << " for key " << buff[0] << "\n" << END;
        } catch ( std::out_of_range& e ) {

            std::cout << RED << "\t [ CATCHED EXCEPTION ] " << e.what( ) << "\n" << END;
        }
    }

    std::cout << BLUE << "\n[ ACCESS[ ] TEST ]\n" << END;
    std::cout << "( try accesses... )\n";
    for ( int i = 0; i < 3; i++ ) {

        getline( std::cin, buff );
        int ret = map[ buff[0] ];
        std::cout << BLUE << "\tfound element " << ret << " for key " << buff[0] << "\n" << END;
    }
    std::cout << "( \"invalid\" accesses insert nodes to map... )\n"; iterator_loop( map.begin( ), map.end( ) );
}

void map_iterator_tests( void ) { 

    std::cout << BLUE << "\n[ ITERATOR TEST ]\n" << END;

    map m;
    init_map( m );

    iterator it = m.begin( );
    iterator it_2( it );
    std::cout << "\n ITERATOR :               ";
    if ( it == it_2 ) std::cout << GREEN << "[ OK ]\n" << END;
    else              std::cout << RED << "[ KO ]\n" << END;

    const_iterator it_const = m.begin( );
    const_iterator it_const_2( it_const );
    const_iterator it_const_3( it );
    //  iterator it_3( it_const );
    std::cout << " CONST_ITERATOR :         ";
    if ( it_const == it_const_2 && it_const == it_const_3 ) 
                      std::cout << GREEN << "[ OK ]\n" << END;
    else              std::cout << RED << "[ KO ]\n" << END;

    reverse_iterator it_rev = m.rbegin( );
    reverse_iterator it_rev_2( it_rev );
    std::cout << " REVERSE_ITERATOR :       ";
    if ( it_rev == it_rev_2 ) 
                      std::cout << GREEN << "[ OK ]\n" << END;
    else              std::cout << RED << "[ KO ]\n" << END;

    const_reverse_iterator it_rev_const = m.rbegin( );
    const_reverse_iterator it_rev_const_2( it_rev_const );
    std::cout << " CONST_REVERSE_ITERATOR : ";
    if ( it_rev_const == it_rev_const_2 ) 
                      std::cout << GREEN << "[ OK ]\n" << END;
    else              std::cout << RED << "[ KO ]\n" << END;    

    std::cout << "\n [ ITERATOR LOOP ]\n";
    iterator_loop( m.begin( ), m.end( ) );
    std::cout << " [ CONST_ITERATOR LOOP ]\n";
    const_iterator c_it = m.begin( );
    const_iterator c_it_end = m.end( );
    iterator_loop( c_it, c_it_end );
    std::cout << " [ REVERSE_ITERATOR LOOP ]\n";
    iterator_loop( m.rbegin( ), m.rend( ) );
    std::cout << " [ CONST_REVERSE_ITERATOR LOOP ]\n";
    const_reverse_iterator it_c_r = m.rbegin( );
    const_reverse_iterator it_c_r_end = m.rend( );    
    iterator_loop( it_c_r, it_c_r_end );
}

void map_capacity_tests( void ) {
    
    std::cout << std::boolalpha;

    std::cout << BLUE << "\n[ EMPTY TEST ]\n" << END;
    map m;
    std::cout << "MAP : "; iterator_loop( m.begin( ), m.end( ) );
    std::cout << "* empty( ) : " << m.empty( ) << "\n";
    std::cout << "MAP : "; iterator_loop( m.begin( ), m.end( ) );
    m.insert( ft::make_pair( 'a', 420 ) );
    std::cout << "* empty( ) : " << m.empty( ) << "\n";

    std::cout << BLUE << "\n[ SIZE TEST ]\n" << END;
    std::cout << "MAP : "; iterator_loop( m.begin( ), m.end( ) );
    std::cout << "* size( ) : " << m.size( ) << "\n";
    init_map( m );
    std::cout << "* size( ) : " << m.size( ) << "\n";

    std::cout << BLUE << "\n[ MAX_SIZE TEST ]\n" << END;
    std::cout << "* max_size( ) : " << m.max_size( ) << "\n";
}


void map_modifiers_tests( void ) {

    map m;

    std::cout << BLUE << "\n[ CLEAR TEST ]\n\n" << END;

    init_map( m );
    m.clear( );
    std::cout << "* clear( ) : " << m.size( ) << "\n";
    std::cout << "MAP : "; iterator_loop( m.begin( ), m.end( ) );

    std::cout << BLUE << "\n[ INSERT TEST ]\n" << END;
    std::cout << "\n[ insert value_type = ft::pair( a, 999 ) ]\n";
    m.insert( ft::make_pair< char, int >( 'a', 999 ) );
    std::cout << "MAP : "; iterator_loop( m.begin( ), m.end( ) );

    std::cout << "\n[ insert range of iterators ]\n";
    map map_aux; init_map( map_aux );
    m.insert( map_aux.begin( ), map_aux.end( ) );
    std::cout << "OLD : "; iterator_loop( m.begin( ), m.end( ) );

    std::cout << "\n[ insert w/ hint & value_type = ft::pair( b, 888 ) ]\n";
    ft::pair <char, int > value_2( 'b', 888 );
    m.insert( m.lower_bound( 'b' ), ft::make_pair< char, int >( 'b', 888 ) );
    std::cout << "MAP : "; iterator_loop( m.begin( ), m.end( ) );

    std::cout << BLUE << "\n[ ERASE TEST ]\n" << END;
    std::cout << "\n[ erase iterator m.begin( )++ ]\n" ;
    m.erase( ++m.begin( ) );
    std::cout << "MAP: "; iterator_loop( m.begin( ), m.end( ) );

    std::cout << "\n[ erase by key ]\n" << std::boolalpha << END;
    for ( int i = 0; i < 3; i++ ) {

        std::cout << RED << "( insert key... )\n" << END;
        getline( std::cin, buff );
        int ret = m.erase( buff[0] );
        std::cout << "Element with key '" << buff[0] << "' erased: " << ( ret ? true : false ) << "\n";
        std::cout << "MAP: "; iterator_loop( m.begin( ), m.end( ) );
    }

    std::cout << "\n[ erase by range of iterators ]\n" << END;
    m.erase( m.begin( ), m.end( ) );
    std::cout << "MAP: "; iterator_loop( m.begin( ), m.end( ) );

    std::cout << BLUE << "\n[ SWAP TEST ]\n" << END;
    map m_swap; init_map( m_swap );
    std::cout << "OLD: "; iterator_loop( m.begin( ), m.end( ) );

    m.swap( m_swap );
    std::cout << "MAP: "; iterator_loop( m_swap.begin( ), m_swap.end( ) );
    std::cout << "OLD: "; iterator_loop( m.begin( ), m.end( ) );        
}

void map_lookup_tests( void ) { 
    
    std::cout << BLUE << "\n[ COUNT TEST ]\n" << END;
    map m;
    init_map( m );
    for( int i = 0; i < 3; i++ ) {

        std::cout << RED << "insert key... : " << END;
        getline( std::cin, buff );
        std::cout << "Number of nodes with key '" << buff[0] 
                  << "' : " << m.count( buff[0] ) << "\n";
    }

    std::cout << BLUE << "\n[ FIND TEST ]\n" << END;
    for( int i = 0; i < 3; i++ ) {

        std::cout << RED << "insert key... : " << END;
        getline( std::cin, buff );
        iterator    find_ret = m.find( buff[0] );
        if ( find_ret == m.end( ) ) std::cout << "node with key " << buff[0] << " not found...\n";
        else std::cout << "node with key " << buff[0] << " found: " << value( *find_ret ) << "\n";

    }

    std::cout << BLUE << "\n[ EQUAL_RANGE TEST ]\n" << END;
    std::cout << RED << "insert key... : " << END;   
    getline( std::cin, buff );
    ft::pair< iterator, iterator > eq_ret = m.equal_range( buff[0] );
    if ( eq_ret.first != m.end( ) )
        std::cout << "Lower bound: " << value( *( eq_ret.first ) );
    if ( eq_ret.second != m.end( ) )        
        std::cout << ", upper bound : " << value( *( eq_ret.second ) ) << '\n';

    std::cout << BLUE << "\n[ LOWER_BOUND TEST ]\n" << END;
    std::cout << RED << "insert key... : " << END;
    getline( std::cin, buff );
    iterator lb_it = m.lower_bound( buff[0] );
    if ( lb_it != m.end( ) )
        std::cout << "Lower bound: " << value( *lb_it ) << "\n";
    else std::cout << RED << " no node with same key or greater than '" << buff[0] << "'\n" << END;

    std::cout << BLUE << "\n[ UPPER_BOUND TEST ]\n" << END;
    std::cout << RED << "insert key... : " << END;
    getline( std::cin, buff );
    iterator ub_it = m.upper_bound( buff[0] );
    if ( ub_it != m.end( ) )
        std::cout << "Upper bound: " << value( *ub_it ) << std::cout << "\n";
    else std::cout << RED << " no node with greater key than '" << buff[0] << "'\n" << END;
}
void map_observers_tests( void ) {

    map m;
    std::cout << std::boolalpha;

    std::cout << BLUE << "\n[ KEY_COMP TEST ]\n" << END;
    map::key_compare key_comp = m.key_comp( );
    map::key_type    k1 = 'c';
    map::key_type    k2 = 'f';
    std::cout << "keys < " << k1 << ", " << k2 
              << " >, key_comp( k1, k2 ) = " << key_comp( k1, k2 ) << '\n';

    std::cout << BLUE << "\n[ VALUE_COMP TEST ]\n" << END;
    map::value_compare value_comp = m.value_comp( );
    map::value_type v1( 'a', 123 );
    map::value_type v2( 'b', 123 );
    std::cout << "values " << value( v1 ) << " and " << value( v2 ) 
              << ", value_comp( v1, v2 ) = " << value_comp( v1, v2 ) << "\n";
}

void map_compare_overloads_tests( void ) { /* placeholder */ 

    std::cout << std::boolalpha;

    map m;
    std::cout << "1. "; init_map( m );

    map m_2;
    std::cout << "2. "; init_map( m_2 );

    std::cout << " m_1 == m_2 : " << ( m == m_2 ) << "\n"
              << " m_1 != m_2 : " << ( m != m_2 ) << "\n"
              << " m_1 <  m_2 : " << ( m < m_2 )  << "\n"
              << " m_1 <= m_2 : " << ( m <= m_2 ) << "\n"
              << " m_1 >  m_2 : " << ( m > m_2 )  << "\n"
              << " m_1 >= m_2 : " << ( m >= m_2 ) << "\n";

    std::cout << BLUE << "\n [ SWAP OVERLOAD ]\n" << END;
    swap( m, m_2 );
    std::cout << "1. "; iterator_loop( m.begin( ), m.end( ) );
    std::cout << "2. "; iterator_loop( m_2.begin( ), m_2.end( ) );
}

void ( *map_table[ N_M_TESTS ] )( void ) = {

    map_constructor_tests,
    map_element_access_tests,
    map_iterator_tests,
    map_capacity_tests,
    map_modifiers_tests,
    map_lookup_tests,
    map_observers_tests,
    map_compare_overloads_tests
};

void map_test( void ) {

    char*       buff_end_ptr;

    while ( 1 ) {

        system( "clear" );
        std::cout << BLUE 
                  << " [ *** LIST OF MAP TESTS *** ]\n"
                  << " | 0          | constr.      |\n"
                  << " | 1          | elem. access |\n"
                  << " | 2          | iterators    |\n"
                  << " | 3          | capacity     |\n"
                  << " | 4          | modifiers    |\n"
                  << " | 5          | lookup       |\n"
                  << " | 6          | observers    |\n"
                  << " | 7          | comp. overl. |\n"
                  << " | __________________________|\n"
                  << " | 8          | exit         |\n"
                  << " [ ************************* ]\n"
                  << END;
        while ( 1 ) {

            std::cout << "\n( waiting for input... )\n";
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &buff_end_ptr, 0 );
            if ( !*buff_end_ptr && id >= 0 && id < N_M_TESTS ) {

                system( "clear" );
                map_table[ id ]( );
                std::cout << BLUE << "\n< press ENTER to continue... >\n" << END;
                std::getline( std::cin, buff );
                break ;
            }
            if ( !*buff_end_ptr && id == N_M_TESTS ) return ;
        }
                  
    }
}
