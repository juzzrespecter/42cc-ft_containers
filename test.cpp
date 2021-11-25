#include "test.hpp"

void exit_leak( void ) {

    system( "leaks map" );
}

void indent( int lvl ) {

    if ( !lvl ) return ;
    for ( int i = 0; i + 1 < lvl; i++ ) {

        std::cout << "     " << "     ";
    }
    std::cout << "     ";
}


int main( void ) {

    std::string buff;
    char*       end_buff_ptr;

    srand( time( NULL ) );

    static void ( *container_tests[ N_C_TESTS ] )( void ) = {

        map_test,
        set_test,
        vector_test,
        stack_test
    };

    while ( 1 ) {

        system( "clear" );
        std::cout << GREEN 
                  << " [ LIST OF AVAILABLE TESTS ]\n"
                  << " | 0          | map        |\n"
                  << " | 1          | set        |\n"
                  << " | 2          | vector     |\n"
                  << " | 3          | stack      |\n"
                  << " | _______________________ |\n"
                  << " | 4          | exit       |\n"
                  << " [ *********************** ]\n"
                  << END;
        while ( 1 ) {

            std::cout << " >> ";
            getline( std::cin, buff );

            int id = strtol( buff.c_str( ), &end_buff_ptr, 0 );
            if ( !*end_buff_ptr && id >= 0 && id < N_C_TESTS ) {

                container_tests[ id ]( );
                break ;
            }
            if ( !*end_buff_ptr && id == 4 ) {
                
                std::cout << GREEN << "bye!\n" << END;
                return EXIT_SUCCESS;
            }
        }
    }
}