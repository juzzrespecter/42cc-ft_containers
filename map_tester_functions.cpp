#include "test.hpp"
#define N_M_TESTS 8
#define N_LOOP 10

static std::string buff;

void fill_map( ft::map< char, int >& m ) {

    for ( int i = 0; i < N_LOOP; i++ ) {

        ft::map< char, int >::key_type      key = 'a' + rand( ) % ( 'z' - 'a' );
        ft::map< char, int >::mapped_type   val = rand( ) % 100;

        m.insert( ft::make_pair( key, val ) );
    }
}

void map_constructor_tests( void ) {

    std::cout << "( testing with map< char, int > )\n";
    std::cout << BLUE << "\n[ DEFAULT CONSTRUCTOR TEST ]\n" << END;

    ft::map< char, int > map_def;
    std::cout << "Def. = ";
    iterator_loop( map_def.begin( ), map_def.end( ) );

    std::cout << BLUE << "\n[ RANGE CONSTRUCTOR TEST ]\n" << END;

    std::cout << "( filling def. with rand values... )\n";
    fill_map( map_def );
    std::cout << " Def. = ";
    iterator_loop( map_def.begin( ), map_def.end( ) );

    ft::map< char, int > map_range( map_def.begin( ), map_def.end( ) );

    std::cout << "Range = ";
    iterator_loop( map_range.begin( ), map_range.end( ) );

    std::cout << BLUE << "\n[ COPY CONSTRUCTOR ]\n" << END;

    std::cout << "( copying with range map... )\n";

    ft::map< char, int > map_copy( map_range );

    std::cout << "Copy = ";
    iterator_loop( map_copy.begin( ), map_copy.end( ) );

    std::cout << BLUE << "\n[ ASSIGNMENT COPY TEST ] \n" << END;
    std::cout << "( new map with random values, then assign to range and print... )\n";

    ft::map< char, int > new_map;
    fill_map( new_map );
    std::cout << "New map = ";
    iterator_loop( new_map.begin( ), new_map.end( ) );
    map_range = new_map;

    std::cout << "  Range = ";
    iterator_loop( map_range.begin( ), map_range.end( ) );
}

void map_element_access_tests( void ) {

    ft::map< char, int > map;

    std::cout << BLUE << "\n[ at( ) TEST ]\n" << END;

    fill_map( map );
    std::cout << "Map = "; iterator_loop( map.begin( ), map.end( ) );
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

    std::cout << BLUE << "\n[ operator[ ] TEST ]\n" << END;
    std::cout << "( try accesses... )\n";
    for ( int i = 0; i < 3; i++ ) {

        getline( std::cin, buff );
        int ret = map[ buff[0] ];
        std::cout << BLUE << "\tfound element " << ret << " for key " << buff[0] << "\n" << END;
    }
    std::cout << "( \"invalid\" accesses insert nodes to map... )\n"; iterator_loop( map.begin( ), map.end( ) );
}

void map_iterator_tests( void ) { 

    ft::map< char, int > map;

    std::cout << BLUE << "\n[ ITERATOR TEST ]\n" << END;

    std::cout << " Using map ";
    fill_map( map ); iterator_loop( map.begin( ), map.end( ) );
    getline( std::cin, buff );
    //rev_iterator_loop( map.begin( ), map.end( ) );

    std::cout << "\n( default construction, initializated to NULL... )\n";
    ft::map< char, int >::iterator map_it;
    getline( std::cin, buff );

    std::cout << "\n( copy assignment, with begin( ) call from map... )\n";
    map_it = map.begin( );
    std::cout << "*it = " << map_it->first << "\n";
    getline( std::cin, buff );

    std::cout << "\n( copy constructor, with begin( ) call... )\n";
    ft::map< char, int >::iterator map_it_cpy( map.begin( ) );
    std::cout << "*cpy_it = " << map_it_cpy->first << "\n";
    getline( std::cin, buff );

    // const iterator
    std::cout << BLUE << "\n[ CONST ITERATOR TEST ]\n" << END;

    ft::map< char, int >::const_iterator const_it_m;
    const_it_m = map.begin( );

    ft::map< char, int >::const_iterator const_it_end( map.end( ) );
    iterator_loop( const_it_m, const_it_end );

    /*          */
    getline( std::cin, buff );
    ft::map< int, int >::iterator it_1;
    ft::map< int, int >::const_iterator c_it_1;

    ft::map< int, int >::iterator it_2( c_it_1 );
    ft::map< int, int >::const_iterator c_it_2( it_1 );

    ft::map< int, int >::iterator it_3( it_2 );

    it_1 = c_it_1;
    c_it_1 = it_1;

    getline( std::cin, buff );
    // const_it_m->second = 34;

    // reverse iterator
    ft::map< char, int >::reverse_iterator rev_it = map.rbegin( );
    ft::map< char, int >::reverse_iterator rev_it_cpy( rev_it );

    //iterator_loop( map.rbegin( ), map.rend( ) );
    //rev_iterator_loop( map.rbegin( ), map.rend( ) );

    std::cout << "derreference: " << rev_it->first << "\n";

    // const reverse iterator    
    ft::map< char, int >::const_reverse_iterator const_rev_it = map.rbegin( );
    ft::map< char, int >::const_reverse_iterator const_rev_end( map.rend( ) );

    //iterator_loop( const_rev_it, const_rev_end );
    //rev_iterator_loop( const_rev_it, const_rev_end );

}

