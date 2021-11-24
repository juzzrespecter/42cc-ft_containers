#include "test.hpp"
#define N_V_TESTS 6

void vector_constructor_tests( void ) {

    ft::vector< int > vector;

    std::cout << "( testing with vector< int > )\n";
    std::cout << BLUE << "\n[ DEFAULT CONSTRUCTOR TEST ]\n" << END;

}

void vector_element_access_tests( void ) {

    /*placeholder*/
}

void vector_iterator_tests( void ) {

    /*placeholder*/
}

void vector_capacity_tests( void ) {

    /*placeholder*/
}

void vector_modifiers_tests( void ) {

    /*placeholder*/
}

void vector_compare_overloads_tests( void ) {

    /*placeholder*/
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

    std::string buff;
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
    
            std::cout << RED << "\n( waiting for input... )\n" << END;
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &buff_end_ptr, 0 );
            if ( !*buff_end_ptr && id >= 0 && id < N_V_TESTS ) {

                system( "clear" );
                vector_table[ id ]( );
                std::cout << RED << "( press ENTER to continue... )\n" << END;
                std::getline( std::cin, buff );
            }
            if ( !*buff_end_ptr && id == N_V_TESTS ) return ;
        }
    }

}