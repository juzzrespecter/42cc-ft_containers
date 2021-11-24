#include "test.hpp"
#define N_SET_TESTS 7

static std::string buff;

void set_constructor_tests( void ) {

    /* placeholder */
}

void set_iterator_tests( void ) {

    /* placeholder */
}

void set_capacity_tests( void ) {

    /* placeholder */
}

void set_modifiers_tests( void ) {

    /* placeholder */
}

void set_lookup_tests( void ) {

    /* placeholder */
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

            std::cout << RED << "\n( waiting for input... )\n" << END;
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &end_buff_ptr, 0 );            
            if ( !*end_buff_ptr && id >= 0 && id < N_SET_TESTS ) {

                system( "clear" );
                set_table[ id ]( );
                std::cout << RED << "( press ENTER to continue... )\n" << END;
                std::getline( std::cin, buff );
                break ;
            }
            if ( id == N_SET_TESTS ) return ;
        }
                  
    }
}