void map_capacity_tests( void ) {
    
    std::cout << std::boolalpha;
    std::cout << BLUE << "\n[ empty( ) TEST ]\n" << END;

    std::cout << "using empty map...\n";
    ft::map< char, int > m;
    std::cout << "\t-> empty( ) : " << m.empty( ) << "\n";

    std::cout << "inserting an element...\n";
    m.insert( ft::make_pair( 'a', 420 ) );
    std::cout << "\t-> empty( ) : " << m.empty( ) << "\n";

    std::cout << BLUE << "\n[ size( ) TEST ]\n" << END;

    std::cout << "\t-> size( ) : " << m.size( ) << "\n";

    std::cout << "adding elements to map...\n";
    fill_map( m ); iterator_loop( m.begin( ), m.end( ) );
    std::cout << "\t-> size( ) : " << m.size( ) << "\n";

    std::cout << BLUE << "\n[ max_size( ) TEST ]\n" << END;

    std::cout << "\t->max_size( ) : " << m.max_size( ) << "\n";
}


void map_modifiers_tests( void ) {

    std::cout << BLUE << "\n[ clear( ) TEST ]\n" << END;

    std::cout << "using filled map with random items...\n";
    ft::map< char, int > m;
    fill_map( m ); iterator_loop( m.begin( ), m.end( ) );

    m.clear( );
    std::cout << "\t-> clear( ) : " << m.size( ) << "\n";
    iterator_loop( m.begin( ), m.end( ) );

    std::cout << BLUE << "\n[ INSERT TEST ]\n" << END;
    std::cout << "value_type overload...\n";

    ft::map< char, int >::value_type value_to_insert( 'a', 999 );
    std::cout << "inserting pair < " << value_to_insert.first << ", " << value_to_insert.second << " >\n";
    m.insert( value_to_insert );
    iterator_loop( m.begin( ), m.end( ) );

    std::cout << "range of iterators overload...\n";
    ft::map< char, int > m_2;
    fill_map( m_2 ); iterator_loop( m_2.begin( ), m_2.end( ) );
    m.insert( m_2.begin( ), m_2.end( ) );
    iterator_loop( m.begin( ), m.end( ) );

    std::cout << "with hint!\n";
    // test with lower bound, etc... also test with invalid it pa ver que pasa

}
void map_lookup_tests( void ) { /* placeholder */ }
void map_observers_tests( void ) { /* placeholder */ }
void map_compare_overloads_tests( void ) { /* placeholder */ }

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

            std::cout << RED << "\n( waiting for input... )\n" << END;
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &buff_end_ptr, 0 );
            if ( !*buff_end_ptr && id >= 0 && id < N_M_TESTS ) {

                system( "clear" );
                map_table[ id ]( );
                std::cout << RED << "( press ENTER to continue... )\n" << END;
                std::getline( std::cin, buff );
                break ;
            }
            if ( !*buff_end_ptr && id == N_M_TESTS ) return ;
        }
                  
    }
}