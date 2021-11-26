#include "tester.hpp"

static std::string buff;

void stack_constructor_tests( void ) {

    /* placeholder */
}

void stack_element_access_tests( void ) {

    /* placeholder */
}

void stack_modifiers_tests( void ) {

    /* placeholder */
}

void stack_compare_overloads_tests( void ) {

    /* placeholder */
}

static void ( *stack_table[ N_S_TESTS ] )( void ) = {

    stack_constructor_tests,
    stack_element_access_tests,
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
                std::cout << RED << "( press ENTER to continue... )\n" << END;
                std::getline( std::cin, buff );
                break ;
            }
        }
    }

}
